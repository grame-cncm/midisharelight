

system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep -e MINGW -e MSYS > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), Darwin)
	GENERATOR ?= Xcode
	PROJ ?= $(BUILDDIR)/midisharelight.xcodeproj
	JOBS ?= -jobs 8
else
ifeq ($(system), MINGW)
	GENERATOR ?= "Visual Studio 14 2015 Win64"
	PROJ ?= $(BUILDDIR)/midisharelight.sln
	JOBS ?= /maxcpucount:4
else
	GENERATOR ?= "Unix Makefiles"
	PREFIX ?= /usr/local
	PROJ ?= $(BUILDDIR)/Makefile
	JOBS ?= -j 4
endif
endif

BUILDDIR := cmake
BUILDOPT ?= --config Release

.PHONY : cmake

#===============================================================
all : $(PROJ)
	cmake --build $(BUILDDIR) $(BUILDOPT) -- $(JOBS)

$(PROJ) : 
	cd $(BUILDDIR) && cmake . -G $(GENERATOR)

cmake : 
	cd $(BUILDDIR) && cmake .

