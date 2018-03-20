# ignore makefile in the package 
bring_includes: 
	todo rm inst/include/*
 	todo cp -r ....

clean: 
	rm src/*.o 
	rm src/*.so
