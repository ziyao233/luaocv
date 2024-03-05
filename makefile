ifeq ($(RELEASE),1)
	CXXFLAGS_DEBUG	= -O2 -DLOCV_RELEASE
else
	CXXFLAGS_DEBUG	= -g
endif

LUA_PKGNAME	?= lua-5.4
LUA_CXXFLAGS	?= $(shell pkg-config --cflags $(LUA_PKGNAME))
LUA_LDFLAGS	?= $(shell pkg-config --libs $(LUA_PKGNAME))

CV_PKGNAME	?= opencv4
CV_CXXFLAGS	?= $(shell pkg-config --cflags $(CV_PKGNAME))
CV_LDFLAGS	?= $(shell pkg-config --libs $(CV_PKGNAME))

DYN_FLAGS	?= -shared -fPIC

CROSS_COMPILE	?=
CXX		?= $(CROSS_COMPILE)g++
CXXLD		?= $(CROSS_COMPILE)g++

CXXFLAGS	?= $(DYN_FLAGS) $(LUA_CXXFLAGS) $(CV_CXXFLAGS) \
		   $(CXXFLAGS_DEBUG) -std=c++11
LDFLAGS		?= $(DYN_FLAGS) $(LUA_LDFLAGS) $(CV_LDFLAGS)

SRCS		:= src/luaocv.cpp src/helper.cpp 		\
	src/core.cpp src/imgcodecs.cpp src/highgui.cpp src/videoio.cpp	\
	src/objdetect.cpp src/imgproc.cpp
OBJS		:= $(patsubst %.cpp, %.o, $(SRCS))

LIB		:= luaocv.so

.PHONY: default clean disbuild

default: $(LIB)

$(LIB): $(OBJS)
	$(CXXLD) $(OBJS) -o $(LIB) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJS)

disbuild: clean
	rm -f $(LIB)
