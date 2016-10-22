EXE                = comparison.exe
COMPILATOR         = g++
COMPILATOR_OPTIONS = -pedantic -Wall -Wextra -g3 -fpic


LIBS               = -lc -lm $(SGTELIB_HOME)/lib/sgtelib.so
INCLUDE            = -I. -I$(SGTELIB_HOME)/src
COMPILE            = $(COMPILATOR) $(COMPILATOR_OPTIONS) $(INCLUDE) -c
OBJS               = comparison.o

all: $(EXE)

%.o: %.cpp
	$(COMPILE) $< -o $@

%.exe: %.o $(OBJS) 
	@echo "=== building $@ from $< ==="
	$(COMPILATOR) -o $@ $< $(LIBS) $(COMPILATOR_OPTIONS)

clean:
	@echo "   cleaning obj files"
	@rm -f $(OBJS)

del:
	@echo "   cleaning trash files"
	@rm -f core *~
	@echo "   cleaning obj files"
	@rm -f $(OBJS)
	@echo "   cleaning exe file"
	@rm -f $(EXE)

