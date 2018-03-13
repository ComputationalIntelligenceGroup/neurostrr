#ifndef NEUROSTR_CORE_NODEDATA_H_
#define NEUROSTR_CORE_NODEDATA_H_

#include <cstdint>
#include <vector>
#include <array>
#include <iostream>
#include <stdexcept>

#include <boost/geometry.hpp>

#include <Eigen/Geometry>

#include <neurostr/core/definitions.h>
#include <neurostr/core/property.h>
#include <neurostr/core/geometry.h>

namespace neurostr {

  /**
   * @class Node
   * @file node.h
   * @brief Node concept class. stores a numeric ID, x,y,z coordinates and point radius
   * Also stores references to its branch and parent node if they exist and
   * implements basic operations.
   */
class Node : public WithProperties{

  public:
 
  using id_type = int;

  /**
   * @brief Empty constructor, creates a node with ID -1 at 0,0,0 with radius 0
   * @return Node
   */
  Node();
  
  /**
   * @brief Creates a node with ID id at 0,0,0 with radius 0
   * @param id Node id
   * @return Node
   */
  Node(int id);
      
  /**
   * @brief Creates a node with ID id at position p with radius r
   * @param id Node id
   * @param p Node position (3D point)
   * @param r Node radius
   * @return Node
   */
  Node( int id, const point_type& p, double r);
  
  /**
   * @brief Creates a node with ID id at position (x,y,z) with radius r
   * @param node_id Node id
   * @param x Node x coordinate
   * @param y Node y coordinate
   * @param z Node z coordinate
   * @param r Node radius
   * @return Node
   */
  Node(int id, double x, double y, double z, double r); 

  /**
   * @brief Default
   */
  Node(const Node& n) = default;
  /**
   * @brief Default
   */
  Node(Node&& n) = default;
  
  /**
   * @brief Default
   */
  Node& operator=(const Node& n) = default;
  
  /**
   * @brief Default
   */
  Node& operator=(Node&& n) = default;

  /**
   * @brief Empty destructor
   * @return 
   */
  ~Node() {}

  /**
   * @brief Compare two nodes by ID.
   * @param n The other node
   * @return True if both ids are equal
   */
  bool operator==(const Node& n) const { return n.id_ == id_; }
  
  /**
   * @brief Compare two nodes by ID.
   * @param n The other node
   * @return True if both ids are different
   */
  bool operator!=(const Node& n) const { return n.id_ != id_; }

  // Accesors
  
  /**
   * @brief Returns node radius
   * @return radius \type{float}
   */
  float radius() const { return radius_; }
  
  /**
   * @brief Returns node id
   * @return ID \type{int}
   */
  const id_type id() const { return id_; }
  
  /**
   * @brief Return node position
   * @return position \type{point_type}
   */
  const point_type& position() const { return position_; }
  
  /**
   * @brief Returns node X coordinate
   * @return x coordinate \type{float}
   */
  float x() const { return geometry::get<0>(position_); }
  
  /**
   * @brief Returns node Y coordinate
   * @return x coordinate \type{float}
   */
  float y() const { return geometry::get<1>(position_); }
  
  /**
   * @brief Returns node Z coordinate
   * @return z coordinate \type{float}
   */
  float z() const { return geometry::get<2>(position_); }
  
  /**
   * @brief Checks wether the parent branch referece is valid
   * @return True if the reference is valid
   */
  bool valid_branch() const { return branch_ != nullptr; }
  
  /**
   * @brief  Returns parent branch
   * @throws runtime_exception If we attempt to access null branch
   * @return Parent branch reference
   */
  Branch& branch();
  
  /**
   * @brief  Returns parent branch
   * @throws runtime_exception If attempt to access null branch
   * @return Parent branch const reference
   */
  const Branch& branch() const ; 
  
  /**
   * @brief Changes node position for \param{p}
   * @param p New node position
   * @return Updated node reference
   */
  Node& position(const point_type& p);
  
  /**
   * @brief Changes node position to \code{x},\code{y},\code{z}
   * @param x New x coordinate
   * @param y New y coordinate
   * @param z New z coordiante
   * @return Updated node reference
   */
  Node& position(float x, float y, float z);

  /**
   * @brief Changes node radius to \code{r}
   * @param r New node radius
   * @return Updated node reference
   */
  Node& radius(float r);
  
