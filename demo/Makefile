PROGS:=demo
CPP_FILES:=$(wildcard *.cpp)
OBJ_FILES:=$(patsubst %.cpp,%.o,$(CPP_FILES))
DEP_FILES:=deps.d
CPPFLAGS:=-I../ -MMD -MF $(DEP_FILES)
LIBS:=../libccpgplot.a $(LIB_PGPLOT) -lpgplot -lcpgplot -L/opt/X11/lib -lX11 -lX11 $(LIB_EXTRA)

all: $(PROGS)

-include $(DEP_FILES)

$(PROG) : $(OBJ_FILES)
	$(CXX) -o $(PROGS) $(OBJ_FILES) $(LIBS) $(CPPFLAGS)

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) $<

clean:
	$(RM) $* $(DEP_FILES) $(OBJ_FILES) $(PROGS)
