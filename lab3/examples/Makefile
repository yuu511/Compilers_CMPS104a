# $Id: Makefile,v 1.16 2019-04-17 18:52:07-07 - - $

UTILDIR = /afs/cats.ucsc.edu/courses/cmps104a-wm/bin

NOWARN  = -Wno-write-strings -Wno-main
OCGPP   = g++ ${NOWARN} -x c++ -include octypes.h

OCSRC   = ${sort ${wildcard *.oc}}
LIBSRC  = oclib.c
LIBOBJ  = ${LIBSRC:.c=.o}
HEADERS = oclib.h octypes.h
OCOBJ   = ${OCSRC:.oc=.o}
EXECS   = ${OCSRC:.oc=.elf}
ALLSRC  = ${HEADERS} ${LIBSRC} ${OCSRC} Makefile
LISTING = Listing.oc-programs

all : ${EXECS}

%.elf : %.o ${LIBOBJ}
	g++ $< ${LIBOBJ} -o $@

%.o : %.oc ${HEADERS}
	${OCGPP} -c $<

${LIBOBJ} : ${LIBSRC}
	gcc -c $<

spotless : clean
	- rm ${LISTING}.{ps,pdf} ${EXECS}

clean :
	-rm ${OCOBJ} ${LIBOBJ}

ci :
	${UTILDIR}/cid + ${ALLSRC}

lis :
	${UTILDIR}/checksource ${ALLSRC}
	${UTILDIR}/mkpspdf ${LISTING}.ps ${ALLSRC}

again :
	make --no-print-directory clean ci all lis
