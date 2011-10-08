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
| This program is under the BSD licence and was written by Asher Glick aglick@tetrakai.com
| This program is provided ASIS with no warranty, though because the source code should be
| relatively simple (or documented well) 
\**/
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
#define PPM_PASSWORD true
#define PPM_PLAINTEXT false

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>


#include "openPassword.h" // required file for saving passwords
#include "configFile.h" // only needed to save config file (OPTIONAL)
#include "advancedInput.h" // only needed if you would like to use input mode 2 (OPTIONAL)
//#inlcude "ncursesInput.h" // only needed if you would like to use the ncurses enviroment
#include "externalCommands.h"

#include "internalCommands.h" // file containing all of the basic commands being run.
using namespace std;



// Configuration Variables
int inputMode = 2;
bool showPassword = true;
string defaultPath;






// Main Function
int main(int argc, char * argv[]) {
  // Tracks if the data has been changed to prompt the user to save when they try to quit
  bool changed = false;
  string filename;
  string password;
  
  // Input Varification //
  // make sure that the input given by the terminal is valad
  if(argc == 1) {
    cout << "Input the path to your password file: ";
    filename = getInput(PPM_PLAINTEXT);
    cout << "What is the password to unlock the file: ";
    password = getInput(PPM_PASSWORD);
  }  
  else if (argc == 2 && string(argv[1]) != "-?") {
    filename = argv[1];
    cout << "What is the password to unlock the file: ";
    password = getInput(PPM_PASSWORD);
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
  
  //printPassword(passwordList);
  string input;
  // begin the cli interface loop allowing the user to input commands
  while(true) {
    cout << "]> ";
    input = getInput(PPM_PLAINTEXT);
    
    /////////////////////////////// Add Command ///////////////////////////////
    //the user wants to add a password to the lsit
    
    if (input == "add" || input == "+" || input == "a") {
      add(passwordList,changed);
    }
    
    ////////////////////////////// Remove Command //////////////////////////////
    // the user wants to remove a password from the list
    else if (input == "remove" || input == "rem" || input == "rm" || input == "-" || input == "r") {
      // unsaved file changes
      changed = true;
      // regular function
      int deleteNumber;
      cout << "Password Number: ";
      input = getInput(PPM_PLAINTEXT);
      if (input == "") continue;
      else if (atoi(input.c_str()) > 0){
        deleteNumber = atoi(input.c_str());
        while (true) {
          cout << "Are you sure you want to delete number " << deleteNumber << "?" ;
          input = getInput(PPM_PLAINTEXT);
          if (input != "") break;
        }
        if (input != "y" && input!="yes") {
          cout << "Nothing Deleted" << endl;
          continue;
        }
        cout << "Deleted Entry Number " << deleteNumber << endl;
      }
      else {
        cout << "that is not a valid number" << endl;
        continue;
      }
      //remove delnum password
      passwordList.erase (passwordList.begin()+deleteNumber-1);
    }
    
    ////////////////////////////// Change command //////////////////////////////
    // the user wants to alter a password form the list
    else if (input == "change" || input == "alter" || input == "mod" || input == "modify") {
      // unsaved file changes
      changed = true;
      // regular function
      int changeNumber;
      cout << "Password Number: ";
      input = getInput(PPM_PLAINTEXT);
      if (input == "") continue;
      else if (atoi(input.c_str()) > 0){
        changeNumber = atoi(input.c_str());
        
      }
      
      
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
      cout << "What do you want to seach for" << endl;
      input = getInput(PPM_PLAINTEXT);
      //search name
      vector<passwd> searchList = passwordList;
      unsigned int erased = 0;
      for (unsigned int i = 0; i < passwordList.size(); i++) {
        if (!within(input,searchList[i].name) && !within(input,searchList[i].username)){// if the criteria are not in the name or username
          searchList[i].name = "";
          searchList[i].username = "";
          searchList[i].password = "";
          erased ++;
        }
      }
      if (searchList.size() == erased) {
        cout << "No Results Found" << endl;
      }
      else {
        printPassword(searchList);
      }
    }
    
    ////////////////////////// List passwords Command //////////////////////////
    // Lists all of the saved username and passwords
    else if (input == "passwords" || input == "passlist" || input == "list") {
      printPassword(passwordList);
    }
    ///// List /////
    else if (input == "show") {
      cout << "What is the number of the password you want to see?" << endl;
      char a;
      cout << "";
      cin >> a;
      cout << "\r                                                  " << endl;
    }
    /////////////////////////////// Save Command ///////////////////////////////
    // Save the current passwords in the same configuration as the old ones
    else if (input == "save" || input == "savepasswords" || input == "s") {
      // regular function
      changed = false;
      // regular function
      cout << "Saving Password List" << endl;
      savePassword(filename, password, passwordList);
    }
    
    ///////////////////////////// Save As command /////////////////////////////
    // Save the current passwords in a new configuration
    else if (input == "saveas" || input == "savepasswordsas") {
      cout << "Save as Filename: ";
      string tempfile;
      tempfile = getInput(PPM_PLAINTEXT);
      string temppass;
      while (true) {
        cout << "Save as Password: ";
        temppass = getInput(PPM_PASSWORD);
        cout << "Re-type Password: ";
        string temppass2;
        temppass2 = getInput(PPM_PASSWORD);
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
      if (changed) {
        while (true) {
          cout << "The file has been changed without saving\nDo you still want to quit?[y/n]" << endl;
          input = getInput(PPM_PLAINTEXT);
          if (input != "") break;
        }
        if (input != "y" && input!="yes") {
          cout << "Quit Aborted" << endl;
          continue;
        }
      }
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
