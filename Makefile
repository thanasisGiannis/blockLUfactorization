ifeq ($(shell uname -m),x86_64)
Arch=intel64
CXXFLAGS+= -m64
MKLFLAGS+= -Wl,--start-group  ${MKLROOT}/lib/intel64/libmkl_intel_ilp64.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -liomp5 -lpthread -lm -ldl
MKLOPTIONS+= -DMKL_ILP64 -I${MKLROOT}/include -L/opt/intel/compilers_and_libraries_2019.5.281/linux/compiler/lib/intel64_lin
else
Arch=ia32
CXXFLAGS+= -m32 
endif 

CXX = g++

all: mLU_serial

build: mmult_serial 

mLU_serial: test_blockLUfactorization.cpp blockLUfactorization.cpp lapack_wrapper.cpp
	$(CXX) $(CXXFLAGS) test_blockLUfactorization.cpp blockLUfactorization.cpp lapack_wrapper.cpp -fopenmp -o mLU_serial -O3  -g $(MKLFLAGS) $(MKLOPTIONS)
	
EXECUTABLES=mLU_serial

clean:
	rm -f $(EXECUTABLES) *.o

	
