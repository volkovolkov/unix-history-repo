/*

            Coda: an Experimental Distributed File System
                             Release 3.1

          Copyright (c) 1987-1998 Carnegie Mellon University
                         All Rights Reserved

Permission  to  use, copy, modify and distribute this software and its
documentation is hereby granted,  provided  that  both  the  copyright
notice  and  this  permission  notice  appear  in  all  copies  of the
software, derivative works or  modified  versions,  and  any  portions
thereof, and that both notices appear in supporting documentation, and
that credit is given to Carnegie Mellon University  in  all  documents
and publicity pertaining to direct or indirect use of this code or its
derivatives.

CODA IS AN EXPERIMENTAL SOFTWARE SYSTEM AND IS  KNOWN  TO  HAVE  BUGS,
SOME  OF  WHICH MAY HAVE SERIOUS CONSEQUENCES.  CARNEGIE MELLON ALLOWS
FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.   CARNEGIE  MELLON
DISCLAIMS  ANY  LIABILITY  OF  ANY  KIND  FOR  ANY  DAMAGES WHATSOEVER
RESULTING DIRECTLY OR INDIRECTLY FROM THE USE OF THIS SOFTWARE  OR  OF
ANY DERIVATIVE WORK.

Carnegie  Mellon  encourages  users  of  this  software  to return any
improvements or extensions that  they  make,  and  to  grant  Carnegie
Mellon the rights to redistribute these changes without encumbrance.
*/

/* $Header: /afs/cs/project/coda-src/cvs/coda/kernel-src/vfs/freebsd/cfs/cfs_vnodeops.c,v 1.12 1998/08/28 18:28:00 rvb Exp $ */

/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 * This code was written for the Coda file system at Carnegie Mellon
 * University.  Contributers include David Steere, James Kistler, and
 * M. Satyanarayanan.  
 */

/*
 * HISTORY
 * $Log: cfs_vnodeops.c,v $
 * Revision 1.12  1998/08/28 18:28:00  rvb
 * NetBSD -current is stricter!
 *
 * Revision 1.11  1998/08/28 18:12:23  rvb
 * Now it also works on FreeBSD -current.  This code will be
 * committed to the FreeBSD -current and NetBSD -current
 * trees.  It will then be tailored to the particular platform
 * by flushing conditional code.
 *
 * Revision 1.10  1998/08/18 17:05:21  rvb
 * Don't use __RCSID now
 *
 * Revision 1.9  1998/08/18 16:31:46  rvb
 * Sync the code for NetBSD -current; test on 1.3 later
 *
 * Revision 1.8  98/02/24  22:22:50  rvb
 * Fixes up mainly to flush iopen and friends
 * 
 * Revision 1.7  98/01/31  20:53:15  rvb
 * First version that works on FreeBSD 2.2.5
 * 
 * Revision 1.6  98/01/23  11:53:47  rvb
 * Bring RVB_CFS1_1 to HEAD
 * 
 * Revision 1.5.2.8  98/01/23  11:21:11  rvb
 * Sync with 2.2.5
 * 
 * Revision 1.5.2.7  97/12/19  14:26:08  rvb
 * session id
 * 
 * Revision 1.5.2.6  97/12/16  22:01:34  rvb
 * Oops add cfs_subr.h cfs_venus.h; sync with peter
 * 
 * Revision 1.5.2.5  97/12/16  12:40:14  rvb
 * Sync with 1.3
 * 
 * Revision 1.5.2.4  97/12/10  14:08:31  rvb
 * Fix O_ flags; check result in cfscall
 * 
 * Revision 1.5.2.3  97/12/10  11:40:27  rvb
 * No more ody
 * 
 * Revision 1.5.2.2  97/12/09  16:07:15  rvb
 * Sync with vfs/include/coda.h
 * 
 * Revision 1.5.2.1  97/12/06  17:41:25  rvb
 * Sync with peters coda.h
 * 
 * Revision 1.5  97/12/05  10:39:23  rvb
 * Read CHANGES
 * 
 * Revision 1.4.14.10  97/11/25  08:08:48  rvb
 * cfs_venus ... done; until cred/vattr change
 * 
 * Revision 1.4.14.9  97/11/24  15:44:48  rvb
 * Final cfs_venus.c w/o macros, but one locking bug
 * 
 * Revision 1.4.14.8  97/11/21  11:28:04  rvb
 * cfs_venus.c is done: first pass
 * 
 * Revision 1.4.14.7  97/11/20  11:46:51  rvb
 * Capture current cfs_venus
 * 
 * Revision 1.4.14.6  97/11/18  10:27:19  rvb
 * cfs_nbsd.c is DEAD!!!; integrated into cfs_vf/vnops.c
 * cfs_nb_foo and cfs_foo are joined
 * 
 * Revision 1.4.14.5  97/11/13  22:03:03  rvb
 * pass2 cfs_NetBSD.h mt
 * 
 * Revision 1.4.14.4  97/11/12  12:09:42  rvb
 * reorg pass1
 * 
 * Revision 1.4.14.3  97/11/06  21:03:28  rvb
 * don't include headers in headers
 * 
 * Revision 1.4.14.2  97/10/29  16:06:30  rvb
 * Kill DYING
 * 
 * Revision 1.4.14.1  1997/10/28 23:10:18  rvb
 * >64Meg; venus can be killed!
 *
 * Revision 1.4  1997/02/20 13:54:50  lily
 * check for NULL return from cfsnc_lookup before CTOV
 *
 * Revision 1.3  1996/12/12 22:11:02  bnoble
 * Fixed the "downcall invokes venus operation" deadlock in all known cases.
 * There may be more
 *
 * Revision 1.2  1996/01/02 16:57:07  bnoble
 * Added support for Coda MiniCache and raw inode calls (final commit)
 *
 * Revision 1.1.2.1  1995/12/20 01:57:34  bnoble
 * Added CFS-specific files
 *
 * Revision 3.1.1.1  1995/03/04  19:08:06  bnoble
 * Branch for NetBSD port revisions
 *
 * Revision 3.1  1995/03/04  19:08:04  bnoble
 * Bump to major revision 3 to prepare for NetBSD port
 *
 * Revision 2.6  1995/02/17  16:25:26  dcs
 * These versions represent several changes:
 * 1. Allow venus to restart even if outstanding references exist.
 * 2. Have only one ctlvp per client, as opposed to one per mounted cfs device.d
 * 3. Allow ody_expand to return many members, not just one.
 *
 * Revision 2.5  94/11/09  20:29:27  dcs
 * Small bug in remove dealing with hard links and link counts was fixed.
 * 
 * Revision 2.4  94/10/14  09:58:42  dcs
 * Made changes 'cause sun4s have braindead compilers
 * 
 * Revision 2.3  94/10/12  16:46:37  dcs
 * Cleaned kernel/venus interface by removing XDR junk, plus
 * so cleanup to allow this code to be more easily ported.
 * 
 * Revision 2.2  94/09/20  14:12:41  dcs
 * Fixed bug in rename when moving a directory.
 * 
 * Revision 2.1  94/07/21  16:25:22  satya
 * Conversion to C++ 3.0; start of Coda Release 2.0
 * 
 * Revision 1.4  93/12/17  01:38:01  luqi
 * Changes made for kernel to pass process info to Venus:
 * 
 * (1) in file cfs.h
 * add process id and process group id in most of the cfs argument types.
 * 
 * (2) in file cfs_vnodeops.c
 * add process info passing in most of the cfs vnode operations.
 * 
 * (3) in file cfs_xdr.c
 * expand xdr routines according changes in (1). 
 * add variable pass_process_info to allow venus for kernel version checking.
 * 
 * Revision 1.3  93/05/28  16:24:33  bnoble
 * *** empty log message ***
 * 
 * Revision 1.2  92/10/27  17:58:25  lily
 * merge kernel/latest and alpha/src/cfs
 * 
 * Revision 2.4  92/09/30  14:16:37  mja
 * 	Redid buffer allocation so that it does kmem_{alloc,free} for all
 * 	architectures.  Zone allocation, previously used on the 386, caused
 * 	panics if it was invoked repeatedly.  Stack allocation, previously
 * 	used on all other architectures, tickled some Mach bug that appeared
 * 	with large stack frames.
 * 	[91/02/09            jjk]
 * 
 * 	Added contributors blurb.
 * 	[90/12/13            jjk]
 * 
 * Revision 2.3  90/07/26  15:50:09  mrt
 * 	    Fixed fix to rename to remove .. from moved directories.
 * 	[90/06/28            dcs]
 * 
 * Revision 1.7  90/06/28  16:24:25  dcs
 * Fixed bug with moving directories, we weren't flushing .. for the moved directory.
 * 
 * Revision 1.6  90/05/31  17:01:47  dcs
 * Prepare for merge with facilities kernel.
 * 
 * 
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/errno.h>
#include <sys/acct.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/namei.h>
#ifdef	__FreeBSD_version
#include <sys/ioccom.h>
#else
#include <sys/ioctl.h>
#endif
#include <sys/mount.h>
#include <sys/proc.h>
#include <sys/select.h>
#ifdef	__NetBSD__
#include <sys/user.h>
#endif
#include <vm/vm.h>
#ifdef	NetBSD1_3
#include <miscfs/genfs/genfs.h>
#endif

#ifdef	__FreeBSD__
#include <vm/vm_object.h>
#include <vm/vm_extern.h>
#ifdef	__FreeBSD_version
#include <sys/fcntl.h>
#endif
#endif

#include <cfs/coda.h>
#include <cfs/cnode.h>
#include <cfs/cfs_vnodeops.h>
#include <cfs/cfs_venus.h>
#include <cfs/coda_opstats.h>
#include <cfs/cfs_subr.h>
#include <cfs/cfsnc.h>
#include <cfs/pioctl.h>

/* 
 * These flags select various performance enhancements.
 */
int cfs_intercept_rdwr = 1;    /* Set to handle read/write in the kernel */
int cfs_attr_cache  = 1;       /* Set to cache attributes in the kernel */
int cfs_symlink_cache = 1;     /* Set to cache symbolic link information */
int cfs_access_cache = 1;      /* Set to handle some access checks directly */

/* structure to keep track of vfs calls */

struct cfs_op_stats cfs_vnodeopstats[CFS_VNODEOPS_SIZE];

#define MARK_ENTRY(op) (cfs_vnodeopstats[op].entries++)
#define MARK_INT_SAT(op) (cfs_vnodeopstats[op].sat_intrn++)
#define MARK_INT_FAIL(op) (cfs_vnodeopstats[op].unsat_intrn++)
#define MARK_INT_GEN(op) (cfs_vnodeopstats[op].gen_intrn++)

/* What we are delaying for in printf */
int cfs_printf_delay = 0;  /* in microseconds */
int cfs_vnop_print_entry = 0;
static int cfs_lockdebug = 0;

/* Definition of the vfs operation vector */

/*
 * Some NetBSD details:
 * 
 *   cfs_start is called at the end of the mount syscall.
 *   cfs_init is called at boot time.
 */

#ifdef __GNUC__
#define ENTRY    \
   if(cfs_vnop_print_entry) myprintf(("Entered %s\n",__FUNCTION__))
#else
#define ENTRY
#endif 

/* Definition of the vnode operation vector */

