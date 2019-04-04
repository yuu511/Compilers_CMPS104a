CPP = g++ 
FLAGS = -g -std=gnu++17 -Wall 
OBJS = main.o one.o two.o
EXECNAME = hello

all : build

build : ${OBJS}
	${CPP} ${FLAGS} -o ${EXECNAME} ${OBJS}

%.o : %.cpp
	${CPP} -c $<

clean :
	rm ${OBJS} ${EXECNAME}

