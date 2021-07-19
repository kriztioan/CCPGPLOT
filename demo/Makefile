PROG:=demo
CPP_FILES:=$(wildcard *.cpp)
OBJ_FILES:=$(patsubst %.cpp,%.o,$(CPP_FILES))
CPPFLAGS:=-I../
LIBS:=../libccpgplot.a -L /usr/include/pgplot/ -lcpgplot -lpgplot

$(PROG) : $(OBJ_FILES)
	$(CXX) -o $(PROG) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) $<

clean:
	$(RM) -f *.o $(PROG)
