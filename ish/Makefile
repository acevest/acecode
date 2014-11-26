CC = g++
CC_FLAGS = -O2 -c
CCF = $(CC) $(CC_FLAGS)
#LINK_FLAGS = -ltermcap -lstdc++
#INSTALL_DIR = /bin
HEADERS = *.h

OBJ=main.o Ish.o Cmd.o Common.o \
	BinaryTree.o Variables.o StringBuffer.o\
	Scanner.o Parser.o
every: $(OBJ) ish

#cleanobj


main.o:main.cc
	$(CCF) $< -o $@

Ish.o:Ish.cc $(HEADERS)
	$(CCF) $< -o $@

Cmd.o:Cmd.cc $(HEADERS)
	$(CCF) $< -o $@
Common.o:Common.cc $(HEADERS)
	$(CCF) $< -o $@

Scanner.o:Scanner.cc $(HEADERS)
	$(CCF) $< -o $@
BinaryTree.o:BinaryTree.cc $(HEADERS)
	$(CCF) $< -o $@
Variables.o:Variables.cc $(HEADERS)
	$(CCF) $< -o $@
StringBuffer.o:StringBuffer.cc $(HEADERS)
	$(CCF) $< -o $@
Parser.o:Parser.cc $(HEADERS)
	$(CCF) $< -o $@

ish: $(OBJ)
	$(CC) $(OBJ) -o ish $(LINK_FLAGS)

cleanobj:
	rm *.o -f

clean:cleanobj
	rm ish -f

