# Makefile for OpenGL projects

# --- Configuration Variables ---

# Name of the executable
PROJECT_NAME = main

# C++ Compiler
CXX = g++

# Compiler flags
# -g: Include debugging information
# -I<path>: Add directory to include search path
CXXFLAGS = -g \
           -I./include \
		   -I./include/MathLibrary \
           -I./include/glad \
           -I./include/KHR \
           -I$(GLFW_INSTALL_DIR)/include

# Linker flags
# -L<path>: Add directory to library search path
# -l<library>: Link with specified library
LDFLAGS = -L$(GLFW_INSTALL_DIR)/lib

# Libraries to link (e.g., glfw3, pthread, dl, GL)
LIBS = -lglfw3 -pthread -ldl -lGL

# Coverage flags
COVERAGE_CXXFLAGS = -O0 --coverage -DCOVERAGE_RUN
COVERAGE_LDFLAGS = --coverage
COVERAGE_HTML_DIR = coverage
COVERAGE_HTML_FILE = $(COVERAGE_HTML_DIR)/index.html
COVERAGE_EXCLUDE = --exclude '(^|.*/)glad\.c$$'

# Math library source files (non-template translation units only)
MATHLIB_SRCS = include/MathLibrary/LibraryTesting.cpp

# Source files (space-separated)
SRCS = main.cpp glad.c $(MATHLIB_SRCS)

# Directory where GLFW is installed.
# This should point to the 'install' directory of your GLFW build.
# Example: /home/user/my_project/glfw_local/install
GLFW_INSTALL_DIR = glfw_local/install

# --- End Configuration Variables ---

# Object files
OBJS = $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)

.PHONY: all clean run coverage coverage-clean coverage-html

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROJECT_NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean c: coverage-clean
	rm -f $(OBJS) $(PROJECT_NAME)

coverage-clean:
	find . \( -name "*.gcda" -o -name "*.gcno" -o -name "*.gcov" \) -delete

coverage: clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) $(COVERAGE_CXXFLAGS)" LDFLAGS="$(LDFLAGS) $(COVERAGE_LDFLAGS)" all
	./$(PROJECT_NAME)
	@if command -v gcovr >/dev/null 2>&1; then \
		gcovr -r . $(COVERAGE_EXCLUDE) --txt --txt-summary; \
	else \
		echo "gcovr not found, generating .gcov files with gcov."; \
		for src in $(filter-out glad.c,$(SRCS)); do \
			gcov -o "$$(dirname $$src)" "$$src" >/dev/null 2>&1 || true; \
		done; \
		echo "Generated .gcov files."; \
	fi

coverage-html: clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) $(COVERAGE_CXXFLAGS)" LDFLAGS="$(LDFLAGS) $(COVERAGE_LDFLAGS)" all
	./$(PROJECT_NAME)
	@mkdir -p $(COVERAGE_HTML_DIR)
	@if command -v gcovr >/dev/null 2>&1; then \
		gcovr -r . $(COVERAGE_EXCLUDE) --html-details -o $(COVERAGE_HTML_FILE); \
		echo "HTML coverage report: $(COVERAGE_HTML_FILE)"; \
	else \
		echo "gcovr not found. Install gcovr to generate HTML (e.g. pip install gcovr)."; \
		exit 1; \
	fi

run r: $(PROJECT_NAME)
	./$(PROJECT_NAME)
