/**
 * Neurolucida Internal structure
 *
 * @author Luis Rodriguez
 *
 */
#ifndef NEUROSTRLIB_IO_NL_STRUCTURE_H_
#define NEUROSTRLIB_IO_NL_STRUCTURE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

#include <neurostr/core/neurite.h>
#include <neurostr/core/neurite_type.h>


namespace neurostr {
namespace io {

/********************
 * @note Internally neurolucida seems to work with nested blocks, creating some sort of block hierarchy.
 * Here we differenciate between vanilla blocks: property, sample and string
 * (that just contain some fundamental value), and container blocks, that are like boxes that create
 * the hierarchy mentioned before. Each container block have one or more info fields. 
 * We have figured out some of them, but there are
 * some unknown fields still that might be important for other purposes.
 *
 */
 
/**
* @brief Neurolucida block types
*/
enum class block_type : std::uint16_t {
  ROOT = 0x0000,  // Custom block to denote root block
  STRING = 0x0001,
  SAMPLE = 0x0101,
  SAMPLE_LIST = 0x0103,
  PROPERTY = 0x0104,
  PROPERTY_LIST = 0x0105,
  CONTOUR = 0x0201,
  TREE = 0x0202,
  SUB_TREE = 0x0203,
  MARKERSET = 0x0204,
  MARKERSET_LIST = 0x0205,
  SPINE = 0x0206,
  SPINE_LIST = 0x0207,
  TEXT = 0x0208,
  DESCRIPTION = 0x0401,
  THUMBNAIL = 0x0402,
  IMAGE = 0x0403,
  END = 0xAABB,
  UNKNOWN = 0xCAFE
};

/**
 * @brief Returns true if the given block type its named
 * @param b Block type
 * @return True if the block type is named
 */
inline bool named(block_type& b) {
  switch (b) {
  case block_type::CONTOUR:
    return (true);
  default:
    return (false);
  }
}

/**
* @brief Contour header in DAT files
*/
typedef struct {
  std::uint16_t closed;  // Closed contour flag
  std::uint8_t face_color[3];
  std::uint8_t back_color[3];
} contour_info;
const int k_contour_info_len = sizeof(contour_info);

/**
* @brief Neurolucida binary tree types
*/
enum class tree_type_cd : std::uint8_t {
  AXON = 0x00,
  DENDRITE = 0x01,
  APICAL = 0x02,
  SOMA = 0xFD,
  NONE = 0xFC,
  SAMPLE_CONTOUR = 0xFE,
  UNKNOWN = 0xFF
};

/**
 * @brief Converts the given tree type code to string
 * @param t Tree type code
 * @return  String
 */
std::string tree_type_tostr(const tree_type_cd& t);

std::ostream& operator<<(std::ostream& os, const tree_type_cd& t);

/**
* @brief Tree header in DAT files
*/
typedef struct {
  tree_type_cd type;
  uint8_t face_color[3];
  uint8_t back_color[3];
} tree_info;

// NEED TO DO THIS BC OF PADDING
const int k_tree_info_len = sizeof(tree_info);

/**
* @brief SubTree header in DAT files
*/
typedef struct {
  uint16_t value1;  // Unknown meaning
  uint16_t value2;  // Unknown meaning
} subtree_info;
const int k_subtree_info_len = sizeof(subtree_info);

/**
 * @brief Given a neurite. Set its type looking at its properties
 * @param n Neurite
 * @return Neurite Type
 */
NeuriteType set_neurite_type_by_nlproperties(Neurite& n);

/**
* @brief Markerset structure for NL files.
*/
typedef struct {
    std::string name;
    std::uint8_t color[4];
    std::vector<property_type> properties; 
    std::vector<Node> samples;
} marker_type;

} // namespace io
} // namespace neurostr

#endif
