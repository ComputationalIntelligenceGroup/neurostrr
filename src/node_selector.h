#ifndef NEUROSTR_SELECTOR_NODE_SELECTOR_H_
#define NEUROSTR_SELECTOR_NODE_SELECTOR_H_

#include <functional>

#include "selector.h"
#include "node.h"
#include "branch.h"
#include "neurite.h"
#include "neuron.h"

namespace neurostr {
namespace selector {

// Node self selector (Actually this is useless)
const auto node_self = [](const Node& n) -> const Node& {
  return n;
};

const auto node_parent = [](const Node& n) -> const Node& {
  
  if(n.valid_parent()) return n.parent();
  if(!n.valid_branch()) return n;
  
  // If node is root (if any)
  if(n.branch().has_root() && n == n.branch().root()){
    // Find branch
    auto branch_it = n.branch().neurite().find(n.branch());
    if(branch_it.node->parent == nullptr){
      // No parent branch - no parent (poor node)
      return n;
    }
    else{
      // Parent branch is the end-2th node
      n.parent(&(*(branch_it.node->parent->data.end()-2)));
    }
  // Node is not the first
  }else if(n.branch().first() != n){
    auto it = std::find(++(n.branch().begin()), n.branch().end(), n);
    --it;
    n.parent(&(*it));
  // Node is the first
  } else {
    auto branch_it = n.branch().neurite().find(n.branch());
    if(branch_it.node->parent == nullptr){
      if(n.branch().has_root()){
        n.parent(&(n.branch().root()));
        return n.branch().root();
      } else {
        return n;
      }
    }
    else{
      // Parent branch is the last node
      n.parent(&(branch_it.node->parent->data.last()));
    }
  }
  
  return n.parent();
};

// IN: Node - Out: Branch
const auto node_branch_selector = [](const Node& n) -> const Branch& {
  return n.branch();
};

// IN: Node SET - Out: Node SET
const auto node_bifurcation_selector = [](
  const std::vector<const_node_reference>::iterator & b,
  const std::vector<const_node_reference>::iterator & e) 
    -> std::vector<const_node_reference> {
      
      
  std::vector<const_node_reference> selection;
  for (auto it = b; it != e; ++it){
    
    // Copy reference
    const Branch& branch = it->get().branch();
    
    // Check that we are the last element of the branch
    if( branch.last() == it->get() ){
      // Then check that the branch has at least two children
      if(branch.neurite().find( branch ).number_of_children() >= 2){
        selection.emplace_back(*it);  
      }
    }
  }
  return selection;
};


// IN: Node SET - Out: Node SET
const auto node_terminal_selector = [](
  const std::vector<const_node_reference>::iterator & b,
  const std::vector<const_node_reference>::iterator & e) 
    -> std::vector<const_node_reference> {
      
      
  std::vector<const_node_reference> selection;
  for (auto it = b; it != e; ++it){
    
    // Copy reference
    const Branch& branch = it->get().branch();
    
    // Check that we are the last element of the branch
    if( branch.last() == it->get() ){
      // Then check that the branch has at least two children
      if(branch.neurite().find( branch ).number_of_children() == 0){
        selection.emplace_back(*it);  
      }
    }
  }
  return selection;
};


// IN: Node - Out: Node SET
const auto node_subtree_selector = [](const Node& n) 
  -> std::vector<const_node_reference> {

  // Copy reference
  const Branch& branch = n.branch();
  
  std::vector<const_node_reference> selection;
  
  // Remaining nodes in the branch
  auto it = branch.begin();
  for ( ; *it != n; ++it); // Skip 
  for (; it != branch.end(); ++it){
      selection.emplace_back(*it);
  }
  
  // Subtree
  auto branch_it = branch.neurite().find( branch );
  for( auto sbit = (++branch.neurite().begin_branch_subtree(branch_it)) ; 
       sbit != branch.neurite().end_branch_subtree(branch_it) ;
       ++sbit){
    for (auto it = sbit->begin(); it != sbit->end(); ++it) {
      selection.emplace_back(*it);
    }
  }

  return selection;
};


// IN: Node - Out: Node SET
const auto node_subtree_terminals = [](const Node& n) 
  -> std::vector<const_node_reference> {

  // Copy reference
  const Branch& branch = n.branch();
  auto branch_it = branch.neurite().find( branch );
  
  std::vector<const_node_reference> selection;
  
  for(auto it = branch.neurite().begin_leaf(branch_it); 
      it != branch.neurite().end_leaf(branch_it); 
      ++it){
      selection.emplace_back(it->last());
  };
  return selection;
};

// IN: Node - Out: Nodeset
const auto node_stem_selector = [](const Node& n) -> std::vector<const_node_reference> {

  std::vector<const_node_reference> selection;  
  const Branch& branch = n.branch();
  
  // Copy remaining nodes
  auto it = branch.rbegin();
  for (; *it != n; ++it);
  for(; it != branch.rend(); ++it){
    selection.emplace_back(*it);
  }

  auto branch_it = branch.neurite().find( branch );
       
  for( auto stit = (++branch.neurite().begin_stem(branch_it)) ; 
       stit != branch.neurite().end_stem(branch_it) ;
       ++stit){
    for (auto it = stit->rbegin(); it != stit->rend(); ++it) {
      selection.emplace_back(*it);
    }
  }

  return selection;
};

// IN: Node - OUT: Nodeset
const auto node_descendants = [](const Node& n ) -> std::vector<const_node_reference> {
  
  // Last node in the branch
  std::vector<const_node_reference> selection;
  
  // Copy reference
  const Branch& branch = n.branch();
    
  // Check that we are the last element of the branch
  if( branch.last() == n ){
    
    // Find branch
    auto branch_it = branch.neurite().find( branch );
    
    for( auto it  = branch.neurite().begin_children(branch_it);
              it != branch.neurite().end_children(branch_it);
              ++it){
      selection.emplace_back(*(it->begin()));
    }
  } else {
    auto node_it = std::find(branch.begin(),branch.end(),n);
    selection.emplace_back(*(++node_it));
  }
  return selection;
};

}; // End selector
}; // End neurostr

#endif
