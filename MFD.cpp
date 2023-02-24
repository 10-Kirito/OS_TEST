#include "MFD.h"

MFD::MFD() {}

MFD::~MFD() {}

void MFD::addUser(UFD user_add){
  user_vector.emplace_back(user_add);
}


