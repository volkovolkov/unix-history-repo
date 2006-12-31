/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 * created from FreeBSD: src/sys/amd64/linux32/syscalls.master,v 1.25 2006/12/31 13:16:00 netchild Exp 
 */

#include <bsm/audit_kevents.h>
#include "opt_compat.h"
#include <sys/param.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>
#include <compat/linux/linux_sysproto.h>
#include <amd64/linux32/linux.h>
#include <amd64/linux32/linux32_proto.h>

#define AS(name) (sizeof(struct name) / sizeof(register_t))

/* The casts are bogus but will do for now. */
struct sysent linux_sysent[] = {
#define	nosys	linux_nosys
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 0 = setup */
	{ AS(sys_exit_args), (sy_call_t *)sys_exit, AUE_EXIT, NULL, 0, 0 },	/* 1 = exit */
	{ 0, (sy_call_t *)linux_fork, AUE_FORK, NULL, 0, 0 },		/* 2 = linux_fork */
	{ AS(read_args), (sy_call_t *)read, AUE_NULL, NULL, 0, 0 },	/* 3 = read */
	{ AS(write_args), (sy_call_t *)write, AUE_NULL, NULL, 0, 0 },	/* 4 = write */
	{ AS(linux_open_args), (sy_call_t *)linux_open, AUE_OPEN_RWTC, NULL, 0, 0 },	/* 5 = linux_open */
	{ AS(close_args), (sy_call_t *)close, AUE_CLOSE, NULL, 0, 0 },	/* 6 = close */
	{ AS(linux_waitpid_args), (sy_call_t *)linux_waitpid, AUE_WAIT4, NULL, 0, 0 },	/* 7 = linux_waitpid */
	{ AS(linux_creat_args), (sy_call_t *)linux_creat, AUE_CREAT, NULL, 0, 0 },	/* 8 = linux_creat */
	{ AS(linux_link_args), (sy_call_t *)linux_link, AUE_LINK, NULL, 0, 0 },	/* 9 = linux_link */
	{ AS(linux_unlink_args), (sy_call_t *)linux_unlink, AUE_UNLINK, NULL, 0, 0 },	/* 10 = linux_unlink */
	{ AS(linux_execve_args), (sy_call_t *)linux_execve, AUE_EXECVE, NULL, 0, 0 },	/* 11 = linux_execve */
	{ AS(linux_chdir_args), (sy_call_t *)linux_chdir, AUE_CHDIR, NULL, 0, 0 },	/* 12 = linux_chdir */
	{ AS(linux_time_args), (sy_call_t *)linux_time, AUE_NULL, NULL, 0, 0 },	/* 13 = linux_time */
	{ AS(linux_mknod_args), (sy_call_t *)linux_mknod, AUE_MKNOD, NULL, 0, 0 },	/* 14 = linux_mknod */
	{ AS(linux_chmod_args), (sy_call_t *)linux_chmod, AUE_CHMOD, NULL, 0, 0 },	/* 15 = linux_chmod */
	{ AS(linux_lchown16_args), (sy_call_t *)linux_lchown16, AUE_LCHOWN, NULL, 0, 0 },	/* 16 = linux_lchown16 */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 17 = break */
	{ AS(linux_stat_args), (sy_call_t *)linux_stat, AUE_STAT, NULL, 0, 0 },	/* 18 = linux_stat */
	{ AS(linux_lseek_args), (sy_call_t *)linux_lseek, AUE_LSEEK, NULL, 0, 0 },	/* 19 = linux_lseek */
	{ 0, (sy_call_t *)linux_getpid, AUE_GETPID, NULL, 0, 0 },	/* 20 = linux_getpid */
	{ AS(linux_mount_args), (sy_call_t *)linux_mount, AUE_MOUNT, NULL, 0, 0 },	/* 21 = linux_mount */
	{ AS(linux_oldumount_args), (sy_call_t *)linux_oldumount, AUE_UMOUNT, NULL, 0, 0 },	/* 22 = linux_oldumount */
	{ AS(linux_setuid16_args), (sy_call_t *)linux_setuid16, AUE_SETUID, NULL, 0, 0 },	/* 23 = linux_setuid16 */
	{ 0, (sy_call_t *)linux_getuid16, AUE_GETUID, NULL, 0, 0 },	/* 24 = linux_getuid16 */
	{ 0, (sy_call_t *)linux_stime, AUE_SETTIMEOFDAY, NULL, 0, 0 },	/* 25 = linux_stime */
	{ AS(linux_ptrace_args), (sy_call_t *)linux_ptrace, AUE_PTRACE, NULL, 0, 0 },	/* 26 = linux_ptrace */
	{ AS(linux_alarm_args), (sy_call_t *)linux_alarm, AUE_NULL, NULL, 0, 0 },	/* 27 = linux_alarm */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 28 = fstat */
	{ 0, (sy_call_t *)linux_pause, AUE_NULL, NULL, 0, 0 },	/* 29 = linux_pause */
	{ AS(linux_utime_args), (sy_call_t *)linux_utime, AUE_UTIME, NULL, 0, 0 },	/* 30 = linux_utime */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 31 = stty */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 32 = gtty */
	{ AS(linux_access_args), (sy_call_t *)linux_access, AUE_ACCESS, NULL, 0, 0 },	/* 33 = linux_access */
	{ AS(linux_nice_args), (sy_call_t *)linux_nice, AUE_NICE, NULL, 0, 0 },	/* 34 = linux_nice */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 35 = ftime */
	{ 0, (sy_call_t *)sync, AUE_SYNC, NULL, 0, 0 },		/* 36 = sync */
	{ AS(linux_kill_args), (sy_call_t *)linux_kill, AUE_KILL, NULL, 0, 0 },	/* 37 = linux_kill */
	{ AS(linux_rename_args), (sy_call_t *)linux_rename, AUE_RENAME, NULL, 0, 0 },	/* 38 = linux_rename */
	{ AS(linux_mkdir_args), (sy_call_t *)linux_mkdir, AUE_MKDIR, NULL, 0, 0 },	/* 39 = linux_mkdir */
	{ AS(linux_rmdir_args), (sy_call_t *)linux_rmdir, AUE_RMDIR, NULL, 0, 0 },	/* 40 = linux_rmdir */
	{ AS(dup_args), (sy_call_t *)dup, AUE_DUP, NULL, 0, 0 },	/* 41 = dup */
	{ AS(linux_pipe_args), (sy_call_t *)linux_pipe, AUE_PIPE, NULL, 0, 0 },	/* 42 = linux_pipe */
	{ AS(linux_times_args), (sy_call_t *)linux_times, AUE_NULL, NULL, 0, 0 },	/* 43 = linux_times */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 44 = prof */
	{ AS(linux_brk_args), (sy_call_t *)linux_brk, AUE_NULL, NULL, 0, 0 },	/* 45 = linux_brk */
	{ AS(linux_setgid16_args), (sy_call_t *)linux_setgid16, AUE_SETGID, NULL, 0, 0 },	/* 46 = linux_setgid16 */
	{ 0, (sy_call_t *)linux_getgid16, AUE_GETGID, NULL, 0, 0 },	/* 47 = linux_getgid16 */
	{ AS(linux_signal_args), (sy_call_t *)linux_signal, AUE_NULL, NULL, 0, 0 },	/* 48 = linux_signal */
	{ 0, (sy_call_t *)linux_geteuid16, AUE_GETEUID, NULL, 0, 0 },	/* 49 = linux_geteuid16 */
	{ 0, (sy_call_t *)linux_getegid16, AUE_GETEGID, NULL, 0, 0 },	/* 50 = linux_getegid16 */
	{ AS(acct_args), (sy_call_t *)acct, AUE_ACCT, NULL, 0, 0 },	/* 51 = acct */
	{ AS(linux_umount_args), (sy_call_t *)linux_umount, AUE_UMOUNT, NULL, 0, 0 },	/* 52 = linux_umount */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 53 = lock */
	{ AS(linux_ioctl_args), (sy_call_t *)linux_ioctl, AUE_IOCTL, NULL, 0, 0 },	/* 54 = linux_ioctl */
	{ AS(linux_fcntl_args), (sy_call_t *)linux_fcntl, AUE_FCNTL, NULL, 0, 0 },	/* 55 = linux_fcntl */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 56 = mpx */
	{ AS(setpgid_args), (sy_call_t *)setpgid, AUE_SETPGRP, NULL, 0, 0 },	/* 57 = setpgid */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 58 = ulimit */
	{ 0, (sy_call_t *)linux_olduname, AUE_NULL, NULL, 0, 0 },	/* 59 = linux_olduname */
	{ AS(umask_args), (sy_call_t *)umask, AUE_UMASK, NULL, 0, 0 },	/* 60 = umask */
	{ AS(chroot_args), (sy_call_t *)chroot, AUE_CHROOT, NULL, 0, 0 },	/* 61 = chroot */
	{ AS(linux_ustat_args), (sy_call_t *)linux_ustat, AUE_NULL, NULL, 0, 0 },	/* 62 = linux_ustat */
	{ AS(dup2_args), (sy_call_t *)dup2, AUE_DUP2, NULL, 0, 0 },	/* 63 = dup2 */
	{ 0, (sy_call_t *)linux_getppid, AUE_GETPPID, NULL, 0, 0 },	/* 64 = linux_getppid */
	{ 0, (sy_call_t *)getpgrp, AUE_GETPGRP, NULL, 0, 0 },		/* 65 = getpgrp */
	{ 0, (sy_call_t *)setsid, AUE_SETSID, NULL, 0, 0 },		/* 66 = setsid */
	{ AS(linux_sigaction_args), (sy_call_t *)linux_sigaction, AUE_NULL, NULL, 0, 0 },	/* 67 = linux_sigaction */
	{ 0, (sy_call_t *)linux_sgetmask, AUE_NULL, NULL, 0, 0 },	/* 68 = linux_sgetmask */
	{ AS(linux_ssetmask_args), (sy_call_t *)linux_ssetmask, AUE_NULL, NULL, 0, 0 },	/* 69 = linux_ssetmask */
	{ AS(linux_setreuid16_args), (sy_call_t *)linux_setreuid16, AUE_SETREUID, NULL, 0, 0 },	/* 70 = linux_setreuid16 */
	{ AS(linux_setregid16_args), (sy_call_t *)linux_setregid16, AUE_SETREGID, NULL, 0, 0 },	/* 71 = linux_setregid16 */
	{ AS(linux_sigsuspend_args), (sy_call_t *)linux_sigsuspend, AUE_NULL, NULL, 0, 0 },	/* 72 = linux_sigsuspend */
	{ AS(linux_sigpending_args), (sy_call_t *)linux_sigpending, AUE_NULL, NULL, 0, 0 },	/* 73 = linux_sigpending */
	{ AS(linux_sethostname_args), (sy_call_t *)linux_sethostname, AUE_SYSCTL, NULL, 0, 0 },	/* 74 = linux_sethostname */
	{ AS(linux_setrlimit_args), (sy_call_t *)linux_setrlimit, AUE_SETRLIMIT, NULL, 0, 0 },	/* 75 = linux_setrlimit */
	{ AS(linux_old_getrlimit_args), (sy_call_t *)linux_old_getrlimit, AUE_GETRLIMIT, NULL, 0, 0 },	/* 76 = linux_old_getrlimit */
	{ AS(linux_getrusage_args), (sy_call_t *)linux_getrusage, AUE_GETRUSAGE, NULL, 0, 0 },	/* 77 = linux_getrusage */
	{ AS(linux_gettimeofday_args), (sy_call_t *)linux_gettimeofday, AUE_NULL, NULL, 0, 0 },	/* 78 = linux_gettimeofday */
	{ AS(linux_settimeofday_args), (sy_call_t *)linux_settimeofday, AUE_SETTIMEOFDAY, NULL, 0, 0 },	/* 79 = linux_settimeofday */
	{ AS(linux_getgroups16_args), (sy_call_t *)linux_getgroups16, AUE_GETGROUPS, NULL, 0, 0 },	/* 80 = linux_getgroups16 */
	{ AS(linux_setgroups16_args), (sy_call_t *)linux_setgroups16, AUE_SETGROUPS, NULL, 0, 0 },	/* 81 = linux_setgroups16 */
	{ AS(linux_old_select_args), (sy_call_t *)linux_old_select, AUE_SELECT, NULL, 0, 0 },	/* 82 = linux_old_select */
	{ AS(linux_symlink_args), (sy_call_t *)linux_symlink, AUE_SYMLINK, NULL, 0, 0 },	/* 83 = linux_symlink */
	{ AS(linux_lstat_args), (sy_call_t *)linux_lstat, AUE_LSTAT, NULL, 0, 0 },	/* 84 = linux_lstat */
	{ AS(linux_readlink_args), (sy_call_t *)linux_readlink, AUE_READLINK, NULL, 0, 0 },	/* 85 = linux_readlink */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 86 = linux_uselib */
	{ AS(swapon_args), (sy_call_t *)swapon, AUE_SWAPON, NULL, 0, 0 },	/* 87 = swapon */
	{ AS(linux_reboot_args), (sy_call_t *)linux_reboot, AUE_REBOOT, NULL, 0, 0 },	/* 88 = linux_reboot */
	{ AS(linux_readdir_args), (sy_call_t *)linux_readdir, AUE_GETDIRENTRIES, NULL, 0, 0 },	/* 89 = linux_readdir */
	{ AS(linux_mmap_args), (sy_call_t *)linux_mmap, AUE_MMAP, NULL, 0, 0 },	/* 90 = linux_mmap */
	{ AS(munmap_args), (sy_call_t *)munmap, AUE_MUNMAP, NULL, 0, 0 },	/* 91 = munmap */
	{ AS(linux_truncate_args), (sy_call_t *)linux_truncate, AUE_TRUNCATE, NULL, 0, 0 },	/* 92 = linux_truncate */
	{ AS(linux_ftruncate_args), (sy_call_t *)linux_ftruncate, AUE_FTRUNCATE, NULL, 0, 0 },	/* 93 = linux_ftruncate */
	{ AS(fchmod_args), (sy_call_t *)fchmod, AUE_FCHMOD, NULL, 0, 0 },	/* 94 = fchmod */
	{ AS(fchown_args), (sy_call_t *)fchown, AUE_FCHOWN, NULL, 0, 0 },	/* 95 = fchown */
	{ AS(linux_getpriority_args), (sy_call_t *)linux_getpriority, AUE_GETPRIORITY, NULL, 0, 0 },	/* 96 = linux_getpriority */
	{ AS(setpriority_args), (sy_call_t *)setpriority, AUE_SETPRIORITY, NULL, 0, 0 },	/* 97 = setpriority */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 98 = profil */
	{ AS(linux_statfs_args), (sy_call_t *)linux_statfs, AUE_STATFS, NULL, 0, 0 },	/* 99 = linux_statfs */
	{ AS(linux_fstatfs_args), (sy_call_t *)linux_fstatfs, AUE_FSTATFS, NULL, 0, 0 },	/* 100 = linux_fstatfs */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 101 = ioperm */
	{ AS(linux_socketcall_args), (sy_call_t *)linux_socketcall, AUE_NULL, NULL, 0, 0 },	/* 102 = linux_socketcall */
	{ AS(linux_syslog_args), (sy_call_t *)linux_syslog, AUE_NULL, NULL, 0, 0 },	/* 103 = linux_syslog */
	{ AS(linux_setitimer_args), (sy_call_t *)linux_setitimer, AUE_SETITIMER, NULL, 0, 0 },	/* 104 = linux_setitimer */
	{ AS(linux_getitimer_args), (sy_call_t *)linux_getitimer, AUE_GETITIMER, NULL, 0, 0 },	/* 105 = linux_getitimer */
	{ AS(linux_newstat_args), (sy_call_t *)linux_newstat, AUE_STAT, NULL, 0, 0 },	/* 106 = linux_newstat */
	{ AS(linux_newlstat_args), (sy_call_t *)linux_newlstat, AUE_LSTAT, NULL, 0, 0 },	/* 107 = linux_newlstat */
	{ AS(linux_newfstat_args), (sy_call_t *)linux_newfstat, AUE_FSTAT, NULL, 0, 0 },	/* 108 = linux_newfstat */
	{ 0, (sy_call_t *)linux_uname, AUE_NULL, NULL, 0, 0 },	/* 109 = linux_uname */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 110 = iopl */
	{ 0, (sy_call_t *)linux_vhangup, AUE_NULL, NULL, 0, 0 },	/* 111 = linux_vhangup */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 112 = idle */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 113 = vm86old */
	{ AS(linux_wait4_args), (sy_call_t *)linux_wait4, AUE_WAIT4, NULL, 0, 0 },	/* 114 = linux_wait4 */
	{ 0, (sy_call_t *)linux_swapoff, AUE_SWAPOFF, NULL, 0, 0 },	/* 115 = linux_swapoff */
	{ AS(linux_sysinfo_args), (sy_call_t *)linux_sysinfo, AUE_NULL, NULL, 0, 0 },	/* 116 = linux_sysinfo */
	{ AS(linux_ipc_args), (sy_call_t *)linux_ipc, AUE_NULL, NULL, 0, 0 },	/* 117 = linux_ipc */
	{ AS(fsync_args), (sy_call_t *)fsync, AUE_FSYNC, NULL, 0, 0 },	/* 118 = fsync */
	{ AS(linux_sigreturn_args), (sy_call_t *)linux_sigreturn, AUE_SIGRETURN, NULL, 0, 0 },	/* 119 = linux_sigreturn */
	{ AS(linux_clone_args), (sy_call_t *)linux_clone, AUE_RFORK, NULL, 0, 0 },	/* 120 = linux_clone */
	{ AS(setdomainname_args), (sy_call_t *)setdomainname, AUE_SYSCTL, NULL, 0, 0 },	/* 121 = setdomainname */
	{ AS(linux_newuname_args), (sy_call_t *)linux_newuname, AUE_NULL, NULL, 0, 0 },	/* 122 = linux_newuname */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 123 = modify_ldt */
	{ 0, (sy_call_t *)linux_adjtimex, AUE_ADJTIME, NULL, 0, 0 },	/* 124 = linux_adjtimex */
	{ AS(linux_mprotect_args), (sy_call_t *)linux_mprotect, AUE_MPROTECT, NULL, 0, 0 },	/* 125 = linux_mprotect */
	{ AS(linux_sigprocmask_args), (sy_call_t *)linux_sigprocmask, AUE_SIGPROCMASK, NULL, 0, 0 },	/* 126 = linux_sigprocmask */
	{ 0, (sy_call_t *)linux_create_module, AUE_NULL, NULL, 0, 0 },	/* 127 = linux_create_module */
	{ 0, (sy_call_t *)linux_init_module, AUE_NULL, NULL, 0, 0 },	/* 128 = linux_init_module */
	{ 0, (sy_call_t *)linux_delete_module, AUE_NULL, NULL, 0, 0 },	/* 129 = linux_delete_module */
	{ 0, (sy_call_t *)linux_get_kernel_syms, AUE_NULL, NULL, 0, 0 },	/* 130 = linux_get_kernel_syms */
	{ 0, (sy_call_t *)linux_quotactl, AUE_QUOTACTL, NULL, 0, 0 },	/* 131 = linux_quotactl */
	{ AS(getpgid_args), (sy_call_t *)getpgid, AUE_GETPGID, NULL, 0, 0 },	/* 132 = getpgid */
	{ AS(fchdir_args), (sy_call_t *)fchdir, AUE_FCHDIR, NULL, 0, 0 },	/* 133 = fchdir */
	{ 0, (sy_call_t *)linux_bdflush, AUE_BDFLUSH, NULL, 0, 0 },	/* 134 = linux_bdflush */
	{ AS(linux_sysfs_args), (sy_call_t *)linux_sysfs, AUE_NULL, NULL, 0, 0 },	/* 135 = linux_sysfs */
	{ AS(linux_personality_args), (sy_call_t *)linux_personality, AUE_PERSONALITY, NULL, 0, 0 },	/* 136 = linux_personality */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 137 = afs_syscall */
	{ AS(linux_setfsuid16_args), (sy_call_t *)linux_setfsuid16, AUE_SETFSUID, NULL, 0, 0 },	/* 138 = linux_setfsuid16 */
	{ AS(linux_setfsgid16_args), (sy_call_t *)linux_setfsgid16, AUE_SETFSGID, NULL, 0, 0 },	/* 139 = linux_setfsgid16 */
	{ AS(linux_llseek_args), (sy_call_t *)linux_llseek, AUE_LSEEK, NULL, 0, 0 },	/* 140 = linux_llseek */
	{ AS(linux_getdents_args), (sy_call_t *)linux_getdents, AUE_GETDIRENTRIES, NULL, 0, 0 },	/* 141 = linux_getdents */
	{ AS(linux_select_args), (sy_call_t *)linux_select, AUE_SELECT, NULL, 0, 0 },	/* 142 = linux_select */
	{ AS(flock_args), (sy_call_t *)flock, AUE_FLOCK, NULL, 0, 0 },	/* 143 = flock */
	{ AS(linux_msync_args), (sy_call_t *)linux_msync, AUE_MSYNC, NULL, 0, 0 },	/* 144 = linux_msync */
	{ AS(linux_readv_args), (sy_call_t *)linux_readv, AUE_READV, NULL, 0, 0 },	/* 145 = linux_readv */
	{ AS(linux_writev_args), (sy_call_t *)linux_writev, AUE_WRITEV, NULL, 0, 0 },	/* 146 = linux_writev */
	{ AS(linux_getsid_args), (sy_call_t *)linux_getsid, AUE_GETSID, NULL, 0, 0 },	/* 147 = linux_getsid */
	{ AS(linux_fdatasync_args), (sy_call_t *)linux_fdatasync, AUE_NULL, NULL, 0, 0 },	/* 148 = linux_fdatasync */
	{ AS(linux_sysctl_args), (sy_call_t *)linux_sysctl, AUE_SYSCTL, NULL, 0, 0 },	/* 149 = linux_sysctl */
	{ AS(mlock_args), (sy_call_t *)mlock, AUE_MLOCK, NULL, 0, 0 },	/* 150 = mlock */
	{ AS(munlock_args), (sy_call_t *)munlock, AUE_MUNLOCK, NULL, 0, 0 },	/* 151 = munlock */
	{ AS(mlockall_args), (sy_call_t *)mlockall, AUE_MLOCKALL, NULL, 0, 0 },	/* 152 = mlockall */
	{ 0, (sy_call_t *)munlockall, AUE_MUNLOCKALL, NULL, 0, 0 },	/* 153 = munlockall */
	{ AS(sched_setparam_args), (sy_call_t *)sched_setparam, AUE_SCHED_SETPARAM, NULL, 0, 0 },	/* 154 = sched_setparam */
	{ AS(sched_getparam_args), (sy_call_t *)sched_getparam, AUE_SCHED_GETPARAM, NULL, 0, 0 },	/* 155 = sched_getparam */
	{ AS(linux_sched_setscheduler_args), (sy_call_t *)linux_sched_setscheduler, AUE_SCHED_SETSCHEDULER, NULL, 0, 0 },	/* 156 = linux_sched_setscheduler */
	{ AS(linux_sched_getscheduler_args), (sy_call_t *)linux_sched_getscheduler, AUE_SCHED_GETSCHEDULER, NULL, 0, 0 },	/* 157 = linux_sched_getscheduler */
	{ 0, (sy_call_t *)sched_yield, AUE_NULL, NULL, 0, 0 },	/* 158 = sched_yield */
	{ AS(linux_sched_get_priority_max_args), (sy_call_t *)linux_sched_get_priority_max, AUE_SCHED_GET_PRIORITY_MAX, NULL, 0, 0 },	/* 159 = linux_sched_get_priority_max */
	{ AS(linux_sched_get_priority_min_args), (sy_call_t *)linux_sched_get_priority_min, AUE_SCHED_GET_PRIORITY_MIN, NULL, 0, 0 },	/* 160 = linux_sched_get_priority_min */
	{ AS(linux_sched_rr_get_interval_args), (sy_call_t *)linux_sched_rr_get_interval, AUE_SCHED_RR_GET_INTERVAL, NULL, 0, 0 },	/* 161 = linux_sched_rr_get_interval */
	{ AS(linux_nanosleep_args), (sy_call_t *)linux_nanosleep, AUE_NULL, NULL, 0, 0 },	/* 162 = linux_nanosleep */
	{ AS(linux_mremap_args), (sy_call_t *)linux_mremap, AUE_NULL, NULL, 0, 0 },	/* 163 = linux_mremap */
	{ AS(linux_setresuid16_args), (sy_call_t *)linux_setresuid16, AUE_SETRESUID, NULL, 0, 0 },	/* 164 = linux_setresuid16 */
	{ AS(linux_getresuid16_args), (sy_call_t *)linux_getresuid16, AUE_GETRESUID, NULL, 0, 0 },	/* 165 = linux_getresuid16 */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 166 = vm86 */
	{ 0, (sy_call_t *)linux_query_module, AUE_NULL, NULL, 0, 0 },	/* 167 = linux_query_module */
	{ AS(poll_args), (sy_call_t *)poll, AUE_POLL, NULL, 0, 0 },	/* 168 = poll */
	{ 0, (sy_call_t *)linux_nfsservctl, AUE_NULL, NULL, 0, 0 },	/* 169 = linux_nfsservctl */
	{ AS(linux_setresgid16_args), (sy_call_t *)linux_setresgid16, AUE_SETRESGID, NULL, 0, 0 },	/* 170 = linux_setresgid16 */
	{ AS(linux_getresgid16_args), (sy_call_t *)linux_getresgid16, AUE_GETRESGID, NULL, 0, 0 },	/* 171 = linux_getresgid16 */
	{ AS(linux_prctl_args), (sy_call_t *)linux_prctl, AUE_PRCTL, NULL, 0, 0 },	/* 172 = linux_prctl */
	{ AS(linux_rt_sigreturn_args), (sy_call_t *)linux_rt_sigreturn, AUE_NULL, NULL, 0, 0 },	/* 173 = linux_rt_sigreturn */
	{ AS(linux_rt_sigaction_args), (sy_call_t *)linux_rt_sigaction, AUE_NULL, NULL, 0, 0 },	/* 174 = linux_rt_sigaction */
	{ AS(linux_rt_sigprocmask_args), (sy_call_t *)linux_rt_sigprocmask, AUE_NULL, NULL, 0, 0 },	/* 175 = linux_rt_sigprocmask */
	{ AS(linux_rt_sigpending_args), (sy_call_t *)linux_rt_sigpending, AUE_NULL, NULL, 0, 0 },	/* 176 = linux_rt_sigpending */
	{ AS(linux_rt_sigtimedwait_args), (sy_call_t *)linux_rt_sigtimedwait, AUE_NULL, NULL, 0, 0 },	/* 177 = linux_rt_sigtimedwait */
	{ 0, (sy_call_t *)linux_rt_sigqueueinfo, AUE_NULL, NULL, 0, 0 },	/* 178 = linux_rt_sigqueueinfo */
	{ AS(linux_rt_sigsuspend_args), (sy_call_t *)linux_rt_sigsuspend, AUE_NULL, NULL, 0, 0 },	/* 179 = linux_rt_sigsuspend */
	{ AS(linux_pread_args), (sy_call_t *)linux_pread, AUE_PREAD, NULL, 0, 0 },	/* 180 = linux_pread */
	{ AS(linux_pwrite_args), (sy_call_t *)linux_pwrite, AUE_PWRITE, NULL, 0, 0 },	/* 181 = linux_pwrite */
	{ AS(linux_chown16_args), (sy_call_t *)linux_chown16, AUE_CHOWN, NULL, 0, 0 },	/* 182 = linux_chown16 */
	{ AS(linux_getcwd_args), (sy_call_t *)linux_getcwd, AUE_GETCWD, NULL, 0, 0 },	/* 183 = linux_getcwd */
	{ 0, (sy_call_t *)linux_capget, AUE_CAPGET, NULL, 0, 0 },	/* 184 = linux_capget */
	{ 0, (sy_call_t *)linux_capset, AUE_CAPSET, NULL, 0, 0 },	/* 185 = linux_capset */
	{ AS(linux_sigaltstack_args), (sy_call_t *)linux_sigaltstack, AUE_NULL, NULL, 0, 0 },	/* 186 = linux_sigaltstack */
	{ 0, (sy_call_t *)linux_sendfile, AUE_SENDFILE, NULL, 0, 0 },	/* 187 = linux_sendfile */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 188 = getpmsg */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 189 = putpmsg */
	{ 0, (sy_call_t *)linux_vfork, AUE_VFORK, NULL, 0, 0 },	/* 190 = linux_vfork */
	{ AS(linux_getrlimit_args), (sy_call_t *)linux_getrlimit, AUE_GETRLIMIT, NULL, 0, 0 },	/* 191 = linux_getrlimit */
	{ AS(linux_mmap2_args), (sy_call_t *)linux_mmap2, AUE_MMAP, NULL, 0, 0 },	/* 192 = linux_mmap2 */
	{ AS(linux_truncate64_args), (sy_call_t *)linux_truncate64, AUE_TRUNCATE, NULL, 0, 0 },	/* 193 = linux_truncate64 */
	{ AS(linux_ftruncate64_args), (sy_call_t *)linux_ftruncate64, AUE_FTRUNCATE, NULL, 0, 0 },	/* 194 = linux_ftruncate64 */
	{ AS(linux_stat64_args), (sy_call_t *)linux_stat64, AUE_STAT, NULL, 0, 0 },	/* 195 = linux_stat64 */
	{ AS(linux_lstat64_args), (sy_call_t *)linux_lstat64, AUE_LSTAT, NULL, 0, 0 },	/* 196 = linux_lstat64 */
	{ AS(linux_fstat64_args), (sy_call_t *)linux_fstat64, AUE_FSTAT, NULL, 0, 0 },	/* 197 = linux_fstat64 */
	{ AS(linux_lchown_args), (sy_call_t *)linux_lchown, AUE_LCHOWN, NULL, 0, 0 },	/* 198 = linux_lchown */
	{ 0, (sy_call_t *)linux_getuid, AUE_GETUID, NULL, 0, 0 },	/* 199 = linux_getuid */
	{ 0, (sy_call_t *)linux_getgid, AUE_GETGID, NULL, 0, 0 },	/* 200 = linux_getgid */
	{ 0, (sy_call_t *)geteuid, AUE_GETEUID, NULL, 0, 0 },		/* 201 = geteuid */
	{ 0, (sy_call_t *)getegid, AUE_GETEGID, NULL, 0, 0 },		/* 202 = getegid */
	{ AS(setreuid_args), (sy_call_t *)setreuid, AUE_SETREUID, NULL, 0, 0 },	/* 203 = setreuid */
	{ AS(setregid_args), (sy_call_t *)setregid, AUE_SETREGID, NULL, 0, 0 },	/* 204 = setregid */
	{ AS(linux_getgroups_args), (sy_call_t *)linux_getgroups, AUE_GETGROUPS, NULL, 0, 0 },	/* 205 = linux_getgroups */
	{ AS(linux_setgroups_args), (sy_call_t *)linux_setgroups, AUE_SETGROUPS, NULL, 0, 0 },	/* 206 = linux_setgroups */
	{ AS(fchown_args), (sy_call_t *)fchown, AUE_NULL, NULL, 0, 0 },	/* 207 = fchown */
	{ AS(setresuid_args), (sy_call_t *)setresuid, AUE_SETRESUID, NULL, 0, 0 },	/* 208 = setresuid */
	{ AS(getresuid_args), (sy_call_t *)getresuid, AUE_GETRESUID, NULL, 0, 0 },	/* 209 = getresuid */
	{ AS(setresgid_args), (sy_call_t *)setresgid, AUE_SETRESGID, NULL, 0, 0 },	/* 210 = setresgid */
	{ AS(getresgid_args), (sy_call_t *)getresgid, AUE_GETRESGID, NULL, 0, 0 },	/* 211 = getresgid */
	{ AS(linux_chown_args), (sy_call_t *)linux_chown, AUE_CHOWN, NULL, 0, 0 },	/* 212 = linux_chown */
	{ AS(setuid_args), (sy_call_t *)setuid, AUE_SETUID, NULL, 0, 0 },	/* 213 = setuid */
	{ AS(setgid_args), (sy_call_t *)setgid, AUE_SETGID, NULL, 0, 0 },	/* 214 = setgid */
	{ AS(linux_setfsuid_args), (sy_call_t *)linux_setfsuid, AUE_SETFSUID, NULL, 0, 0 },	/* 215 = linux_setfsuid */
	{ AS(linux_setfsgid_args), (sy_call_t *)linux_setfsgid, AUE_SETFSGID, NULL, 0, 0 },	/* 216 = linux_setfsgid */
	{ AS(linux_pivot_root_args), (sy_call_t *)linux_pivot_root, AUE_PIVOT_ROOT, NULL, 0, 0 },	/* 217 = linux_pivot_root */
	{ AS(linux_mincore_args), (sy_call_t *)linux_mincore, AUE_MINCORE, NULL, 0, 0 },	/* 218 = linux_mincore */
	{ AS(madvise_args), (sy_call_t *)madvise, AUE_MADVISE, NULL, 0, 0 },	/* 219 = madvise */
	{ AS(linux_getdents64_args), (sy_call_t *)linux_getdents64, AUE_GETDIRENTRIES, NULL, 0, 0 },	/* 220 = linux_getdents64 */
	{ AS(linux_fcntl64_args), (sy_call_t *)linux_fcntl64, AUE_FCNTL, NULL, 0, 0 },	/* 221 = linux_fcntl64 */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 222 =  */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 223 =  */
	{ 0, (sy_call_t *)linux_gettid, AUE_NULL, NULL, 0, 0 },	/* 224 = linux_gettid */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 225 = linux_readahead */
	{ 0, (sy_call_t *)linux_setxattr, AUE_NULL, NULL, 0, 0 },	/* 226 = linux_setxattr */
	{ 0, (sy_call_t *)linux_lsetxattr, AUE_NULL, NULL, 0, 0 },	/* 227 = linux_lsetxattr */
	{ 0, (sy_call_t *)linux_fsetxattr, AUE_NULL, NULL, 0, 0 },	/* 228 = linux_fsetxattr */
	{ 0, (sy_call_t *)linux_getxattr, AUE_NULL, NULL, 0, 0 },	/* 229 = linux_getxattr */
	{ 0, (sy_call_t *)linux_lgetxattr, AUE_NULL, NULL, 0, 0 },	/* 230 = linux_lgetxattr */
	{ 0, (sy_call_t *)linux_fgetxattr, AUE_NULL, NULL, 0, 0 },	/* 231 = linux_fgetxattr */
	{ 0, (sy_call_t *)linux_listxattr, AUE_NULL, NULL, 0, 0 },	/* 232 = linux_listxattr */
	{ 0, (sy_call_t *)linux_llistxattr, AUE_NULL, NULL, 0, 0 },	/* 233 = linux_llistxattr */
	{ 0, (sy_call_t *)linux_flistxattr, AUE_NULL, NULL, 0, 0 },	/* 234 = linux_flistxattr */
	{ 0, (sy_call_t *)linux_removexattr, AUE_NULL, NULL, 0, 0 },	/* 235 = linux_removexattr */
	{ 0, (sy_call_t *)linux_lremovexattr, AUE_NULL, NULL, 0, 0 },	/* 236 = linux_lremovexattr */
	{ 0, (sy_call_t *)linux_fremovexattr, AUE_NULL, NULL, 0, 0 },	/* 237 = linux_fremovexattr */
	{ AS(linux_tkill_args), (sy_call_t *)linux_tkill, AUE_NULL, NULL, 0, 0 },	/* 238 = linux_tkill */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 239 = linux_sendfile64 */
	{ AS(linux_sys_futex_args), (sy_call_t *)linux_sys_futex, AUE_NULL, NULL, 0, 0 },	/* 240 = linux_sys_futex */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 241 = linux_sched_setaffinity */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 242 = linux_sched_getaffinity */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 243 = linux_set_thread_area */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 244 = linux_get_thread_area */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 245 = linux_io_setup */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 246 = linux_io_destroy */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 247 = linux_io_getevents */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 248 = inux_io_submit */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 249 = linux_io_cancel */
	{ 0, (sy_call_t *)linux_fadvise64, AUE_NULL, NULL, 0, 0 },	/* 250 = linux_fadvise64 */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 251 =  */
	{ AS(linux_exit_group_args), (sy_call_t *)linux_exit_group, AUE_EXIT, NULL, 0, 0 },	/* 252 = linux_exit_group */
	{ 0, (sy_call_t *)linux_lookup_dcookie, AUE_NULL, NULL, 0, 0 },	/* 253 = linux_lookup_dcookie */
	{ 0, (sy_call_t *)linux_epoll_create, AUE_NULL, NULL, 0, 0 },	/* 254 = linux_epoll_create */
	{ 0, (sy_call_t *)linux_epoll_ctl, AUE_NULL, NULL, 0, 0 },	/* 255 = linux_epoll_ctl */
	{ 0, (sy_call_t *)linux_epoll_wait, AUE_NULL, NULL, 0, 0 },	/* 256 = linux_epoll_wait */
	{ 0, (sy_call_t *)linux_remap_file_pages, AUE_NULL, NULL, 0, 0 },	/* 257 = linux_remap_file_pages */
	{ AS(linux_set_tid_address_args), (sy_call_t *)linux_set_tid_address, AUE_NULL, NULL, 0, 0 },	/* 258 = linux_set_tid_address */
	{ 0, (sy_call_t *)linux_timer_create, AUE_NULL, NULL, 0, 0 },	/* 259 = linux_timer_create */
	{ 0, (sy_call_t *)linux_timer_settime, AUE_NULL, NULL, 0, 0 },	/* 260 = linux_timer_settime */
	{ 0, (sy_call_t *)linux_timer_gettime, AUE_NULL, NULL, 0, 0 },	/* 261 = linux_timer_gettime */
	{ 0, (sy_call_t *)linux_timer_getoverrun, AUE_NULL, NULL, 0, 0 },	/* 262 = linux_timer_getoverrun */
	{ 0, (sy_call_t *)linux_timer_delete, AUE_NULL, NULL, 0, 0 },	/* 263 = linux_timer_delete */
	{ AS(linux_clock_settime_args), (sy_call_t *)linux_clock_settime, AUE_CLOCK_SETTIME, NULL, 0, 0 },	/* 264 = linux_clock_settime */
	{ AS(linux_clock_gettime_args), (sy_call_t *)linux_clock_gettime, AUE_NULL, NULL, 0, 0 },	/* 265 = linux_clock_gettime */
	{ AS(linux_clock_getres_args), (sy_call_t *)linux_clock_getres, AUE_NULL, NULL, 0, 0 },	/* 266 = linux_clock_getres */
	{ AS(linux_clock_nanosleep_args), (sy_call_t *)linux_clock_nanosleep, AUE_NULL, NULL, 0, 0 },	/* 267 = linux_clock_nanosleep */
	{ AS(linux_statfs64_args), (sy_call_t *)linux_statfs64, AUE_STATFS, NULL, 0, 0 },	/* 268 = linux_statfs64 */
	{ 0, (sy_call_t *)linux_fstatfs64, AUE_FSTATFS, NULL, 0, 0 },	/* 269 = linux_fstatfs64 */
	{ AS(linux_tgkill_args), (sy_call_t *)linux_tgkill, AUE_NULL, NULL, 0, 0 },	/* 270 = linux_tgkill */
	{ AS(linux_utimes_args), (sy_call_t *)linux_utimes, AUE_UTIMES, NULL, 0, 0 },	/* 271 = linux_utimes */
	{ 0, (sy_call_t *)linux_fadvise64_64, AUE_NULL, NULL, 0, 0 },	/* 272 = linux_fadvise64_64 */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 273 =  */
	{ 0, (sy_call_t *)linux_mbind, AUE_NULL, NULL, 0, 0 },	/* 274 = linux_mbind */
	{ 0, (sy_call_t *)linux_get_mempolicy, AUE_NULL, NULL, 0, 0 },	/* 275 = linux_get_mempolicy */
	{ 0, (sy_call_t *)linux_set_mempolicy, AUE_NULL, NULL, 0, 0 },	/* 276 = linux_set_mempolicy */
	{ 0, (sy_call_t *)linux_mq_open, AUE_NULL, NULL, 0, 0 },	/* 277 = linux_mq_open */
	{ 0, (sy_call_t *)linux_mq_unlink, AUE_NULL, NULL, 0, 0 },	/* 278 = linux_mq_unlink */
	{ 0, (sy_call_t *)linux_mq_timedsend, AUE_NULL, NULL, 0, 0 },	/* 279 = linux_mq_timedsend */
	{ 0, (sy_call_t *)linux_mq_timedreceive, AUE_NULL, NULL, 0, 0 },	/* 280 = linux_mq_timedreceive */
	{ 0, (sy_call_t *)linux_mq_notify, AUE_NULL, NULL, 0, 0 },	/* 281 = linux_mq_notify */
	{ 0, (sy_call_t *)linux_mq_getsetattr, AUE_NULL, NULL, 0, 0 },	/* 282 = linux_mq_getsetattr */
	{ 0, (sy_call_t *)linux_kexec_load, AUE_NULL, NULL, 0, 0 },	/* 283 = linux_kexec_load */
	{ 0, (sy_call_t *)linux_waitid, AUE_NULL, NULL, 0, 0 },	/* 284 = linux_waitid */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0 },			/* 285 =  */
	{ 0, (sy_call_t *)linux_add_key, AUE_NULL, NULL, 0, 0 },	/* 286 = linux_add_key */
	{ 0, (sy_call_t *)linux_request_key, AUE_NULL, NULL, 0, 0 },	/* 287 = linux_request_key */
	{ 0, (sy_call_t *)linux_keyctl, AUE_NULL, NULL, 0, 0 },	/* 288 = linux_keyctl */
	{ 0, (sy_call_t *)linux_ioprio_set, AUE_NULL, NULL, 0, 0 },	/* 289 = linux_ioprio_set */
	{ 0, (sy_call_t *)linux_ioprio_get, AUE_NULL, NULL, 0, 0 },	/* 290 = linux_ioprio_get */
	{ 0, (sy_call_t *)linux_inotify_init, AUE_NULL, NULL, 0, 0 },	/* 291 = linux_inotify_init */
	{ 0, (sy_call_t *)linux_inotify_add_watch, AUE_NULL, NULL, 0, 0 },	/* 292 = linux_inotify_add_watch */
	{ 0, (sy_call_t *)linux_inotify_rm_watch, AUE_NULL, NULL, 0, 0 },	/* 293 = linux_inotify_rm_watch */
	{ 0, (sy_call_t *)linux_migrate_pages, AUE_NULL, NULL, 0, 0 },	/* 294 = linux_migrate_pages */
	{ 0, (sy_call_t *)linux_openat, AUE_NULL, NULL, 0, 0 },	/* 295 = linux_openat */
	{ 0, (sy_call_t *)linux_mkdirat, AUE_NULL, NULL, 0, 0 },	/* 296 = linux_mkdirat */
	{ 0, (sy_call_t *)linux_mknodat, AUE_NULL, NULL, 0, 0 },	/* 297 = linux_mknodat */
	{ 0, (sy_call_t *)linux_fchownat, AUE_NULL, NULL, 0, 0 },	/* 298 = linux_fchownat */
	{ 0, (sy_call_t *)linux_futimesat, AUE_NULL, NULL, 0, 0 },	/* 299 = linux_futimesat */
	{ 0, (sy_call_t *)linux_fstatat64, AUE_NULL, NULL, 0, 0 },	/* 300 = linux_fstatat64 */
	{ 0, (sy_call_t *)linux_unlinkat, AUE_NULL, NULL, 0, 0 },	/* 301 = linux_unlinkat */
	{ 0, (sy_call_t *)linux_renameat, AUE_NULL, NULL, 0, 0 },	/* 302 = linux_renameat */
	{ 0, (sy_call_t *)linux_linkat, AUE_NULL, NULL, 0, 0 },	/* 303 = linux_linkat */
	{ 0, (sy_call_t *)linux_symlinkat, AUE_NULL, NULL, 0, 0 },	/* 304 = linux_symlinkat */
	{ 0, (sy_call_t *)linux_readlinkat, AUE_NULL, NULL, 0, 0 },	/* 305 = linux_readlinkat */
	{ 0, (sy_call_t *)linux_fchmodat, AUE_NULL, NULL, 0, 0 },	/* 306 = linux_fchmodat */
	{ 0, (sy_call_t *)linux_faccessat, AUE_NULL, NULL, 0, 0 },	/* 307 = linux_faccessat */
	{ 0, (sy_call_t *)linux_pselect6, AUE_NULL, NULL, 0, 0 },	/* 308 = linux_pselect6 */
	{ 0, (sy_call_t *)linux_ppoll, AUE_NULL, NULL, 0, 0 },	/* 309 = linux_ppoll */
	{ 0, (sy_call_t *)linux_unshare, AUE_NULL, NULL, 0, 0 },	/* 310 = linux_unshare */
};
