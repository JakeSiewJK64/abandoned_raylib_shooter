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

# Set DEBUG flag if debug=true is passed
ifeq ($(debug), true)
	CFLAGS = -DDEBUG_MODE
else ifeq ($(test), true)
	CFLAGS = -DTEST_MODE
else
	CFLAGS =
endif

# default target
all: clean $(TARGET) run

# Rule to create the target binary
$(TARGET): $(SOURCES)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# Clean the build files
clean:
	rm -rf $(BINDIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# show project status
show_project_stats:
	@cloc --exclude-lang=JSON,make .

# Phony targets
.PHONY: all clean run show_project_stats
