/*-
 * Copyright (c) 2013 Hudson River Trading LLC
 * Copyright (c) 2014, 2016 The FreeBSD Foundation
 * Written by: John H. Baldwin <jhb@FreeBSD.org>
 * All rights reserved.
 *
 * Portions of this software were developed by Konstantin Belousov
 * under sponsorship from the FreeBSD Foundation.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.4/sys/sys/procctl.h 352125 2019-09-10 07:29:21Z kib $
 */

#ifndef	_SYS_PROCCTL_H_
#define	_SYS_PROCCTL_H_

#ifndef _KERNEL
#include <sys/types.h>
#include <sys/wait.h>
#endif

#define	PROC_SPROTECT		1	/* set protected state */
#define	PROC_REAP_ACQUIRE	2	/* reaping enable */
#define	PROC_REAP_RELEASE	3	/* reaping disable */
#define	PROC_REAP_STATUS	4	/* reaping status */
#define	PROC_REAP_GETPIDS	5	/* get descendants */
#define	PROC_REAP_KILL		6	/* kill descendants */
#define	PROC_TRACE_CTL		7	/* en/dis ptrace and coredumps */
#define	PROC_TRACE_STATUS	8	/* query tracing status */
#define	PROC_TRAPCAP_CTL	9	/* trap capability errors */
#define	PROC_TRAPCAP_STATUS	10	/* query trap capability status */
#define	PROC_PDEATHSIG_CTL	11	/* set parent death signal */
#define	PROC_PDEATHSIG_STATUS	12	/* get parent death signal */
#define	PROC_STACKGAP_CTL	17	/* en/dis stack gap on MAP_STACK */
#define	PROC_STACKGAP_STATUS	18	/* query stack gap */

/* Operations for PROC_SPROTECT (passed in integer arg). */
#define	PPROT_OP(x)	((x) & 0xf)
#define	PPROT_SET	1
#define	PPROT_CLEAR	2

/* Flags for PROC_SPROTECT (ORed in with operation). */
#define	PPROT_FLAGS(x)	((x) & ~0xf)
#define	PPROT_DESCEND	0x10
#define	PPROT_INHERIT	0x20

/* Result of PREAP_STATUS (returned by value). */
struct procctl_reaper_status {
	u_int	rs_flags;
	u_int	rs_children;
	u_int	rs_descendants;
	pid_t	rs_reaper;
	pid_t	rs_pid;
	u_int	rs_pad0[15];
};

/* struct procctl_reaper_status rs_flags */
#define	REAPER_STATUS_OWNED	0x00000001
#define	REAPER_STATUS_REALINIT	0x00000002

struct procctl_reaper_pidinfo {
	pid_t	pi_pid;
	pid_t	pi_subtree;
	u_int	pi_flags;
	u_int	pi_pad0[15];
};

#define	REAPER_PIDINFO_VALID	0x00000001
#define	REAPER_PIDINFO_CHILD	0x00000002
#define	REAPER_PIDINFO_REAPER	0x00000004

struct procctl_reaper_pids {
	u_int	rp_count;
	u_int	rp_pad0[15];
	struct procctl_reaper_pidinfo *rp_pids;
};

struct procctl_reaper_kill {
	int	rk_sig;		/* in  - signal to send */
	u_int	rk_flags;	/* in  - REAPER_KILL flags */
	pid_t	rk_subtree;	/* in  - subtree, if REAPER_KILL_SUBTREE */
	u_int	rk_killed;	/* out - count of processes successfully
				   killed */
	pid_t	rk_fpid;	/* out - first failed pid for which error
				   is returned */
	u_int	rk_pad0[15];
};

#define	REAPER_KILL_CHILDREN	0x00000001
#define	REAPER_KILL_SUBTREE	0x00000002

#define	PROC_TRACE_CTL_ENABLE		1
#define	PROC_TRACE_CTL_DISABLE		2
#define	PROC_TRACE_CTL_DISABLE_EXEC	3

#define	PROC_TRAPCAP_CTL_ENABLE		1
#define	PROC_TRAPCAP_CTL_DISABLE	2

#define	PROC_STACKGAP_ENABLE		0x0001
#define	PROC_STACKGAP_DISABLE		0x0002
#define	PROC_STACKGAP_ENABLE_EXEC	0x0004
#define	PROC_STACKGAP_DISABLE_EXEC	0x0008

#ifndef _KERNEL
__BEGIN_DECLS
int	procctl(idtype_t, id_t, int, void *);
__END_DECLS

#endif

#endif /* !_SYS_PROCCTL_H_ */
