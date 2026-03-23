CXX = g++
CXXFLAGS = -g -std=c++11
LDFLAGS = -lglfw3 -pthread -lGLEW -ldl -lGL

SOURCES = main.cpp shader.cpp shape.cpp shapes.cpp gameobject.cpp glad.c
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: clean $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

glad.c:
	@echo "Please ensure glad.c is in the project directory"

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run:
	./$(EXECUTABLE)

.PHONY: all clean run