struct vnodeopv_entry_desc cfs_vnodeop_entries[] = {
    { &vop_default_desc, nbsd_vop_error },
    { &vop_lookup_desc, cfs_lookup },		/* lookup */
    { &vop_create_desc, cfs_create },		/* create */
    { &vop_mknod_desc, nbsd_vop_error },	/* mknod */
    { &vop_open_desc, cfs_open },		/* open */
    { &vop_close_desc, cfs_close },		/* close */
    { &vop_access_desc, cfs_access },		/* access */
    { &vop_getattr_desc, cfs_getattr },		/* getattr */
    { &vop_setattr_desc, cfs_setattr },		/* setattr */
    { &vop_read_desc, cfs_read },		/* read */
    { &vop_write_desc, cfs_write },		/* write */
    { &vop_ioctl_desc, cfs_ioctl },		/* ioctl */
/* 1.3    { &vop_select_desc, cfs_select },	select */
    { &vop_mmap_desc, nbsd_vop_error },		/* mmap */
    { &vop_fsync_desc, cfs_fsync },		/* fsync */
    { &vop_remove_desc, cfs_remove },		/* remove */
    { &vop_link_desc, cfs_link },		/* link */
    { &vop_rename_desc, cfs_rename },		/* rename */
    { &vop_mkdir_desc, cfs_mkdir },		/* mkdir */
    { &vop_rmdir_desc, cfs_rmdir },		/* rmdir */
    { &vop_symlink_desc, cfs_symlink },		/* symlink */
    { &vop_readdir_desc, cfs_readdir },		/* readdir */
    { &vop_readlink_desc, cfs_readlink },	/* readlink */
    { &vop_abortop_desc, cfs_abortop },		/* abortop */
    { &vop_inactive_desc, cfs_inactive },	/* inactive */
    { &vop_reclaim_desc, cfs_reclaim },		/* reclaim */
    { &vop_lock_desc, cfs_lock },		/* lock */
    { &vop_unlock_desc, cfs_unlock },		/* unlock */
    { &vop_bmap_desc, cfs_bmap },		/* bmap */
    { &vop_strategy_desc, cfs_strategy },	/* strategy */
    { &vop_print_desc, nbsd_vop_error },	/* print */
    { &vop_islocked_desc, cfs_islocked },	/* islocked */
    { &vop_pathconf_desc, nbsd_vop_error },	/* pathconf */
    { &vop_advlock_desc, nbsd_vop_nop },	/* advlock */
    { &vop_bwrite_desc, nbsd_vop_error },	/* bwrite */
    { &vop_lease_desc, nbsd_vop_nop },          /* lease */

#ifdef	__FreeBSD_version
#else	/*  FreeBSD stable & NetBSD both */
    { &vop_blkatoff_desc, nbsd_vop_error },	/* blkatoff */
    { &vop_valloc_desc, nbsd_vop_error },	/* valloc */
    { &vop_vfree_desc, nbsd_vop_error },	/* vfree */
    { &vop_truncate_desc, nbsd_vop_error },	/* truncate */
    { &vop_update_desc, nbsd_vop_error },	/* update */
#endif

    /* NetBSD only */
#ifdef	__NetBSD__
#ifdef	NetBSD1_3
    { &vop_seek_desc, genfs_seek },		/* seek */
#else
    { &vop_seek_desc, nbsd_vop_error },		/* seek */
#endif
#endif

    /* FreeBSD only */
#ifdef	__FreeBSD__

#ifdef	__FreeBSD_version

    { &vop_poll_desc,		(vop_t *) vop_stdpoll },
    { &vop_getpages_desc, (vop_t *) cfs_fbsd_getpages },       /* pager intf.*/
    { &vop_putpages_desc, (vop_t *) cfs_fbsd_putpages },       /* pager intf.*/

#if	0
#define UFS_BLKATOFF(aa, bb, cc, dd) VFSTOUFS((aa)->v_mount)->um_blkatoff(aa, bb, cc, dd)
#define UFS_VALLOC(aa, bb, cc, dd) VFSTOUFS((aa)->v_mount)->um_valloc(aa, bb, cc, dd)
#define UFS_VFREE(aa, bb, cc) VFSTOUFS((aa)->v_mount)->um_vfree(aa, bb, cc)
#define UFS_TRUNCATE(aa, bb, cc, dd, ee) VFSTOUFS((aa)->v_mount)->um_truncate(aa, bb, cc, dd, ee)
#define UFS_UPDATE(aa, bb, cc, dd) VFSTOUFS((aa)->v_mount)->um_update(aa, bb, cc, dd)

    missing
    { &vop_reallocblks_desc,	(vop_t *) ufs_missingop },
    { &vop_cachedlookup_desc,	(vop_t *) ufs_lookup },
    { &vop_whiteout_desc,	(vop_t *) ufs_whiteout },
#endif

#else	/* FreeBSD stable */
    { &vop_getpages_desc, fbsd_vnotsup },       /* pager intf.*/
    { &vop_putpages_desc, fbsd_vnotsup },       /* pager intf.*/
    { &vop_seek_desc, nbsd_vop_error },		/* seek */
    { &vop_blkatoff_desc, nbsd_vop_error },	/* blkatoff */
    { &vop_valloc_desc, nbsd_vop_error },	/* valloc */
    { &vop_vfree_desc, nbsd_vop_error },	/* vfree */
    { &vop_truncate_desc, nbsd_vop_error },	/* truncate */
    { &vop_update_desc, nbsd_vop_error },	/* update */
#endif
#endif
    { (struct vnodeop_desc*)NULL, (int(*)(void *))NULL }
};

#ifdef __NetBSD__
struct vnodeopv_desc cfs_vnodeop_opv_desc = 
        { &cfs_vnodeop_p, cfs_vnodeop_entries };

#define NAMEI_FREE(a) FREE(a, M_NAMEI)
#endif

#ifdef __FreeBSD__
static struct vnodeopv_desc cfs_vnodeop_opv_desc =
		{ &cfs_vnodeop_p, cfs_vnodeop_entries };

#include <sys/kernel.h>
VNODEOP_SET(cfs_vnodeop_opv_desc);

int
fbsd_vnotsup(ap)
    void *ap;
{
    return(EOPNOTSUPP);
}

#ifdef	__FreeBSD_version
#include <vm/vm_zone.h>

#define NAMEI_FREE(a) zfree(namei_zone, a);
#else
#define NAMEI_FREE(a) FREE(a, M_NAMEI)
#endif
#endif

/* Definitions of NetBSD vnodeop interfaces */

/* A generic panic: we were called with something we didn't define yet */
int
nbsd_vop_error(void *anon) {
    struct vnodeop_desc **desc = (struct vnodeop_desc **)anon;

    myprintf(("Vnode operation %s called, but not defined\n",
	      (*desc)->vdesc_name));
    panic("nbsd_vop_error");
    return 0;
}

/* A generic do-nothing.  For lease_check, advlock */
int
nbsd_vop_nop(void *anon) {
    struct vnodeop_desc **desc = (struct vnodeop_desc **)anon;

    if (cfsdebug) {
	myprintf(("Vnode operation %s called, but unsupported\n",
		  (*desc)->vdesc_name));
    } 
   return (0);
}

int
cfs_vnodeopstats_init(void)
{
	register int i;
	
	for(i=0;i<CFS_VNODEOPS_SIZE;i++) {
		cfs_vnodeopstats[i].opcode = i;
		cfs_vnodeopstats[i].entries = 0;
		cfs_vnodeopstats[i].sat_intrn = 0;
		cfs_vnodeopstats[i].unsat_intrn = 0;
		cfs_vnodeopstats[i].gen_intrn = 0;
	}
	
	return 0;
}
		
/* 
 * cfs_open calls Venus to return the device, inode pair of the cache
 * file holding the data. Using iget, cfs_open finds the vnode of the
 * cache file, and then opens it.
 */
int
cfs_open(v)
    void *v;
{
    /* 
     * NetBSD can pass the O_EXCL flag in mode, even though the check
     * has already happened.  Venus defensively assumes that if open
     * is passed the EXCL, it must be a bug.  We strip the flag here.
     */
/* true args */
    struct vop_open_args *ap = v;
    register struct vnode **vpp = &(ap->a_vp);
    struct cnode *cp = VTOC(*vpp);
    int flag = ap->a_mode & (~O_EXCL);
    struct ucred *cred = ap->a_cred;
    struct proc *p = ap->a_p;
/* locals */
    int error;
    struct vnode *vp;
    dev_t dev;
    ino_t inode;

    MARK_ENTRY(CFS_OPEN_STATS);

    /* Check for open of control file. */
    if (IS_CTL_VP(*vpp)) {
	/* XXX */
	/* if (WRITEABLE(flag)) */ 
	if (flag & (FWRITE | O_TRUNC | O_CREAT | O_EXCL)) {
	    MARK_INT_FAIL(CFS_OPEN_STATS);
	    return(EACCES);
	}
	MARK_INT_SAT(CFS_OPEN_STATS);
	return(0);
    }

    error = venus_open(vtomi((*vpp)), &cp->c_fid, flag, cred, p, &dev, &inode);
    if (error)
	return (error);
    if (!error) {
	CFSDEBUG( CFS_OPEN,myprintf(("open: dev %d inode %d result %d\n",
				  dev, inode, error)); )
    }

    /* Translate the <device, inode> pair for the cache file into
       an inode pointer. */
    error = cfs_grab_vnode(dev, inode, &vp);
    if (error)
	return (error);

    /* We get the vnode back locked in both Mach and NetBSD.  Needs unlocked */
    VOP_X_UNLOCK(vp, 0);
    /* Keep a reference until the close comes in. */
    vref(*vpp);                

    /* Save the vnode pointer for the cache file. */
    if (cp->c_ovp == NULL) {
	cp->c_ovp = vp;
    } else {
	if (cp->c_ovp != vp)
	    panic("cfs_open:  cp->c_ovp != ITOV(ip)");
    }
    cp->c_ocount++;

    /* Flush the attribute cached if writing the file. */
    if (flag & FWRITE) {
	cp->c_owrite++;
	cp->c_flags &= ~C_VATTR;
    }

    /* Save the <device, inode> pair for the cache file to speed
       up subsequent page_read's. */
    cp->c_device = dev;
    cp->c_inode = inode;

    /* Open the cache file. */
    error = VOP_OPEN(vp, flag, cred, p); 
#ifdef	__FreeBSD__
    if (error) {
    	printf("cfs_open: VOP_OPEN on container failed %d\n", error);
	return (error);
    }
    if (vp->v_type == VREG) {
    	error = vfs_object_create(vp, p, cred, 1);
	if (error != 0) {
	    printf("cfs_open: vfs_object_create() returns %d\n", error);
	    vput(vp);
	}
    }
#endif
    return(error);
}

/*
 * Close the cache file used for I/O and notify Venus.
 */
int
cfs_close(v)
    void *v;
{
/* true args */
    struct vop_close_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
    int flag = ap->a_fflag;
    struct ucred *cred = ap->a_cred;
    struct proc *p = ap->a_p;
/* locals */
    int error;

    MARK_ENTRY(CFS_CLOSE_STATS);

    /* Check for close of control file. */
    if (IS_CTL_VP(vp)) {
	MARK_INT_SAT(CFS_CLOSE_STATS);
	return(0);
    }

    if (IS_UNMOUNTING(cp)) {
	if (cp->c_ovp) {
	    printf("cfs_close: destroying container ref %d, ufs vp %p of vp %p/cp %p\n",
		    vp->v_usecount, cp->c_ovp, vp, cp);
	    vgone(cp->c_ovp);
	} else {
	    printf("cfs_close: NO container vp %p/cp %p\n", vp, cp);
	}
	return ENODEV;
    } else {
	VOP_CLOSE(cp->c_ovp, flag, cred, p); /* Do errors matter here? */
	vrele(cp->c_ovp);
    }

    if (--cp->c_ocount == 0)
	cp->c_ovp = NULL;

    if (flag & FWRITE)                    /* file was opened for write */
	--cp->c_owrite;

    error = venus_close(vtomi(vp), &cp->c_fid, flag, cred, p);
    vrele(CTOV(cp));

    CFSDEBUG(CFS_CLOSE, myprintf(("close: result %d\n",error)); )
    return(error);
}

int
cfs_read(v)
    void *v;
{
    struct vop_read_args *ap = v;

    ENTRY;
    return(cfs_rdwr(ap->a_vp, ap->a_uio, UIO_READ,
		    ap->a_ioflag, ap->a_cred, ap->a_uio->uio_procp));
}

int
cfs_write(v)
    void *v;
{
    struct vop_write_args *ap = v;

    ENTRY;
    return(cfs_rdwr(ap->a_vp, ap->a_uio, UIO_WRITE,
		    ap->a_ioflag, ap->a_cred, ap->a_uio->uio_procp));
}

