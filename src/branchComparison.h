#ifndef NEUROSTR_METHOD_BRANCHCOMPARISON_H_
#define NEUROSTR_METHOD_BRANCHCOMPARISON_H_

#include <vector>

#include "branch.h"
#include "neuron.h"

#include "selector.h"
#include "node_selector.h"
#include "universal_selector.h"
#include "branch_selector.h"
#include "neurite_selector.h"
#include "neuron_selector.h"


#include "branch_measure.h"

namespace neurostr {
namespace methods {
  
  // align branches and computes theri f. dist
  float oriented_frechet_branch_distance(const Branch &a, const  Branch &b, bool normalize = false);
  
  std::vector<float> inter_pair_distance( Neuron& n , bool restrict_order = false, bool sided = false  );
  std::vector<std::vector<float>> inter_pair_distance_byorder( Neuron& n, bool sided = false);
  
} // Selector
} // Neurostr

#endif
