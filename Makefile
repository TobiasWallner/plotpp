

.PHONY: help
help:
	@echo Build C++ GCC with CMake
	@echo ========================
	@echo build-gcc     builds the project
	@echo run-gcc       runs a and executable Default: exe=line
	@echo clean-gcc     deletes all compiled files (preparation for re-compilation)
	@echo rebuild-gcc   re-compiles the whole project
	@echo ---
	@echo Build the Documentation
	@echo =======================
	@echo build-docs    builds the documentation with Doxygen/doxybook2/mkdocs
	@echo serve-docs     opens a browser to show the documentation and starts an html server
	@echo deploy-docs   deploys the website to the branch `gh-pages` and pushes it

#############################################################
#					 OS independend commands
#############################################################

# Detect the operating system
OS ?= $(shell uname -s)

ifeq ($(OS),Windows_NT)
    RM = rmdir /S /Q
else
    RM = rm -rf
endif

# create a timestamp file
ifeq ($(OS),Windows_NT)
	TIMESTAMP = type nul > $@
else
	TIMESTAMP = touch $@
endif

# Define OPEN_BROWSER command based on the OS
ifeq ($(OS),Windows_NT)
    OPEN_BROWSER = cmd /c start
else ifeq ($(OS),Linux)
    OPEN_BROWSER = xdg-open
else ifeq ($(OS),Darwin)
    OPEN_BROWSER = open
endif

ifeq ($(OS),Windows_NT)
    FIND_FILES = $(shell dir /s /b $(1))
else
    FIND_FILES = $(shell find $(1) -type f)
endif

#############################################################
#					Build C++ GCC with CMake
#############################################################

# build-gcc
#	builds the project
# 
# run-gcc
#	runs a and executable Default: exe=line
#
# clean-gcc
#	deletes all compiled files (preparation for re-compilation)
# 
# rebuild-gcc
# 	re-compiles the whole project

# private: generate the build configuration for ninja
BUILD_GENERATOR = "Ninja Multi-Config"
CPM_SOURCE_CACHE  = "C:\CPM_SOURCE_CACHE"
build_gcc/CMakeCache.txt: CMakeLists.txt build_gcc/build/Release/generators/conan_toolchain.cmake
	cmake -S . -B build_gcc -G $(BUILD_GENERATOR) -DBUILD_EXAMPLES=ON -DCPM_SOURCE_CACHE=$(CPM_SOURCE_CACHE)

# private: compile the project
build_gcc\examples\Release\.timestamp: build_gcc/CMakeCache.txt plotpp/* examples/*
	cmake --build build_gcc --config Release
	$(TIMESTAMP)

# public: build the project
.PHONY: build-gcc
build-gcc: cls build_gcc\examples\Release\.timestamp

# public: run one of the compiled executables
exe=line
.PHONY: run-gcc
run-gcc: build-gcc
	.\build_gcc\examples\Release\$(exe).exe

# public: clean the build binary files
.PHONY: clean-gcc
clean-gcc:
	cmake --build build_gcc --config Release --target clean

# public: re-compile the project
.PHONY:	rebuild-gcc
rebuild-gcc: clean-gcc build-gcc
	

#############################################################
#					 Documentation
#############################################################

# make commands
# -------------
# make build-docs
#	builds the documentation with Doxygen/doxybook2/mkdocs
#
# make serve-docs
#	opens a browser to show the documentation and starts an html server
#
# make deploy-docs
# 	deploys the website to the branch `gh-pages` and pushes it

# private: build doxygen xml from the source code
docs/doxygen/.timestamp: plotpp/* Doxyfile
	doxygen Doxyfile
	$(TIMESTAMP)

# private: convert doxygen xml to markdown
XML_INPUT = docs\doxygen\xml
MD_OUTPUT = docs\docs\API
docs/docs/API/.timestamp: docs/doxybook2-config.json docs/doxygen/.timestamp
	if not exist $(MD_OUTPUT) mkdir $(MD_OUTPUT)
	doxybook2 --input $(XML_INPUT) --output $(MD_OUTPUT) --config docs/doxybook2-config.json
	$(TIMESTAMP)

# private: build the website with mkdocs from the markdown files
docs/site/.timestamp: docs/mkdocs.yml $(call FIND_FILES,"docs/docs") docs/docs/API/.timestamp
	mkdocs build -f docs/mkdocs.yml
	$(TIMESTAMP)

# public: build the documentation
.PHONY: build-docs
build-docs: docs/site/.timestamp

# public: show the documentation	
.PHONY: serve-docs
serve-docs: build-docs
	$(OPEN_BROWSER) http://127.0.0.1:8000/
	mkdocs serve -f docs/mkdocs.yml

# public: deploy the documentation to github
.PHONY: deploy-docs
deploy-docs: build-docs
	mkdocs gh-deploy -f docs/mkdocs.yml
	
.PHONY: clean-docs
clean-docs: 
	$(RM) "docs/doxygen"
	$(RM) "docs/site"
	$(RM) "docs/docs/API"

#############################################################
#						Misc
#############################################################

.PHONY: cls
cls:
	cls
	

	