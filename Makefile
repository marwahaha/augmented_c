CC = cc
SRC = src
DIST = dist
INCLUDE = includes

OBJS = $(DIST)/deps
BINS = $(DIST)/bins
CLOGFLAGS = -DAKST_LOG_WARN -DAKST_LOG_ERROR -DAKST_LOG_INFO
CFLAGS = -Wall $(CLOGFLAGS)
CINCLUDE = -I$(INCLUDE)

# a list of all header files in the project
H_SOURCE = $(wildcard $(INCLUDE)/*.h)

# a list of c source code in project
C_SOURCE = $(wildcard $(SRC)/*.c)

# a list of object files generated during compilation
OBJ_FILES = $(C_SOURCE:$(SRC)/%.c=$(OBJS)/%.o)


TARGET_NAMES = main

NATIVE_TARGETS = $(TARGET_NAMES:%=$(BINS)/%__native)

default: $(NATIVE_TARGETS)

$(BINS)/%__native: $(OBJ_FILES) $(BINS)
	$(CC) -o $@ $(OBJ_FILES) $(CINCLUDE)

$(OBJS)/%.o: $(SRC)/%.c $(H_SOURCE) $(OBJS)
	$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDE)

clean:
	rm -rf $(DIST)

$(DIST):
	mkdir -p $(DIST)

$(OBJS): $(DIST)
	mkdir -p $(OBJS)

$(BINS): $(DIST)
	mkdir -p $(BINS)

.PHONY: clean default
.PRECIOUS: $(OBJ_FILES)
