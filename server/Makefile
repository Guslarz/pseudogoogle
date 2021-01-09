CCX := g++
CCXFLAGS := -Wall -I./ -std=c++17 -pthread
LDFLAGS := -lcurl -lgumbo -lpthread
EXEC := main.cc
EXEC_OUTPUT := pseudogoogle_server
OBJ := \
	website/get_request.o \
	website/website.o \
	storage/storage.o \
	loader/loader.o \
	server/server.o

all: $(EXEC_OUTPUT)

$(EXEC_OUTPUT): $(EXEC) $(OBJ)
	$(CCX) $^ $(CCXFLAGS) $(LDFLAGS) -o $@

$(OBJ):	%.o : %.cc %.h
	$(CCX) $< $(CCXFLAGS) -c -o $@

clean:
	rm -f $(OBJ)