int
cfs_rdwr(vp, uiop, rw, ioflag, cred, p)
    struct vnode *vp;
    struct uio *uiop;
    enum uio_rw rw;
    int ioflag;
    struct ucred *cred;
    struct proc *p;
{ 
/* upcall decl */
  /* NOTE: container file operation!!! */
/* locals */
    struct cnode *cp = VTOC(vp);
    struct vnode *cfvp = cp->c_ovp;
    int igot_internally = 0;
    int opened_internally = 0;
    int error = 0;

    MARK_ENTRY(CFS_RDWR_STATS);

    CFSDEBUG(CFS_RDWR, myprintf(("cfs_rdwr(%d, %p, %d, %qd, %d)\n", rw, 
			      uiop->uio_iov->iov_base, uiop->uio_resid, 
			      uiop->uio_offset, uiop->uio_segflg)); )
	
    /* Check for rdwr of control object. */
    if (IS_CTL_VP(vp)) {
	MARK_INT_FAIL(CFS_RDWR_STATS);
	return(EINVAL);
    }

    /* Redirect the request to UFS. */

    /* 
     * If file is not already open this must be a page
     * {read,write} request.  Iget the cache file's inode
     * pointer if we still have its <device, inode> pair.
     * Otherwise, we must do an internal open to derive the
     * pair. 
     */
    if (cfvp == NULL) {
	/* 
	 * If we're dumping core, do the internal open. Otherwise
	 * venus won't have the correct size of the core when
	 * it's completely written.
	 */
	if (cp->c_inode != 0 && !(p && (p->p_acflag & ACORE))) { 
	    igot_internally = 1;
	    error = cfs_grab_vnode(cp->c_device, cp->c_inode, &cfvp);
	    if (error) {
		MARK_INT_FAIL(CFS_RDWR_STATS);
		return(error);
	    }
	    /* 
	     * We get the vnode back locked in both Mach and
	     * NetBSD.  Needs unlocked 
	     */
	    VOP_X_UNLOCK(cfvp, 0);
	}
	else {
	    opened_internally = 1;
	    MARK_INT_GEN(CFS_OPEN_STATS);
	    error = VOP_OPEN(vp, (rw == UIO_READ ? FREAD : FWRITE), 
			     cred, p);
printf("cfs_rdwr: Internally Opening %p\n", vp);
#ifdef	__FreeBSD__
	    if (error) {
		printf("cfs_rdwr: VOP_OPEN on container failed %d\n", error);
		return (error);
	    }
	    if (vp->v_type == VREG) {
		error = vfs_object_create(vp, p, cred, 1);
		if (error != 0) {
		    printf("cfs_rdwr: vfs_object_create() returns %d\n", error);
		    vput(vp);
		}
	    }
#endif
	    if (error) {
		MARK_INT_FAIL(CFS_RDWR_STATS);
		return(error);
	    }
	    cfvp = cp->c_ovp;
	}
    }

    /* Have UFS handle the call. */
    CFSDEBUG(CFS_RDWR, myprintf(("indirect rdwr: fid = (%lx.%lx.%lx), refcnt = %d\n",
			      cp->c_fid.Volume, cp->c_fid.Vnode, 
			      cp->c_fid.Unique, CTOV(cp)->v_usecount)); )

    if (rw == UIO_READ) {
	error = VOP_READ(cfvp, uiop, ioflag, cred);
    } else {
	error = VOP_WRITE(cfvp, uiop, ioflag, cred);
#ifdef	__FreeBSD__
	/* ufs_write updates the vnode_pager_setsize for the vnode/object */
	{   struct vattr attr;

	    if (VOP_GETATTR(cfvp, &attr, cred, p) == 0) {
		vnode_pager_setsize(vp, attr.va_size);
#ifdef	__DEBUG_FreeBSD__
		printf("write: vnode_pager_setsize(%p, %d)\n", vp, attr.va_size);
#endif
	    }
	}
#endif
    }

    if (error)
	MARK_INT_FAIL(CFS_RDWR_STATS);
    else
	MARK_INT_SAT(CFS_RDWR_STATS);

    /* Do an internal close if necessary. */
    if (opened_internally) {
	MARK_INT_GEN(CFS_CLOSE_STATS);
	(void)VOP_CLOSE(vp, (rw == UIO_READ ? FREAD : FWRITE), cred, p);
    }

    /* Invalidate cached attributes if writing. */
    if (rw == UIO_WRITE)
	cp->c_flags &= ~C_VATTR;
    return(error);
}

int
cfs_ioctl(v)
    void *v;
{
/* true args */
    struct vop_ioctl_args *ap = v;
    struct vnode *vp = ap->a_vp;
    int com = ap->a_command;
    caddr_t data = ap->a_data;
    int flag = ap->a_fflag;
    struct ucred *cred = ap->a_cred;
    struct proc  *p = ap->a_p;
/* locals */
    int error;
    struct vnode *tvp;
    struct nameidata ndp;
    struct PioctlData *iap = (struct PioctlData *)data;

    MARK_ENTRY(CFS_IOCTL_STATS);

    CFSDEBUG(CFS_IOCTL, myprintf(("in cfs_ioctl on %s\n", iap->path));)
	
    /* Don't check for operation on a dying object, for ctlvp it
       shouldn't matter */
	
    /* Must be control object to succeed. */
    if (!IS_CTL_VP(vp)) {
	MARK_INT_FAIL(CFS_IOCTL_STATS);
	CFSDEBUG(CFS_IOCTL, myprintf(("cfs_ioctl error: vp != ctlvp"));)
	    return (EOPNOTSUPP);
    }
    /* Look up the pathname. */

    /* Should we use the name cache here? It would get it from
       lookupname sooner or later anyway, right? */

    NDINIT(&ndp, LOOKUP, (iap->follow ? FOLLOW : NOFOLLOW), UIO_USERSPACE, ((caddr_t)iap->path), p);
    error = namei(&ndp);
    tvp = ndp.ni_vp;

    if (error) {
	MARK_INT_FAIL(CFS_IOCTL_STATS);
	CFSDEBUG(CFS_IOCTL, myprintf(("cfs_ioctl error: lookup returns %d\n",
				   error));)
	return(error);
    }

    /* 
     * Make sure this is a coda style cnode, but it may be a
     * different vfsp 
     */
    /* XXX: this totally violates the comment about vtagtype in vnode.h */
    if (tvp->v_tag != VT_CFS) {
	vrele(tvp);
	MARK_INT_FAIL(CFS_IOCTL_STATS);
	CFSDEBUG(CFS_IOCTL, 
		 myprintf(("cfs_ioctl error: %s not a coda object\n", 
			iap->path));)
	return(EINVAL);
    }

    if (iap->vi.in_size > VC_MAXDATASIZE) {
	vrele(tvp);
	return(EINVAL);
    }
    error = venus_ioctl(vtomi(tvp), &((VTOC(tvp))->c_fid), com, flag, data, cred, p);

    if (error)
	MARK_INT_FAIL(CFS_IOCTL_STATS);
    else
	CFSDEBUG(CFS_IOCTL, myprintf(("Ioctl returns %d \n", error)); )

    vrele(tvp);
    return(error);
}

#if	0
int
cfs_select(v)
    void *v;
{
/* true args */
    struct vop_select_args *ap = v;
    struct vnode *vp = ap->a_vp;
    int which = ap->a_which;
    struct ucred *cred = ap->a_cred;
    struct proc *p = ap->a_p;
/* upcall decl */
/* locals */

	MARK_ENTRY(CFS_SELECT_STATS);

	myprintf(("in cfs_select\n"));
	MARK_INT_FAIL(CFS_SELECT_STATS);
	return (EOPNOTSUPP);
}
#endif

/*
 * To reduce the cost of a user-level venus;we cache attributes in
 * the kernel.  Each cnode has storage allocated for an attribute. If
 * c_vattr is valid, return a reference to it. Otherwise, get the
 * attributes from venus and store them in the cnode.  There is some
 * question if this method is a security leak. But I think that in
 * order to make this call, the user must have done a lookup and
 * opened the file, and therefore should already have access.  
 */
int
cfs_getattr(v)
    void *v;
{
/* true args */
    struct vop_getattr_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
    struct vattr *vap = ap->a_vap;
    struct ucred *cred = ap->a_cred;
    struct proc *p = ap->a_p;
/* locals */
    int error;
    struct cnode *scp = NULL;

    MARK_ENTRY(CFS_GETATTR_STATS);

#if	0
    /* Check for operation on a dying object */
    if (IS_DYING(cp)) {
	COMPLAIN_BITTERLY(getattr, cp->c_fid);
	scp = cp;	/* Save old cp */
	/* If no error, gives a valid vnode with which to work. */
	error = getNewVnode(&vp);	
	if (error) {
	    MARK_INT_FAIL(CFS_GETATTR_STATS);
	    return(error);	/* Can't contact dead venus */
	}
	cp = VTOC(vp);
    }
#endif

#ifdef	__FreeBSD__
    if (IS_UNMOUNTING(cp))
	return ENODEV;
#endif
    /* Check for getattr of control object. */
    if (IS_CTL_VP(vp)) {
	MARK_INT_FAIL(CFS_GETATTR_STATS);
	return(ENOENT);
    }

    /* Check to see if the attributes have already been cached */
    if (VALID_VATTR(cp)) { 
	CFSDEBUG(CFS_GETATTR, { myprintf(("attr cache hit: (%lx.%lx.%lx)\n",
				       cp->c_fid.Volume,
				       cp->c_fid.Vnode,
				       cp->c_fid.Unique));});
	CFSDEBUG(CFS_GETATTR, if (!(cfsdebug & ~CFS_GETATTR))
		 print_vattr(&cp->c_vattr); );
	
	*vap = cp->c_vattr;
	MARK_INT_SAT(CFS_GETATTR_STATS);
	if (scp) vrele(vp);
	return(0);
    }

    error = venus_getattr(vtomi(vp), &cp->c_fid, cred, p, vap);

    if (!error) {
	CFSDEBUG(CFS_GETATTR, myprintf(("getattr miss (%lx.%lx.%lx): result %d\n",
				     cp->c_fid.Volume,
				     cp->c_fid.Vnode,
				     cp->c_fid.Unique,
				     error)); )
	    
	CFSDEBUG(CFS_GETATTR, if (!(cfsdebug & ~CFS_GETATTR))
		 print_vattr(vap);	);
	
#ifdef	__FreeBSD__
    {	int size = vap->va_size;
    	struct vnode *convp = cp->c_ovp;
	if (convp != (struct vnode *)0) {
	    vnode_pager_setsize(convp, size);
#ifdef	__DEBUG_FreeBSD__
	    printf("getattr: vnode_pager_setsize(%p, %d)\n", convp, size);
#endif
	}
    }
#endif
	/* If not open for write, store attributes in cnode */   
	if ((cp->c_owrite == 0) && (cfs_attr_cache)) {  
	    cp->c_vattr = *vap;
	    cp->c_flags |= C_VATTR; 
	}
	
    }
    if (scp) vrele(vp);
    return(error);
}

int
cfs_setattr(v)
    void *v;
{
/* true args */
    struct vop_setattr_args *ap = v;
    register struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
    register struct vattr *vap = ap->a_vap;
    struct ucred *cred = ap->a_cred;
    struct proc *p = ap->a_p;
/* locals */
    int error;

    MARK_ENTRY(CFS_SETATTR_STATS);

    /* Check for setattr of control object. */
    if (IS_CTL_VP(vp)) {
	MARK_INT_FAIL(CFS_SETATTR_STATS);
	return(ENOENT);
    }

    if (cfsdebug & CFSDBGMSK(CFS_SETATTR)) {
	print_vattr(vap);
    }
    error = venus_setattr(vtomi(vp), &cp->c_fid, vap, cred, p);

    if (!error)
	cp->c_flags &= ~C_VATTR;

#ifdef	__FreeBSD__
    {	int size = vap->va_size;
    	struct vnode *convp = cp->c_ovp;
	if (size != VNOVAL && convp != (struct vnode *)0) {
	    vnode_pager_setsize(convp, size);
#ifdef	__DEBUG_FreeBSD__
	    printf("setattr: vnode_pager_setsize(%p, %d)\n", convp, size);
#endif
	}
    }
#endif
    CFSDEBUG(CFS_SETATTR,	myprintf(("setattr %d\n", error)); )
    return(error);
}

