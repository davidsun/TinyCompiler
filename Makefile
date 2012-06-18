CXX 		= g++
CXXFLAGS 	= -O3
TARGET      = main

.SUFFIXES: .o .cpp

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

main: Exception.o Utils.o Item.o CodeItem.o ItemSet.o LexicalAnalytics.o LRAnalytics.o CodeGenerator.o CodeRunner.o
	$(CXX) $(CXXFLAGS) -o main Exception.o Utils.o Item.o CodeItem.o ItemSet.o LexicalAnalytics.o LRAnalytics.o CodeGenerator.o CodeRunner.o main.cpp

clean:
	rm -f *.o

run:
	./main
