# ignore makefile in the package 
bring_includes: 
	todo rm inst/include/*
 	todo cp -r ....

update: 
  	todo find change header if needed 

clean: 
	rm src/*.o 
	rm src/*.so
