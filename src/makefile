BUILD_DIR          = ../build
BIN_DIR            = ../bin
LIB_DIR            = ../lib
EXE                = $(BIN_DIR)/sgtelib_main.exe $(BIN_DIR)/sgtelib_server.exe
LIB                = $(LIB_DIR)/sgtelib.a $(LIB_DIR)/sgtelib.so
COMPILATOR         = g++
COMPILATOR_OPTIONS = -pedantic -Wall -Wextra -g3 -fpic


LIBS               = -lc -lm
INCLUDE            = -I. 
COMPILE            = $(COMPILATOR) $(COMPILATOR_OPTIONS) $(INCLUDE) -c
OBJS_LIB           = TrainingSet.o Surrogate_Parameters.o Surrogate_KS.o Surrogate_RBF.o \
                     Surrogate_PRS.o Surrogate_PRS_EDGE.o Surrogate_LOWESS.o Surrogate_Kriging.o Surrogate_PRS_CAT.o Surrogate_Ensemble.o \
                     Surrogate.o Matrix.o Kernel.o Surrogate_Utils.o Surrogate_Factory.o \
                     Tests.o 
OBJS               = $(OBJS_LIB) sgtelib_main.o sgtelib_server.o



OBJS     := $(addprefix $(BUILD_DIR)/,$(OBJS))
OBJS_LIB := $(addprefix $(BUILD_DIR)/,$(OBJS_LIB))

all: $(OBJS) $(LIB) $(EXE)

$(BIN_DIR)/%.exe: $(BUILD_DIR)/%.o $(OBJS) 
	@echo "=== building $@ from $< ==="
	$(COMPILATOR) -o $@ $(OBJS_LIB) $< $(LIBS) $(COMPILATOR_OPTIONS)

%.a: $(OBJS_LIB)
	@echo "=== building $@ ==="
	@ar -r $@ $(OBJS_LIB)
	@ranlib $@

$(LIB_DIR)/%.so: $(OBJS_LIB)
	@echo "=== building $@ ==="
	$(COMPILATOR) -shared -o $@ $(OBJS_LIB) $(LIBS)

$(BUILD_DIR)/%.o: %.cpp
	$(COMPILE) $< -o $@

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
	@echo "   cleaning librery file"
	@rm -f $(LIB)
