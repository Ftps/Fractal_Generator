TARGET = Fractal_Gen
LIBS = -lm -lpython3.7m -lboost_system -lboost_filesystem
CC = g++
CFLAGS = -Wall -pedantic -o3
H_LOC = Source/Headers
O_LOC = Source/Files

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard $(O_LOC)/*.cpp))
HEADERS = $(wildcard $(H_LOC)/*.hpp)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@
	-rm -f $(O_LOC)/*.o

clean:
	-rm -f $(TARGET)
	-rm -f $(O_LOC)/*.o
