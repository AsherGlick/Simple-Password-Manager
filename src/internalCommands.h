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
      std::cout << "Are you sure you want to delete number " << deleteNumber << "?" ;
      input = getInput(PPM_PLAINTEXT,inputMode);
      if (input != "") break;
    }
    if (input != "y" && input!="yes") {
      std::cout << "Nothing Deleted" << std::endl;
      return;
    }
    std::cout << "Deleted Entry Number " << deleteNumber << std::endl;
  }
  else {
    std::cout << "that is not a valid number" << std::endl;
    return;
  }
  //remove delnum password
  passwordList.erase (passwordList.begin()+deleteNumber-1);
}
#endif
