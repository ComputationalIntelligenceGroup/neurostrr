# neurostr 
The goal of `neurostr` is to to provide an R interface to the NeuroSTR C++ library.

## Installing   
Install the package with:  
```r
# install.packages("devtools") # run this line if you do not have devtools installed
devtools::install_github("ComputationalIntelligenceGroup/neurostrr")
``` 

The package has only been tested on Ubuntu 16.04. It requires C++ 14.

## Example  
See the vignette for more details. `vignette('neurostr', 'neurostr')`. 

## How it works 
The package simply contains all header and cpp files from NeuroSTR along with its dependencies (besides BH and Eigen). The current version contains code from **add a github tag** of NeuroSTR. 

## Known Issues  
In order to build the package on Ubuntu 14.04, remove the SystemRequirements: C++14 line from DESCRIPTION and set R to use a compiler that defaults to C++14. 
See <http://dirk.eddelbuettel.com/blog/2017/06/13/>
