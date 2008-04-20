/*-
 * Copyright (c) 2007-2008 Sam Leffler, Errno Consulting
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

/*
 * IEEE 802.11 PHY-related support.
 */

#include "opt_inet.h"

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/systm.h>

#include <sys/socket.h>

#include <net/if.h>
#include <net/if_media.h>

#include <net80211/ieee80211_var.h>
#include <net80211/ieee80211_phy.h>

#ifdef notyet
struct ieee80211_ds_plcp_hdr {
	uint8_t		i_signal;
	uint8_t		i_service;
	uint16_t	i_length;
	uint16_t	i_crc;
} __packed;

#endif	/* notyet */

/* shorthands to compact tables for readability */
#define	OFDM	IEEE80211_T_OFDM
#define	CCK	IEEE80211_T_CCK
#define	TURBO	IEEE80211_T_TURBO
#define	PBCC	(IEEE80211_T_HT+1)		/* XXX */

static struct ieee80211_rate_table ieee80211_11b_table = {
	4,  /* number of rates, XXX no PBCC */
	{ 0 },
	{
/*                               short            ctrl  */
/*                            Preamble  dot11Rate Rate */
/*   1 Mb */ {  CCK,    1000,    0x00, (0x80| 2),   0 },
/*   2 Mb */ {  CCK,    2000,    0x04, (0x80| 4),   1 },
/* 5.5 Mb */ {  CCK,    5500,    0x04, (0x80|11),   1 },
/*  11 Mb */ {  CCK,   11000,    0x04, (0x80|22),   1 },
/*  22 Mb */ { PBCC,   22000,    0x04,        44,   3 }
	},
};


static struct ieee80211_rate_table ieee80211_11g_table = {
	12,  /* number of rates */
	{ 0 },
	{
/*                               short            ctrl  */
/*                            Preamble  dot11Rate Rate */
/*   1 Mb */ {  CCK,     1000,    0x00, (0x80| 2),   0 },
/*   2 Mb */ {  CCK,     2000,    0x04, (0x80| 4),   1 },
/* 5.5 Mb */ {  CCK,     5500,    0x04, (0x80|11),   2 },
/*  11 Mb */ {  CCK,    11000,    0x04, (0x80|22),   3 },
/*   6 Mb */ {  OFDM,    6000,    0x00,        12,   4 },
/*   9 Mb */ {  OFDM,    9000,    0x00,        18,   4 },
/*  12 Mb */ {  OFDM,   12000,    0x00,        24,   6 },
/*  18 Mb */ {  OFDM,   18000,    0x00,        36,   6 },
/*  24 Mb */ {  OFDM,   24000,    0x00,        48,   8 },
/*  36 Mb */ {  OFDM,   36000,    0x00,        72,   8 },
/*  48 Mb */ {  OFDM,   48000,    0x00,        96,   8 },
/*  54 Mb */ {  OFDM,   54000,    0x00,       108,   8 }
	},
};

static struct ieee80211_rate_table ieee80211_11a_table = {
	8,  /* number of rates */
	{ 0 },
	{
/*                               short            ctrl  */
/*                            Preamble  dot11Rate Rate */
/*   6 Mb */ {  OFDM,    6000,    0x00, (0x80|12),   0 },
/*   9 Mb */ {  OFDM,    9000,    0x00,        18,   0 },
/*  12 Mb */ {  OFDM,   12000,    0x00, (0x80|24),   2 },
/*  18 Mb */ {  OFDM,   18000,    0x00,        36,   2 },
/*  24 Mb */ {  OFDM,   24000,    0x00, (0x80|48),   4 },
/*  36 Mb */ {  OFDM,   36000,    0x00,        72,   4 },
/*  48 Mb */ {  OFDM,   48000,    0x00,        96,   4 },
/*  54 Mb */ {  OFDM,   54000,    0x00,       108,   4 }
	},
};

