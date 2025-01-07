SRCDIR=src
LIBDIR=lib
BINDIR=bin
INCLUDEDIR=include
TESTDIR=$(SRCDIR)/tests
TESTBINDIR=tests
DOCDIR=doc
CC = gcc
AR = ar
CFLAGS=-Wall -pedantic -g -std=gnu99
LDFLAGS=
EXEC=huffman
SRC= hello.c main.c
OBJ= $(SRC:.c=.o)
TESTS= testTad testListeChainee

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.o $(SRCDIR)/mainCompression.o $(SRCDIR)/mainDecompression.o $(LIBDIR)/libTad.a $(LIBDIR)/liblisteChainee.a $(LIBDIR)/libentierAllocationDynamique.a $(LIBDIR)/libaccesseursOctets.a
	$(CC) $(LDFLAGS) $(SRCDIR)/main.o $(SRCDIR)/mainCompression.o $(SRCDIR)/mainDecompression.o -lTad -Llib -llisteChainee -lentierAllocationDynamique -laccesseursOctets -lm -o $(BINDIR)/$(EXEC)

all : $(BINDIR)/$(EXEC) $(DOCDIR)/latex $(DOCDIR)/html

tests : $(TESTS)

doc : $(DOCDIR)/latex $(DOCDIR)/html

testTad : $(TESTDIR)/testTad.o $(LIBDIR)/libTad.a $(LIBDIR)/libentierAllocationDynamique.a $(LIBDIR)/libaccesseursOctets.a
	$(CC) $(LDFLAGS) -o $(TESTBINDIR)/testTad $(TESTDIR)/testTad.o -lTad -Llib -lcunit -llisteChainee -lentierAllocationDynamique -laccesseursOctets -lm

testListeChainee : $(TESTDIR)/testListeChainee.o $(LIBDIR)/liblisteChainee.a $(LIBDIR)/libentierAllocationDynamique.a $(LIBDIR)/libcdcAllocationDynamique.a
	$(CC) $(LDFLAGS) -o $(TESTBINDIR)/$@ $(TESTDIR)/$@.o -Llib -llisteChainee -lentierAllocationDynamique -lcdcAllocationDynamique -lcunit -lm

$(LIBDIR)/libTad.a : $(SRCDIR)/TAD_Octet.o  $(SRCDIR)/TAD_CodeBinaire.o $(SRCDIR)/TAD_ArbreDeHuffman.o $(SRCDIR)/TAD_FileDePriorite.o  $(SRCDIR)/TAD_Statistiques.o $(SRCDIR)/listeChainee.o $(SRCDIR)/mainTypes.o $(SRCDIR)/TAD_TableDeCodage.o $(LIBDIR)/liblisteChainee.a
	$(AR)  -r $@  $^

$(LIBDIR)/lib%.a : $(SRCDIR)/%.o
	$(AR)  -r $@  $^

$(LIBDIR)/lib%.a : $(TESTDIR)/%.o
	$(AR)  -r $@  $^

$(SRCDIR)/%.o : $(SRCDIR)/%.c $(INCLUDEDIR)/%.h
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)  

$(TESTDIR)/%.o : $(TESTDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

$(DOCDIR)/% : $(SRCDIR)/*
	doxygen
	(cd $(DOCDIR)/latex/ && make) 

clean : 
	rm -rf $(BINDIR)/*
	rm -rf $(TESTBINDIR)/*
	rm -rf $(LIBDIR)/*
	rm -rf $(SRCDIR)/*.o
	rm -rf $(TESTDIR)/*.o
	rm -rf $(DOCDIR)/
