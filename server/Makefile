MYHTML_DIR := ./third_party/myhtml

CCX := g++
CCXFLAGS := -Wall -I./ -I$(MYHTML_DIR)/include -L$(MYHTML_DIR)/lib -pthread
LDFLAGS := -lmyhtml_static -lpthread
EXEC := main.cc
EXEC_OUTPUT := main
OBJ := \
	website/website.o \
	storage/storage.o \
	loader/loader.o \
	server/server.o

all: $(EXEC_OUTPUT)

$(EXEC_OUTPUT): $(EXEC) $(OBJ)
	$(CCX) $^ $(CCXFLAGS) $(LDFLAGS) -o $@

$(OBJ):	%.o : %.cc myhtml
	$(CCX) $< $(CCXFLAGS) -c -o $@

myhtml:
	$(MAKE) -C $(MYHTML_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MYHTML_DIR) clean