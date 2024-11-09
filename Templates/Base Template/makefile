CXX = g++
CXXFLAGS = -std=c++17 -DUSE_PCH -g -Wall


PCH = pch.h.gch
GCC_VERSION = $(shell gcc -dumpversion)
HEADER_PATH = /usr/include/x86_64-linux-gnu/c++/$(GCC_VERSION)

BASE ?= base.cpp
CNT ?= 10

.PHONY: noargs
noargs:
	@echo "'make %.out' to compile '%.cpp'"
	@echo "'make gen' to generate '$(CNT)' copies of '$(BASE)'"
	@echo "'make clean' to remove generated .cpp files"
	@echo "'make clean-all' to remove all generated files"

$(PCH):
	@echo "Compiling headers..."
	@$(CXX) $(CXXFLAGS) -I$(HEADER_PATH) -x c++-header $(HEADER_PATH)/bits/stdc++.h -o $(PCH)

.PHONY: gen
gen: $(PCH)
	@	if [ $(CNT) -gt 26 ]; then \
			echo "Error: CNT exceeds 26. Cannot generate more than 26 files with unique letters."; \
			exit 1; \
		fi; 

	@	echo "Generating files..."

	@	for i in $$(seq 0 $$(($(CNT)-1))); do \
			A=$$(printf \\$$(printf '%03o' $$((i+65)))); \
			cat $(BASE) > "$$A.cpp"; \
		done
	@echo "Generated $(CNT) files."

.PHONY: clean
clean::
	@echo "Deleting generated .cpp files..."
	@rm -f [A-Z].cpp

clean::
	@echo "Deleting binaries..."
	@rm -f ?

set-ulimit:
	ulimit -s 1048576

%: %.cpp $(PCH) set-ulimit
	$(CXX) $(CXXFLAGS) -I. $< -o $@

.PHONY: clean-all
clean-all:: clean
	@echo "Deleting precompiled headers..."
	@rm -f $(PCH)
