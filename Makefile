CC := gcc
CFLAGS := -Wall -Wextra -O0 -g
LDFLAGS := -lreadline
TARGET := mysh

all: $(TARGET)

$(TARGET): src/mysh.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGET)