int
cfs_access(v)
    void *v;
{
/* true args */
    struct vop_access_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
    int mode = ap->a_mode;
    struct ucred *cred = ap->a_cred;
    struct proc *p = ap->a_p;
/* locals */
    int error;

    MARK_ENTRY(CFS_ACCESS_STATS);

    /* Check for access of control object.  Only read access is
       allowed on it. */
    if (IS_CTL_VP(vp)) {
	/* bogus hack - all will be marked as successes */
	MARK_INT_SAT(CFS_ACCESS_STATS);
	return(((mode & VREAD) && !(mode & (VWRITE | VEXEC))) 
	       ? 0 : EACCES);
    }

    /*
     * if the file is a directory, and we are checking exec (eg lookup) 
     * access, and the file is in the namecache, then the user must have 
     * lookup access to it.
     */
    if (cfs_access_cache) {
	if ((vp->v_type == VDIR) && (mode & VEXEC)) {
	    if (cfsnc_lookup(cp, ".", 1, cred)) {
		MARK_INT_SAT(CFS_ACCESS_STATS);
		return(0);                     /* it was in the cache */
	    }
	}
    }

    error = venus_access(vtomi(vp), &cp->c_fid, mode, cred, p);

    return(error);
}

/*
 * CFS abort op, called after namei() when a CREATE/DELETE isn't actually
 * done. If a buffer has been saved in anticipation of a cfs_create or
 * a cfs_remove, delete it.
 */
/* ARGSUSED */
int
cfs_abortop(v)
    void *v;
{
/* true args */
    struct vop_abortop_args /* {
	struct vnode *a_dvp;
	struct componentname *a_cnp;
    } */ *ap = v;
/* upcall decl */
/* locals */

    if ((ap->a_cnp->cn_flags & (HASBUF | SAVESTART)) == HASBUF)
	NAMEI_FREE(ap->a_cnp->cn_pnbuf);
    return (0);
}

int
cfs_readlink(v)
    void *v;
{
/* true args */
    struct vop_readlink_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
    struct uio *uiop = ap->a_uio;
    struct ucred *cred = ap->a_cred;
    struct proc *p = ap->a_uio->uio_procp;
/* locals */
    int error;
    char *str;
    int len;

    MARK_ENTRY(CFS_READLINK_STATS);

    /* Check for readlink of control object. */
    if (IS_CTL_VP(vp)) {
	MARK_INT_FAIL(CFS_READLINK_STATS);
	return(ENOENT);
    }

    if ((cfs_symlink_cache) && (VALID_SYMLINK(cp))) { /* symlink was cached */
	uiop->uio_rw = UIO_READ;
	error = uiomove(cp->c_symlink, (int)cp->c_symlen, uiop);
	if (error)
	    MARK_INT_FAIL(CFS_READLINK_STATS);
	else
	    MARK_INT_SAT(CFS_READLINK_STATS);
	return(error);
    }

    error = venus_readlink(vtomi(vp), &cp->c_fid, cred, p, &str, &len);

    if (!error) {
	uiop->uio_rw = UIO_READ;
	error = uiomove(str, len, uiop);

	if (cfs_symlink_cache) {
	    cp->c_symlink = str;
	    cp->c_symlen = len;
	    cp->c_flags |= C_SYMLINK;
	} else
	    CFS_FREE(str, len);
    }

    CFSDEBUG(CFS_READLINK, myprintf(("in readlink result %d\n",error));)
    return(error);
}

int
cfs_fsync(v)
    void *v;
{
/* true args */
    struct vop_fsync_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
    struct ucred *cred = ap->a_cred;
    struct proc *p = ap->a_p;
/* locals */
    struct vnode *convp = cp->c_ovp;
    int error;
   
    MARK_ENTRY(CFS_FSYNC_STATS);

    /* Check for fsync on an unmounting object */
    /* The NetBSD kernel, in it's infinite wisdom, can try to fsync
     * after an unmount has been initiated.  This is a Bad Thing,
     * which we have to avoid.  Not a legitimate failure for stats.
     */
    if (IS_UNMOUNTING(cp)) {
	return(ENODEV);
    }

    /* Check for fsync of control object. */
    if (IS_CTL_VP(vp)) {
	MARK_INT_SAT(CFS_FSYNC_STATS);
	return(0);
    }

    if (convp)
    	VOP_FSYNC(convp, cred, MNT_WAIT, p);

#ifdef	__FreeBSD__
    /*
     * We see fsyncs with usecount == 1 then usecount == 0.
     * For now we ignore them.
     */
    /*
    if (!vp->v_usecount) {
    	printf("cfs_fsync on vnode %p with %d usecount.  c_flags = %x (%x)\n",
		vp, vp->v_usecount, cp->c_flags, cp->c_flags&C_PURGING);
    }
    */
#endif

    /*
     * We can expect fsync on any vnode at all if venus is pruging it.
     * Venus can't very well answer the fsync request, now can it?
     * Hopefully, it won't have to, because hopefully, venus preserves
     * the (possibly untrue) invariant that it never purges an open
     * vnode.  Hopefully.
     */
    if (cp->c_flags & C_PURGING) {
	return(0);
    }

#ifdef	__FreeBSD__
    /* needs research */
    return 0;
#endif
    error = venus_fsync(vtomi(vp), &cp->c_fid, cred, p);

    CFSDEBUG(CFS_FSYNC, myprintf(("in fsync result %d\n",error)); );
    return(error);
}

int
cfs_inactive(v)
    void *v;
{
    /* XXX - at the moment, inactive doesn't look at cred, and doesn't
       have a proc pointer.  Oops. */
/* true args */
    struct vop_inactive_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
    struct ucred *cred __attribute__((unused)) = NULL;
    struct proc *p __attribute__((unused)) = curproc;
/* upcall decl */
/* locals */

    /* We don't need to send inactive to venus - DCS */
    MARK_ENTRY(CFS_INACTIVE_STATS);

    if (IS_CTL_VP(vp)) {
	MARK_INT_SAT(CFS_INACTIVE_STATS);
	return 0;
    }

    CFSDEBUG(CFS_INACTIVE, myprintf(("in inactive, %lx.%lx.%lx. vfsp %p\n",
				  cp->c_fid.Volume, cp->c_fid.Vnode, 
				  cp->c_fid.Unique, vp->v_mount));)

#ifdef	__DEBUG_FreeBSD__
    if (vp->v_flag & VXLOCK)
	printf ("Inactive: Vnode is Locked\n");
#endif

    /* If an array has been allocated to hold the symlink, deallocate it */
    if ((cfs_symlink_cache) && (VALID_SYMLINK(cp))) {
	if (cp->c_symlink == NULL)
	    panic("cfs_inactive: null symlink pointer in cnode");
	
	CFS_FREE(cp->c_symlink, cp->c_symlen);
	cp->c_flags &= ~C_SYMLINK;
	cp->c_symlen = 0;
    }

    /* Remove it from the table so it can't be found. */
    cfs_unsave(cp);
    if ((struct cfs_mntinfo *)(vp->v_mount->mnt_data) == NULL) {
	myprintf(("Help! vfsp->vfs_data was NULL, but vnode %p wasn't dying\n", vp));
	panic("badness in cfs_inactive\n");
    }

    if (IS_UNMOUNTING(cp)) {
#ifdef	DEBUG
	printf("cfs_inactive: IS_UNMOUNTING use %d: vp %p, cp %p\n", vp->v_usecount, vp, cp);
	if (cp->c_ovp != NULL)
	    printf("cfs_inactive: cp->ovp != NULL use %d: vp %p, cp %p\n",
	    	   vp->v_usecount, vp, cp);
#endif
#ifdef	NEW_LOCKMGR
	NEW_LOCKMGR(&cp->c_lock, LK_RELEASE, &vp->v_interlock);
#endif
    } else {
#ifdef DIAGNOSTIC
	if (CTOV(cp)->v_usecount) {
	    panic("cfs_inactive: nonzero reference count");
	}
	if (cp->c_ovp != NULL) {
	    panic("cfs_inactive:  cp->ovp != NULL");
	}
#endif
#ifdef	NEW_LOCKMGR
	VOP_X_UNLOCK(vp, 0);
#endif
	vgone(vp);
    }

    MARK_INT_SAT(CFS_INACTIVE_STATS);
    return(0);
}

/*
 * Remote file system operations having to do with directory manipulation.
 */

/* 
 * It appears that in NetBSD, lookup is supposed to return the vnode locked
 */
