TARGET = Fractal_Gen
LIBS = -lm -lboost_system -lboost_filesystem -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -lQt5Widgets -lQt5Gui -lQt5Core  -fPIC
CC = g++
CFLAGS = -Wall -pedantic -o3 -L/usr/include/qt/QtWidgets -L/usr/include/qt -L/usr/include/qt/QtCore -L/usr/include/qt/QtGui
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
