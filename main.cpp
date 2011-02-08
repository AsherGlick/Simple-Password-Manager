#include <iostream>
#include <fstream>
#include <openssl/aes.h>
using namespace std;
int main(int argc, char * argv[]) {
  string filename;
  string password;
  if(argc == 1) {
    cout << "Input the path to your password file:";
    getline(cin,filename);
    cout << "What is the password to unlock the file:";
    getline(cin,password);
  }  
  else if (argc == 2 && string(argv[1]) != "-?") {
    filename = argv[1];
    cout << "What is the password to unlock the file:";
    getline(cin,password);
  }
  else if (argc == 3) {
    filename = argv[1];
    password = argv[2];
  }
  else {
    cout << "There are four ways to initilize the program" << endl;
    cout << "  " << argv[0] << endl;
    cout << "  " << argv[0] << " -?" << endl;
    cout << "  " << argv[0] << " <filename>" << endl;
    cout << "  " << argv[0] << " <filename> <password>" << endl;
    cout << " * It is not recomended that you put the password into the command line prompt" << endl;
    return 0;
  }
  // Now we have the filename and password
  
}
