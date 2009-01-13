

WIIUSE_DIR = wiiuse/src/release-x86_64-redhat-linux
WIIUSE_LIB = $(WIIUSE_DIR)/libwiiuse.so

INCLUDES = -Iwiiuse/src/ -I.

CPPFLAGS = -Wall -fPIC -funroll-loops $(INCLUDES)
CXXFLAGS = 
LIBS = -lglut -lm -lGL -lGLU -lwiiuse
LDFLAGS = -L$(WIIUSE_DIR)

CXX = g++

WIIINTERFACE_SRC = WiiInterface.cpp

CAMERA_SRC = Camera.cpp

MAIN_SRC = main.cpp events.cpp display.cpp init.cpp

SOURCES = $(MAIN_SRC) $(CAMERA_SRC:%=Camera/%) $(WIIINTERFACE_SRC:%=WiiInterface/%)
OBJS = $(MAIN_SRC:%.cpp=%.o) $(CAMERA_SRC:%.cpp=Camera/%.o) $(WIIINTERFACE_SRC:%.cpp=WiiInterface/%.o)

all: wiicontrol


wiicontrol: $(OBJS) wiiuse
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(INCLUDES) -o wiicontrol $(LIBS)

wiiuse: $(WIIUSE_LIB)

$(WIIUSE_LIB):
	@$(MAKE) -C wiiuse/src	

clean:
	@$(MAKE) -C wiiuse/src clean
	rm -f $(OBJS)



