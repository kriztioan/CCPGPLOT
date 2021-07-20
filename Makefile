LIB_FILES:=libccpgplot.a
CPP_FILES:=$(wildcard *.cpp)
OBJ_FILES:=$(patsubst %.cpp,%.o,$(CPP_FILES))

$(LIB_FILES) : $(OBJ_FILES)
	$(AR) -q $(LIB_FILES) *.o

%.o: %.cpp
	$(CXX) -c $<

demo: $(LIB_FILES)
	$(MAKE) -C demo	

clean:
	$(RM) *.o *.a
	$(MAKE) -C demo clean
