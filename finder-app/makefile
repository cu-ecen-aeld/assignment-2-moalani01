CC := $(CROSS_COMPILE)gcc

TARGET := writer
SRC := writer.c
OBJ := writer.o

all: $(TARGET)

$(OBJ): $(SRC)
	$(CC) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean