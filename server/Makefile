CCX := g++
CCXFLAGS := -Wall -I./
LDFLAGS :=
EXEC := main.cc
EXEC_OUTPUT := main
OBJ := \
	website/website.o \
	storage/storage.o \
	loader/loader.o \
	server/server.o
GUMBO_DIR := ./third_party/gumbo-parser

all: $(EXEC_OUTPUT)

$(EXEC_OUTPUT): $(EXEC) $(OBJ)
	$(CCX) $^ $(CCXFLAGS) $(LDFLAGS) -o $@

$(OBJ):	%.o : %.cc
	$(CCX) $< $(CCXFLAGS) -c -o $@

gumbo:
	cd $(GUMBO_DIR) && ./autogen.sh
	cd $(GUMBO_DIR) && ./configure
	$(MAKE) -C $(GUMBO_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(GUMBO_DIR) clean