int
cfs_lookup(v)
    void *v;
{
/* true args */
    struct vop_lookup_args *ap = v;
    struct vnode *dvp = ap->a_dvp;
    struct cnode *dcp = VTOC(dvp);
    struct vnode **vpp = ap->a_vpp;
    /* 
     * It looks as though ap->a_cnp->ni_cnd->cn_nameptr holds the rest
     * of the string to xlate, and that we must try to get at least
     * ap->a_cnp->ni_cnd->cn_namelen of those characters to macth.  I
     * could be wrong. 
     */
    struct componentname  *cnp = ap->a_cnp;
    struct ucred *cred = cnp->cn_cred;
    struct proc *p = cnp->cn_proc;
/* locals */
    struct cnode *cp;
    struct cnode *scp = NULL;
    const char *nm = cnp->cn_nameptr;
    int len = cnp->cn_namelen;
    ViceFid VFid;
    int	vtype;
    int error = 0;

    MARK_ENTRY(CFS_LOOKUP_STATS);

    CFSDEBUG(CFS_LOOKUP, myprintf(("lookup: %s in %lx.%lx.%lx\n",
				   nm, dcp->c_fid.Volume,
				   dcp->c_fid.Vnode, dcp->c_fid.Unique)););

#if	0
    /* Check for operation on a dying object */
    if (IS_DYING(dcp)) {
	COMPLAIN_BITTERLY(lookup, dcp->c_fid);
	scp = dcp;	/* Save old dcp */
	/* If no error, gives a valid vnode with which to work. */
	error = getNewVnode(&dvp);	
	if (error) {
	    MARK_INT_FAIL(CFS_LOOKUP_STATS);
	    return(error);	/* Can't contact dead venus */
	}
	dcp = VTOC(dvp);
    }
#endif

    /* Check for lookup of control object. */
    if (IS_CTL_NAME(dvp, nm, len)) {
	*vpp = cfs_ctlvp;
	vref(*vpp);
	MARK_INT_SAT(CFS_LOOKUP_STATS);
	if (scp) vrele(dvp);
	goto exit;
    }

    if (len+1 > CFS_MAXNAMLEN) {
	MARK_INT_FAIL(CFS_LOOKUP_STATS);
	CFSDEBUG(CFS_LOOKUP, myprintf(("name too long: lookup, %lx.%lx.%lx(%s)\n",
				    dcp->c_fid.Volume, dcp->c_fid.Vnode,
				    dcp->c_fid.Unique, nm)););
	*vpp = (struct vnode *)0;
	error = EINVAL;
	goto exit;
    }
    /* First try to look the file up in the cfs name cache */
    /* lock the parent vnode? */
    cp = cfsnc_lookup(dcp, nm, len, cred);
    if (cp) {
	*vpp = CTOV(cp);
	vref(*vpp);
	CFSDEBUG(CFS_LOOKUP, 
		 myprintf(("lookup result %d vpp %p\n",error,*vpp));)
    } else {
	
	/* The name wasn't cached, so we need to contact Venus */
	error = venus_lookup(vtomi(dvp), &dcp->c_fid, nm, len, cred, p, &VFid, &vtype);
	
	if (error) {
	    MARK_INT_FAIL(CFS_LOOKUP_STATS);
	    CFSDEBUG(CFS_LOOKUP, myprintf(("lookup error on %lx.%lx.%lx(%s)%d\n",
					dcp->c_fid.Volume, dcp->c_fid.Vnode, dcp->c_fid.Unique, nm, error));)
	    *vpp = (struct vnode *)0;
	} else {
	    MARK_INT_SAT(CFS_LOOKUP_STATS);
	    CFSDEBUG(CFS_LOOKUP, 
		     myprintf(("lookup: vol %lx vno %lx uni %lx type %o result %d\n",
			    VFid.Volume, VFid.Vnode, VFid.Unique, vtype,
			    error)); )
		
	    cp = makecfsnode(&VFid, dvp->v_mount, vtype);
	    *vpp = CTOV(cp);
	    
	    /* enter the new vnode in the Name Cache only if the top bit isn't set */
	    /* And don't enter a new vnode for an invalid one! */
	    if (!(vtype & CFS_NOCACHE) && scp == 0)
		cfsnc_enter(VTOC(dvp), nm, len, cred, VTOC(*vpp));
	}
    }

 exit:
    if (scp) vrele(dvp);
    /* 
     * If we are creating, and this was the last name to be looked up,
     * and the error was ENOENT, then there really shouldn't be an
     * error and we can make the leaf NULL and return success.  Since
     * this is supposed to work under Mach as well as NetBSD, we're
     * leaving this fn wrapped.  We also must tell lookup/namei that
     * we need to save the last component of the name.  (Create will
     * have to free the name buffer later...lucky us...)
     */
    if (((cnp->cn_nameiop == CREATE) || (cnp->cn_nameiop == RENAME))
	&& (cnp->cn_flags & ISLASTCN)
	&& (error == ENOENT))
    {
	error = EJUSTRETURN;
	cnp->cn_flags |= SAVENAME;
	*ap->a_vpp = NULL;
    }

    /* 
     * If we are removing, and we are at the last element, and we
     * found it, then we need to keep the name around so that the
     * removal will go ahead as planned.  Unfortunately, this will
     * probably also lock the to-be-removed vnode, which may or may
     * not be a good idea.  I'll have to look at the bits of
     * cfs_remove to make sure.  We'll only save the name if we did in
     * fact find the name, otherwise cfs_remove won't have a chance
     * to free the pathname.  
     */
    if ((cnp->cn_nameiop == DELETE)
	&& (cnp->cn_flags & ISLASTCN)
	&& !error)
    {
	cnp->cn_flags |= SAVENAME;
    }

    /* 
     * If the lookup went well, we need to (potentially?) unlock the
     * parent, and lock the child.  We are only responsible for
     * checking to see if the parent is supposed to be unlocked before
     * we return.  We must always lock the child (provided there is
     * one, and (the parent isn't locked or it isn't the same as the
     * parent.)  Simple, huh?  We can never leave the parent locked unless
     * we are ISLASTCN
     */
    if (!error || (error == EJUSTRETURN)) {
	if (!(cnp->cn_flags & LOCKPARENT) || !(cnp->cn_flags & ISLASTCN)) {
	    if ((error = VOP_X_UNLOCK(dvp, 0))) {
		return error; 
	    }	    
	    /* 
	     * The parent is unlocked.  As long as there is a child,
	     * lock it without bothering to check anything else. 
	     */
	    if (*ap->a_vpp) {
		if ((error = VOP_X_LOCK(*ap->a_vpp, LK_EXCLUSIVE))) {
		    printf("cfs_lookup: ");
		    panic("unlocked parent but couldn't lock child");
		}
	    }
	} else {
	    /* The parent is locked, and may be the same as the child */
	    if (*ap->a_vpp && (*ap->a_vpp != dvp)) {
		/* Different, go ahead and lock it. */
		if ((error = VOP_X_LOCK(*ap->a_vpp, LK_EXCLUSIVE))) {
		    printf("cfs_lookup: ");
		    panic("unlocked parent but couldn't lock child");
		}
	    }
	}
    } else {
	/* If the lookup failed, we need to ensure that the leaf is NULL */
	/* Don't change any locking? */
	*ap->a_vpp = NULL;
    }
    return(error);
}

/*ARGSUSED*/
int
cfs_create(v)
    void *v;
{
/* true args */
    struct vop_create_args *ap = v;
    struct vnode *dvp = ap->a_dvp;
    struct cnode *dcp = VTOC(dvp);
    struct vattr *va = ap->a_vap;
    int exclusive = 1;
    int mode = ap->a_vap->va_mode;
    struct vnode **vpp = ap->a_vpp;
    struct componentname  *cnp = ap->a_cnp;
    struct ucred *cred = cnp->cn_cred;
    struct proc *p = cnp->cn_proc;
/* locals */
    int error;
    struct cnode *cp;
    const char *nm = cnp->cn_nameptr;
    int len = cnp->cn_namelen;
    ViceFid VFid;
    struct vattr attr;

    MARK_ENTRY(CFS_CREATE_STATS);

    /* All creates are exclusive XXX */
    /* I'm assuming the 'mode' argument is the file mode bits XXX */

    /* Check for create of control object. */
    if (IS_CTL_NAME(dvp, nm, len)) {
	*vpp = (struct vnode *)0;
	MARK_INT_FAIL(CFS_CREATE_STATS);
	return(EACCES);
    }

    error = venus_create(vtomi(dvp), &dcp->c_fid, nm, len, exclusive, mode, va, cred, p, &VFid, &attr);

    if (!error) {
	
	/* If this is an exclusive create, panic if the file already exists. */
	/* Venus should have detected the file and reported EEXIST. */

	if ((exclusive == 1) &&
	    (cfs_find(&VFid) != NULL))
	    panic("cnode existed for newly created file!");
	
	cp = makecfsnode(&VFid, dvp->v_mount, attr.va_type);
	*vpp = CTOV(cp);
	
	/* Update va to reflect the new attributes. */
	(*va) = attr;
	
	/* Update the attribute cache and mark it as valid */
	if (cfs_attr_cache) {
	    VTOC(*vpp)->c_vattr = attr;
	    VTOC(*vpp)->c_flags |= C_VATTR;       
	}

	/* Invalidate the parent's attr cache, the modification time has changed */
	VTOC(dvp)->c_flags &= ~C_VATTR;
	
	/* enter the new vnode in the Name Cache */
	cfsnc_enter(VTOC(dvp), nm, len, cred, VTOC(*vpp));
	
	CFSDEBUG(CFS_CREATE, 
		 myprintf(("create: (%lx.%lx.%lx), result %d\n",
			VFid.Volume, VFid.Vnode, VFid.Unique, error)); )
    } else {
	*vpp = (struct vnode *)0;
	CFSDEBUG(CFS_CREATE, myprintf(("create error %d\n", error));)
    }

    /* Locking strategy. */
    /*
     * In NetBSD, all creates must explicitly vput their dvp's.  We'll
     * go ahead and use the LOCKLEAF flag of the cnp argument.
     * However, I'm pretty sure that create must return the leaf
     * locked; so there is a DIAGNOSTIC check to ensure that this is
     * true.
     */
#ifdef	__FreeBSD_version
    /*
     * Well, FreeBSD -current does the vput put in
     * kern/vfs_vnops.c.c:vn_open()
     */
#else
    vput(dvp);
#endif
    if (!error) {
	if (cnp->cn_flags & LOCKLEAF) {
	    if ((error = VOP_X_LOCK(*ap->a_vpp, LK_EXCLUSIVE))) {
		printf("cfs_create: ");
		panic("unlocked parent but couldn't lock child");
	    }
	}
#ifdef DIAGNOSTIC
	else {
	    printf("cfs_create: LOCKLEAF not set!\n");
	}
#endif /* DIAGNOSTIC */
    }
    /* Have to free the previously saved name */
    /* 
     * This condition is stolen from ufs_makeinode.  I have no idea
     * why it's here, but what the hey...
     */
    if ((cnp->cn_flags & SAVESTART) == 0) {
	NAMEI_FREE(cnp->cn_pnbuf);
    }
    return(error);
}

int
cfs_remove(v)
    void *v;
{
/* true args */
    struct vop_remove_args *ap = v;
    struct vnode *dvp = ap->a_dvp;
    struct cnode *cp = VTOC(dvp);
    struct componentname  *cnp = ap->a_cnp;
    struct ucred *cred = cnp->cn_cred;
    struct proc *p = cnp->cn_proc;
/* locals */
    int error;
    const char *nm = cnp->cn_nameptr;
    int len = cnp->cn_namelen;
    struct cnode *tp;

    MARK_ENTRY(CFS_REMOVE_STATS);

    CFSDEBUG(CFS_REMOVE, myprintf(("remove: %s in %lx.%lx.%lx\n",
				   nm, cp->c_fid.Volume, cp->c_fid.Vnode,
				   cp->c_fid.Unique)););

    /* Remove the file's entry from the CFS Name Cache */
    /* We're being conservative here, it might be that this person
     * doesn't really have sufficient access to delete the file
     * but we feel zapping the entry won't really hurt anyone -- dcs
     */
    /* I'm gonna go out on a limb here. If a file and a hardlink to it
     * exist, and one is removed, the link count on the other will be
     * off by 1. We could either invalidate the attrs if cached, or
     * fix them. I'll try to fix them. DCS 11/8/94
     */
    tp = cfsnc_lookup(VTOC(dvp), nm, len, cred);
    if (tp) {
	if (VALID_VATTR(tp)) {	/* If attrs are cached */
	    if (tp->c_vattr.va_nlink > 1) {	/* If it's a hard link */
		tp->c_vattr.va_nlink--;
	    }
	}
	
	cfsnc_zapfile(VTOC(dvp), nm, len); 
	/* No need to flush it if it doesn't exist! */
    }
    /* Invalidate the parent's attr cache, the modification time has changed */
    VTOC(dvp)->c_flags &= ~C_VATTR;

    /* Check for remove of control object. */
    if (IS_CTL_NAME(dvp, nm, len)) {
	MARK_INT_FAIL(CFS_REMOVE_STATS);
	return(ENOENT);
    }

    error = venus_remove(vtomi(dvp), &cp->c_fid, nm, len, cred, p);

    CFSDEBUG(CFS_REMOVE, myprintf(("in remove result %d\n",error)); )

#ifdef	__FreeBSD_version
    /*
     * Well, FreeBSD -current does the vrele/vput put in
     * kern/vfs_syscalls.c:unlink()
     */
#else
    /* 
     * Regardless of what happens, we have to unconditionally drop
     * locks/refs on parent and child.  (I hope).  This is based on
     * what ufs_remove seems to be doing.
     */
    if (dvp == ap->a_vp) {
	vrele(ap->a_vp);
    } else {
	vput(ap->a_vp);
    }
    vput(dvp);
#endif

    if ((cnp->cn_flags & SAVESTART) == 0) {
	NAMEI_FREE(cnp->cn_pnbuf);
    }
    return(error);
}

