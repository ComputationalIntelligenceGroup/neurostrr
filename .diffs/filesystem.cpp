#include "filesystem.h"

namespace neurostr {
namespace io{
  // very simple replacements for boost stem and extension
  std::string get_extension(const std::string& path) { 
    return path.substr(path.find_last_of(".") + 1);
  }

  // very simple replacements for boost stem and extension
  std::string get_stem(const std::string& path) { 
    int folder_ind_linux = path.find_last_of("/");
    int folder_ind_win = path.find_last_of("\\");
    int folder_ind = std::max(folder_ind_linux, folder_ind_win);
    int length  = path.find_last_of(".") - folder_ind - 1; 
    return path.substr(folder_ind + 1, length);
  }


}//io
}//neurostr
