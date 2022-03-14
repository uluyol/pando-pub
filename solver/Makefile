ifndef CPLEX_DIR
$(error must set CPLEX_DIR to point to CPLEX_Studio directory)
endif

SYSTEM := x86-64_linux/static_pic
ifeq ($(shell uname),Darwin)
	SYSTEM := x86-64_osx/static_pic
endif

CXXFLAGS ?= -O2 -Wall
CPLEX_CXXFLAGS := -fPIC -fno-strict-aliasing -I$(CPLEX_DIR)/cplex/include -I$(CPLEX_DIR)/concert/include -DIL_STD
CPLEX_LDFLAGS := -L$(CPLEX_DIR)/cplex/lib/$(SYSTEM) -L$(CPLEX_DIR)/concert/lib/$(SYSTEM) -lconcert -lilocplex -lcplex -lm -lpthread

all: bin/$(BINSUB)ilpsolver

bin/$(BINSUB)ilpsolver: ilpsolver.cc
	@mkdir -p bin/$(BINSUB)
	$(CXX) $(CXXFLAGS) $(CPLEX_CXXFLAGS) -o $@ $< $(LDFLAGS) $(CPLEX_LDFLAGS)

cross:
	docker run --rm -v $(CURDIR):/w -v $(CROSS_CPLEX_DIR):/v gcc:7 bash -c "cd /w && make LDFLAGS=-static BINSUB=linux_amd64/ CPLEX_DIR=/v all"

clean:
	rm -rf bin
