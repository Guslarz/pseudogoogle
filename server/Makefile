CC := gcc
CCX := g++
CFLAGS := -Wall
LDFLAGS :=
EXEC := main.cc
EXEC_OUTPUT := main
GUMBO_DIR := ./third_party/gumbo-parser

all: $(EXEC_OUTPUT)

$(EXEC_OUTPUT): $(EXEC) gumbo 
	$(CCX) $< $(CFLAGS) $(LDFLAGS) -o $@

gumbo:
	cd $(GUMBO_DIR) && ./autogen.sh
	cd $(GUMBO_DIR) && ./configure
	$(MAKE) -C $(GUMBO_DIR)

clean:
	$(MAKE) -C $(GUMBO_DIR) clean