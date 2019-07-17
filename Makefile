# $Id: Makefile,v 1.38 2019-04-10 15:51:41-07 - - $

DEPSFILE  = Makefile.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
WARNING   = -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast
CPP       = g++ -std=gnu++17 -g -O0
CPPWARN   = ${CPP} ${WARNING} -fdiagnostics-color=never
CPPYY     = ${CPP} -Wno-sign-compare -Wno-register
MKDEPS    = g++ -std=gnu++17 -MM
GRIND     = valgrind --leak-check=full --show-reachable=yes
FLEX      = flex --outfile=${LEXCPP}
BISON     = bison --defines=${PARSEHDR} --output=${PARSECPP}

MODULES   = astree lyutils string_set auxlib symbol_table 3ac
HDRSRC    = ${MODULES:=.h}
CPPSRC    = ${MODULES:=.cpp} main.cpp
FLEXSRC   = scanner.l
BISONSRC  = parser.y
PARSEHDR  = yyparse.h
LEXCPP    = yylex.cpp
PARSECPP  = yyparse.cpp
CGENS     = ${LEXCPP} ${PARSECPP}
ALLGENS   = ${PARSEHDR} ${CGENS}
EXECBIN   = oc
ALLCSRC   = ${CPPSRC} ${CGENS}
OBJECTS   = ${ALLCSRC:.cpp=.o}
LEXOUT    = yylex.output
PARSEOUT  = yyparse.output
REPORTS   = ${LEXOUT} ${PARSEOUT}
MODSRC    = ${foreach MOD, ${MODULES}, ${MOD}.h ${MOD}.cpp}
MISCSRC   = ${filter-out ${MODSRC}, ${HDRSRC} ${CPPSRC}}
ALLSRC    = README ${FLEXSRC} ${BISONSRC} ${MODSRC} ${MISCSRC} Makefile
TESTINS   = ${wildcard test*.in}
EXECTEST  = ${EXECBIN} -ly
LISTSRC   = ${ALLSRC} ${DEPSFILE} ${PARSEHDR}
TESTFILES = ${THISDIR}/examples/*
TESTOC = ./examples/test.oc
SUBMITDIR = cmps104a-wm.s19
ASGN      = asg5
TESTSTRINGSET = ${TESTFILES:.oc = .str}

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${CPPWARN} -o${EXECBIN} ${OBJECTS}

yylex.o : yylex.cpp
	${CPPYY} -c $<

yyparse.o : yyparse.cpp
	${CPPYY} -c $<

%.o : %.cpp
	${CPPWARN} -c $<


${LEXCPP} : ${FLEXSRC}
	${FLEX} ${FLEXSRC}

${PARSECPP} ${PARSEHDR} : ${BISONSRC}
	${BISON} ${BISONSRC}

ci : ${ALLSRC} ${TESTINS}
	- checksource ${ALLSRC}
	cid + ${ALLSRC} ${TESTINS} test?.inh

lis : ${LISTSRC} tests
	mkpspdf List.source.ps ${LISTSRC}
	mkpspdf List.output.ps ${REPORTS} \
	${foreach test, ${TESTINS:.in=}, \
	${patsubst %, ${test}.%, in out err log}}

clean :
	- rm ${OBJECTS} ${ALLGENS} ${REPORTS} \
	${DEPSFILE} *.str *.tok *.ast *.sym *.oil *.log
	- rm ${foreach test, ${TESTINS:.in=}, \
	${patsubst %, ${test}.%, out err log}}

spotless : clean
	- rm ${EXECBIN} List.*.ps List.*.pdf

deps : ${ALLCSRC}
	@ echo "# ${DEPSFILE} created `date` by ${MAKE}" >${DEPSFILE}
	${MKDEPS} ${ALLCSRC} >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps

tests : ${EXECBIN}
	touch ${TESTINS}
	make --no-print-directory ${TESTINS:.in=.out}

%.out %.err : %.in
	${GRIND} --log-file=$*.log ${EXECTEST} $< 1>$*.out 2>$*.err; \
	echo EXIT STATUS = $$? >>$*.log

again :
	gmake --no-print-directory spotless deps ci all lis

test : ${EXECBIN}
	./${EXECBIN} -@ast ${TESTOC}

valgrind : ${EXECBIN}
	 valgrind ./${EXECBIN} -@ast -y ${TESTOC}

submit :
	submit ${SUBMITDIR} ${ASGN} ${ALLSRC} 2>&1 | tee submit.txt

vim :
	vim $(ALLSRC) ${TESTOC}


ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

