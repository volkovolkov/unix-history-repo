/*-
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)tabnec25-t.c	4.3 (Berkeley) 4/18/91
 */

#define INCH 240
/*
NEC Spinwriter 7725 and 5525 (Diablo replacements)
with Technical Math/Times Roman thimble
12 chars/inch, 6 lines/inch
nroff driving tables
width and code tables
*/

struct {
	int bset;
	int breset;
	int Hor;
	int Vert;
	int Newline;
	int Char;
	int Em;
	int Halfline;
	int Adj;
	char *twinit;
	char *twrest;
	char *twnl;
	char *hlr;
	char *hlf;
	char *flr;
	char *bdon;
	char *bdoff;
	char *ploton;
	char *plotoff;
	char *up;
	char *down;
	char *right;
	char *left;
	char *codetab[256-32];
	int zzz;
	} t = {
/*bset*/	0,
/*breset*/	0177420,
/*Hor*/		INCH/60,
/*Vert*/	INCH/48,
/*Newline*/	INCH/6,
/*Char*/	INCH/12,
/*Em*/		INCH/12,
/*Halfline*/	INCH/12,
/*Adj*/		INCH/12,
/*twinit*/	"\0334\033\037\013",
/*twrest*/	"\0334\033\037\015",
/*twnl*/	"\015\n",
/*hlr*/		"\033D",
/*hlf*/		"\033U",
/*flr*/		"\033\n",
/*bdon*/	"",
/*bdoff*/	"",
/*ploton*/	"\0333",
/*plotoff*/	"\0334",
/*up*/		"\033\n",
/*down*/	"\n",
/*right*/	" ",
/*left*/	"\b",
/*codetab*/
"\001 ",	/*space*/
"\001!",	/*!*/
"\002\200\047\202\047",	/*"*/
"\001#",	/*#*/
"\001\200|\341S\301",	/*$*/
"\001%",	/*%*/
"\000",	/*&*/
"\001'",	/*' close*/
"\001(",	/*(*/
"\001)",	/*)*/
"\001*",	/***/
"\001+",	/*+*/
"\001,",	/*,*/
"\001-",	/*- hyphen*/
"\001.",	/*.*/
"\001/",	/*/*/
"\2010",	/*0*/
"\2011",	/*1*/
"\2012",	/*2*/
"\2013",	/*3*/
"\2014",	/*4*/
"\2015",	/*5*/
"\2016",	/*6*/
"\2017",	/*7*/
"\2018",	/*8*/
"\2019",	/*9*/
"\001:",	/*:*/
"\001:\b,",	/*;*/
"\001<",	/*<*/
"\001=",	/*=*/
"\001>",	/*>*/
"\001?",	/*?*/
"\001@",	/*@*/
"\201A",	/*A*/
"\201B",	/*B*/
"\201C",	/*C*/
"\201D",	/*D*/
"\201E",	/*E*/
"\201F",	/*F*/
"\201G",	/*G*/
"\201H",	/*H*/
"\201I",	/*I*/
"\201J",	/*J*/
"\201K",	/*K*/
"\201L",	/*L*/
"\201M",	/*M*/
"\201N",	/*N*/
"\201O",	/*O*/
"\201P",	/*P*/
"\201Q",	/*Q*/
"\201R",	/*R*/
"\201S",	/*S*/
"\201T",	/*T*/
"\201U",	/*U*/
"\201V",	/*V*/
"\201W",	/*W*/
"\201X",	/*X*/
"\201Y",	/*Y*/
"\201Z",	/*Z*/
"\001[",	/*[*/
"\001\016\112\017",	/*\*/
"\001]",	/*]*/
"\001\344.\201\341.\201\301.\242\304",	/*^*/
"\001_",	/*_ dash*/
"\001'",	/*` open*/
"\201a",	/*a*/
"\201b",	/*b*/
"\201c",	/*c*/
"\201d",	/*d*/
"\201e",	/*e*/
"\201f",	/*f*/
"\201g",	/*g*/
"\201h",	/*h*/
"\201i",	/*i*/
"\201j",	/*j*/
"\201k",	/*k*/
"\201l",	/*l*/
"\201m",	/*m*/
"\201n",	/*n*/
"\201o",	/*o*/
"\201p",	/*p*/
"\201q",	/*q*/
"\201r",	/*r*/
"\201s",	/*s*/
"\201t",	/*t*/
"\201u",	/*u*/
"\201v",	/*v*/
"\201w",	/*w*/
"\201x",	/*x*/
"\201y",	/*y*/
"\201z",	/*z*/
"\001{",	/*{*/
"\001|",	/*|*/
"\001}",	/*}*/
"\001\343\016\074\017\303",	/*~*/
"\000\0",	/*narrow sp*/
"\001-",	/*hyphen*/
"\001O\b+",	/*bullet*/
"\002[]",	/*square*/
"\001-",	/*3/4 em*/
"\001_",	/*rule*/
"\2031/4",	/*1/4*/
"\2031/2",	/*1/2*/
"\2033/4",	/*3/4*/
"\001-",	/*minus*/
"\202fi",	/*fi*/
"\202fl",	/*fl*/
"\202ff",	/*ff*/
"\203ffi",	/*ffi*/
"\203ffl",	/*ffl*/
"\001\343o\303",	/*degree*/
"\001\342-\302|",	/*dagger*/
"\001\342s\302s",	/*section*/
"\001'",	/*foot mark*/
"\001'",	/*acute accent*/
"\001\345.\201\301.\201\304",	/*grave accent*/
"\001_",	/*underrule*/
"\001/",	/*slash (longer)*/
"\000\0",	/*half narrow space*/
"\001 ",	/*unpaddable space*/
"\001\016\123\017",	/*alpha*/
"\001\046",	/*beta*/
"\001\016\107\017",	/*gamma*/
"\001\016\113\017",	/*delta*/
"\001\016\116\017",	/*epsilon*/
"\001\200c\201\301,\241\343<\302",	/*zeta*/
"\001\016\114\017",	/*eta*/
"\001O\b-",	/*theta*/
"\001i",	/*iota*/
"\001k",	/*kappa*/
"\001\016\102\017",	/*lambda*/
"\001\073",	/*mu*/
"\001\241(\203/\242",	/*nu*/
"\001\016\104\017",	/*xi*/
"\001o",	/*omicron*/
"\001\042",	/*pi*/
"\001\016\106\017",	/*rho*/
"\001\016\126\017",	/*sigma*/
"\001\016\103\017",	/*tau*/
"\001v",	/*upsilon*/
"\001o\b/",	/*phi*/
"\001x",	/*chi*/
"\001\200/-\301\202'\244'\202\341",	/*psi*/
"\001\016\130\017",	/*omega*/
"\001\242|\202\344-\304\342\202'\242\302",	/*Gamma*/
"\001\016\101\017",	/*Delta*/
"\001O\b=",	/*Theta*/
"\002/\242\016\112\017\202",	/*Lambda*/
"\001\341_\346_\307\341-\301",	/*Xi*/
"\001\242[]\204[]\242\343-\303",	/*Pi*/
"\001\341>\301\302-\346-\304\241",	/*Sigma*/
"\000\0",	/**/
"\001Y",	/*Upsilon*/
"\001o\b[\b]",	/*Phi*/
"\001\200[]-\301\202'\244'\202\341",	/*Psi*/
"\001\134",	/*Omega*/
"\001\301-\341\202\303'\202\343/\244",	/*square root*/
"\001\341s\301\202'\242",	/*terminal sigma*/
"\001\343-\303",	/*root en*/
"\001>\b_",	/*>=*/
"\001<\b_",	/*<=*/
"\001=\b_",	/*identically equal*/
"\001-",	/*equation minus*/
"\001=\b\344\016\074\017\304",	/*approx =*/
"\001\016\074\017",	/*approximates*/
"\001=\b/",	/*not equal*/
"\002 \245-\204->\201",	/*right arrow*/
"\002 \245<-\204-\201",	/*left arrow*/
"\001\016\132\017",	/*up arrow*/
"\001\016\136\017",	/*down arrow*/
"\001=",	/*equation equal*/
"\001x",	/*multiply*/
"\001\200.-\345.\305",	/*divide*/
"\001+\b_",	/*plus-minus*/
"\001U",	/*cup (union)*/
"\001\343\140\203\136\243\303",	/*cap (intersection)*/
"\002 \242\245\341(\301\341\204_\346_\203\307",	/*subset of*/
"\002 \243\341_\346_\307\204\341)\301\241",	/*superset of*/
"\002 \242\245\341(\301\341\204_\346_\307_\203",	/*improper subset of*/
"\002 \243_\341_\346_\307\341\204)\301\241",	/*improper superset of*/
"\001\016\137\017",	/*infinity*/
"\001\016\115\017",	/*partial derivative*/
"\001\200\016\112\017\203/\243\344\201-\201-\304\242",	/*gradient*/
"\001\200-\202\343,\303\242",	/*not*/
"\001\044",	/*integral sign*/
"\001\016\135\017",	/*proportional to*/
"\0010\b/",	/*empty set*/
"\001\200(\201-\241",	/*member of*/
"\001+",	/*equation plus*/
"\003(r)",	/*registered*/
"\003(c)",	/*copyright*/
"\001|",	/*box rule */
"\001c\b/",	/*cent sign*/
"\001\341=\301|",	/*dbl dagger*/
"\002*>",	/*right hand*/
"\002<*",	/*left hand*/
"\001*",	/*math * */
"\003(b)",	/*bell system sign*/
"\001|",	/*or (was star)*/
"\001O",	/*circle*/
"\001|",	/*left top (of big curly)*/
"\001|",	/*left bottom*/
"\001|",	/*right top*/
"\001|",	/*right bot*/
"\001|",	/*left center of big curly bracket*/
"\001|",	/*right center of big curly bracket*/
"\001|",	/*bold vertical*/
"\001\201\016\076\017\241",	/*left floor (left bot of big sq bract)*/
"\001\241\016\100\017\201",	/*right floor (right bot ")*/
"\001\201\140\241",	/*left ceiling (lt of ")*/
"\001\241\136\201"};	/*right ceiling (rt of ")*/
