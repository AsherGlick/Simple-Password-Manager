#ifndef internal_commands_h_
#define internal_commands_h_
void add (std::vector<passwd> &passwordList, bool & changed)
{
  //unsaved file changes
  changed = true;
  //regular function
  passwd newpass;
  std::cout << "name: ";
  newpass.name = getInput(PPM_PLAINTEXT);
  std::cout << "username: ";
  newpass.username = getInput(PPM_PLAINTEXT);
  std::cout << "password: ";
  newpass.password = getInput(PPM_PASSWORD);
  passwordList.push_back(newpass);
  sort(passwordList.begin(), passwordList.end(), lessThenPassword);
  std::cout << "Added to the password list" << std::endl;
}    
#endif
