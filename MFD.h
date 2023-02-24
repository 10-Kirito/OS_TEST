#ifndef MFD_H
#define MFD_H

#include "UFD.h"
#include <vector>


class MFD
{
public:
  MFD();

  void addUser(UFD user_add);
  std::vector<UFD> getUser(){ return user_vector; }
  MFD(MFD &&) = default;
  MFD(const MFD &) = default;
  MFD &operator=(MFD &&) = default;
  MFD &operator=(const MFD &) = default;
  ~MFD();

private:
  std::vector<UFD> user_vector;
};

#endif // DEBUG
