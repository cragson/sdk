/*-
 * Copyright (C) 2006 Jason Evans <jasone@FreeBSD.org>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice(s), this list of conditions and the following disclaimer as
 *    the first lines of this file unmodified other than the possible
 *    addition of one or more copyright notices.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice(s), this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.4/include/malloc_np.h 331722 2018-03-29 02:50:57Z eadler $
 */

#ifndef _MALLOC_NP_H_
#define	_MALLOC_NP_H_
#include <sys/cdefs.h>
#include <sys/types.h>
#include <stdbool.h>
#include <strings.h>

__BEGIN_DECLS
typedef void *(chunk_alloc_t)(void *, size_t, size_t, bool *, bool *, unsigned);
typedef bool (chunk_dalloc_t)(void *, size_t, bool, unsigned);
typedef bool (chunk_commit_t)(void *, size_t, size_t, size_t, unsigned);
typedef bool (chunk_decommit_t)(void *, size_t, size_t, size_t, unsigned);
typedef bool (chunk_purge_t)(void *, size_t, size_t, size_t, unsigned);
typedef bool (chunk_split_t)(void *, size_t, size_t, size_t, bool, unsigned);
typedef bool (chunk_merge_t)(void *, size_t, void *, size_t, bool, unsigned);
typedef struct {
	chunk_alloc_t		*alloc;
	chunk_dalloc_t		*dalloc;
	chunk_commit_t		*commit;
	chunk_decommit_t	*decommit;
	chunk_purge_t		*purge;
	chunk_split_t		*split;
	chunk_merge_t		*merge;
} chunk_hooks_t;

size_t	malloc_usable_size(const void *ptr);

void	malloc_stats_print(void (*write_cb)(void *, const char *),
    void *cbopaque, const char *opts);
int	mallctl(const char *name, void *oldp, size_t *oldlenp, void *newp,
    size_t newlen);
int	mallctlnametomib(const char *name, size_t *mibp, size_t *miblenp);
int	mallctlbymib(const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen);

#define	MALLOCX_LG_ALIGN(la)	(la)
#define	MALLOCX_ALIGN(a)	(ffsl(a)-1)
#define	MALLOCX_ZERO		((int)0x40)
#define	MALLOCX_TCACHE(tc)	((int)(((tc)+2) << 8))
#define	MALLOCX_TCACHE_NONE	MALLOCX_TCACHE(-1)
#define	MALLOCX_ARENA(a)	((int)(((a)+1) << 20))

void	*mallocx(size_t size, int flags);
void	*rallocx(void *ptr, size_t size, int flags);
size_t	xallocx(void *ptr, size_t size, size_t extra, int flags);
size_t	sallocx(const void *ptr, int flags);
void	dallocx(void *ptr, int flags);
void	sdallocx(void *ptr, size_t size, int flags);
size_t	nallocx(size_t size, int flags);

void *	__calloc(size_t number, size_t size) __malloc_like;
void *	__malloc(size_t size) __malloc_like;
void *	__realloc(void *ptr, size_t size);
void	__free(void *ptr);
int	__posix_memalign(void **ptr, size_t alignment, size_t size);
void	*__aligned_alloc(size_t alignment, size_t size);
size_t	__malloc_usable_size(const void *ptr);
void	__malloc_stats_print(void (*write_cb)(void *, const char *),
    void *cbopaque, const char *opts);
int	__mallctl(const char *name, void *oldp, size_t *oldlenp, void *newp,
    size_t newlen);
int	__mallctlnametomib(const char *name, size_t *mibp, size_t *miblenp);
int	__mallctlbymib(const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen);
void	*__mallocx(size_t size, int flags);
void	*__rallocx(void *ptr, size_t size, int flags);
size_t	__xallocx(void *ptr, size_t size, size_t extra, int flags);
size_t	__sallocx(const void *ptr, int flags);
void	__dallocx(void *ptr, int flags);
void	__sdallocx(void *ptr, size_t size, int flags);
size_t	__nallocx(size_t size, int flags);
__END_DECLS

#endif /* _MALLOC_NP_H_ */