static struct ieee80211_rate_table ieee80211_half_table = {
	8,  /* number of rates */
	{ 0 },
	{
/*                               short            ctrl  */
/*                            Preamble  dot11Rate Rate */
/*   6 Mb */ {  OFDM,   3000,    0x00, (0x80| 6),  0 },
/*   9 Mb */ {  OFDM,   4500,    0x00,         9,  0 },
/*  12 Mb */ {  OFDM,   6000,    0x00, (0x80|12),  2 },
/*  18 Mb */ {  OFDM,   9000,    0x00,        18,  2 },
/*  24 Mb */ {  OFDM,  12000,    0x00, (0x80|24),  4 },
/*  36 Mb */ {  OFDM,  18000,    0x00,        36,  4 },
/*  48 Mb */ {  OFDM,  24000,    0x00,        48,  4 },
/*  54 Mb */ {  OFDM,  27000,    0x00,        54,  4 }
	},
};

static struct ieee80211_rate_table ieee80211_quarter_table = {
	8,  /* number of rates */
	{ 0 },
	{
/*                               short            ctrl  */
/*                            Preamble  dot11Rate Rate */
/*   6 Mb */ {  OFDM,    1500,    0x00, (0x80| 3),  0 },
/*   9 Mb */ {  OFDM,    2250,    0x00,         4,  0 },
/*  12 Mb */ {  OFDM,    3000,    0x00, (0x80| 6),  2 },
/*  18 Mb */ {  OFDM,    4500,    0x00,         9,  2 },
/*  24 Mb */ {  OFDM,    6000,    0x00, (0x80|12),  4 },
/*  36 Mb */ {  OFDM,    9000,    0x00,        18,  4 },
/*  48 Mb */ {  OFDM,   12000,    0x00,        24,  4 },
/*  54 Mb */ {  OFDM,   13500,    0x00,        27,  4 }
	},
};

static struct ieee80211_rate_table ieee80211_turbog_table = {
	7,  /* number of rates */
	{ 0 },
	{
/*                               short            ctrl  */
/*                            Preamble  dot11Rate Rate */
/*   6 Mb */ {  TURBO,   6000,    0x00, (0x80|12),   0 },
/*  12 Mb */ {  TURBO,  12000,    0x00, (0x80|24),   1 },
/*  18 Mb */ {  TURBO,  18000,    0x00,        36,   1 },
/*  24 Mb */ {  TURBO,  24000,    0x00, (0x80|48),   3 },
/*  36 Mb */ {  TURBO,  36000,    0x00,        72,   3 },
/*  48 Mb */ {  TURBO,  48000,    0x00,        96,   3 },
/*  54 Mb */ {  TURBO,  54000,    0x00,       108,   3 }
	},
};

static struct ieee80211_rate_table ieee80211_turboa_table = {
	8,  /* number of rates */
	{ 0 },
	{
/*                               short            ctrl  */
/*                            Preamble  dot11Rate Rate */
/*   6 Mb */ {  TURBO,   6000,    0x00, (0x80|12),   0 },
/*   9 Mb */ {  TURBO,   9000,    0x00,        18,   0 },
/*  12 Mb */ {  TURBO,  12000,    0x00, (0x80|24),   2 },
/*  18 Mb */ {  TURBO,  18000,    0x00,        36,   2 },
/*  24 Mb */ {  TURBO,  24000,    0x00, (0x80|48),   4 },
/*  36 Mb */ {  TURBO,  36000,    0x00,        72,   4 },
/*  48 Mb */ {  TURBO,  48000,    0x00,        96,   4 },
/*  54 Mb */ {  TURBO,  54000,    0x00,       108,   4 }
	},
};

#undef	OFDM
#undef	CCK
#undef	TURBO
#undef	XR

