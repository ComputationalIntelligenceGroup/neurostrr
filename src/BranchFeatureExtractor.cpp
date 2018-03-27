#include <stdio.h>

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

