LIB_FILES:=libccpgplot.a
CPP_FILES:=$(wildcard *.cpp)
OBJ_FILES:=$(patsubst %.cpp,%.o,$(CPP_FILES))
DEP_FILES:=deps.d
CPPFLAGS:=-MMD -MF $(DEP_FILES)

all: $(LIB_FILES)

-include $(DEP_FILES)

$(LIB_FILES) : $(OBJ_FILES)
	$(AR) -q $(LIB_FILES) *.o $(CPPFLAGS)

%.o: %.cpp
	$(CXX) -c $(INC_PGPLOT) $< $(CPPFLAGS)

demo: $(LIB_FILES)
	$(MAKE) -C demo

clean:
	$(RM) $(DEP_FILES) $(OBJ_FILES) $(LIB_FILES)
	$(MAKE) -C demo clean
