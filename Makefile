LIB_FILES:=libccpgplot.a
CPP_FILES:=$(wildcard *.cpp)
OBJ_FILES:=$(patsubst %.cpp,%.o,$(CPP_FILES))

$(LIB_FILES) : $(OBJ_FILES)
	$(AR) -q $(LIB_FILES) *.o

%.o: %.cpp
	$(CXX) -c $<

clean:
	$(RM) -f *.o *.a
	$(MAKE) -C demo clean

demo: $(LIB_FILES)
	$(MAKE) -C demo
	