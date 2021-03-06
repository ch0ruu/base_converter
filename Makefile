SOURCE_NAMES := $(notdir $(wildcard ./src/*.c)) # <notdir> removes absolute path, keeping just file names
OBJECT_NAMES := $(subst .c,.o,$(SOURCE_NAMES))
BINARY_NAME  := base_converter

SOURCE_PATHS := $(patsubst %,$(CURDIR)/src/%,$(SOURCE_NAMES))
OBJECT_PATHS := $(patsubst %.c,$(CURDIR)/obj/%.o,$(SOURCE_NAMES))
BINARY_PATH  := $(patsubst %, $(CURDIR)/bin/%,$(BINARY_NAME))

HEADER_FLAGS :=
LIB_FLAGS :=

all: clean $(OBJECT_PATHS) $(BINARY_PATH)
	@echo [-] Successfully compiled program: [ $(BINARY_NAME) ]
	@echo -----------------------------------------------------------------
	@echo
	@echo [ $(BINARY_NAME) ] is located in [ ./bin ] directory.

$(BINARY_PATH): $(OBJECT_PATHS)
	@if [ ! -d ./bin ]; then mkdir ./bin; fi
	@echo [3] Building [ $(BINARY_NAME) ] in [ ./bin ] directory
	@cd ./bin && \
		gcc $(OBJECT_PATHS) $(LIB_FLAGS) -o $(BINARY_NAME) -O3 -Wall -Wextra -Wpedantic
	@echo [3] Successfully built [ $(BINARY_NAME) ] in [ ./bin ] directory
	@echo -----------------------------------------------------------------

$(OBJECT_PATHS):
	@if [ ! -d ./obj ]; then mkdir ./obj; fi
	@echo [2] Building [ $(OBJECT_NAMES)] in [ ./obj ] directory
	@cd ./obj && \
		gcc -g $(SOURCE_PATHS) $(HEADER_FLAGS) -c -O3 -Wall -Wextra -Wpedantic
	@echo [2] Successfully built [ $(OBJECT_NAMES)] in [ ./obj ] directory
	@echo -----------------------------------------------------------------

clean:
	@echo [1] Cleaning [ ./obj ./bin ] directories
	@rm -f $(OBJECT_PATHS) $(BINARY_PATH)
	@echo [1] Successfully cleaned [ ./obj ./bin ] directories
	@echo -----------------------------------------------------------------

.PHONY: all clear clean