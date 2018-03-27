#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

#include "node_features.h"

//' Compute node features
//'
//' @export
// [[Rcpp::export]]
std::string compute_node_features(std::string ifile, bool omitapical = false, bool omitaxon = false, bool omitdend = false, bool correct = false)
{
  // Log errors in std::cerr
  neurostr::log::init_log_cerr();
  neurostr::log::enable_log(); 

  std::stringstream outbuffer; 
  compute_node_features(outbuffer, ifile, omitapical, omitaxon, omitdend, correct); 
  return outbuffer.str();
}


