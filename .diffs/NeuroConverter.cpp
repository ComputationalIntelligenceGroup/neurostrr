#include <string>
#include <iostream>
#include <algorithm>
#include <exception>

#include <boost/format.hpp>

#include "filesystem.h"
#include "log.h"
#include "parser_dispatcher.h"
#include "SWCWriter.h"
#include "JSONWriter.h"
#include "neuro_converter.h"

//' Converts a reconstruction to SWC or JSON.
//'
//' @export
// [[Rcpp::export]]
void convert(std::string ifile,  std::string ofile, bool correct = false)
{

  neurostr::log::init_log_cerr();
  neurostr::log::enable_log(); 

  convert(ifile, ofile, ext, correct, eps); 

}
