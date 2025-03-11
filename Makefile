.PHONY: help
help:
	@echo Build C++ with GCC/Clang/MSVC and CMake
	@echo =======================================
	@echo build-gcc/clang/msvc     builds the project
	@echo run-gcc/clang/msvc       runs a and executable Default: exe=line
	@echo clean-gcc/clang/msvc     deletes all compiled files (preparation for re-compilation)
	@echo rebuild-gcc/clang/msvc   re-compiles the whole project
	@echo ---
	@echo Build the Documentation
	@echo =======================
	@echo build-docs    builds the documentation with Doxygen/doxybook2/mkdocs
	@echo serve-docs    opens a browser to show the documentation and starts an html server
	@echo deploy-docs   deploys the website to the branch `gh-pages` and pushes it

#############################################################
#					 OS independend commands
#############################################################

# Detect the operating system
OS ?= $(shell uname -s)

# Remove a file
ifeq ($(OS),Windows_NT)
    RM = del
else
    RM = rm
endif

# Remove a directory
ifeq ($(OS),Windows_NT)
    RMDIR = rmdir /S /Q
else
    RMDIR = rm -rf
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

# find files recursively
ifeq ($(OS),Windows_NT)
    FIND_FILES = $(shell dir /s /b $(1))
else
    FIND_FILES = $(shell find $(1) -type f)
endif

# export an environment variable
ifeq ($(OS),Windows_NT)
    EXPORT = set
else
    EXPORT = export
endif

#############################################################
#					Build C++ with GCC and CMake
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
build_gcc/CMakeCache.txt: CMakeLists.txt
	$(EXPORT) CC=gcc & $(EXPORT) CXX=g++ & cmake -S . -B build_gcc -G "Ninja Multi-Config" -DBUILD_EXAMPLES=ON

# private: compile the project
build_gcc\examples\Release\.timestamp: build_gcc/CMakeCache.txt plotpp/* examples/*
	$(EXPORT) CC=gcc & $(EXPORT) CXX=g++ & cmake --build build_gcc --config Release
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
	$(RM) build_gcc\examples\Release\.timestamp

# public: re-compile the project
.PHONY:	rebuild-gcc
rebuild-gcc: clean-gcc build-gcc

#############################################################
#					Build C++ with Clang and CMake
#############################################################

# build-clang
#	builds the project
# 
# run-clang
#	runs a and executable Default: exe=line
#
# clean-clang
#	deletes all compiled files (preparation for re-compilation)
# 
# rebuild-clang
# 	re-compiles the whole project

# private: generate the build configuration for ninja
build_clang/CMakeCache.txt: CMakeLists.txt
	$(EXPORT) CC=clang & $(EXPORT) CXX=clang++ & cmake -S . -B build_clang -G "Ninja Multi-Config" -DBUILD_EXAMPLES=ON

# private: compile the project
build_clang\examples\Release\.timestamp: build_clang/CMakeCache.txt plotpp/* examples/*
	$(EXPORT) CC=clang & $(EXPORT) CXX=clang++ & cmake --build build_clang --config Release
	$(TIMESTAMP)

# public: build the project
.PHONY: build-clang
build-clang: cls build_clang\examples\Release\.timestamp

# public: run one of the compiled executables
exe=line
.PHONY: run-clang
run-clang: build-clang
	.\build_clang\examples\Release\$(exe).exe

# public: clean the build binary files
.PHONY: clean-clang
clean-clang:
	cmake --build build_clang --config Release --target clean
	$(RM) build_clang\examples\Release\.timestamp

# public: re-compile the project
.PHONY:	rebuild-clang
rebuild-clang: clean-clang build-clang
	
#############################################################
#					Build C++ with MSVC and CMake
#############################################################

# build-msvc
#	builds the project
# 
# run-msvc
#	runs a and executable Default: exe=line
#
# clean-msvc
#	deletes all compiled files (preparation for re-compilation)
# 
# rebuild-msvc
# 	re-compiles the whole project

# private: generate the build configuration for ninja
build_msvc/CMakeCache.txt: CMakeLists.txt
	cmake -S . -B build_msvc -G "Visual Studio 17 2022" -DBUILD_EXAMPLES=ON

# private: compile the project
build_msvc\examples\Release\.timestamp: build_msvc/CMakeCache.txt plotpp/* examples/*
	cmake --build build_msvc --config Release
	$(TIMESTAMP)

# public: build the project
.PHONY: build-msvc
build-msvc: cls build_msvc\examples\Release\.timestamp

# public: run one of the compiled executables
exe=line
.PHONY: run-msvc
run-msvc: build-msvc
	.\build_msvc\examples\Release\$(exe).exe

# public: clean the build binary files
.PHONY: clean-msvc
clean-msvc:
	cmake --build build_msvc --config Release --target clean
	$(RM) build_msvc\examples\Release\.timestamp
	

# public: re-compile the project
.PHONY:	rebuild-msvc
rebuild-msvc: clean-msvc build-msvc

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
	$(RMDIR) "docs/doxygen"
	$(RMDIR) "docs/site"
	$(RMDIR) "docs/docs/API"

#############################################################
#						Misc
#############################################################

.PHONY: cls
cls:
	cls
	

	