# Compiler
CC = gcc

# Python configuration
PYTHON_CONFIG = python3-config
CFLAGS = $(shell $(PYTHON_CONFIG) --cflags)
LDFLAGS = $(shell $(PYTHON_CONFIG) --ldflags)

# Plugin source and target
PLUGIN_SRC = /Pygame/pygame_plugin.c
PLUGIN_TARGET = pygame_plugin.so

# Build the plugin
all: $(PLUGIN_TARGET)

$(PLUGIN_TARGET): $(PLUGIN_SRC)
	$(CC) -shared -o $@ -fPIC $(CFLAGS) $< $(LDFLAGS)

# Clean up
clean:
	rm -f $(PLUGIN_TARGET)