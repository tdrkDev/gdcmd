#
# Configuration
#
CFLAGS := -std=gnu18
LDFLAGS := -lpthread -lncurses
CC := clang

BINARY := gdcmd
INSTALL := /usr/bin/gdcmd
RUN_ARGS := $(shell pwd)/level.gdcmd

#
# Auto-generated
#
ROOTDIR := $(shell pwd)
SOURCES := $(shell find * -name *.c -type f)
OBJECTS := $(subst .c,.o,$(shell find * -type f -name *.c -printf "%f\n"))
SOURCES := $(subst src/,../src/,$(SOURCES))

CFLAGS += -I../include

all: link

clean:
	@echo -e "\e[32mCleaning...\e[0m"
	@rm -rf out

build: clean
	@echo -e "\e[32mBuilding...\e[0m"
	@$(shell mkdir -p $(ROOTDIR)/out && cd $(ROOTDIR)/out && $(CC) $(CFLAGS) -c $(SOURCES))

link: build
	@echo -e "\e[32mLinking...\e[0m"
	@$(shell mkdir -p $(ROOTDIR)/out && cd $(ROOTDIR)/out && $(CC) $(CFLAGS) $(LDFLAGS) -o $(BINARY) $(OBJECTS))
	@echo -e "\e[32mBuilt out/$(BINARY).\e[0m"

run: link
	@chmod +x out/$(BINARY)
	@./out/$(BINARY) $(RUN_ARGS)

install: link
	@mv -f out/$(BINARY) $(INSTALL)
	@chmod +x $(INSTALL)
