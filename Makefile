# Makefile for Starknight

# G++ compiler options
CXX = g++
CXXFLAGS = -g

# linker options
LDLIBS = sfml-graphics sfml-audio sfml-window sfml-system

# File dependencies, groupings, and names
APTDEPENDENCIES = libsfml-dev

# Default functions for using make
.PHONY: clean depends
.DEFAULT: starknight
clean:
	git clean -xfd
depends:
	sudo apt-get -y install ${APTDEPENDENCIES}

# Main executable
starknight: Entity.o Button.o Actor.o Character.o starknight.o
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS:%=-l%)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^