/*
 * Setup a rate table's reverse lookup table and fill in
 * ack durations.  The reverse lookup tables are assumed
 * to be initialized to zero (or at least the first entry).
 * We use this as a key that indicates whether or not
 * we've previously setup the reverse lookup table.
 *
 * XXX not reentrant, but shouldn't matter
 */
static void
ieee80211_setup_ratetable(struct ieee80211_rate_table *rt)
{
#define	N(a)	(sizeof(a)/sizeof(a[0]))
#define	WLAN_CTRL_FRAME_SIZE \
	(sizeof(struct ieee80211_frame_ack) + IEEE80211_CRC_LEN)

	int i;

	for (i = 0; i < N(rt->rateCodeToIndex); i++)
		rt->rateCodeToIndex[i] = (uint8_t) -1;
	for (i = 0; i < rt->rateCount; i++) {
		uint8_t code = rt->info[i].dot11Rate;
		uint8_t cix = rt->info[i].ctlRateIndex;
		uint8_t ctl_rate = rt->info[cix].dot11Rate;

		rt->rateCodeToIndex[code] = i;
		if (code & IEEE80211_RATE_BASIC) {
			/*
			 * Map w/o basic rate bit too.
			 */
			code &= IEEE80211_RATE_VAL;
			rt->rateCodeToIndex[code] = i;
		}

		/*
		 * XXX for 11g the control rate to use for 5.5 and 11 Mb/s
		 *     depends on whether they are marked as basic rates;
		 *     the static tables are setup with an 11b-compatible
		 *     2Mb/s rate which will work but is suboptimal
		 *
		 * NB: Control rate is always less than or equal to the
		 *     current rate, so control rate's reverse lookup entry
		 *     has been installed and following call is safe.
		 */
		rt->info[i].lpAckDuration = ieee80211_compute_duration(rt,
			WLAN_CTRL_FRAME_SIZE, ctl_rate, 0);
		rt->info[i].spAckDuration = ieee80211_compute_duration(rt,
			WLAN_CTRL_FRAME_SIZE, ctl_rate, IEEE80211_F_SHPREAMBLE);
	}

#undef WLAN_CTRL_FRAME_SIZE
#undef N
}

/* Setup all rate tables */
static void
ieee80211_phy_init(void)
{
#define N(arr)	(int)(sizeof(arr) / sizeof(arr[0]))
	static struct ieee80211_rate_table * const ratetables[] = {
		&ieee80211_half_table,
		&ieee80211_quarter_table,
		&ieee80211_11a_table,
		&ieee80211_11g_table,
		&ieee80211_turbog_table,
		&ieee80211_turboa_table,
		&ieee80211_turboa_table,
		&ieee80211_11a_table,
		&ieee80211_11g_table,
		&ieee80211_11b_table
	};
	int i;

	for (i = 0; i < N(ratetables); ++i)
		ieee80211_setup_ratetable(ratetables[i]);

#undef N
}
SYSINIT(wlan_phy, SI_SUB_DRIVERS, SI_ORDER_FIRST, ieee80211_phy_init, NULL);

const struct ieee80211_rate_table *
ieee80211_get_ratetable(struct ieee80211_channel *c)
{
	const struct ieee80211_rate_table *rt;

	/* XXX HT */
	if (IEEE80211_IS_CHAN_HALF(c))
		rt = &ieee80211_half_table;
	else if (IEEE80211_IS_CHAN_QUARTER(c))
		rt = &ieee80211_quarter_table;
	else if (IEEE80211_IS_CHAN_HTA(c))
		rt = &ieee80211_11a_table;	/* XXX */
	else if (IEEE80211_IS_CHAN_HTG(c))
		rt = &ieee80211_11g_table;	/* XXX */
	else if (IEEE80211_IS_CHAN_108G(c))
		rt = &ieee80211_turbog_table;
	else if (IEEE80211_IS_CHAN_ST(c))
		rt = &ieee80211_turboa_table;
	else if (IEEE80211_IS_CHAN_TURBO(c))
		rt = &ieee80211_turboa_table;
	else if (IEEE80211_IS_CHAN_A(c))
		rt = &ieee80211_11a_table;
	else if (IEEE80211_IS_CHAN_ANYG(c))
		rt = &ieee80211_11g_table;
	else if (IEEE80211_IS_CHAN_B(c))
		rt = &ieee80211_11b_table;
	else {
		/* NB: should not get here */
		panic("%s: no rate table for channel; freq %u flags 0x%x\n",
		      __func__, c->ic_freq, c->ic_flags);
	}
	return rt;
}

