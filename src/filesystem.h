#ifndef NEUROSTRLIB_IO_FILESYSTEM_H
#define NEUROSTRLIB_IO_FILESYSTEM_H
#include <algorithm>
#include <string>

namespace neurostr {
namespace io{

  /**
   * @brief very simple replacements for boost stem and extension
   * @param ext File path
   * @return std::string extension
   */
  std::string get_extension(const std::string& path);


  /**
   * @brief very simple replacements for boost stem and extension
   * @param ext File path
   * @return std::string stem
   */
  std::string get_stem(const std::string& path);

}
}

#endif
