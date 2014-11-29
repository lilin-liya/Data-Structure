PROGRAM = rpn
SOURCE = rpn.cpp
OBJECTS = rpn.o

CPPOPTIONS = -IStanfordCPPLib -fvisibility-inlines-hidden
LDOPTIONS = -L.
LIB = -lStanfordCPPLib

all: $(PROGRAM)

rpn: $(OBJECTS)
	g++ -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

rpn.o: rpn.cpp Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) rpn.cpp

libStanfordCPPLib.a:
	@rm -f libStanfordCPPLib.a
	(cd StanfordCPPLib; make all)
	ln -s StanfordCPPLib/libStanfordCPPLib.a .

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAM)

handin:
	zip -r StudentNumber_homework7.zip $(SOURCE) Makefile
	echo 'Modify StudentNumber to your own'
