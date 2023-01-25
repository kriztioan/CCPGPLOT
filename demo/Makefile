PROG:=demo
CPP_FILES:=$(wildcard *.cpp)
OBJ_FILES:=$(patsubst %.cpp,%.o,$(CPP_FILES))
CPPFLAGS:=-I../
LIBS:=../libccpgplot.a $(LIB_PGPLOT) -lpgplot -lcpgplot -L/opt/X11/lib -lX11 -lX11 $(LIB_EXTRA)

$(PROG) : $(OBJ_FILES)
	$(CXX) -o $(PROG) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) $<

clean:
	$(RM) *.o $(PROG)
