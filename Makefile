#	$OpenBSD: Makefile,v 1.30 2017/07/03 22:21:47 espie Exp $

PROG=		httpd
SRCS=		parse.y
SRCS+=		compat/cryptutil.c compat/imsg-buffer.c compat/vis.c
SRCS+=		compat/imsg.c compat/getdtablecount.c compat/base64.c
SRCS+=		compat/evbuffer.c compat/freezero.c compat/explicit_bzero.c
SRCS+=		config.c control.c httpd.c log.c logger.c proc.c
SRCS+=		server.c server_http.c server_file.c server_fcgi.c
MAN=		httpd.8 httpd.conf.5

SRCS+=		patterns.c
MAN+=		patterns.7

LDADD=		-levent -ltls -lssl -lcrypto -lutil -lbsd -lcrypt
DPADD=		${LIBEVENT} ${LIBTLS} ${LIBSSL} ${LIBCRYPTO} ${LIBUTIL}
#DEBUG=		-g -DDEBUG=3 -O0
LDFLAGS+=	-L/usr/lib -L/lib
CFLAGS+=	-D_GNU_SOURCE -DLIBBSD_OVERLAY
CFLAGS+=	-Wall -I${.CURDIR} -I${.CURDIR}/compat
CFLAGS+=	-I/usr/include -I/usr/include/bsd
CFLAGS+=	-Wstrict-prototypes -Wmissing-prototypes
CFLAGS+=	-Wmissing-declarations
CFLAGS+=	-Wshadow -Wpointer-arith
CFLAGS+=	-Wsign-compare -Wcast-qual
YFLAGS=

.include <bsd.prog.mk>
