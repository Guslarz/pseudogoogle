CCX := g++
CCXFLAGS := -Wall -I./
LDFLAGS := -lcurl
EXEC := main.cc
EXEC_OUTPUT := server_main
OBJ := \
	website/get_request.o \
	website/website.o \
	storage/storage.o \
	loader/loader.o \
	server/server.o

all: $(EXEC_OUTPUT)

$(EXEC_OUTPUT): $(EXEC) $(OBJ)
	$(CCX) $^ $(CCXFLAGS) $(LDFLAGS) -o $@

$(OBJ):	%.o : %.cc
	$(CCX) $< $(CCXFLAGS) -c -o $@

clean:
	rm -f $(OBJ)