
FREETYPE_CFLAGS = $(shell freetype-config --cflags)
FREETYPE_LIBS = $(shell freetype-config --libs)

WIIUSE_DIR = wiiuse/src/release-x86_64-redhat-linux
WIIUSE_LIB = $(WIIUSE_DIR)/libwiiuse.so

INCLUDES = -Iwiiuse/src/ -I.

CPPFLAGS = -Wall -g -fPIC -funroll-loops $(INCLUDES) $(FREETYPE_CFLAGS)
CXXFLAGS = 
LIBS = -lglut -lm -lGL -lGLU -lwiiuse $(FREETYPE_LIBS)
LDFLAGS = -L$(WIIUSE_DIR)

CXX = g++

MAINMENU_SRC = MainMenu.cpp

ABSTRACTSCENE_SRC = AbstractScene.cpp

WIIINTERFACE_SRC = WiiInterface.cpp

CAMERA_SRC = Camera.cpp

FREETYPE_SRC = FreeType.cpp

MAIN_SRC = main.cpp events.cpp display.cpp init.cpp

SOURCES = $(MAIN_SRC) $(CAMERA_SRC:%=Camera/%) $(WIIINTERFACE_SRC:%=WiiInterface/%) $(MAINMENU_SRC:%=MainMenu/%) $(ABSTRACTSCENE_SRC:%=AbstractScene/%) $(FREETYPE_SRC:%=FreeType/%)
OBJS = $(MAIN_SRC:%.cpp=%.o) $(CAMERA_SRC:%.cpp=Camera/%.o) $(WIIINTERFACE_SRC:%.cpp=WiiInterface/%.o) $(MAINMENU_SRC:%.cpp=MainMenu/%.o) $(ABSTRACTSCENE_SRC:%.cpp=AbstractScene/%.o) $(FREETYPE_SRC:%.cpp=FreeType/%.o)

all: wiicontrol


wiicontrol: $(OBJS) wiiuse
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(INCLUDES) -o wiicontrol $(LIBS)

wiiuse: $(WIIUSE_LIB)

$(WIIUSE_LIB):
	@$(MAKE) -C wiiuse/src	

clean:
	@$(MAKE) -C wiiuse/src clean
	rm -f $(OBJS)



