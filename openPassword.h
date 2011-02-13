#ifndef open_password_h
#define open_password_h
#include<fstream>
#include<vector>
struct passwd {
  std::string name;
  std::string username;
  std::string password;
};
std::vector<passwd> openPassword(std::string filename, std::string password) {
  std::ifstream myfile;
  myfile.open (filename.c_str());
  std::string input;
  myfile >> input;
  myfile.close();
}
#endif
