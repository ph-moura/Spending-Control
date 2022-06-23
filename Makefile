CXXSOURCES = ${wildcard *.cpp}
HXXSOURCES = ${wildcard *.h}
OBJECTS    = ${CXXSOURCES:.cpp=.o}
TARGET     = Finances

CXX        = g++
CXXFLAGS   = -pipe -O2 -flto -std=c++17\
             -fno-fat-lto-objects\
             -Wall -Wextra -D_REENTRANT -fPIC 

LINK       = g++
LFLAGS     = -Wl,-O1 -pipe -O2 -flto=8\
             -fno-fat-lto-objects\
             -fuse-linker-plugin -fPIC

INCPATH    = -I. -I/usr/include/qt\
             -I/usr/include/qt/QtWidgets\
             -I/usr/include/qt/QtGui\
             -I/usr/include/qt/QtCore\
             -I/usr/include/qt/QtCharts

LIBS       = /usr/lib/libQt5Widgets.so\
             /usr/lib/libQt5Gui.so\
             /usr/lib/libQt5Charts.so\
             /usr/lib/libQt5Core.so -lGL -lpthread   

all: ${TARGET}

${TARGET}: ${OBJECTS}  
	${LINK} ${LFLAGS} -o ${TARGET} ${OBJECTS} ${LIBS}

%.o: %.cpp %.h
	${CXX} -c ${CXXFLAGS} ${INCPATH} -o $@ $< 

main.o: main.cpp 
	${CXX} -c ${CXXFLAGS} ${INCPATH} -o main.o main.cpp

clean:
	rm -rf *.o ${TARGET} *~ */*.o */*~
