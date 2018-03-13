#include <neurostr/io/SWCWriter.h>


namespace neurostr {
namespace io {
  
  
SWCWriter::SWCWriter(std::ostream& s) : stream_(s) {};
SWCWriter::~SWCWriter() {};

      
std::ostream& SWCWriter::write(Neuron& n) const{
  writeHeader(n);
  writeData(n);
  return stream_;
}
      
unsigned int SWCWriter::convertNeuriteType(const NeuriteType& t){
  switch(t){
    case NeuriteType::kUndefined: return 0;
    case NeuriteType::kSoma: return 1;
    case NeuriteType::kAxon: return 2;
    case NeuriteType::kDendrite: return 3;
    case NeuriteType::kApical: return 4;
    case NeuriteType::kOther: return 5;
    default: return 5;
  }
}
    
void SWCWriter::writeHeader(Neuron& n) const {
    writeStaticHeader();
    writeNeuroInfo(n);
    writeNeuroProperties(n);
}

void SWCWriter::writeData(Neuron& n) const {
  // Write soma
  if(n.begin_soma() != n.end_soma()){
    writeNode(*n.begin_soma(), convertNeuriteType(NeuriteType::kSoma),no_parent_id);
  }
  
  for(auto it = std::next(n.begin_soma(),1); it != n.end_soma(); ++it){
    writeNode(*it, convertNeuriteType(NeuriteType::kSoma),std::prev(it,1)->id());
  }
    
  // Write Neurites
  for(auto it = n.begin_neurite(); it != n.end_neurite(); ++it){
    unsigned int type = convertNeuriteType(it->type());
    for(auto node = it->begin_node(); node != it->end_node(); ++node){
      auto parent = selector::node_parent(*node);
      unsigned int parent_id;
  
      if (parent == *node) parent_id = no_parent_id;
      else parent_id = parent.id();
      writeNode(*node, type, parent_id);
   }
  }
  
}
      
// Header management
void SWCWriter::writeStaticHeader() const {
  stream_ << boost::format("%c File generated by neurostrlib\n") % comment_char;
}
void SWCWriter::writeNeuroInfo(Neuron& n) const {
  stream_ << boost::format("%c ID %s\n") % comment_char % n.id();
  stream_ << boost::format("%c UP %.3f %.3f %.3f\n") 
    % comment_char 
    % geometry::get<0>(n.up())
    % geometry::get<1>(n.up())
    % geometry::get<2>(n.up());
}

void SWCWriter::writeNeuroProperties(Neuron& n) const {
  for(auto it = n.begin_properties(); it != n.end_properties(); it++)
    writeProperty(*it);
}


void SWCWriter::writeProperty(const PropertyMap::property_type& p) const{
  stream_ << boost::format("%c %s %s\n") % comment_char
      % PropertyMap::key(p) 
      % PropertyMap::value_as_string(p);
}
      
// Data management
void SWCWriter::writeNode(Node& n, unsigned int type, int parent_id) const {
  
  
  stream_ << boost::format("%u %u %.3f %.3f %.3f %.3f %u\n")
      % n.id() 
      % type
      % n.x()
      % n.y()
      % n.z()
      % (n.radius()*2.0)
      % parent_id;
}

    

} // io
} // neurostr