/*
 * Convert PLCP signal/rate field to 802.11 rate (.5Mbits/s)
 *
 * Note we do no parameter checking; this routine is mainly
 * used to derive an 802.11 rate for constructing radiotap
 * header data for rx frames.
 *
 * XXX might be a candidate for inline
 */
uint8_t
ieee80211_plcp2rate(uint8_t plcp, int ofdm)
{
	if (ofdm) {
		static const uint8_t ofdm_plcp2rate[16] = {
			[0xb]	= 12,
			[0xf]	= 18,
			[0xa]	= 24,
			[0xe]	= 36,
			[0x9]	= 48,
			[0xd]	= 72,
			[0x8]	= 96,
			[0xc]	= 108
		};
		return ofdm_plcp2rate[plcp & 0xf];
	} else {
		static const uint8_t cck_plcp2rate[16] = {
			[0xa]	= 2,	/* 0x0a */
			[0x4]	= 4,	/* 0x14 */
			[0x7]	= 11,	/* 0x37 */
			[0xe]	= 22,	/* 0x6e */
			[0xc]	= 44,	/* 0xdc , actually PBCC */
		};
		return cck_plcp2rate[plcp & 0xf];
	}
}

/*
 * Covert 802.11 rate to PLCP signal.
 */
uint8_t
ieee80211_rate2plcp(int rate)
{
	switch (rate) {
	/* CCK rates (returned values are device-dependent) */
	case 2:		return 0x0;
	case 4:		return 0x1;
	case 11:	return 0x2;
	case 22:	return 0x3;

	/* OFDM rates (cf IEEE Std 802.11a-1999, pp. 14 Table 80) */
	case 12:	return 0xb;
	case 18:	return 0xf;
	case 24:	return 0xa;
	case 36:	return 0xe;
	case 48:	return 0x9;
	case 72:	return 0xd;
	case 96:	return 0x8;
	case 108:	return 0xc;
	}
	return 0xff;		/* XXX unsupported/unknown rate */
}
/*
 * Compute the time to transmit a frame of length frameLen bytes
 * using the specified rate, phy, and short preamble setting.
 * SIFS is included.
 */
