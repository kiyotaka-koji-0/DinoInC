CC=gcc

CFLAGS=$(shell pkg-config --cflags raylib)

LIBS=$(shell pkg-config --libs raylib) \
-lm \
-pthread \
-ldl \
-lrt \
-lX11

TARGET=game
SRC=main.c

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)
	./$(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)%