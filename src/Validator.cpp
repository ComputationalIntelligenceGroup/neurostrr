#include <stdio.h>

#include <stdio.h>

#include <string>
#include <iostream>
#include <algorithm>
#include <boost/format.hpp>

#include "log.h"
#include "neuron.h"
#include "parser_dispatcher.h"
#include "predefined_validators.h"

namespace nv = neurostr::validator;


template <typename V>
void output_validation(const neurostr::Neuron& n,
                       const V& validation,
                       std::ostream& os,
                       const bool exhaustive,
                       bool& first){

    V test = validation;
    test.validate(n);

    if(!first)
      std::cout << "," << std::endl;

    test.toJSON(os,!exhaustive);

    first = false;
};


//' Compute branch features
//'
//' @export
// [[Rcpp::export]]
 void validate(std::string ifile)
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

  bool first = true;

  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  neurostr::Neuron& n = *(r->begin());

  /** Remove **/
  if(omitapical) n.erase_apical();
  if(omitaxon) n.erase_axon();
  if(omitdend) n.erase_dendrites();


  // Run validations and output report
  std::cout << "[" << std::endl;

  // Execute attached
  if(attached && !omitsoma){
    output_validation(n,
                      nv::neurites_attached_to_soma,
                      std::cout,
                      exhaustive,
                      first);
  }

  // Execute has soma
  if(soma && !omitsoma){
    output_validation(n,
                      nv::neuron_has_soma,
                      std::cout,
                      exhaustive,
                      first);
  }

  // Execute planar rec - disabled for 2D
  if(planar && !bidim){
    output_validation(n,
                      nv::planar_reconstruction_validator_factory(planar_rec_threshold),
                      std::cout,
                      exhaustive,
                      first);
  }

  if(dendcount && !omitdend){
    output_validation(n,
                      nv::dendrite_count_validator_factory(dcount_min,dcount_max),
                      std::cout,
                      exhaustive,
                      first);
  }

  if(apcount && !omitapical){
    output_validation(n,
                      nv::apical_count_validator_factory(!nostrict),
                      std::cout,
                      exhaustive,
                      first);
  }

  if(axoncount && !omitaxon){
    output_validation(n,
                      nv::axon_count_validator_factory(!nostrict),
                      std::cout,
                      exhaustive,
                      first);
  }

  if(trif){
    output_validation(n,
                      nv::no_trifurcations_validator,
                      std::cout,
                      exhaustive,
                      first);
  }

  if(linear){
    output_validation(n,
                      nv::linear_branches_validator_factory(linear_branch_threshold),
                      std::cout,
                      exhaustive,
                      first);
  }

  if(zerolen){
    output_validation(n,
                      nv::zero_length_segments_validator,
                      std::cout,
                      exhaustive,
                      first);
  }

  // Intersecting nodes - disabled when nodiams flag is present
  if(intersec && !nodiams){
    output_validation(n,
                      nv::radius_length_segments_validator,
                      std::cout,
                      exhaustive,
                      first);
  }

  // Non decreasing radius - disabled when nodiams flag is present
  if(nodecr  && !nodiams ){
    output_validation(n,
                      nv::increasing_radius_validator,
                      std::cout,
                      exhaustive,
                      first);
  }

  if(branchcoll){
    output_validation(n,
                      nv::branch_collision_validator_factory(nodiams),
                      std::cout,
                      exhaustive,
                      first);
  }

  if(segcoll){
    output_validation(n,
                      nv::segment_collision_validator,
                      std::cout,
                      exhaustive,
                      first);
  }


  if(angles){
    output_validation(n,
                      nv::extreme_angles_validator,
                      std::cout,
                      exhaustive,
                      first);
  }

  std::cout << "]" << std::endl;

}
