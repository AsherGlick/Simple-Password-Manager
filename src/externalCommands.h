void help(bool all);
string lowerCase (string input);
bool lessThenPassword(passwd one, passwd two);
bool within (string searchFor, string searchIn);
string getInput(bool isPassword);
void configTerminal();
void printWidth(std::string print, int width);
void printPassword (vector<passwd> passwordList);

/************************** Help / Help All function **************************\
| a function that displays the commands to use in a basic or in depth mode     |
\******************************************************************************/
void help (bool all) {
  if (all) {
    cout << "The help all function is currently unavalable becuse the entire list" << endl;
    cout << "of functions has not been declared yet, once the functions have been" << endl;
    cout << "declared then this function will be compleetly implemented, until   " << endl;
    cout << "then here is the regular help funciton" << endl;
    help(false);
  }
  else {
    cout << "  add    - adds a passoword to the list" << endl;
    cout << "  remove - removes a password from the list" << endl;
    cout << "  change - changes a password on the list" << endl;
    cout << "  find   - finds passwords with a specific name" << endl;
    cout << "  list   - prints out the entire list of passwords" << endl;
    cout << "  save   - saves the current password file" << endl;
    cout << "  saveas - save the password files with new settings" << endl;
    cout << "  help   - displays a list of functions" << endl;
    cout << "  ?-A    - displays a list of functions an all possible variables" << endl;
  }
}

/***** Ignore Case *****\
| A simple function to return a any string in lowercase only
\***********************/
string lowerCase (string input) {
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
bool within (string searchFor, string searchIn) {
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
string getInput(bool isPassword) {
  if (inputMode == 1) { // input mode is standard cin
    string input;
    getline (cin, input);
    return input;
  }
  else if (inputMode == 2) { // input mode is advanced mode
    #ifdef _advancedInput_h_
      return (getInput2(isPassword));  
    #endif
    #ifndef _advancedInput_h_
      cout << "   <<<<ERROR>>>>" << endl;
      cout << "ADVANCED INPUT MODE WAS NOT COMPILED IN THIS PROGRAM" << endl;
      cout << " In order to use the advanced input mode you need to compile the program with the advanced input file, by default the source code does not compile with this function. If you want to use advanced input read the documentation page on how to incude advanced input" << endl;
      // Do a default input
      string input;
      getline (cin, input);
      return input;
    #endif
  }
  else if (inputMode == 3) { // input mode is ncruses mode
    #ifdef _nCursesIO_h_
      return(getInputNcurses(isPassword));
    #endif
    #ifndef _nCursesIO_h_
      cout << "<([ ERROR ])>" << endl;
      cout << "NCURSES INPUT MODE WAS NOT COMPILED IN THIS PROGRAM" << endl;
      cout << " In order to use the ncurses IO mode you need to" << endl;
      cout << "compile the program with the ncurses IO file. By default the source code does not compile with this feature. If you want to use the ncurses IO read the documentation page on how to include the ncurses IO functions" << endl;
      // Do a default input
      string input;
      getline (cin, input);
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
void configTerminal() {
  #ifndef _config_file_h_
  cout << "Config files operations are not included in this build. Configurations will return to default after you close the program" << endl;
  #endif
  string input;
  while (true) {
    cout << "CONFIG>";
    input = getInput(PPM_PLAINTEXT);
    if (input == "exit") break;
    else if (input == "name") {
      cout << "change the default name of the passwords file" << endl;
    }
    else if (input == "inputType") {
      cout << "change the type of input:" << endl;
    }
    else if (input == "") {
    }
    else {
      cout << "This is the Configure Terminal" << endl;
      cout << "  Use 'exit' to return to normal mode" << endl;
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
void printPassword (vector<passwd> passwordList) {
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
  cout << "NUMBER\t";
  printWidth("NAME",namelength);
  printWidth("USERNAME",usernamelength);
  if (showPassword) {
    printWidth("PASSWORD",passwordlength);
  }
  cout << endl;
  for (unsigned int i = 0 ; i < passwordList.size(); i++) {
    if (passwordList[i].name == "" && passwordList[i].username == "" && passwordList[i].password == "") continue;
    cout << i+1 << '\t';
    printWidth(passwordList[i].name,namelength);
    printWidth(passwordList[i].username,usernamelength);
    if (showPassword) {
      printWidth(passwordList[i].password,passwordlength);
    }
    cout << endl;
  }  
}
