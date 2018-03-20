#ifndef NEUROSTR_METHODS_BOX_CUTTER_H_
#define NEUROSTR_METHODS_BOX_CUTTER_H_

#include "geometry.h"
#include "branch.h"
#include "neurite.h"
#include "neuron.h"

namespace neurostr{
namespace methods{
  
  void neuronBoxCutter( Neuron& n,const point_type& min_corner, const point_type& max_corner );
  
  void neuriteBoxCutter( Neurite& n, const box_type& box);
  
  bool branchBoxCutter( Branch& b, const box_type& box);
  
  void BoxCutterRestore( Neuron& n );
     
} // methods
} // neurostr


#endif
