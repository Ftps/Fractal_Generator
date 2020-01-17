TARGET = Fractal_Gen
LIBS = -lm -lboost_system -lboost_filesystem -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -lQt5Widgets -lQt5Gui -lQt5Core
CC = g++
MOC = moc-qt5
CFLAGS = -Wall -pedantic -o3 -fPIC
H_LOC = Source/Headers
O_LOC = Source/Files
INCDIRS = -I/usr/include/qt -I/usr/include/qt/QtWidgets -I/usr/include/qt/QtCore -I/usr/include/qt/QtGui

HEADERS = $(wildcard $(H_LOC)/*.hpp)
MOCS = $(shell grep -l Q_OBJECT $(HEADERS))

MOC_SOURCES = $(MOCS:.hpp=.moc.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard $(O_LOC)/*.cpp)) $(MOC_SOURCES:.cpp=.o)

.PHONY: default all clean

default: $(TARGET)
all: default

#$(info $$MOC_S is [${MOC_SOURCES}])

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

%.moc.cpp: %.hpp
	$(MOC) $(INCDIRS) $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@
	-rm -f $(O_LOC)/*.o
	-rm -f $(H_LOC)/*.o

clean:
	-rm -f $(TARGET)
	-rm -f $(O_LOC)/*.o
	-rm -f $(H_LOC)/*.o