uint16_t
ieee80211_compute_duration(const struct ieee80211_rate_table *rt,
	uint32_t frameLen, uint16_t rate, int isShortPreamble)
{
	uint8_t rix = rt->rateCodeToIndex[rate];
	uint32_t bitsPerSymbol, numBits, numSymbols, phyTime, txTime;
	uint32_t kbps;

	KASSERT(rix != (uint8_t)-1, ("rate %d has no info", rate));
	kbps = rt->info[rix].rateKbps;
	if (kbps == 0)			/* XXX bandaid for channel changes */
		return 0;

	switch (rt->info[rix].phy) {
	case IEEE80211_T_CCK:
#define CCK_SIFS_TIME		10
#define CCK_PREAMBLE_BITS	144
#define CCK_PLCP_BITS		48
		phyTime		= CCK_PREAMBLE_BITS + CCK_PLCP_BITS;
		if (isShortPreamble && rt->info[rix].shortPreamble)
			phyTime >>= 1;
		numBits		= frameLen << 3;
		txTime		= CCK_SIFS_TIME + phyTime
				+ ((numBits * 1000)/kbps);
		break;
#undef CCK_SIFS_TIME
#undef CCK_PREAMBLE_BITS
#undef CCK_PLCP_BITS

	case IEEE80211_T_OFDM:
#define OFDM_SIFS_TIME		16
#define OFDM_PREAMBLE_TIME	20
#define OFDM_PLCP_BITS		22
#define OFDM_SYMBOL_TIME	4

#define OFDM_SIFS_TIME_HALF	32
#define OFDM_PREAMBLE_TIME_HALF	40
#define OFDM_PLCP_BITS_HALF	22
#define OFDM_SYMBOL_TIME_HALF	8

#define OFDM_SIFS_TIME_QUARTER 		64
#define OFDM_PREAMBLE_TIME_QUARTER	80
#define OFDM_PLCP_BITS_QUARTER		22
#define OFDM_SYMBOL_TIME_QUARTER	16
		if (rt == &ieee80211_half_table) {
			bitsPerSymbol	= (kbps * OFDM_SYMBOL_TIME_QUARTER) / 1000;
			KASSERT(bitsPerSymbol != 0, ("1/2 rate bps"));

			numBits		= OFDM_PLCP_BITS + (frameLen << 3);
			numSymbols	= howmany(numBits, bitsPerSymbol);
			txTime		= OFDM_SIFS_TIME_QUARTER 
					+ OFDM_PREAMBLE_TIME_QUARTER
					+ (numSymbols * OFDM_SYMBOL_TIME_QUARTER);
		} else if (rt == &ieee80211_quarter_table) {
			bitsPerSymbol	= (kbps * OFDM_SYMBOL_TIME_HALF) / 1000;
			KASSERT(bitsPerSymbol != 0, ("1/4 rate bps"));

			numBits		= OFDM_PLCP_BITS + (frameLen << 3);
			numSymbols	= howmany(numBits, bitsPerSymbol);
			txTime		= OFDM_SIFS_TIME_HALF
					+ OFDM_PREAMBLE_TIME_HALF
					+ (numSymbols * OFDM_SYMBOL_TIME_HALF);
		} else { /* full rate channel */
			bitsPerSymbol	= (kbps * OFDM_SYMBOL_TIME) / 1000;
			KASSERT(bitsPerSymbol != 0, ("full rate bps"));

			numBits		= OFDM_PLCP_BITS + (frameLen << 3);
			numSymbols	= howmany(numBits, bitsPerSymbol);
			txTime		= OFDM_SIFS_TIME
					+ OFDM_PREAMBLE_TIME
					+ (numSymbols * OFDM_SYMBOL_TIME);
		}
		break;

#undef OFDM_SIFS_TIME
#undef OFDM_PREAMBLE_TIME
#undef OFDM_PLCP_BITS
#undef OFDM_SYMBOL_TIME

	case IEEE80211_T_TURBO:
#define TURBO_SIFS_TIME		8
#define TURBO_PREAMBLE_TIME	14
#define TURBO_PLCP_BITS		22
#define TURBO_SYMBOL_TIME	4
		/* we still save OFDM rates in kbps - so double them */
		bitsPerSymbol = ((kbps << 1) * TURBO_SYMBOL_TIME) / 1000;
		KASSERT(bitsPerSymbol != 0, ("turbo bps"));

		numBits       = TURBO_PLCP_BITS + (frameLen << 3);
		numSymbols    = howmany(numBits, bitsPerSymbol);
		txTime        = TURBO_SIFS_TIME + TURBO_PREAMBLE_TIME
			      + (numSymbols * TURBO_SYMBOL_TIME);
		break;
#undef TURBO_SIFS_TIME
#undef TURBO_PREAMBLE_TIME
#undef TURBO_PLCP_BITS
#undef TURBO_SYMBOL_TIME

	default:
		panic("%s: unknown phy %u (rate %u)\n", __func__,
		      rt->info[rix].phy, rate);
		break;
	}
	return txTime;
}
