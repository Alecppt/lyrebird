##(1) student's name:     Alec Chen
##(2) student ID:         301187669
##(3) SFU user name:      cca169
##(4) lecture section:    CMPT 300 D1 (Fall 2015)
##(5) instructor's name:  Brian Booth
##(6) TA's name:          Scott Kristjanson



.SUFFIXES: .h .o .c

CCFLAGS= -g -Wall -Werror -ansi -DMEMWATCH -DMW_STDIO
CC = gcc
LIBS = -lm
CCEXEC = lyrebird
OBJCS = main.o memwatch.o decrypt.o

all: $(CCEXEC)

$(CCEXEC): $(OBJCS)
	@echo Linking $@ . . .
	$(CC) $(CCFLAGS) $(OBJCS) -o $@ $(LIBS)


%.o: %.c
	@echo Compiling $< . . .
	$(CC) -c $(CCFLAGS) $<

clean:
	rm -f core $(OBJCS)	$(CCEXEC) memwatch.log
