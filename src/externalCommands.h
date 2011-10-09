#include <iostream>
#include <vector>

void help(bool all);
std::string lowerCase (std::string input);
bool lessThenPassword(passwd one, passwd two);
bool within (std::string searchFor, std::string searchIn);
std::string getInput(bool isPassword, int inputMode);
void configTerminal(int inputMode);
void printWidth(std::string print, int width);
void printPassword (std::vector<passwd> passwordList, bool showPassword);

/************************** Help / Help All function **************************\
| a function that displays the commands to use in a basic or in depth mode     |
\******************************************************************************/
void help (bool all) {
  if (all) {
    std::cout << "The help all function is currently unavalable becuse the entire list" << std::endl;
    std::cout << "of functions has not been declared yet, once the functions have been" << std::endl;
    std::cout << "declared then this function will be compleetly implemented, until   " << std::endl;
    std::cout << "then here is the regular help funciton" << std::endl;
    help(false);
  }
  else {
    std::cout << "  add    - adds a passoword to the list" << std::endl;
    std::cout << "  remove - removes a password from the list" << std::endl;
    std::cout << "  change - changes a password on the list" << std::endl;
    std::cout << "  find   - finds passwords with a specific name" << std::endl;
    std::cout << "  list   - prints out the entire list of passwords" << std::endl;
    std::cout << "  save   - saves the current password file" << std::endl;
    std::cout << "  saveas - save the password files with new settings" << std::endl;
    std::cout << "  help   - displays a list of functions" << std::endl;
    std::cout << "  ?-A    - displays a list of functions an all possible variables" << std::endl;
  }
}

/***** Ignore Case *****\
| A simple function to return a any string in lowercase only
\******************************************************************************/
std::string lowerCase (std::string input) {
  for (unsigned int i = 0; i < input.size(); i++){
    if (input[i] >= 'A' && input[i] <= 'Z') {
      input[i] += 32;
    }
  }
  return input;
}

/***************************** Less Then Password *****************************\
| a less then function used for sorting the vector of passwords                |
\******************************************************************************/
bool lessThenPassword(passwd one, passwd two) {
  return (lowerCase(one.name) < lowerCase(two.name));
}

/*********************************** Within ***********************************\
| This is a search function that searches for a string within another string   |
| this allows the typed input to check for                                     |
\******************************************************************************/
bool within (std::string searchFor, std::string searchIn) {
  searchFor = lowerCase(searchFor);
  searchIn = lowerCase(searchIn);
  int size = searchIn.size() - searchFor.size() + 1;
  if (size < 0) return false;
  //if (searchIn == searchFor) return true;
  for (int i = 0; i < size; i++) {
    if (searchFor == searchIn.substr(i,searchFor.size())) {
      return true;
    }
  }
  return false;
} 

/********************************* Get Input *********************************\
\*****************************************************************************/
std::string getInput(bool isPassword, int inputMode) {
  if (inputMode == 1) { // input mode is standard cin
    std::string input;
    getline (std::cin, input);
    return input;
  }
  else if (inputMode == 2) { // input mode is advanced mode
    #ifdef _advancedInput_h_
      return (getInput2(isPassword));  
    #endif
    #ifndef _advancedInput_h_
      std::cout << "   <<<<ERROR>>>>" << std::endl;
      std::cout << "ADVANCED INPUT MODE WAS NOT COMPILED IN THIS PROGRAM" << std::endl;
      std::cout << " In order to use the advanced input mode you need to compile the program with the advanced input file, by default the source code does not compile with this function. If you want to use advanced input read the documentation page on how to incude advanced input" << std::endl;
      // Do a default input
      std::string input;
      getline (std::cin, input);
      return input;
    #endif
  }
  else if (inputMode == 3) { // input mode is ncruses mode
    #ifdef _nCursesIO_h_
      return(getInputNcurses(isPassword));
    #endif
    #ifndef _nCursesIO_h_
      std::cout << "<([ ERROR ])>" << std::endl;
      std::cout << "NCURSES INPUT MODE WAS NOT COMPILED IN THIS PROGRAM" << std::endl;
      std::cout << " In order to use the ncurses IO mode you need to" << std::endl;
      std::cout << "compile the program with the ncurses IO file. By default the source code does not compile with this feature. If you want to use the ncurses IO read the documentation page on how to include the ncurses IO functions" << std::endl;
      // Do a default input
      std::string input;
      getline (std::cin, input);
      return input;
    #endif
  }
  return ("");
}

/***************************** Configure Terminal *****************************\
| The configure terminal function is a configure mode for the password manager |
| it allows you to use special commands that do not affect any password list   |
| and only affect the program. Commands in the configure terminal include      |
| displaying the documentation, version information                            |
\******************************************************************************/
void configTerminal(int inputMode) {
  #ifndef _config_file_h_
  std::cout << "Config files operations are not included in this build. Configurations will return to default after you close the program" << std::endl;
  #endif
  std::string input;
  while (true) {
    std::cout << "CONFIG>";
    input = getInput(PPM_PLAINTEXT,inputMode);
    if (input == "exit") break;
    else if (input == "name") {
      std::cout << "change the default name of the passwords file" << std::endl;
    }
    else if (input == "inputType") {
      std::cout << "change the type of input:" << std::endl;
    }
    else if (input == "") {
    }
    else {
      std::cout << "This is the Configure Terminal" << std::endl;
      std::cout << "  Use 'exit' to return to normal mode" << std::endl;
    }
  }
}

/******************************* Print Password *******************************\
| this prints all the passwords that are in the file                           |
| in columns                                                                   |
| it uses the print width function to format the table                         |
\******************************************************************************/
void printWidth(std::string print, int width) {
  int whitespace = width - print.size();
  std::cout << print;
  for (int i = 0; i < whitespace; i++) std::cout << ' ';
}
void printPassword (std::vector<passwd> passwordList, bool showPassword) {
  unsigned int namelength = 4;
  unsigned int usernamelength = 8;
  unsigned int passwordlength = 8;
  for (unsigned int i = 0; i < passwordList.size(); i++)
    if (passwordList[i].name.size() > namelength)
      namelength = passwordList[i].name.size();
  for (unsigned int i = 0; i < passwordList.size(); i++) 
    if (passwordList[i].username.size() > usernamelength)
      usernamelength = passwordList[i].username.size();
  for (unsigned int i = 0; i < passwordList.size(); i++)
    if (passwordList[i].password.size() > passwordlength)
      passwordlength = passwordList[i].password.size();
  
  namelength++;
  usernamelength++;
  passwordlength++;
  std::cout << "NUMBER\t";
  printWidth("NAME",namelength);
  printWidth("USERNAME",usernamelength);
  if (showPassword) {
    printWidth("PASSWORD",passwordlength);
  }
  std::cout << std::endl;
  for (unsigned int i = 0 ; i < passwordList.size(); i++) {
    if (passwordList[i].name == "" && passwordList[i].username == "" && passwordList[i].password == "") continue;
    std::cout << i+1 << '\t';
    printWidth(passwordList[i].name,namelength);
    printWidth(passwordList[i].username,usernamelength);
    if (showPassword) {
      printWidth(passwordList[i].password,passwordlength);
    }
    std::cout << std::endl;
  }  
}
