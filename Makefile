

INCLUDES = -Iwiiuse/src/

CPPFLAGS = -Wall -fPIC -funroll-loops $(INCLUDES)
CXXFLAGS = 
LIBS = -lglut -lm -lGL -l GLU
CXX = g++

WIIINTERFACE_SRC = WiiInterface.cpp

CAMERA_SRC = Camera.cpp

MAIN_SRC = main.cpp events.cpp display.cpp init.cpp

SOURCES = $(MAIN_SRC) $(CAMERA_SRC:%=Camera/%) $(WIIINTERFACE_SRC:%=WiiInterface/%)
OBJS = $(MAIN_SRC:%.cpp=%.o) $(CAMERA_SRC:%.cpp=Camera/%.o) $(WIIINTERFACE_SRC:%.cpp=WiiInterface/%.o)

all: wiicontrol

wiicontrol: $(OBJS) wiiuse
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(INCLUDES) -o wiicontrol $(LIBS)

wiiuse:
	cd wiiuse
	make


clean:
	rm -f $(OBJS)



