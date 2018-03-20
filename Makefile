# ignore makefile in the package 
import: 
	todo rm inst/include/* WATCH out with this 
	find /home/bmihaljevic/code-others/cig-neurostr/include/ -type f -exec cp -t src/ {} \;
	todo cpp find /home/bmihaljevic/code-others/cig-neurostr/include/ -type f -exec cp -t src/ {} \; 

update: 
  	todo find change header if needed 
	 find -type f -name '*.h' -exec sed -i "s/#include <neurostr.*\/\(.*\)>/#include \"\1\"/g"  {} \;
	 find -type f -name '*.cpp' -exec sed -i "s/#include <neurostr.*\/\(.*\)>/#include \"\1\"/g"  {} \; 
 	todo cp -r ....
	todo update parser dispatcher 

clean: 
	rm src/*.o 
	rm src/*.so
