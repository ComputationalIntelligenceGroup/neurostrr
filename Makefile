# ignore makefile in the package 
NEUROSTR_PATH=/home/bmihaljevic/code-cig/cig-neurostr/

import: 
	rm -rf inst/include/* 
	rm -rf src/*.h src/*.cpp 
	cp -r ${NEUROSTR_PATH}/bundled/*  inst/include
	#cp - r ${NEUROSTR_PATH}/include/neurostr/*  inst/include
	find ${NEUROSTR_PATH}/include/neurostr -type f -iname "*.h" -exec cp -t src/ {} \; 
	find ${NEUROSTR_PATH} -type f -iname '*.cpp' -exec cp -t src/ {} \; 

adapt: 
	find -type f -name '*.h' -exec sed -i "s/#include <neurostr.*\/\(.*\)>/#include \"\1\"/g"  {} \;
	find -type f -name '*.cpp' -exec sed -i "s/#include <neurostr.*\/\(.*\)>/#include \"\1\"/g"  {} \; 
	# update parser dispatcher and add required files
	rm src/BranchFeatureExtractor.cpp
	rm src/NeuroConverter.cpp
	rm src/NodeFeatureExtractor.cpp
	rm src/Validator.cpp 
	cp .diffs/* src/ 
	git clean -f 


update: import adapt

clean: 
	rm src/*.o 
	rm src/*.so

clean-all: 
	rm src/*.o 
	rm src/*.so
