#include <stdio.h> 

#include <string>
#include <iostream>
#include <algorithm>
#include <boost/format.hpp>

#include "log.h"
#include "neuron.h"

#include "universal_measure.h"
#include "branch_measure.h"
#include "neurite_measure.h"
#include "node_measure.h"
#include "aggregate.h"
#include "measure_operations.h"

#include "neurite_selector.h"

#include "parser_dispatcher.h"
#include "lmeasure_decl.h"
#include "branch_features.h"

#include "node_features.h" 

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

#include "predefined_validators.h" 
#include "validator_tool.h"


namespace ns = neurostr::selector;
namespace nm = neurostr::measure;
namespace nlm = neurostr::measure::lmeasure;

//' Compute branch features
//'
//' @export
// [[Rcpp::export]]
std::string compute_branch_features(std::string ifile, bool omitapical = false, bool omitaxon = false, bool omitdend = false, bool correct = false, std::string selection = "all") {
  std::stringstream outbuffer;
  compute_branch_measures(ifile, omitapical, omitaxon, omitdend, correct, selection, outbuffer );
  return outbuffer.str();
} 


//' Compute node features
//'
//' Use resolved paths, i.e., not with ~ for the home directory.
//'
//' @example
//' file <- system.file("extdata/", "C030502A.swc", package = "neurostr")
//' convert(file, ext = "swc") 
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


//' Converts a reconstruction to SWC or JSON.
//'
//' @export
// [[Rcpp::export]]
std::string convert(std::string ifile,  std::string ext, float eps = 0.0, bool correct = false)
{ 

  neurostr::log::init_log_cerr();
  neurostr::log::enable_log(); 

  std::ofstream ofs(ofile);
  convert(ifile, ofs, ext, correct, eps); 
  ofs.close(); 

  return ofs.str();
}

namespace nv = neurostr::validator;


template <typename V>
void output_validation(const neurostr::Neuron& n,
                       const V& validation,
                       std::ostream& os,
                       const bool exhaustive,
                       std::stringstream& outbuffer,
                       bool& first){

    V test = validation;
    test.validate(n);

    if(!first)
      outbuffer << "," << std::endl;

    test.toJSON(os,!exhaustive);

    first = false;
};


//' Compute branch features
//'
//' @export
// [[Rcpp::export]]
std::string validate(std::string ifile)
{

  neurostr::log::init_log_cerr();
  //neurostr::log::log_level(neurostr::log::warning); // emit warning error or critical

  // Parameters
  float planar_rec_threshold = 1.01;
  float linear_branch_threshold = 1.01;
  int dcount_min = 2;
  int dcount_max = 13;

  // Tests
  bool attached = true;
  bool soma = true;
  bool planar = true;
  bool dendcount = true;
  bool apcount = true;
  bool axoncount = true;
  bool trif = true;
  bool linear = true;
  bool zerolen = true;
  bool intersec = true;
  bool nodecr = true;
  bool segcoll = false ;
  bool branchcoll = true;
  bool angles =true;

  // Print all outs
  bool exhaustive = false;

  // Strict mode
  bool nostrict = false;

  // nodiams
  bool nodiams = false;

  // 2D
  bool bidim = false;

  // omits
  bool omitapical = false;
  bool omitaxon = false;
  bool omitdend = false;
  bool omitsoma = false; 

  std::stringstream outbuffer;

  do_validate(outbuffer, ifile, attached, soma, planar, dendcount, apcount, axoncount, trif, linear, zerolen, intersec , nodecr, segcoll , branchcoll, angles, exhaustive, nostrict, nodiams, bidim, omitapical, omitaxon, omitdend, omitsoma, planar_rec_threshold, linear_branch_threshold, dcount_min, dcount_max);

  return outbuffer.str();
}
