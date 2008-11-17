# Specify extensions of files to delete when cleaning
CLEANEXTS = o a

# Specify the target file and the install directory
OUTPUTFILE = libmylib.a
INSTALLDIR = lib

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libmylib.a from mylib.o
$(OUTPUTFILE): mylib.o
	ar ru $@ $^
	ranlib $@

# No rule to build mylib.o from .cpp
# files is required; this is handled by make's database of
# implicit rules

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)
	mkdir -p include
	cp -p mylib.h include

.PHONY: clean
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done

# Indicate dependencies of .ccp files on .hpp files
#mylib.o: mylib.h
#	g++ -c mylib.cpp