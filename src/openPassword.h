/******************************** Licence Info ********************************\
| Copyright (c) 2011, ASHER GLICK (aglick@tetrakai.com) All rights reserved.   |
| Redistribution and use in source and binary forms, with or without           |
| modification, are permitted provided that the following conditions are met:  |
| * Redistributions of source code must retain the above copyright notice,     |
|   this list of conditions and the following disclaimer.                      |
| * Redistributions in binary form must reproduce the above copyright notice,  |
|   this list of conditions and the following disclaimer in the documentation  |
|   and/or other materials provided with the distribution.                     |
| * Neither the name of Rensselaer Polytechnic Institute nor the names of its  |
|   contributors may be used to endorse or promote products derived from this  |
|   software without specific prior written permission.                        |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  |
| AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    |
| IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   |
| ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    |
| LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          |
| CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         |
| SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     |
| INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      |
| CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      |
| ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   |
| POSSIBILITY OF SUCH DAMAGE.                                                  |
| This licence information can also be found in ./COPYING                      |
\******************************************************************************/

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
  unsigned int passwordIterator = 0;
  for (unsigned int i = 0; i < input.size(); i++) {
    output[i] = (input[i]-password[passwordIterator])%255;
    passwordIterator++;
    if (passwordIterator >= password.size()) {
      passwordIterator = 0;
    }
  }
  return output;
}

std::string unEncrypt (std::string input,std::string password) {
  std::string output = input;
  if (password == "") {
    return output;
  }
  // unEncrypt function (this can be modified)
  unsigned int passwordIterator = 0;
  for (unsigned int i = 0; i < input.size(); i++) {
    output[i] = (input[i]+password[passwordIterator])%255;
    passwordIterator++;
    if (passwordIterator >= password.size()) {
      passwordIterator = 0;
    }
  }
  return output;
}

/******************************* Open Password *******************************\
| This function opens the file and unencrypts it then return a formatted      |
| version of the contents of the file as a vector of struct passwd            |
\*****************************************************************************/
/* Remove Slashes *\
\**/
std::string removeSlashes(std::string input) {
  for (unsigned int i = 0; i < input.size(); i++) {
    if (input[i] == '\\') {
      if (input[i+1] == '\\') {
        input.erase(i,1);
      }
      else input[i] = ' ';
    }
  }
  return input;
}
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
  if (fileString.size() == 0) {
    // if file does not exist create a virtual one
    std::cout << "New Password File Created" << std::endl;
    myfile << 0;
  }
  else {
    // otherwise unencrypt the file and load it into memory
    myfile << unEncrypt(fileString,password);
  }
  
  int count;
  myfile >> count;
  
  std::vector<passwd> passwordList;
  for (int i = 0; i < count; i ++) {
    passwd newpass;
    myfile >> newpass.name;
    newpass.name = removeSlashes(newpass.name);
    passwordList.push_back(newpass);
  }
  for (int i = 0; i < count; i++) {
    myfile >> passwordList[i].username;
    passwordList[i].username = removeSlashes(passwordList[i].username);
  }
  for (int i = 0; i < count; i++) {
    myfile >> passwordList[i].password;
    passwordList[i].username = removeSlashes(passwordList[i].username);
  }
  
  return passwordList;
}
/******************************* Save Password *******************************\
| take the username and password information turn it into a string, encrypt   |
| the document and save it to a file                                          |
\*****************************************************************************/
/* Add Slashes *\
\*/
std::string addSlashes(std::string input) {
  for (unsigned int i = 0; i < input.size(); i++) {
    if (input[i] == ' ') {
      input[i] = '\\';
    }
    else if (input[i] == '\\') {
      input.insert(i,"\\");
      i++;
    }
  }
  return input;
}
bool savePassword(std::string filename, std::string password, std::vector<passwd> passwordList) {
  std::stringstream outstring;
  
  outstring << passwordList.size() << " ";
  for (unsigned int i = 0; i < passwordList.size(); i++) {
    outstring << addSlashes(passwordList[i].name) << " ";
  }
  for (unsigned int i = 0; i < passwordList.size(); i++) {
    outstring << addSlashes(passwordList[i].username) << " ";
  }
  for (unsigned int i = 0; i < passwordList.size(); i++) {
    outstring << addSlashes(passwordList[i].password) << " ";
  }
  
  std::ofstream outfile;
  outfile.open(filename.c_str());
  outfile << encrypt(outstring.str(),password);
  outfile.close();
  return true;
}

#endif