int
cfs_link(v)
    void *v;
{
/* true args */
    struct vop_link_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
#ifdef	__NetBSD__
    struct vnode *tdvp = ap->a_dvp;
#elif	defined(__FreeBSD__)
    struct vnode *tdvp = ap->a_tdvp;
#endif
    struct cnode *tdcp = VTOC(tdvp);
    struct componentname *cnp = ap->a_cnp;
    struct ucred *cred = cnp->cn_cred;
    struct proc *p = cnp->cn_proc;
/* locals */
    int error;
    const char *nm = cnp->cn_nameptr;
    int len = cnp->cn_namelen;

    MARK_ENTRY(CFS_LINK_STATS);

    if (cfsdebug & CFSDBGMSK(CFS_LINK)) {

	myprintf(("nb_link:   vp fid: (%lx.%lx.%lx)\n",
		  cp->c_fid.Volume, cp->c_fid.Vnode, cp->c_fid.Unique));
	myprintf(("nb_link: tdvp fid: (%lx.%lx.%lx)\n",
		  tdcp->c_fid.Volume, tdcp->c_fid.Vnode, tdcp->c_fid.Unique));
	
    }
    if (cfsdebug & CFSDBGMSK(CFS_LINK)) {
	myprintf(("link:   vp fid: (%lx.%lx.%lx)\n",
		  cp->c_fid.Volume, cp->c_fid.Vnode, cp->c_fid.Unique));
	myprintf(("link: tdvp fid: (%lx.%lx.%lx)\n",
		  tdcp->c_fid.Volume, tdcp->c_fid.Vnode, tdcp->c_fid.Unique));

    }

    /* Check for link to/from control object. */
    if (IS_CTL_NAME(tdvp, nm, len) || IS_CTL_VP(vp)) {
	MARK_INT_FAIL(CFS_LINK_STATS);
	return(EACCES);
    }

    /*
     * According to the ufs_link operation here's the locking situation:
     *     We enter with the thing called "dvp" (the directory) locked.
     *     We must unconditionally drop locks on "dvp"
     *
     *     We enter with the thing called "vp" (the linked-to) unlocked,
     *       but ref'd (?)
     *     We seem to need to lock it before calling cfs_link, and
     *       unconditionally unlock it after.
     */

#ifdef	__FreeBSD_version
    /*
     * Well, FreeBSD -current does the vrele/vput put in
     * kern/vfs_syscalls.c:link()
     */
#else
    if ((ap->a_vp != tdvp) && (error = VOP_X_LOCK(ap->a_vp, LK_EXCLUSIVE))) {
	goto exit;
    }
#endif
	
    error = venus_link(vtomi(vp), &cp->c_fid, &tdcp->c_fid, nm, len, cred, p);

    /* Invalidate the parent's attr cache, the modification time has changed */
    VTOC(tdvp)->c_flags &= ~C_VATTR;
    VTOC(vp)->c_flags &= ~C_VATTR;

    CFSDEBUG(CFS_LINK,	myprintf(("in link result %d\n",error)); )

exit:

#ifdef	__FreeBSD_version
    /*
     * Well, FreeBSD -current does the vrele/vput put in
     * kern/vfs_syscalls.c:link()
     */
#else
    if (ap->a_vp != tdvp) {
	VOP_X_UNLOCK(ap->a_vp, 0);
    }
    vput(tdvp);
#endif

    /* Drop the name buffer if we don't need to SAVESTART */
    if ((cnp->cn_flags & SAVESTART) == 0) {
	NAMEI_FREE(cnp->cn_pnbuf);
    }
    return(error);
}

int
cfs_rename(v)
    void *v;
{
/* true args */
    struct vop_rename_args *ap = v;
    struct vnode *odvp = ap->a_fdvp;
    struct cnode *odcp = VTOC(odvp);
    struct componentname  *fcnp = ap->a_fcnp;
    struct vnode *ndvp = ap->a_tdvp;
    struct cnode *ndcp = VTOC(ndvp);
    struct componentname  *tcnp = ap->a_tcnp;
    struct ucred *cred = fcnp->cn_cred;
    struct proc *p = fcnp->cn_proc;
/* true args */
    int error;
    const char *fnm = fcnp->cn_nameptr;
    int flen = fcnp->cn_namelen;
    const char *tnm = tcnp->cn_nameptr;
    int tlen = tcnp->cn_namelen;

    MARK_ENTRY(CFS_RENAME_STATS);

    /* Hmmm.  The vnodes are already looked up.  Perhaps they are locked?
       This could be Bad. XXX */
#ifdef DIAGNOSTIC
    if ((fcnp->cn_cred != tcnp->cn_cred)
	|| (fcnp->cn_proc != tcnp->cn_proc))
    {
	panic("cfs_rename: component names don't agree");
    }
#endif DIAGNOSTIC

    /* Check for rename involving control object. */ 
    if (IS_CTL_NAME(odvp, fnm, flen) || IS_CTL_NAME(ndvp, tnm, tlen)) {
	MARK_INT_FAIL(CFS_RENAME_STATS);
	return(EACCES);
    }

    /* Problem with moving directories -- need to flush entry for .. */
    if (odvp != ndvp) {
	struct cnode *ovcp = cfsnc_lookup(VTOC(odvp), fnm, flen, cred);
	if (ovcp) {
	    struct vnode *ovp = CTOV(ovcp);
	    if ((ovp) &&
		(ovp->v_type == VDIR)) /* If it's a directory */
		cfsnc_zapfile(VTOC(ovp),"..", 2);
	}
    }

    /* Remove the entries for both source and target files */
    cfsnc_zapfile(VTOC(odvp), fnm, flen);
    cfsnc_zapfile(VTOC(ndvp), tnm, tlen);

    /* Invalidate the parent's attr cache, the modification time has changed */
    VTOC(odvp)->c_flags &= ~C_VATTR;
    VTOC(ndvp)->c_flags &= ~C_VATTR;

    if (flen+1 > CFS_MAXNAMLEN) {
	MARK_INT_FAIL(CFS_RENAME_STATS);
	error = EINVAL;
	goto exit;
    }

    if (tlen+1 > CFS_MAXNAMLEN) {
	MARK_INT_FAIL(CFS_RENAME_STATS);
	error = EINVAL;
	goto exit;
    }

    error = venus_rename(vtomi(odvp), &odcp->c_fid, &ndcp->c_fid, fnm, flen, tnm, tlen, cred, p);

 exit:
    CFSDEBUG(CFS_RENAME, myprintf(("in rename result %d\n",error));)
    /* XXX - do we need to call cache pureg on the moved vnode? */
    cache_purge(ap->a_fvp);

    /* It seems to be incumbent on us to drop locks on all four vnodes */
    /* From-vnodes are not locked, only ref'd.  To-vnodes are locked. */

    vrele(ap->a_fvp);
    vrele(odvp);

    if (ap->a_tvp) {
	if (ap->a_tvp == ndvp) {
	    vrele(ap->a_tvp);
	} else {
	    vput(ap->a_tvp);
	}
    }

    vput(ndvp);
    return(error);
}

int
cfs_mkdir(v)
    void *v;
{
/* true args */
    struct vop_mkdir_args *ap = v;
    struct vnode *dvp = ap->a_dvp;
    struct cnode *dcp = VTOC(dvp);	
    struct componentname  *cnp = ap->a_cnp;
    register struct vattr *va = ap->a_vap;
    struct vnode **vpp = ap->a_vpp;
    struct ucred *cred = cnp->cn_cred;
    struct proc *p = cnp->cn_proc;
/* locals */
    int error;
    const char *nm = cnp->cn_nameptr;
    int len = cnp->cn_namelen;
    struct cnode *cp;
    ViceFid VFid;
    struct vattr ova;

    MARK_ENTRY(CFS_MKDIR_STATS);

    /* Check for mkdir of target object. */
    if (IS_CTL_NAME(dvp, nm, len)) {
	*vpp = (struct vnode *)0;
	MARK_INT_FAIL(CFS_MKDIR_STATS);
	return(EACCES);
    }

    if (len+1 > CFS_MAXNAMLEN) {
	*vpp = (struct vnode *)0;
	MARK_INT_FAIL(CFS_MKDIR_STATS);
	return(EACCES);
    }

    error = venus_mkdir(vtomi(dvp), &dcp->c_fid, nm, len, va, cred, p, &VFid, &ova);

    if (!error) {
	if (cfs_find(&VFid) != NULL)
	    panic("cnode existed for newly created directory!");
	
	
	cp =  makecfsnode(&VFid, dvp->v_mount, va->va_type);
	*vpp = CTOV(cp);
	
	/* enter the new vnode in the Name Cache */
	cfsnc_enter(VTOC(dvp), nm, len, cred, VTOC(*vpp));

	/* as a side effect, enter "." and ".." for the directory */
	cfsnc_enter(VTOC(*vpp), ".", 1, cred, VTOC(*vpp));
	cfsnc_enter(VTOC(*vpp), "..", 2, cred, VTOC(dvp));

	if (cfs_attr_cache) {
	    VTOC(*vpp)->c_vattr = ova;		/* update the attr cache */
	    VTOC(*vpp)->c_flags |= C_VATTR;	/* Valid attributes in cnode */
	}

	/* Invalidate the parent's attr cache, the modification time has changed */
	VTOC(dvp)->c_flags &= ~C_VATTR;
	
	CFSDEBUG( CFS_MKDIR, myprintf(("mkdir: (%lx.%lx.%lx) result %d\n",
				    VFid.Volume, VFid.Vnode, VFid.Unique, error)); )
    } else {
	*vpp = (struct vnode *)0;
	CFSDEBUG(CFS_MKDIR, myprintf(("mkdir error %d\n",error));)
    }

    /*
     * Currently, all mkdirs explicitly vput their dvp's.
     * It also appears that we *must* lock the vpp, since
     * lockleaf isn't set, but someone down the road is going
     * to try to unlock the new directory.
     */
#ifdef	__FreeBSD_version
    /*
     * Well, FreeBSD -current does the vrele/vput put in
     * kern/vfs_syscalls.c:mkdir()
     */
#else
    vput(dvp);
    if (!error) {
	if ((error = VOP_X_LOCK(*ap->a_vpp, LK_EXCLUSIVE))) {
	    panic("cfs_mkdir: couldn't lock child");
	}
    }
#endif

    /* Have to free the previously saved name */
    /* 
     * ufs_mkdir doesn't check for SAVESTART before freeing the
     * pathname buffer, but ufs_create does.  For the moment, I'll
     * follow their lead, but this seems like it is probably
     * incorrect.  
     */
    NAMEI_FREE(cnp->cn_pnbuf);
    return(error);
}

int
cfs_rmdir(v)
    void *v;
{
/* true args */
    struct vop_rmdir_args *ap = v;
    struct vnode *dvp = ap->a_dvp;
    struct cnode *dcp = VTOC(dvp);
    struct componentname  *cnp = ap->a_cnp;
    struct ucred *cred = cnp->cn_cred;
    struct proc *p = cnp->cn_proc;
/* true args */
    int error;
    const char *nm = cnp->cn_nameptr;
    int len = cnp->cn_namelen;
    struct cnode *cp;
   
    MARK_ENTRY(CFS_RMDIR_STATS);

    /* Check for rmdir of control object. */
    if (IS_CTL_NAME(dvp, nm, len)) {
	MARK_INT_FAIL(CFS_RMDIR_STATS);
	return(ENOENT);
    }

    /* We're being conservative here, it might be that this person
     * doesn't really have sufficient access to delete the file
     * but we feel zapping the entry won't really hurt anyone -- dcs
     */
    /*
     * As a side effect of the rmdir, remove any entries for children of
     * the directory, especially "." and "..".
     */
    cp = cfsnc_lookup(dcp, nm, len, cred);
    if (cp) cfsnc_zapParentfid(&(cp->c_fid), NOT_DOWNCALL);

    /* Remove the file's entry from the CFS Name Cache */
    cfsnc_zapfile(dcp, nm, len);

    /* Invalidate the parent's attr cache, the modification time has changed */
    dcp->c_flags &= ~C_VATTR;

    error = venus_rmdir(vtomi(dvp), &dcp->c_fid, nm, len, cred, p);

    CFSDEBUG(CFS_RMDIR, myprintf(("in rmdir result %d\n", error)); )

#ifdef	__FreeBSD_version
    /*
     * Well, FreeBSD -current does the vrele/vput put in
     * kern/vfs_syscalls.c:rmdir()
     */
#else
    /*
     * regardless of what happens, we need to drop locks/refs on the 
     * parent and child.  I think. 
     */
    if (dvp == ap->a_vp) {
	vrele(ap->a_vp);
    } else {
	vput(ap->a_vp);
    }
    vput(dvp);
#endif

    if ((cnp->cn_flags & SAVESTART) == 0) {
	NAMEI_FREE(cnp->cn_pnbuf);
    }
    return(error);
}

