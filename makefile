TARGET = Fractal_Gen
LIBS = -lm -lboost_system -lboost_filesystem -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -lQt5Widgets -lQt5Gui -lQt5Core
CC = g++
CFLAGS = -Wall -pedantic -o3 -I/usr/include/qt/QtWidgets -I/usr/include/qt -I/usr/include/qt/QtCore -I/usr/include/qt/QtGui -fPIC
H_LOC = Source/Headers
O_LOC = Source/Files

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard $(O_LOC)/*.cpp))
HEADERS = $(wildcard $(H_LOC)/*.hpp)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@
	-rm -f $(O_LOC)/*.o

clean:
	-rm -f $(TARGET)
	-rm -f $(O_LOC)/*.o
