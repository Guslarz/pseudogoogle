CC := gcc

GUMBO_DIR := ./third_party/gumbo-parser

all: gumbo

gumbo:
	cd $(GUMBO_DIR) && ./autogen.sh
	cd $(GUMBO_DIR) && ./configure
	$(MAKE) -C $(GUMBO_DIR)

clean:
	$(MAKE) -C $(GUMBO_DIR) clean