#ifndef NEUROSTR_VALIDATION_PREDEFINED_VALIDATORS_H_
#define NEUROSTR_VALIDATION_PREDEFINED_VALIDATORS_H_

#include <string>

#include "selector.h"

#include "measure.h"
#include "neurite_measure.h"
#include "branch_measure.h"
#include "neuron_measure.h"

#include "checks.h"
#include "validator.h"

namespace neurostr {
namespace validator {

namespace ns = neurostr::selector;
namespace nm = neurostr::measure;
namespace nv = neurostr::validator;


/**
* @brief Neurite validator. Checks that neurites are attached to the soma
**/
const auto neurites_attached_to_soma =
    nv::create_validator(nm::root_is_soma,
                         nv::is_true,
                         "Neurites are attached to soma",
                         "Fails if neurites are not attached to the soma");

/**
* @brief Neuron validator. Checks that neuron soma is defined
**/
const auto neuron_has_soma =
    nv::create_validator(nm::has_soma,
                         nv::is_true,
                         "Neuron has soma",
                         "Pass if the neuron has at least one soma node" );


/**
* @brief Neurite validator. Verifies that neurite reconstruction is not planar by
* checking that its non-axis aligned box volume is over the minimum value (close to 0)
**/
auto planar_reconstruction_validator_factory(float min) {
  return nv::create_validator( 
                              nm::selectorMeasureCompose(ns::neurite_node_selector, nm::box_volume),
                              nv::range_check_factory(min),
                              "Planar neurite validation",
                              "Fails if the non-axis aligned box volume of the neurite is lower than predefined threshold");
}

/**
* @brief Neuron validator. Checks that the number of dendrites in the neuron is in the range [min,max)
**/
auto dendrite_count_validator_factory(unsigned int min, unsigned int max) {
  return nv::create_validator(
                              nm::neuron_dendrite_counter,
                              nv::range_check_factory<unsigned int>(min, max),
                              "Basal dendrite count",
                              "Pass if the dendrite count is greater or equal than " + std::to_string(min) + " and less than " + std::to_string(max));
} 

/**
* @brief Neuron validator. Checks that the number of apical dendrites in the neuron is not greater than 2
* @param strict If true, Neurons with no apical dendrite are rejected
**/
auto apical_count_validator_factory(bool strict = false) {
  if(strict) {
    return nv::create_validator(
                              nm::neuron_apical_counter,
                              nv::range_check_factory<unsigned int>(1,2),
                              "Strict apical dendrite count",
                              "Pass if and only if there is one apical dendrite");
  } else {
    return nv::create_validator(
                              nm::neuron_apical_counter,
                              nv::range_check_factory<unsigned int>(0,2),
                              "Tolerant apical dendrite count",
                              "Fails if there are two or more apical dendrites");
  } 
}

/**
* @brief Neuron validator. Checks that the number of axons in the neuron is not greater than 2
* @param strict If true, Neurons with no axon are rejected
**/
auto axon_count_validator_factory(bool strict = false) {
  if(strict) {
    return nv::create_validator(
                              nm::neuron_axon_counter,
                              nv::range_check_factory<unsigned int>(1,2),
                              "Strict axon count",
                              "Pass if and only if there is one axon");
  } else {
    return nv::create_validator(
                              nm::neuron_axon_counter,
                              nv::range_check_factory<unsigned int>(0,2),
                              "Tolerant axon count",
                              "Fails if there are two or more axons");
  } 
}

/**
* @brief Node validator. Checks that the number of descendants of a node is at most 2.
*/
const auto no_trifurcations_validator = nv::create_validator(
                              nm::desc_count,
                              nv::range_check_factory<unsigned int>(0,3),
                              "Trifurcation validator",
                              "Fails on those nodes with more than two descendants"); // Check that each node has a number of descs < 3

/**
 * @brief Branch validator. Verifies that the branch reconstruction is not a prefect straight line by
 * checking that its tortuosity value is not equal to 1
 * @param min Minimum accepted tortuosity value
 */
auto linear_branches_validator_factory(float min = 1.01) {
    return nv::create_validator(
                         nm::tortuosity,
                         nv::range_check_factory<float>(min),
                         "Linear branch validator",
                         "Fails when the branch tortuosity falls below " + std::to_string(min) );
}

/**
 * @brief Node validator. Checks that the length of the compartment associated to each node 
 * is not zero.
 */
const auto zero_length_segments_validator =
  nv::create_validator(nm::node_length_to_parent,
                       nv::range_check_factory<float>(1E-6),
                       "Zero length segments validator",
                       "Fails when a segment length is close to zero");

/**
 * @brief Node validator. Check that the distance between two consecutive nodes is
 * greater than the sum of their radiuses.
 */                       
const auto radius_length_segments_validator =
  nv::create_validator(nm::node_length_to_parent_border,
                       nv::range_check_factory<float>(1E-6),
                       "Length smaller than radius validator",
                       "Fails when two consecutive node spheres intersection is not empty");
                       
/**
*@brief Node validator. Checks that the node radius is not increasing.
**/
const auto increasing_radius_validator =
  nv::create_validator(nm::node_segment_taper_rate_hillman,
                       nv::range_check_factory<float>(0),
                       "Non-decreasing diameter validator",
                       "Fails when diameter increases between two consecutive nodes") ;


/**
* @brief Node validator. Check that the node compartment don't collide with any other
* compartment in the reconstruction
*/
const auto segment_collision_validator =
  nv::create_validator(  nm::segment_distance_to_closest,
                         nv::range_check_factory<float>(0.01),
                         "Segment collision validator",
                         "Fails when the distance between any two segments is too close to zero");


/**
 * @brief Branch validator. Check that the Branch dont collide with any other branch in the neuron
 * @param ignore_diams If true, node diameter value are ignored
 */
auto branch_collision_validator_factory(bool ignore_diams=false){
  return nv::create_validator(  nm::branch_intersects_factory(ignore_diams),
                         nv::empty_string,
                         "Branch collision validator",
                         "Fails when the distance between any two branches is zero");
}

/**
* @brief Node validator. Check that the elongation/bifurcation angle are not too high to be plausible
*/
const auto extreme_angles_validator  =
    nv::create_validator(nm::extreme_angle,
                         nv::is_false,
                         "Extreme angles validator",
                         "Fails when either elongation or bifurcation angles are too high to be plausible");

}  // Validation
}  // Neurostr
#endif

