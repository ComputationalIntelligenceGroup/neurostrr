#ifndef NEUROSTR_MEASURE_NEURITE_MEASURE_H_
#define NEUROSTR_MEASURE_NEURITE_MEASURE_H_

#include <Eigen/Dense>
#include <Eigen/SVD>

#include "node.h"
#include "neurite.h"

#include "measure_operations.h"
#include "node_measure.h"

#include "selector.h"
#include "node_selector.h"
#include "neurite_selector.h"

namespace neurostr {

namespace measure {
  
const auto root_is_soma = [](const Neurite& n) -> bool {
  return n.root_is_soma();
};


} // measure
} // neurostr

#endif
