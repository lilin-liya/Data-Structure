# Makefile for Maze
#****************************************************************

PROGRAM = Maze
SOURCE = Maze.cpp
OBJECTS = Maze.o

CPPOPTIONS = -IStanfordCPPLib -fvisibility-inlines-hidden
LDOPTIONS = -L.
LIB = -lStanfordCPPLib

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PROGRAM)

Maze: $(OBJECTS)
	g++ -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

Maze.o: Maze.cpp Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) Maze.cpp

libStanfordCPPLib.a:
	@rm -f libStanfordCPPLib.a
	(cd StanfordCPPLib; make all)
	ln -s StanfordCPPLib/libStanfordCPPLib.a .

# ***************************************************************
# Standard entries to remove files from the directories
#    tidy  -- eliminate unwanted files
#    clean -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAM)

handin:
	zip -r StudentNumber_homework3.zip $(SOURCE) Makefile testmap_1.txt testmap_2.txt testmap_3.txt
	echo "Modify StudentNumber to your own"
