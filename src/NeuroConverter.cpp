#include <string>
#include <iostream>
#include <algorithm>
#include <exception>

#include <boost/format.hpp>

#include "log.h"
#include "parser_dispatcher.h"
#include "SWCWriter.h"
#include "JSONWriter.h"

//' Converts a reconstruction to SWC or JSON.
//'
//' @export
// [[Rcpp::export]]
void convert(std::string ifile,  std::string ofile, bool correct = false)
{

  neurostr::log::init_log_cerr();
  neurostr::log::enable_log();

  // Output Format
  std::string ext;

  // Apply RDP simplification
  float eps = 0.0;
  // ("help,h", "Produce help message")
  // ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
  // ("format,f", po::value< std::string>(&ext), "Output format (swc or json)")
  // ("output,o", po::value< std::string>(&ofile), "Output file")
  // ("correct,c", "Try to correct errors in the reconstruction")
  // NSTR_LOG_(error, "Input/output file required");

  // Create ofstream /ifstreams
  std::ofstream ofs(ofile);

  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);

  // Simpify / correct
  for(auto it = r->begin(); it != r->end(); ++it){
    if(correct) it->correct();
    if(eps != 0.0 ){
      it->simplify(eps);
    }
  }

  // Transform extension to lower
  std::transform(ext.begin(),ext.end(),ext.begin(),::tolower);

  // Select a writer depending on the extension
  if(ext == "swc"){
    if(r->size() > 1){
      NSTR_LOG_(warn, "The output SWC file will only contain the first neuron in the reconstruction. The rest are ignored");
    }
    neurostr::io::SWCWriter writer(ofs);
    writer.write(*(r->begin()));  // Writes first neuron

  } else if (ext == "json"){
    neurostr::io::JSONWriter writer(ofs);
    writer.write(*r);
  } else {
    // Error - Unrecognized
    NSTR_LOG_(error,"Unrecognized output format");
    std::cout << "Accepted formats: swc, json" << std::endl << std::endl ;
    return;
  }

  // Close stream - Reconstruction should be autom. free'd (unique_ptr)
  ofs.close();
}
