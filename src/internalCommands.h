#ifndef internal_commands_h_
#define internal_commands_h_
/************************************* ADD ************************************\
|
\******************************************************************************/
void add (std::vector<passwd> &passwordList, bool & changed, int inputMode)
{
  //unsaved file changes
  changed = true;
  //regular function
  passwd newpass;
  std::cout << "name: ";
  newpass.name = getInput(PPM_PLAINTEXT,inputMode);
  std::cout << "username: ";
  newpass.username = getInput(PPM_PLAINTEXT,inputMode);
  std::cout << "password: ";
  newpass.password = getInput(PPM_PASSWORD,inputMode);
  passwordList.push_back(newpass);
  sort(passwordList.begin(), passwordList.end(), lessThenPassword);
  std::cout << "Added to the password list" << std::endl;
}    
/*********************************** REMOVE ***********************************\
|
\******************************************************************************/
void remove (std::vector<passwd> &passwordList, bool & changed, int inputMode) {
  std::string input;
  // unsaved file changes
  changed = true;
  // regular function
  int deleteNumber;
  std::cout << "Password Number: ";
  input = getInput(PPM_PLAINTEXT,inputMode);
  if (input == "") return;
  else if (atoi(input.c_str()) > 0){
    deleteNumber = atoi(input.c_str());
    while (true) {
      std::cout << "Are you sure you want to delete "<< passwordList[deleteNumber-1].name << "  " << passwordList[deleteNumber-1].username<< "?" ;
      input = getInput(PPM_PLAINTEXT,inputMode);
      if (input != "") break;
    }
    if (input != "y" && input!="yes") {
      std::cout << "Nothing Deleted" << std::endl;
      return;
    }
  }
  else {
    std::cout << "that is not a valid number" << std::endl;
    return;
  }
  //remove delnum password
  passwordList.erase (passwordList.begin()+deleteNumber-1);
  std::cout << "Deleted Entry Number " << deleteNumber << std::endl;
}
/*********************************** SEARCH ***********************************\
|
\******************************************************************************/
void search (std::vector<passwd> &passwordList, bool & changed, int inputMode, bool showPassword) {
  std::string input;
  // search for a password based on the name
  std::cout << "What do you want to seach for" << std::endl;
  input = getInput(PPM_PLAINTEXT,inputMode);
  //search name
  std::vector<passwd> searchList = passwordList;
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
    std::cout << "No Results Found" << std::endl;
  }
  else {
    printPassword(searchList, showPassword);
  }
}
/************************************ SAVE ************************************\
|
\******************************************************************************/
void save (std::string filename, std::string password, std::vector<passwd> passwordList, bool &changed){
  changed = false;
  // regular function
  std::cout << "Saving Password List" << std::endl;
  savePassword(filename, password, passwordList);
}
#endif
