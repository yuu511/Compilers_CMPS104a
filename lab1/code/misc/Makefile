# $Id: Makefile,v 1.1 2017-09-21 15:53:38-07 - - $

GPP       = g++ -g -O0 -Wall -Wextra -std=gnu++14
LISTING   = Listing.ps

all : addresses macros
	cid + Makefile

% : %.c
	cid + $<
	${GPP} $< -o $@

lis : all addresses.output macros.output Makefile
	mkpspdf ${LISTING} parser.y parser.h \
	   addresses.c addresses.output \
	   macros.c macros.output \
	   Makefile

ci :
	cid + make-kw-table.perl \
	    parser.y printtokens.c Makefile \

%.output : %
	./$< >$@

