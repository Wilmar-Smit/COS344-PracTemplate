
PROJECT_NAME = main


CXX = g++


CXXFLAGS = -g \
           -I./include \
		   -I./MathLibrary \
           -I./include/glad \
           -I./include/KHR \
           -I$(GLFW_INSTALL_DIR)/include


LDFLAGS = -L$(GLFW_INSTALL_DIR)/lib


LIBS = -lglfw3 -pthread -ldl -lGL


COVERAGE_CXXFLAGS = -O0 --coverage -DCOVERAGE_RUN
COVERAGE_LDFLAGS = --coverage
COVERAGE_HTML_DIR = coverage
COVERAGE_HTML_FILE = $(COVERAGE_HTML_DIR)/index.html
COVERAGE_EXCLUDE = --exclude '(^|.*/)glad\.c$$'


MATHLIB_SRCS = MathLibrary/LibraryTesting.cpp \
			   MathLibrary/2D_shapes/shape.cpp \
			   MathLibrary/2D_shapes/Triangle.cpp \
			   MathLibrary/2D_shapes/Square.cpp \
			   MathLibrary/2D_shapes/circle.cpp



SHAPE3D_SRCS := $(wildcard MathLibrary/3D_shapes/*.cpp)

SURFACES_SRCS := $(wildcard surfaces/*.cpp)

LIGHT_SRCS := $(wildcard lights/*.cpp)

SCENE_SRCS = sceneClasses/drawerVisitor.cpp sceneClasses/complexSceneHolder.cpp

SRCS = main.cpp assets/assets.cpp shader.cpp glad.c camera/camera.cpp controls/controlManager.cpp $(SURFACES_SRCS) $(LIGHT_SRCS)  $(MATHLIB_SRCS) $(BORDER_SRCS) $(OBSERVER_SRCS) $(SHAPE3D_SRCS) $(SCENE_SRCS)


TEST_NAME = test_runner
TEST_SRCS = test_main.cpp glad.c assets.cpp $(MATHLIB_SRCS) $(SHAPE3D_SRCS) $(SCENE_SRCS)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_OBJS := $(TEST_OBJS:.c=.o)
 
# Directory where GLFW is installed.
# This should point to the 'install' directory of your GLFW build.
# Example: /home/user/my_project/glfw_local/install
GLFW_INSTALL_DIR = glfw_local/install

# --- End Configuration Variables ---

quote = $(foreach a,$1,"$(a)")

# Object files
OBJS = $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)

.PHONY: all clean run coverage coverage-clean coverage-html test

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CXX) $(call quote,$(OBJS)) $(LDFLAGS) $(LIBS) -o $(PROJECT_NAME)


$(TEST_NAME): $(TEST_OBJS)
	$(CXX) $(call quote,$(TEST_OBJS)) $(LDFLAGS) $(LIBS) -o $(TEST_NAME)

# Build the standalone test runner
test: $(TEST_NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c "$<" -o "$@"

%.o: %.c
	$(CXX) $(CXXFLAGS) -c "$<" -o "$@"

clean c: coverage-clean
	rm -f $(call quote,$(OBJS)) $(PROJECT_NAME) $(call quote,$(TEST_OBJS)) $(TEST_NAME)


run r: $(PROJECT_NAME)
	./$(PROJECT_NAME)


valgrind v: $(TEST_NAME)
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./$(TEST_NAME)

bear: 
	$(MAKE) clean
	bear -- make