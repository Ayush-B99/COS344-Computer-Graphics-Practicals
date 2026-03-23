# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -fprofile-arcs -ftest-coverage -Iinclude -Isrc -I/opt/homebrew/opt/catch2
LDFLAGS = 
ifneq ("$(wildcard lib)","")
    LDFLAGS += -Llib
endif
SRCDIR = src
INCDIR = include
BUILDDIR = build
BINDIR = bin
DOCSDIR = docs
TARGET = $(BINDIR)/my_project
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
#SOURCES = $(filter-out $(SRCDIR)/DemoMain.cpp, $(wildcard $(SRCDIR)/*.cpp))
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))
TEMP_DIR = temp
ZIP_DIR = submit

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Compiling
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the application
run: clean $(TARGET)
	$(TARGET)

# Run without cleaning
run_only: $(TARGET)
	$(TARGET)

# Detect memory leaks using valgrind
leaks: $(TARGET)
	export MallocStackLogging=1; leaks -atExit --list -- $(TARGET) | awk 'BEGIN { print "Memory Leak Summary:\n" } /^Process/ { print } /^Leak/ { print }'

# Clean build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR) $(TEMP_DIR)
	rm -f $(SRCDIR)/*.gcno $(SRCDIR)/*.gcda $(SRCDIR)/*.gcov

# Static analysis with cppcheck
check:
	cppcheck --enable=all $(SRCDIR)/*.cpp

# Show coverage
#coverage: run_only
#	gcov -f -m -r -a $(SRCDIR)/*.cpp
#	cd $(BUILDDIR) && gcov -f -m -r -a ../$(SRCDIR)/*.cpp
SRC_FILES := $(notdir $(wildcard $(SRCDIR)/*.cpp))

coverage: run_only
	cd $(BUILDDIR) && gcov -f -m -r -a $(SRC_FILES)

# Show coverage summary
summary: coverage
	python3 -m gcovr -r . --exclude $(SRCDIR)/Main.cpp --print-summary

# use this command for cevrage testing -> gcovr -r . --html --html-details -o coverage-report.html

# Zip files for test submission
zip_test: prepare_zip_test
	@mkdir -p $(ZIP_DIR)
	@rm -rf $(ZIP_DIR)/u23596351.zip
	@if [ -n "$$(ls -A $(TEMP_DIR))" ]; then zip -j $(ZIP_DIR)/u23596351.zip $(TEMP_DIR)/*; else echo "Nothing to zip"; fi
	@rm -rf $(TEMP_DIR)

# Zip files for submission
zip: prepare_zip
	@mkdir -p $(ZIP_DIR)
	@rm -rf $(ZIP_DIR)/u23596351.zip
	@if [ -n "$$(ls -A $(TEMP_DIR))" ]; then zip -j $(ZIP_DIR)/u23596351.zip $(TEMP_DIR)/*; else echo "Nothing to zip"; fi
	@rm -rf $(TEMP_DIR)

# Prepare files for zipping for test
prepare_zip_test:
	@mkdir -p $(TEMP_DIR)
	@cp $(SRCDIR)/*.cpp $(TEMP_DIR) 2>/dev/null || true
	@cp $(INCDIR)/*.h $(TEMP_DIR) 2>/dev/null || true
	@cp data/*.txt $(TEMP_DIR) 2>/dev/null || true
	cp Makefile $(TEMP_DIR)
	# Create a simple Makefile in TEMP_DIR
	echo 'CXX = g++' > $(TEMP_DIR)/Makefile
	echo 'CXXFLAGS = -std=c++17 -Wall -Wextra' >> $(TEMP_DIR)/Makefile
	echo 'TARGET = my_project_test' >> $(TEMP_DIR)/Makefile
	echo 'SRCDIR = .' >> $(TEMP_DIR)/Makefile
	echo 'SOURCES = $$(wildcard $$(SRCDIR)/*.cpp)' >> $(TEMP_DIR)/Makefile
	echo 'OBJECTS = $$(SOURCES:.cpp=.o)' >> $(TEMP_DIR)/Makefile
	echo '' >> $(TEMP_DIR)/Makefile
	echo 'all: build' >> $(TEMP_DIR)/Makefile
	echo '' >> $(TEMP_DIR)/Makefile
	echo 'build: $$(OBJECTS)' >> $(TEMP_DIR)/Makefile
	echo '	$$(CXX) $$(CXXFLAGS) -o $$(TARGET) $$(OBJECTS)' >> $(TEMP_DIR)/Makefile
	echo '' >> $(TEMP_DIR)/Makefile
	echo 'clean:' >> $(TEMP_DIR)/Makefile
	echo '	rm -f $$(OBJECTS) $$(TARGET)' >> $(TEMP_DIR)/Makefile
	echo '' >> $(TEMP_DIR)/Makefile
	echo 'run: build' >> $(TEMP_DIR)/Makefile
	echo '	./$$(TARGET)' >> $(TEMP_DIR)/Makefile

# Prepare files for zipping
prepare_zip:
	@mkdir -p $(TEMP_DIR)
	@cp $(SRCDIR)/*.cpp $(TEMP_DIR) 2>/dev/null || true
	@cp $(INCDIR)/*.h $(TEMP_DIR) 2>/dev/null || true
	@cp data/*.txt $(TEMP_DIR) 2>/dev/null || true

# Setup command
setup:
	@mkdir -p $(SRCDIR) $(INCDIR) $(BUILDDIR) $(BINDIR) $(DOCSDIR) $(ZIP_DIR)
	@echo '#include <iostream>' > $(SRCDIR)/main.cpp
	@echo '' >> $(SRCDIR)/main.cpp
	@echo 'int main() {' >> $(SRCDIR)/main.cpp
	@echo '    std::cout << "Hello, World!" << std::endl;' >> $(SRCDIR)/main.cpp
	@echo '    return 0;' >> $(SRCDIR)/main.cpp
	@echo '}' >> $(SRCDIR)/main.cpp

# Create a new header file
h:
	@if [ -z "$(name)" ]; then \
	    echo "Please provide a name for the header file."; \
	    exit 1; \
	fi
	@mkdir -p $(INCDIR)
	@name=$$(basename $(name)); \
	echo '#ifndef ' $$(echo $$name | tr a-z A-Z)_H > $(INCDIR)/$$name.h; \
	echo '#define ' $$(echo $$name | tr a-z A-Z)_H >> $(INCDIR)/$$name.h; \
	echo '' >> $(INCDIR)/$$name.h; \
	echo 'class ' $$(echo $$name | sed "s/\\b\(.\)/\u\1/g") ' {' >> $(INCDIR)/$$name.h; \
	echo 'public:' >> $(INCDIR)/$$name.h; \
	if [ -z "$(no_ctor)" ]; then \
		echo '    ' $$(echo $$name | sed "s/\\b\(.\)/\u\1/g") '();' >> $(INCDIR)/$$name.h; \
	fi; \
	if [ -z "$(no_dtor)" ]; then \
		echo '    ~' $$(echo $$name | sed "s/\\b\(.\)/\u\1/g") '();' >> $(INCDIR)/$$name.h; \
	fi; \
	if [ ! -z "$(methods)" ]; then \
		for method in $(methods); do \
			echo '    void ' $$method '();' >> $(INCDIR)/$$name.h; \
		done; \
	fi; \
	echo '};' >> $(INCDIR)/$$name.h; \
	echo '' >> $(INCDIR)/$$name.h; \
	echo '#endif // ' $$(echo $$name | tr a-z A-Z)_H >> $(INCDIR)/$$name.h

# Create a new source file
cpp:
	@if [ -z "$(name)" ]; then \
	    echo "Please provide a name for the source file."; \
	    exit 1; \
	fi
	@mkdir -p $(SRCDIR)
	@name=$$(basename $(name)); \
	echo '#include "'$$name'.h"' > $(SRCDIR)/$$name.cpp; \
	echo '' >> $(SRCDIR)/$$name.cpp; \
	if [ -z "$(no_ctor)" ]; then \
		echo $$(echo $$name | sed "s/\\b\(.\)/\u\1/g") '::' $$(echo $$name | sed "s/\\b\(.\)/\u\1/g") '() {' >> $(SRCDIR)/$$name.cpp; \
		echo '    // Constructor implementation' >> $(SRCDIR)/$$name.cpp; \
		echo '}' >> $(SRCDIR)/$$name.cpp; \
		echo '' >> $(SRCDIR)/$$name.cpp; \
	fi; \
	if [ -z "$(no_dtor)" ]; then \
		echo $$(echo $$name | sed "s/\\b\(.\)/\u\1/g") '::~' $$(echo $$name | sed "s/\\b\(.\)/\u\1/g") '() {' >> $(SRCDIR)/$$name.cpp; \
		echo '    // Destructor implementation' >> $(SRCDIR)/$$name.cpp; \
		echo '}' >> $(SRCDIR)/$$name.cpp; \
		echo '' >> $(SRCDIR)/$$name.cpp; \
	fi; \
	if [ ! -z "$(methods)" ]; then \
		for method in $(methods); do \
			echo 'void ' $$(echo $$name | sed "s/\\b\(.\)/\u\1/g") '::' $$method '() {' >> $(SRCDIR)/$$name.cpp; \
			echo '    // Method implementation' >> $(SRCDIR)/$$name.cpp; \
			echo '}' >> $(SRCDIR)/$$name.cpp; \
			echo '' >> $(SRCDIR)/$$name.cpp; \
		done; \
	fi

# Create both a new header and source file
class: h cpp

# Help command
help:
	@echo "Makefile Help:"
	@echo ""
	@echo "Targets:"
	@echo "  all            - Build the target executable."
	@echo "  run            - Clean and run the target executable."
	@echo "  run_only       - Run the target executable without cleaning."
	@echo "  leaks          - Check for memory leaks using valgrind."
	@echo "  clean          - Clean build artifacts."
	@echo "  check          - Run static analysis with cppcheck."
	@echo "  coverage       - Show code coverage using gcov."
	@echo "  summary        - Show code coverage summary using gcovr."
	@echo "  zip_test       - Zip files for test submission with additional Makefile."
	@echo "  zip            - Zip files for submission."
	@echo "  setup          - Set up initial project structure with main.cpp."
	@echo "  h              - Create a new header file. Parameters: name, no_ctor, no_dtor, methods."
	@echo "  cpp            - Create a new source file. Parameters: name, no_ctor, no_dtor, methods."
	@echo "  class          - Create a new class with header and source files. Parameters: name, no_ctor, no_dtor, methods."
	@echo ""
	@echo "Parameters:"
	@echo "  name           - The name of the header/source/class file."
	@echo "  no_ctor        - Set to 1 to exclude the default constructor."
	@echo "  no_dtor        - Set to 1 to exclude the default destructor."
	@echo "  methods        - A space-separated list of methods to include, passed as a quoted string."

# Phony targets
.PHONY: all run run_only clean check coverage leaks summary zip_test zip prepare_zip_test prepare_zip setup h cpp class help