  /**
   * @brief Changes node parent branch for \code{b}
   * @param b Parent branch pointer
   * @return Updated node refernece
   */
  Node& branch(Branch* b );
  /**
   * @brief Changes node parent node for \code{n}
   * @param n Parent node pointer
   * @return Updated node refernece
   */  
  void parent(const Node* n ) const; // Mutable
  
  /**
   * @brief Constructs the vector form \code{this} to \code{p}
   * @param p Vector end point
   * @return Vector from \code{this} to \code{p}
   */
  point_type vectorTo(const point_type& p) const;
  
  /**
   * @brief Constructs the vector form \code{this} to \code{n}
   * @param n Vector end position
   * @return Vector from \code{this} to \code{n}
   */
  point_type vectorTo(const Node& n) const;
  
  /**
   * @brief Euclidean distance between \code{this} and \code{p}
   * @param p 3D Point
   * @return Euclidean distance between \code{this} and \code{p}
   */
  float distance(const point_type& p) const;
  
  /**
   * @brief Euclidean distance between \code{this} and \code{n}
   * @param n Node
   * @return Euclidean distance between \code{this} and \code{n}
   */
  float distance(const Node& n) const;

  
  /**
   * @brief Checks whether the parent reference is valid
   * @return True if the reference is valid
   */
  bool valid_parent() const { return parent_ != nullptr; }
  
  /**
   * @brief Returns a reference to the parent node
   * @throws runtime_exception Attempt to access null parent
   * @return Parent node reference
   */
  const Node& parent() const;
  
  /**
   * @brief Returns a reference to the parent node
   * @throws runtime_exception Attempt to access null parent
   * @return Parent node reference
   */
  //Node& parent() ;
  
  /**
   * @brief Distance to our parent node (given). Alias for distance.
   * Length result is cached
   * @param parent Parent node
   * @return Euclidean distance
   */
  float length(const Node& parent) const;
  
  /**
   * @brief Distance to our parent node (stored). Alias for distance.
   * Length result is cached
   * @return Euclidean distance
   */
  float length() const;
  
  /**
   * @brief Invalidate length cached value
   */
  void invalidate_length() const { valid_length_ = false; };

  /**
   * @brief Compute node local basis. parent->node vector determines
   * the first vector of the basis. The rest are computed to create a right-oriented
   * orthonormal basis using up vector. Basis are cached.
   * @param parent Parent node
   * @param up Up reference (Z) in the environment
   */
  const std::array<point_type, 3>& local_basis(const Node& parent ,
                                               const point_type& up) const;
                                               
  
/**
   * @brief Compute node local basis. parent->node vector determines
   * the first vector of the basis. The rest are computed to create a right-oriented
   * orthonormal basis using up vector. Basis are cached. Uses stored parent
   * @param up Up reference (Z) in the environment
   */                                            
  const std::array<point_type, 3>& local_basis(const point_type& up) const;
                            
  /**
   * @brief Invalidate local basis cached value
   */
  void invalidate_basis() const { valid_local_basis_ = false; }
  
  /**
   * @brief Traslate the node by the vector given
   * @param traslation_v Traslation vector
   */
  void traslate(const point_type& traslation_v );
  
  /**
   * @brief Rotates the Node applying th quaternion q
   * @param q Rotation quaternion
   */
  void rotate(const Eigen::Quaternionf& q);
  
  /**
   * @brief Scales the node wrt the reference point \code{p} by \code{r}
   * @param r Scalar reduction
   * @param p Reference point
   */
  void scale(float r, const point_type& p );
  
  /**
   * @brief Scales the node multiplying each coordinate for the given scale
   * @param rx X scaling 
   * @param ry Y scalin
   * @param rz Z scaling
   */
  void scale(float rx, float ry, float rz);

  // To string
  friend std::ostream& operator<<(std::ostream&, const Node&);

  private:
 
 /**
  * @brief Throws an exception if branch is null
  */
  void _check_null_branch() const;
  
  /**
  * @brief Throws an exception if parent is null
  */
  void _check_null_parent() const;
  
  // Node identifier
  id_type id_;
  
  // Parent branch
  Branch* branch_;
  mutable const Node* parent_; // Parent node

  // Node properties
  point_type position_;
  float radius_;

  // Cached values
  mutable bool valid_length_;
  mutable float length_;

  // More cached values
  mutable bool valid_local_basis_;
  mutable std::array<point_type, 3> local_basis_;


};  // Class node

}  // Namespace neurostr

#endif  // NEUROSTR_BASE_NODEDATA_H_