int
cfs_symlink(v)
    void *v;
{
/* true args */
    struct vop_symlink_args *ap = v;
    struct vnode *tdvp = ap->a_dvp;
    struct cnode *tdcp = VTOC(tdvp);	
    struct componentname *cnp = ap->a_cnp;
    struct vattr *tva = ap->a_vap;
    char *path = ap->a_target;
    struct ucred *cred = cnp->cn_cred;
    struct proc *p = cnp->cn_proc;
/* locals */
    int error;
    /* 
     * XXX I'm assuming the following things about cfs_symlink's
     * arguments: 
     *       t(foo) is the new name/parent/etc being created.
     *       lname is the contents of the new symlink. 
     */
#ifdef	NetBSD1_3
    const 
#endif
          char *nm = cnp->cn_nameptr;
    int len = cnp->cn_namelen;
    int plen = strlen(path);

    /* XXX What about the vpp argument?  Do we need it? */
    /* 
     * Here's the strategy for the moment: perform the symlink, then
     * do a lookup to grab the resulting vnode.  I know this requires
     * two communications with Venus for a new sybolic link, but
     * that's the way the ball bounces.  I don't yet want to change
     * the way the Mach symlink works.  When Mach support is
     * deprecated, we should change symlink so that the common case
     * returns the resultant vnode in a vpp argument.
     */

    MARK_ENTRY(CFS_SYMLINK_STATS);

    /* Check for symlink of control object. */
    if (IS_CTL_NAME(tdvp, nm, len)) {
	MARK_INT_FAIL(CFS_SYMLINK_STATS);
	return(EACCES);
    }

    if (plen+1 > CFS_MAXPATHLEN) {
	MARK_INT_FAIL(CFS_SYMLINK_STATS);
	return(EINVAL);
    }

    if (len+1 > CFS_MAXNAMLEN) {
	MARK_INT_FAIL(CFS_SYMLINK_STATS);
	error = EINVAL;
	goto exit;
    }

    error = venus_symlink(vtomi(tdvp), &tdcp->c_fid, path, plen, nm, len, tva, cred, p);

    /* Invalidate the parent's attr cache, the modification time has changed */
    tdcp->c_flags &= ~C_VATTR;

#ifdef	__FreeBSD_version

#else
    if (!error)
    {
	struct nameidata nd;
	NDINIT(&nd, LOOKUP, FOLLOW|LOCKLEAF, UIO_SYSSPACE, nm, p);
	nd.ni_cnd.cn_cred = cred;
	nd.ni_loopcnt = 0;
	nd.ni_startdir = tdvp;
	nd.ni_cnd.cn_pnbuf = (char *)nm;
	nd.ni_cnd.cn_nameptr = nd.ni_cnd.cn_pnbuf;
	nd.ni_pathlen = len;
	vput(tdvp);
	error = lookup(&nd);
	*ap->a_vpp = nd.ni_vp;
    }

    /* 
     * Okay, now we have to drop locks on dvp.  vpp is unlocked, but
     * ref'd.  It doesn't matter what happens in either symlink or
     * lookup.  Furthermore, there isn't any way for (dvp == *vpp), so
     * we don't bother checking.  
     */
/*  vput(ap->a_dvp);		released earlier */
    if (*ap->a_vpp) {
    	VOP_X_UNLOCK(*ap->a_vpp, 0);	/* this line is new!! It is necessary because lookup() calls
				   VOP_LOOKUP (cfs_lookup) which returns vpp locked.  cfs_nb_lookup
				   merged with cfs_lookup() to become cfs_lookup so UNLOCK is
				   necessary */
    	vrele(*ap->a_vpp);
    }
#endif

    /* 
     * Free the name buffer 
     */
    if ((cnp->cn_flags & SAVESTART) == 0) {
	NAMEI_FREE(cnp->cn_pnbuf);
    }

 exit:    
    CFSDEBUG(CFS_SYMLINK, myprintf(("in symlink result %d\n",error)); )
    return(error);
}

/*
 * Read directory entries.
 */
int
cfs_readdir(v)
    void *v;
{
/* true args */
    struct vop_readdir_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
    register struct uio *uiop = ap->a_uio;
    struct ucred *cred = ap->a_cred;
    int *eofflag = ap->a_eofflag;
#if	defined(__NetBSD__) && defined(NetBSD1_3) && (NetBSD1_3 >= 7)
    off_t **cookies = ap->a_cookies;
    int *ncookies = ap->a_ncookies;
#elif	defined(NetBSD1_3)
    off_t *cookies = ap->a_cookies;
    int ncookies = ap->a_ncookies;
#elif	NetBSD1_2
    u_long *cookies = ap->a_cookies;
    int ncookies = ap->a_ncookies;
#elif	defined(__FreeBSD__) && defined(__FreeBSD_version)
    u_long **cookies = ap->a_cookies;
    int *ncookies = ap->a_ncookies;
#elif	defined(__FreeBSD__)
    u_int **cookies = ap->a_cookies;
    int *ncookies = ap->a_ncookies;
#endif
    struct proc *p = ap->a_uio->uio_procp;
/* upcall decl */
/* locals */
    int error = 0;

    MARK_ENTRY(CFS_READDIR_STATS);

    CFSDEBUG(CFS_READDIR, myprintf(("cfs_readdir(%p, %d, %qd, %d)\n", uiop->uio_iov->iov_base, uiop->uio_resid, uiop->uio_offset, uiop->uio_segflg)); )
	
    /* Check for readdir of control object. */
    if (IS_CTL_VP(vp)) {
	MARK_INT_FAIL(CFS_READDIR_STATS);
	return(ENOENT);
    }

    if (cfs_intercept_rdwr) {
	/* Redirect the request to UFS. */
	
	/* If directory is not already open do an "internal open" on it. */
	int opened_internally = 0;
	if (cp->c_ovp == NULL) {
	    opened_internally = 1;
	    MARK_INT_GEN(CFS_OPEN_STATS);
	    error = VOP_OPEN(vp, FREAD, cred, p);
printf("cfs_readdir: Internally Opening %p\n", vp);
#ifdef	__FreeBSD__
	    if (error) {
		printf("cfs_readdir: VOP_OPEN on container failed %d\n", error);
		return (error);
	    }
	    if (vp->v_type == VREG) {
		error = vfs_object_create(vp, p, cred, 1);
		if (error != 0) {
		    printf("cfs_readdir: vfs_object_create() returns %d\n", error);
		    vput(vp);
		}
	    }
#endif
	    if (error) return(error);
	}
	
	/* Have UFS handle the call. */
	CFSDEBUG(CFS_READDIR, myprintf(("indirect readdir: fid = (%lx.%lx.%lx), refcnt = %d\n",cp->c_fid.Volume, cp->c_fid.Vnode, cp->c_fid.Unique, vp->v_usecount)); )
#ifdef	__NetBSD__
	error = VOP_READDIR(cp->c_ovp, uiop, cred, eofflag, cookies,
			       ncookies);
#elif	defined(__FreeBSD__)
	error = VOP_READDIR(cp->c_ovp, uiop, cred, eofflag, ncookies,
			       cookies);
#endif
	
	if (error)
	    MARK_INT_FAIL(CFS_READDIR_STATS);
	else
	    MARK_INT_SAT(CFS_READDIR_STATS);
	
	/* Do an "internal close" if necessary. */ 
	if (opened_internally) {
	    MARK_INT_GEN(CFS_CLOSE_STATS);
	    (void)VOP_CLOSE(vp, FREAD, cred, p);
	}
    }
    else {
	/* Read the block from Venus. */
	struct iovec *iovp = uiop->uio_iov;
	unsigned count = iovp->iov_len;
	int size;
	
	
	/* Make the count a multiple of DIRBLKSIZ (borrowed from ufs_readdir). */	
#define DIRBLKSIZ DEV_BSIZE
	if ((uiop->uio_iovcnt != 1) || (count < DIRBLKSIZ) ||
	    (uiop->uio_offset & (DIRBLKSIZ - 1)))
	    return (EINVAL);
	count &= ~(DIRBLKSIZ - 1);
	uiop->uio_resid -= iovp->iov_len - count;
	iovp->iov_len = count;
	if (count > VC_MAXDATASIZE)
	    return(EINVAL);
	
	
	error = venus_readdir(vtomi(CTOV(cp)), &cp->c_fid, count, uiop->uio_offset, cred, p, iovp->iov_base, &size);
	
	CFSDEBUG(CFS_READDIR,
		 myprintf(("cfs_readdir(%p, %d, %qd, %d) returns (%d, %d)\n",
			iovp->iov_base, count,
			uiop->uio_offset, uiop->uio_segflg, error,
			size)); )	
	if (!error) {
	    iovp->iov_base += size;
	    iovp->iov_len -= size;
	    uiop->uio_resid -= size;
	    uiop->uio_offset += size;
	}
    }

    return(error);
}

/*
 * Convert from file system blocks to device blocks
 */
int
cfs_bmap(v)
    void *v;
{
    /* XXX on the global proc */
/* true args */
    struct vop_bmap_args *ap = v;
    struct vnode *vp __attribute__((unused)) = ap->a_vp;	/* file's vnode */
    daddr_t bn __attribute__((unused)) = ap->a_bn;	/* fs block number */
    struct vnode **vpp = ap->a_vpp;			/* RETURN vp of device */
    daddr_t *bnp __attribute__((unused)) = ap->a_bnp;	/* RETURN device block number */
    struct proc *p __attribute__((unused)) = curproc;
/* upcall decl */
/* locals */

#ifdef	__FreeBSD__
#ifdef	__FreeBSD_version
	int ret = 0;
	struct cnode *cp;

	cp = VTOC(vp);
	if (cp->c_ovp) {
		printf("cfs_bmap: container .. ");
		ret =  VOP_BMAP(cp->c_ovp, bn, vpp, bnp, ap->a_runp, ap->a_runb);
		printf("VOP_BMAP(cp->c_ovp %p, bn %p, vpp %p, bnp %p, ap->a_runp %p, ap->a_runb %p) = %d\n",
			cp->c_ovp, bn, vpp, bnp, ap->a_runp, ap->a_runb, ret);
		return ret;
	} else {
		printf("cfs_bmap: no container\n");
		return(EOPNOTSUPP);
	}
#else
        /* Just like nfs_bmap(). Do not touch *vpp, this cause pfault. */
	return(EOPNOTSUPP);
#endif
#else	/* !FreeBSD */
	*vpp = (struct vnode *)0;
	myprintf(("cfs_bmap called!\n"));
	return(EINVAL);
#endif
}

/*
 * I don't think the following two things are used anywhere, so I've
 * commented them out 
 * 
 * struct buf *async_bufhead; 
 * int async_daemon_count;
 */
int
cfs_strategy(v)
    void *v;
{
/* true args */
    struct vop_strategy_args *ap = v;
    register struct buf *bp __attribute__((unused)) = ap->a_bp;
    struct proc *p __attribute__((unused)) = curproc;
/* upcall decl */
/* locals */

#ifdef	__FreeBSD__
#ifdef	__FreeBSD_version
	printf("cfs_strategy: called ???\n");
	return(EOPNOTSUPP);
#else	/* ! __MAYBE_FreeBSD__ */
	myprintf(("cfs_strategy called!  "));
	return(EOPNOTSUPP);
#endif	/* __MAYBE_FreeBSD__ */
#else	/* ! __FreeBSD__ */
	myprintf(("cfs_strategy called!  "));
	return(EINVAL);
#endif	/* __FreeBSD__ */
}

int
cfs_reclaim(v) 
    void *v;
{
/* true args */
    struct vop_reclaim_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
/* upcall decl */
/* locals */

/*
 * Forced unmount/flush will let vnodes with non zero use be destroyed!
 */
    ENTRY;

    if (IS_UNMOUNTING(cp)) {
#ifdef	DEBUG
	if (VTOC(vp)->c_ovp) {
	    if (IS_UNMOUNTING(cp))
		printf("cfs_reclaim: c_ovp not void: vp %p, cp %p\n", vp, cp);
	}
#endif
    } else {
#ifdef DIAGNOSTIC
	if (vp->v_usecount != 0) 
	    vprint("cfs_reclaim: pushing active", vp);
	if (VTOC(vp)->c_ovp) {
	    panic("cfs_reclaim: c_ovp not void");
    }
#endif DIAGNOSTIC
    }	
    cache_purge(vp);
    cfs_free(VTOC(vp));
    VTOC(vp) = NULL;
    return (0);
}

