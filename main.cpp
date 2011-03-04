/**\
| This is the Paranoid Password Manager. The purpose of this program is so paranoid people
| like myself have a secure password manager without any shady or closed source parts of
| the progarm that may have the ability to send your password to a remote server and allow
| others to access your files.
| This program will encrypt your password file based on a password you give it, this is the
| only password you will need to remember in order to get access to your password file, 
| even if an intruder were to gain access to your file system they would not be able
| to read your passwords, however if an intruder allready has access to your root priviliges
| then this program will not help you because 
| This program is under the BSD licence and was written by Asher Glick asherg@tetrakai.com
| This program is provided ASIS with no warranty, though because the source code should be
| relatively simple (or documented well) 
\**/
#include <iostream>
#include <fstream>
#include "openPassword.h"
using namespace std;

void printPassword (vector<passwd> passwordList);
void configTerminal();
void help(bool all);
void configTerminal();

int main(int argc, char * argv[]) {
  string filename;
  string password;
  
  // Input Varification //
  // make sure that the input given by the terminal is valad
  if(argc == 1) {
    cout << "Input the path to your password file: ";
    getline(cin,filename);
    cout << "What is the password to unlock the file: ";
    getline(cin,password);
  }  
  else if (argc == 2 && string(argv[1]) != "-?") {
    filename = argv[1];
    cout << "What is the password to unlock the file: ";
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
  
  
  /// Get file username and password listing from the username and passoword ///
  // NOTE: The password List variable is the variable that stores your password
  // if you do not trust the location which you got this source from you should
  // make sure to check all the functions that have this variable pass into them
  vector<passwd> passwordList = openPassword(filename, password);
  
  printPassword(passwordList);
  string input;
  // begin the cli interface loop allowing the user to input commands
  while(true) {
    cout << "]> ";
    getline(cin,input);
    
    
    /////////////////////////////// Add Command ///////////////////////////////
    //the user wants to add a password to the lsit
    
    if (input == "add" || input == "+" || input == "a") {
      passwd newpass;
      cout << "name: ";
      cin >> newpass.name;
      cout << "username: ";
      cin >> newpass.username;
      cout << "password: ";
      cin >> newpass.password;
      passwordList.push_back(newpass);
      getline(cin,input);
    }
    
    ////////////////////////////// Remove command //////////////////////////////
    // the user wants to remove a password from the list
    else if (input == "remove" || input == "rem" || input == "rm" || input == "-" || input == "r") {
      int deleteNumber;
      cout << "Password Number: ";
      cin >> deleteNumber;
      //remove delnum password
      passwordList.erase (passwordList.begin()+deleteNumber);
      getline(cin,input);
    }
    
    ////////////////////////////// Change command //////////////////////////////
    // the user wants to alter a password form the list
    else if (input == "change" || input == "alter" || input == "mod" || input == "modify") {
      int changeNumber;
      cout << "Password Number: ";
    }
    
    //////////////////////////// Configure Command ////////////////////////////
    // The user wants to enter the configuration mode of the program
    else if (input == "config") {
      // Enter config mode
      configTerminal();
    }
    
    ////////////////////////////// Search Command //////////////////////////////
    // This command searches through your passwords, this is to be used to
    // manage large numbers of passwords quickly
    else if (input == "find" || input == "search") {
      // search for a password based on the name
      cout << "what do you want to search for? Name Username Password" << endl;
      getline(cin, input);
      if (input == "name" || input == "Name") {
        cout << "What name do you want to seach for" << endl;
        getline(cin,input);
        //search name
        vector<passwd> searchList = passwordList;
        for (int i = 0; i < passwordList.size(); i++) {
          if (searchList[i].name != input) {
            searchList[i].name = "";
            searchList[i].username = "";
            searchList[i].password = "";
          }
        }
        printPassword(searchList);
      }
      else if (input == "username" || input == "Username" || input == "user" || input == "User") {
      }
      else if (input == "password" || input == "Password") {
        
      }
      else {
        cout << "error, input not regognized" << endl;
      }
    }
    
    ////////////////////////// List passwords Command //////////////////////////
    // Lists all of the saved username and passwords
    else if (input == "passwords" || input == "passlist" || input == "list" || input == "show") {
      printPassword(passwordList);
    }
    
    /////////////////////////////// Save Command ///////////////////////////////
    // Save the current passwords in the same configuration as the old ones
    else if (input == "save" || input == "savepasswords" || input == "s") {
      cout << "Saving Password List" << endl;
      savePassword(filename, password, passwordList);
    }
    
    ///////////////////////////// Save As command /////////////////////////////
    // Save the current passwords in a new configuration
    else if (input == "saveas" || input == "savepasswordsas") {
      cout << "Save as Filename: ";
      string tempfile;
      getline(cin, tempfile);
      string temppass;
      while (true) {
        cout << "Save as Password: ";
        getline(cin,temppass);
        cout << "Re-type Password: ";
        string temppass2;
        getline(cin,temppass2);
        if (temppass != temppass2) {
          cout << "Error, passwords do not match" << endl;
        }
        else break;
      }
      savePassword(tempfile,temppass,passwordList);
      cout << "Passwords saved as " << tempfile << endl;
    }
    
    /////////////////////////////// Exit Command ///////////////////////////////
    // quit out of the program
    else if (input == "exit" || input == "quit") {
      break;
    }
    
    /////////////////////////////// Help Command ///////////////////////////////
    // if the user wants to see the basic commands of the system
    else if (input == "help" || input == "?" || input == "--?") {
      help(false); // run the help command, do not display all
    }
    
    ///////////////////////////// Help All Command /////////////////////////////
    // a command that shows all the functions and function variations allong with what they do
    else if (input == "help-all" || input == "?-A" || input == "?-a") {
      help(true); // run the help command, do display all
    }
    
    ////////////////////////////// Empty Command //////////////////////////////
    // the input line is blank, the user just pressed return, do nothing
    else if (input == "");
    
    ///////////////////////////// Unknown Command /////////////////////////////
    // This displays an error message followed by the help menu
    else {
      cout << "error: command not recognised" << endl;
      help(false); // run the help command, do not display all
    }
  }
}

/************************** Help / Help All function **************************\
| a function that displays the commands to use in a basic or in depth mode     |
\******************************************************************************/
void help (bool all) {
  if (!all) {
    
  }
  else {
    cout << "  add    - adds a passoword to the list" << endl;
    cout << "  remove - removes a password from the list" << endl;
    cout << "  change - changes a password on the list" << endl;
    cout << "  find   - finds passwords with a specific name" << endl;
    cout << "  list   - prints out the entire list of passwords" << endl;
    cout << "  save   - saves the passowrd file with the same configurations as it was opened with" << endl;
    cout << "  saveas - save the password files with new settings" << endl;
    cout << "  help   - displays a list of functions" << endl;
    cout << "  ?-A    - displays a list of functions an all possible variables" << endl;
  }
}


/***************************** Configure Terminal *****************************\
| The configure terminal function is a configure mode for the password manager |
| it allows you to use special commands that do not affect any password list   |
| and only affect the program. Commands in the configure terminal include      |
| displaying the documentation, version information                            |
\******************************************************************************/
void configTerminal() {
  string input;
  while (true) {
    getline(cin, input);
    if (input == "exit") break;
    else {
      cout << "This is the Configure Terminal" << endl;
      cout << "  Use 'exit' to return to normal mode" << endl;
    }
  }
}

/******************************* Print Password *******************************\
| this prints all the passwords that are in the file
| in columns
| it uses the print width function to format the table
\******************************************************************************/
void printWidth(std::string print, int width) {
  int whitespace = width - print.size();
  std::cout << print;
  for (int i = 0; i < whitespace; i++) std::cout << ' ';
}
void printPassword (vector<passwd> passwordList) {
  int namelength = 4;
  int usernamelength = 8;
  int passwordlength = 8;
  for (int i = 0; i < passwordList.size(); i++)
    if (passwordList[i].name.size() > namelength)
      namelength = passwordList[i].name.size();
  for (int i = 0; i < passwordList.size(); i++) 
    if (passwordList[i].username.size() > usernamelength)
      usernamelength = passwordList[i].username.size();
  for (int i = 0; i < passwordList.size(); i++)
    if (passwordList[i].password.size() > passwordlength)
      passwordlength = passwordList[i].password.size();
  
  namelength++;
  usernamelength++;
  passwordlength++;
  cout << "NUMBER\t";
  printWidth("NAME",namelength);
  printWidth("USERNAME",usernamelength);
  printWidth("PASSWORD",passwordlength);
  cout << endl;
  for (int i = 0 ; i < passwordList.size(); i++) {
    if (passwordList[i].name == "" && passwordList[i].username == "" && passwordList[i].password == "") continue;
    cout << i << '\t';
    printWidth(passwordList[i].name,namelength);
    printWidth(passwordList[i].username,usernamelength);
    printWidth(passwordList[i].password,passwordlength);
    cout << endl;
  }  
}
