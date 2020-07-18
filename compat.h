/*
 * Copyright (c) 2020 Rene Ammerlaan (0xff@qsrs.nl)
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef COMPAT_H_
#define COMPAT_H_

#include <sys/types.h>
#include <event.h>

#ifndef __dead
# define __dead __attribute__((noreturn))
#endif

#ifndef pledge
# define pledge(s, p) (0)
#endif

#ifndef DEF_WEAK
# define DEF_WEAK(x)
#endif

#ifndef IPV6_MINHOPCOUNT
# define IPV6_MINHOPCOUNT	73
#endif

#ifndef SO_REUSEPORT
# define SO_REUSEPORT		SO_REUSEADDR
#endif

/* Avoid imsg overflow */
#if PATH_MAX > 1024
# undef PATH_MAX
# define PATH_MAX	1024
#endif

/* From OpenNTPD portable */
#if !defined(SA_LEN)
# if defined(HAVE_STRUCT_SOCKADDR_SA_LEN)
#  define SA_LEN(x)	((x)->sa_len)
# else
#  define SA_LEN(x)     ((x)->sa_family == AF_INET6 ? \
			sizeof(struct sockaddr_in6) : \
			sizeof(struct sockaddr_in))
# endif
#endif

/* From OpenBGPD portable */
#if !defined(SS_LEN)
# if defined(HAVE_STRUCT_SOCKADDR_STORAGE_SS_LEN)
#  define SS_LEN(x)  ((x)->ss_len)
# else
#  define SS_LEN(x)  SA_LEN((struct sockaddr *)(x))
# endif
#endif

/* compat prototypes */
__attribute__((weak)) void
		 __explicit_bzero_hook(void *, size_t);
int		 b64_pton(char const *, u_char *, size_t);
void		 bufferevent_read_pressure_cb(struct evbuffer *, size_t, size_t, void *);
int		 crypt_checkpass(const char *, const char *);
void		 explicit_bzero(void *, size_t);
void		 freezero(void *, size_t);
int		 getdtablecount(void);
void		*recallocarray(void *, size_t, size_t, size_t);

/* missing struct */
struct evbuffer {
	u_char *buffer;
	u_char *orig_buffer;

	size_t misalign;
	size_t totallen;
	size_t off;

	void (*cb)(struct evbuffer *, size_t, size_t, void *);
	void *cbarg;
};

#endif /* COMPAT_H */
