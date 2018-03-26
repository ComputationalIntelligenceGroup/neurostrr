# ignore makefile in the package 
NEUROSTR_PATH=/home/bmihaljevic/code-others/cig-neurostr/

import: 
	rm inst/include/* 
	cp - r ${NEUROSTR_PATH}/bundled/*  inst/include
	#cp - r ${NEUROSTR_PATH}/include/neurostr/*  inst/include
	find ${NEUROSTR_PATH}/include/neurostr -type f -iname '*.h$' -exec cp -t src/ {} \; 
	find ${NEUROSTR_PATH} -type f -iname '*.cpp$' -exec cp -t src/ {} \; 

update: 
  	# todo find change header if needed 
	# find -type f -name '*.h' -exec sed -i "s/#include <neurostr.*\/\(.*\)>/#include \"\1\"/g"  {} \;
	# find -type f -name '*.cpp' -exec sed -i "s/#include <neurostr.*\/\(.*\)>/#include \"\1\"/g"  {} \; 
 	# todo cp -r ....
	# todo update parser dispatcher 

clean: 
	rm src/*.o 
	rm src/*.so
