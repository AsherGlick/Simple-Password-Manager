#ifndef open_password_h
#define open_password_h
#include <fstream>
#include <sstream>
#include <vector>
struct passwd {
  std::string name;
  std::string username;
  std::string password;
};


std::string encrypt (std::string input, std::string password) {
  std::string output = input;
  if (password == "") {
    return output;
  }
  // encrypt function (this can be modified)
  int passwordIterator = 0;
  for (int i = 0; i < input.size(); i++) {
    output[i] = (input[i]-password[passwordIterator])%255;
    passwordIterator++;
    if (passwordIterator >= password.size()) {
      passwordIterator = 0;
    }
  }
}

std::string unEncrypt (std::string input,std::string password) {
  std::string output = input;
  if (password == "") {
    return output;
  }
  // unEncrypt function (this can be modified)
  int passwordIterator = 0;
  for (int i = 0; i < input.size(); i++) {
    output[i] = (input[i]+password[passwordIterator])%255;
    passwordIterator++;
    if (passwordIterator >= password.size()) {
      passwordIterator = 0;
    }
  }
}
/******************************* Open Password *******************************\
| This function opens the file and unencrypts it then return a formatted      |
| version of the contents of the file as a vector of struct passwd            |
\*****************************************************************************/
std::vector<passwd> openPassword(std::string filename, std::string password) {
  std::ifstream passfile;
  passfile.open (filename.c_str());
  
  std::string fileString;
  std::string input;
  
  while (getline(passfile,input)) {
    fileString += input + '\n';
  }
  passfile.close();
  
  // entire file loaded into memory
  std::stringstream myfile;
  myfile << unEncrypt(fileString,password);
  
  
  int count;
  myfile >> count;
  
  std::vector<passwd> passwordList;
  for (int i = 0; i < count; i ++) {
    passwd newpass;
    myfile >> newpass.name;
    passwordList.push_back(newpass);
  }
  for (int i = 0; i < count; i++) {
    myfile >> passwordList[i].username;
  }
  for (int i = 0; i < count; i++) {
    myfile >> passwordList[i].password;
  }
  
  return passwordList;
}
/******************************* Save Password *******************************\
| take the username and password information turn it into a string, encrypt   |
| the document and save it to a file                                          |
\*****************************************************************************/
bool savePassword(std::string filename, std::string password, std::vector<passwd> passwordList) {
  std::stringstream outstring;
  
  outstring << passwordList.size() << " ";
  for (int i = 0; i < passwordList.size(); i++) {
    outstring << passwordList[i].name << " ";
  }
  for (int i = 0; i < passwordList.size(); i++) {
    outstring << passwordList[i].username << " ";
  }
  for (int i = 0; i < passwordList.size(); i++) {
    outstring << passwordList[i].password << " ";
  }
  
  std::ofstream outfile;
  outfile.open(filename.c_str());
  outfile << encrypt(outstring.str(),password);
  outfile.close();
  return true;
}
#endif
