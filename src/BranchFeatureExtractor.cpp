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

namespace ns = neurostr::selector;
namespace nm = neurostr::measure;
namespace nlm = neurostr::measure::lmeasure;

namespace branch_features {

 std::string escape_string(const std::string& s){
   return "\""+s+"\"";
 }

 std::string escape_string(const char *c){
   return escape_string(std::string(c));
 }


 std::map<std::string, float> get_branch_measures(const neurostr::Branch& b){

   std::map<std::string, float> m; // measures
   bool is_bifurcation = false;


  // Number of nodes
  m.emplace( "N_nodes", b.size());

  // Tortuosity
  m.emplace( "tortuosity", nm::tortuosity(b));

  // Hillman taper rate
  m.emplace( "hill_taper_rate", nm::taper_rate_hillman(b));

  // Burker taper rate
  m.emplace( "burker_taper_rate", nm::taper_rate_burker(b));

  // Centrifugal order
  m.emplace( "centrifugal_order", b.order());

  // Length
  m.emplace("length", b.length());

  // Number of descs
  int ndescs = b.neurite().find(b).number_of_children();
  is_bifurcation = ndescs > 1;
  m.emplace("N_descs", ndescs);

  // Is terminal
  auto terminals = ns::neurite_terminal_branches(b.neurite());
  bool inside  = false;
  for (auto br_it = terminals.begin(); br_it != terminals.end(); ++br_it)
    if (br_it->get() == b) inside = true;
  m.emplace("is_terminal", (float) inside );

  // Is pre-terminal
  auto pre_terminals = ns::neurite_pre_terminal_branches(b.neurite());
  inside  = false;
  for (auto br_it = pre_terminals.begin(); br_it != pre_terminals.end(); ++br_it)
    if (br_it->get() == b) inside = true;
  m.emplace("is_pre_terminal", (float) inside );

  // Num. of tips
  auto it = b.neurite().find(b);
  auto cit = b.neurite().begin_children(it);
  auto n1 = NAN;
  auto n2 = NAN;
  if(it.number_of_children() == 2){
      n1 = std::distance(b.neurite().begin_leaf(cit),b.neurite().end_leaf(cit));
      ++cit;
      n2 = std::distance(b.neurite().begin_leaf(cit),b.neurite().end_leaf(cit));
      if (n1 == 0.0) n1 = 1.0;
      if (n2 == 0.0) n2 = 1.0;
  }
  m.emplace("n_tips_left", (float) n1);
  m.emplace("n_tips_right", (float) n2 );
  auto pas = NAN;
  if (ndescs == 2) {
      if (n1 + n2 > 2) {
          pas = std::abs(n1 - n2) / (n1 + n2 - 2);
      }
  }
  m.emplace("pas", (float) pas );

  m.emplace("x", (float) b.last().x());

  m.emplace("y", (float) b.last().y());

  m.emplace("z", (float) b.last().z());
  //
  // N tips
  // m.emplace("n_tips", nlm::n_tips(b));


  // Volume
  m.emplace("volume",   nm::selectorMeasureCompose(ns::branch_node_selector,
                          nm::measureEachAggregate( nm::node_volume,
                                                    nm::aggregate::sum_aggr_factory<float,float>(0.0)))(b));

  // Surface
  m.emplace("surface",   nm::selectorMeasureCompose(ns::branch_node_selector,
                          nm::measureEachAggregate( nm::node_compartment_surface,
                                                    nm::aggregate::sum_aggr_factory<float,float>(0.0)))(b));

  // Box volume
  m.emplace("box_volume",   nm::selectorMeasureCompose(ns::branch_node_selector,
                                                       nm::box_volume)(b));

  // Fractal dim
  m.emplace("fractal_dimension",   nm::branch_fractal_dim(b));


  /** Bifurcation measures **/
  if(is_bifurcation){

    // Local bifurcation angle
    m.emplace( "local_bifurcation_angle", nm::local_bifurcation_angle(b));

    // Local tilt angle
    m.emplace( "local_tilt_angle", nm::local_tilt_angle(b));

    // Local torque angle
    m.emplace( "local_torque_angle", nm::local_torque_angle(b));

    // Remote bifurcation angle
    m.emplace( "remote_bifurcation_angle", nm::remote_bifurcation_angle(b));

    // Remote tilt angle
    m.emplace( "remote_tilt_angle", nm::remote_tilt_angle(b));

    // Remote torque angle
    m.emplace( "remote_torque_angle", nm::remote_torque_angle(b));

    // Child diameter ratio
    m.emplace( "child_diam_ratio", nm::child_diam_ratio(b));

    // Partition asymmetry
    m.emplace( "partition_asymmetry", nm::partition_asymmetry(b)) ;

    // Vertex type
    m.emplace( "vertex_type", nm::vertex_type(b)) ;
  } else {
    NSTR_LOG_(info, std::string("Branch ") + b.idString() + " is not a bifurcation branch. Bif. measures are skipped" );
  }

  return m;

}

void print_branch_id(const neurostr::Branch& b, std::ostream& os){
  os << escape_string("neuron") << " : " << escape_string(b.neurite().neuron().id()) << ", ";
  os << escape_string("neurite") << " : " << b.neurite().id() << ", ";
  os << escape_string("neurite_type") << " : ";
  if(b.neurite().type() == neurostr::NeuriteType::kAxon){
    os << escape_string("Axon");
  } else if(b.neurite().type() == neurostr::NeuriteType::kApical){
    os << escape_string("Apical");
  } else if(b.neurite().type() == neurostr::NeuriteType::kDendrite){
    os << escape_string("Dendrite");
  } else {
    os << escape_string("Unknown");
  }

  os << ", " << escape_string("branch") << " : " << escape_string(b.idString()) ;
  os << ", " << escape_string("node") << " : " << b.last().id() ;
}

// Note: This should be done with rapidjson
void print_measures(std::map<std::string, float>& m ,
                            std::ostream& os ){
  bool first = true;
  // Measures json element
  os << escape_string("measures") << " : { ";

  // Print each measure
  for(auto it = m.begin(); it!=m.end();++it ){

    // If values vector is not empty
    if(!std::isnan(it->second)){
      if(first){
        first = false;
      } else {
        os << ", ";
      }

     // Print key and value
      os << escape_string(it->first) << " : " << std::to_string(it->second) ;

    } // End if value is nan

  } // End for loop
  os << " }"; // Close measures
}

void print_branch_measures(const neurostr::Branch& b, std::ostream& os){
  os << "{" ;
  // Print neurite ID
  print_branch_id(b,os);
  os << ", ";

  // Get measures
  auto m = get_branch_measures(b);

  // Print them
  print_measures(m,os);

  // End obj
  os << "}";
}

}

//' Compute branch features
//'
//' @export
// [[Rcpp::export]]
std::string compute_branch_features(std::string ifile)
{
  // Log errors in std::cerr
  neurostr::log::init_log_cerr();
  neurostr::log::enable_log();

  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);

  // Measure each neurite and output report
  bool first = true;
  std::cout << "[" << std::endl;

  // For each neuron
  for(auto n_it = r->begin(); n_it != r->end(); ++n_it){
    neurostr::Neuron& n = *n_it;

    // Select branch subset
    std::vector<ns::const_branch_reference> branches;
    branches = ns::neuron_branch_selector(n);

    // Select branches
    for(auto it = branches.begin(); it != branches.end(); ++it){
      if(!first){
        std::cout << " , ";
      }
      first = false;

      branch_features::print_branch_measures(*it, std::cout);
    }
  }

  std::cout << "]" << std::endl;

}

