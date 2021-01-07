GUMBO_DIR := ./third_party/gumbo-parser

CCX := g++
CCXFLAGS := -Wall -I./ -I$(GUMBO_DIR)/src
LDFLAGS := 
EXEC := main.cc
EXEC_OUTPUT := main
OBJ := \
	website/website.o \
	storage/storage.o \
	loader/loader.o \
	server/server.o

all: $(EXEC_OUTPUT)

$(EXEC_OUTPUT): $(EXEC) $(OBJ)
	$(GUMBO_DIR)/libtool --mode=link $(CCX) $^ $(CCXFLAGS) $(LDFLAGS) -o $@ \
		$(GUMBO_DIR)/libgumbo.la

$(OBJ):	%.o : %.cc gumbo
	$(CCX) $< $(CCXFLAGS) -c -o $@

gumbo:
	cd $(GUMBO_DIR) && ./autogen.sh
	cd $(GUMBO_DIR) && ./configure
	$(MAKE) -C $(GUMBO_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(GUMBO_DIR) clean