#ifdef	NEW_LOCKMGR
int
cfs_lock(v)
    void *v;
{
/* true args */
    struct vop_lock_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
#ifdef	__FreeBSD_version
    struct proc  *p = ap->a_p;
#endif
/* upcall decl */
/* locals */

    ENTRY;

    if (cfs_lockdebug) {
	myprintf(("Attempting lock on %lx.%lx.%lx\n",
		  cp->c_fid.Volume, cp->c_fid.Vnode, cp->c_fid.Unique));
    }

    return (NEW_LOCKMGR(&cp->c_lock, ap->a_flags, &vp->v_interlock));
}

int
cfs_unlock(v)
    void *v;
{
/* true args */
    struct vop_unlock_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp = VTOC(vp);
#ifdef	__FreeBSD_version
    struct proc  *p = ap->a_p;
#endif
/* upcall decl */
/* locals */

    ENTRY;
    if (cfs_lockdebug) {
	myprintf(("Attempting unlock on %lx.%lx.%lx\n",
		  cp->c_fid.Volume, cp->c_fid.Vnode, cp->c_fid.Unique));
    }

    return (NEW_LOCKMGR(&cp->c_lock, ap->a_flags | LK_RELEASE, &vp->v_interlock));
}

int
cfs_islocked(v)
    void *v;
{
/* true args */
    struct vop_islocked_args *ap = v;
    struct cnode *cp = VTOC(ap->a_vp);
    ENTRY;

    return (lockstatus(&cp->c_lock));
}
#else
int
cfs_lock(v)
    void *v;
{
/* true args */
    struct vop_lock_args *ap = v;
    struct vnode *vp = ap->a_vp;
    struct cnode *cp;
    struct proc  *p __attribute__((unused)) = curproc; /* XXX */
/* upcall decl */
/* locals */

    ENTRY;
    cp = VTOC(vp);

    if (cfs_lockdebug) {
	myprintf(("Attempting lock on %lx.%lx.%lx\n",
		  cp->c_fid.Volume, cp->c_fid.Vnode, cp->c_fid.Unique));
    }
start:
    while (vp->v_flag & VXLOCK) {
	vp->v_flag |= VXWANT;
#ifdef	__NetBSD__
	(void) sleep((caddr_t)vp, PINOD);
#elif	defined(__FreeBSD__)
	(void) tsleep((caddr_t)vp, PINOD, "cfs_lock1", 0);
#endif
    }
    if (vp->v_tag == VT_NON)
	return (ENOENT);

    if (cp->c_flags & C_LOCKED) {
	cp->c_flags |= C_WANTED;
#ifdef DIAGNOSTIC
	myprintf(("cfs_lock: lock contention"));
	cfsnc_name(cp);
	myprintf(("\n"));
#endif
#ifdef	__NetBSD__
	(void) sleep((caddr_t)cp, PINOD);
#elif	defined(__FreeBSD__)
	(void) tsleep((caddr_t)cp, PINOD, "cfs_lock2", 0);
#endif
#ifdef DIAGNOSTIC
	myprintf(("cfs_lock: contention resolved\n"));
#endif
	goto start;
    }
    cp->c_flags |= C_LOCKED;
    return (0);
}

int
cfs_unlock(v)
    void *v;
{
/* true args */
    struct vop_unlock_args *ap = v;
    struct cnode *cp = VTOC(ap->a_vp);
/* upcall decl */
/* locals */

    ENTRY;
    if (cfs_lockdebug) {
	myprintf(("Attempting unlock on %lx.%lx.%lx\n",
		  cp->c_fid.Volume, cp->c_fid.Vnode, cp->c_fid.Unique));
    }
#ifdef DIAGNOSTIC
    if ((cp->c_flags & C_LOCKED) == 0) 
	panic("cfs_unlock: not locked");
#endif
    cp->c_flags &= ~C_LOCKED;
    if (cp->c_flags & C_WANTED) {
	cp->c_flags &= ~C_WANTED;
	wakeup((caddr_t)cp);
    }
    return (0);
}

int
cfs_islocked(v)
    void *v;
{
/* true args */
    struct vop_islocked_args *ap = v;

    ENTRY;
    if (VTOC(ap->a_vp)->c_flags & C_LOCKED)
	return (1);
    return (0);
}
#endif

/* How one looks up a vnode given a device/inode pair: */
int
cfs_grab_vnode(dev_t dev, ino_t ino, struct vnode **vpp)
{
    /* This is like VFS_VGET() or igetinode()! */
    int           error;
    struct mount *mp;

    if (!(mp = devtomp(dev))) {
	myprintf(("cfs_grab_vnode: devtomp(%d) returns NULL\n", dev));
	return(ENXIO);
    }

    /* XXX - ensure that nonzero-return means failure */
    error = VFS_VGET(mp,ino,vpp);
    if (error) {
	myprintf(("cfs_grab_vnode: iget/vget(%d, %d) returns %p, err %d\n", 
		  dev, ino, *vpp, error));
	return(ENOENT);
    }
    return(0);
}

void
print_vattr( attr )
	struct vattr *attr;
{
    char *typestr;

    switch (attr->va_type) {
    case VNON:
	typestr = "VNON";
	break;
    case VREG:
	typestr = "VREG";
	break;
    case VDIR:
	typestr = "VDIR";
	break;
    case VBLK:
	typestr = "VBLK";
	break;
    case VCHR:
	typestr = "VCHR";
	break;
    case VLNK:
	typestr = "VLNK";
	break;
    case VSOCK:
	typestr = "VSCK";
	break;
    case VFIFO:
	typestr = "VFFO";
	break;
    case VBAD:
	typestr = "VBAD";
	break;
    default:
	typestr = "????";
	break;
    }


    myprintf(("attr: type %s mode %d uid %d gid %d fsid %d rdev %d\n",
	      typestr, (int)attr->va_mode, (int)attr->va_uid,
	      (int)attr->va_gid, (int)attr->va_fsid, (int)attr->va_rdev));

    myprintf(("      fileid %d nlink %d size %d blocksize %d bytes %d\n",
	      (int)attr->va_fileid, (int)attr->va_nlink, 
	      (int)attr->va_size,
	      (int)attr->va_blocksize,(int)attr->va_bytes));
    myprintf(("      gen %ld flags %ld vaflags %d\n",
	      attr->va_gen, attr->va_flags, attr->va_vaflags));
    myprintf(("      atime sec %d nsec %d\n",
	      (int)attr->va_atime.tv_sec, (int)attr->va_atime.tv_nsec));
    myprintf(("      mtime sec %d nsec %d\n",
	      (int)attr->va_mtime.tv_sec, (int)attr->va_mtime.tv_nsec));
    myprintf(("      ctime sec %d nsec %d\n",
	      (int)attr->va_ctime.tv_sec, (int)attr->va_ctime.tv_nsec));
}

/* How to print a ucred */
void
print_cred(cred)
	struct ucred *cred;
{

	int i;

	myprintf(("ref %d\tuid %d\n",cred->cr_ref,cred->cr_uid));

	for (i=0; i < cred->cr_ngroups; i++)
		myprintf(("\tgroup %d: (%d)\n",i,cred->cr_groups[i]));
	myprintf(("\n"));

}

/*
  -----------------------------------------------------------------------------------
 */

/*
 * Return a vnode for the given fid.
 * If no cnode exists for this fid create one and put it
 * in a table hashed by fid.Volume and fid.Vnode.  If the cnode for
 * this fid is already in the table return it (ref count is
 * incremented by cfs_find.  The cnode will be flushed from the
 * table when cfs_inactive calls cfs_unsave.
 */
struct cnode *
makecfsnode(fid, vfsp, type)
     ViceFid *fid; struct mount *vfsp; short type;
{
    struct cnode *cp;
    int          err;

    if ((cp = cfs_find(fid)) == NULL) {
	struct vnode *vp;
	
	cp = cfs_alloc();
#ifdef	NEW_LOCKMGR
	lockinit(&cp->c_lock, PINOD, "cnode", 0, 0);
#endif
	cp->c_fid = *fid;
	
	err = getnewvnode(VT_CFS, vfsp, cfs_vnodeop_p, &vp);  
	if (err) {                                                
	    panic("cfs: getnewvnode returned error %d\n", err);   
	}                                                         
	vp->v_data = cp;                                          
	vp->v_type = type;                                      
	cp->c_vnode = vp;                                         
	cfs_save(cp);
	
    } else {
	vref(CTOV(cp));
    }

    return cp;
}



#ifdef MACH
/*
 * read a logical block and return it in a buffer */
int
cfs_bread(vp, lbn, bpp)
    struct vnode *vp;
    daddr_t lbn;
    struct buf **bpp; 
{
    myprintf(("cfs_bread called!\n"));
    return(EINVAL);
}

/*
 * release a block returned by cfs_bread
 */
int
cfs_brelse(vp, bp)
    struct vnode *vp;
    struct buf *bp; 
{

    myprintf(("cfs_brelse called!\n"));
    return(EINVAL);
}

int
cfs_badop()
{
	panic("cfs_badop");
}

int
cfs_noop()
{
	return (EINVAL);
}

int
cfs_fid(vp, fidpp)
	struct vnode *vp;
	struct fid **fidpp;
{
	struct cfid *cfid;

	cfid = (struct cfid *)kalloc(sizeof(struct cfid));
	bzero((caddr_t)cfid, sizeof(struct cfid));
	cfid->cfid_len = sizeof(struct cfid) - (sizeof(struct fid) - MAXFIDSZ);
	cfid->cfid_fid = VTOC(vp)->c_fid;
	*fidpp = (struct fid *)cfid;
	return (0);
}

int
cfs_freefid(vp, fidp)
	struct vnode *vp;
	struct fid *fidp;
{
	kfree((struct cfid *)fidp, sizeof(struct cfid));
	return (0);
}

/*
 * Record-locking requests are passed to the local Lock-Manager daemon.
 */
int
cfs_lockctl(vp, ld, cmd, cred)
	struct vnode *vp;
	struct flock *ld;
	int cmd;
	struct ucred *cred;
{ 
	myprintf(("cfs_lockctl called!\n"));
	return(EINVAL);
}

cfs_page_read(vp, buffer, size, offset, cred)
	struct vnode	*vp;
	caddr_t		buffer;
	int		size;
	vm_offset_t	offset;
	struct ucred *cred;
{ 
	struct cnode *cp = VTOC(vp);
	struct uio uio;
	struct iovec iov;
	int error = 0;

	CFSDEBUG(CFS_RDWR, myprintf(("cfs_page_read(%p, %d, %d), fid = (%lx.%lx.%lx), refcnt = %d\n", buffer, size, offset, VTOC(vp)->c_fid.Volume, VTOC(vp)->c_fid.Vnode, VTOC(vp)->c_fid.Unique, vp->v_count)); )

	iov.iov_base = buffer;
	iov.iov_len = size;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = offset;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_resid = size;
	error = cfs_rdwr(vp, &uio, UIO_READ, 0, cred);
	if (error) {
	    myprintf(("error %d on pagein (cfs_rdwr)\n", error));
	    error = EIO;
	}

/*
	if (!error && (cp->states & CWired) == 0)
	    cfs_Wire(cp);
*/

	return(error);
}

cfs_page_write(vp, buffer, size, offset, cred, init)
	struct vnode	*vp;
	caddr_t buffer;
	int size;
	vm_offset_t	offset;
	struct ucred *cred;
	boolean_t init;
{
	struct cnode *cp = VTOC(vp);
	struct uio uio;
	struct iovec iov;
	int error = 0;

	CFSDEBUG(CFS_RDWR, myprintf(("cfs_page_write(%p, %d, %d), fid = (%lx.%lx.%lx), refcnt = %d\n", buffer, size, offset, VTOC(vp)->c_fid.Volume, VTOC(vp)->c_fid.Vnode, VTOC(vp)->c_fid.Unique, vp->v_count)); )

	if (init) {
	    panic("cfs_page_write: called from data_initialize");
	}

	iov.iov_base = buffer;
	iov.iov_len = size;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_offset = offset;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_resid = size;
	error = cfs_rdwr(vp, &uio, UIO_WRITE, 0, cred);
	if (error) {
	    myprintf(("error %d on pageout (cfs_rdwr)\n", error));
	    error = EIO;
	}

	return(error);
}

#endif
