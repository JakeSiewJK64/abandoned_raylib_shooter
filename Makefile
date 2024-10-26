# gcc -o build/myprogram src/* -l raylib -lGL -lm -lpthread -ldl -lrt -lX11

# compiler and flags
CC = gcc
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# directories
SRCDIR = src
BINDIR = build

# output binary
TARGET = $(BINDIR)/myprogram.out

# source files
SOURCES = $(wildcard $(SRCDIR)/*.c)

# default target
all: $(TARGET) run

# Rule to create the target binary
$(TARGET): $(SOURCES)
	@mkdir -p $(BINDIR)
	$(CC) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# Clean the build files
clean:
	rm -rf $(BINDIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run