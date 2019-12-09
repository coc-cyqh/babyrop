CC=gcc
OUTPUT_DID=bin
SOURCR_DIR=src
# Canary on / x64 / C99 / Debug
CFLAGS=-fstack-protector-all -std=c99 -g -pie -fPIC
# Static / NX on / x64  / PIE on
LD= -z noexecstack  -z now -fstack-protector-all -pie  -fPIC 
# NX off / x86
LD_D=-z execstack 

OBJ=bin.o utility.o
VPATH = ${SOURCR_DIR}:${OUTPUT_DID}

.PHONY: clean

all: dir bin

debug: dir bin-dbg

dyn: dir bin-dyn

bin: ${OBJ}
	${CC}  ${OBJ:%.o=${OUTPUT_DID}/%.o} -o ${OUTPUT_DID}/$@ ${LD}
	strip -s ${OUTPUT_DID}/$@

bin-dbg: ${OBJ}
	${CC}  ${OBJ:%.o=${OUTPUT_DID}/%.o} -o ${OUTPUT_DID}/$@ ${LD}

bin-dyn: ${OBJ}
	${CC}  ${OBJ:%.o=${OUTPUT_DID}/%.o} -o ${OUTPUT_DID}/$@ ${LD_D}
	strip -s ${OUTPUT_DID}/$@

dir:
	-mkdir bin

${OBJ}: %.o: %.c
	${CC} -c $< -o ${OUTPUT_DID}/$@ ${CFLAGS}


clean:
	-rm ${OUTPUT_DID}/*.o
	-rm ${OUTPUT_DID}/.gdb_history
	-rm ${OUTPUT_DID}/*.idb
	-rm */peda-session-*
	-rm .gdb_history
	-rm peda-session-*
	-rm */*~
	-rm *~
