#
# Configuration
#
SOURCES := src/main.c src/level.c src/player.c src/fb.c
CFLAGS := -std=gnu18
LDFLAGS := -lpthread -lncurses
CC := clang

#
# Auto-generated
#
OBJECTS := $(subst src/,,$(SOURCES))
OBJECTS := $(subst .c,.o,$(OBJECTS))

CFLAGS += -Iinclude

all: run

clean:
	@echo -e "\e[32mCleaning...\e[0m"
	@rm -rf $(OBJECTS)
	@rm -rf gdcmd

build: clean
	@echo -e "\e[32mBuilding...\e[0m"
	@$(CC) $(CFLAGS) -c $(SOURCES)

link: build
	@echo -e "\e[32mLinking...\e[0m"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o gdcmd $(OBJECTS)
	@echo -e "\e[32mBuilt gdcmd.\e[0m"

run: link
	@chmod +x gdcmd
	@./gdcmd $(shell pwd)/level.gdcmd

install: link
	@mv -f gdcmd /usr/bin/gdcmd
	@chmod +x /usr/bin/gdcmd
