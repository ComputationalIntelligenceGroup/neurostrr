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

 std::string escape_string(const std::string& s){
   return "\""+s+"\"";
 }

 std::string escape_string(const char *c){
   return escape_string(std::string(c));
 }


std::map<std::string, float> get_node_measures(const neurostr::Node& n){

  std::map<std::string, float> m; // measures

  // Node (compartment) length
  m.emplace( "node_length" , nm::node_length_to_parent(n));
  m.emplace( "node_root_dist", nm::node_distance_to_root(n));
  // Node path distance to root
  m.emplace( "node_root_path", nm::node_path_to_root(n));
  m.emplace( "x", n.x());
  m.emplace( "y", n.y());
  m.emplace( "z", n.z());

  auto zemo = ns::node_subtree_terminals(n);
  int tdegree = std::distance(zemo.begin(), zemo.end());
  m.emplace( "terminal_degree", tdegree);

  auto parent = nm::vector_from_parent(n);
  m.emplace( "change_x", parent.get<0>());
  m.emplace( "change_y", parent.get<1>());
  m.emplace( "change_z", parent.get<2>());

  m.emplace( "node_local_elongation", nm::node_local_elongation_angle(n));
  std::pair<float, float> orientation = nm::node_local_orientation(n);
  m.emplace( "node_local_orientation.a", orientation.first );
  m.emplace( "node_local_orientation.e", orientation.second );
  m.emplace( "extreme_angle", (float) nm::extreme_angle(n));

  return m;

}

void print_node_id(const neurostr::Node& n, std::ostream& os){
  const neurostr::Branch& b = n.branch();
  os << escape_string("neuron") << " : " << escape_string(b.neurite().neuron().id()) << ", ";
  os << escape_string("neurite") << " : " << b.neurite().id() << ", ";
  os << escape_string("neurite_type") << " : ";

  //auto avg_direction = nm::nodeset_avg_orientation(ns::neuron_node_selector(b.neurite().neuron()));

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
  os << ", " << escape_string("node") << " : " << n.id() ;
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

void print_node_measures(const neurostr::Node& b, std::ostream& os){
  os << "{" ;
  // Print neurite ID
  print_node_id(b,os);
  os << ", ";

  // Get measures
  auto m = get_node_measures(b);

  // Print them
  print_measures(m,os);

  // End obj
  os << "}";
}


int main()
{

  std::string ifile = "~/code/bbp-data/data/BBP_SWC/C030502A.swc";
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);

  // Measure each neurite and output report
  bool first = true;
  std::cout << "[" << std::endl;

  // For each neuron
  for(auto n_it = r->begin(); n_it != r->end(); ++n_it){
    neurostr::Neuron& n = *n_it;

    std::vector<ns::const_node_reference> nodes;
    nodes = ns::neuron_node_selector(n);

    // Select branches
    for(auto it = nodes.begin(); it != nodes.end(); ++it){
      if(!first){
        std::cout << " , ";
      }
      first = false;

      print_node_measures(*it, std::cout);
    }
  }

  std::cout << "]" << std::endl;

}

