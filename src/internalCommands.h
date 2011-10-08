#ifndef internal_commands_h_
#define internal_commands_h_
void add (std::vector<passwd> &passwordList, bool & changed)
{
  //unsaved file changes
  changed = true;
  //regular function
  passwd newpass;
  cout << "name: ";
  newpass.name = getInput(PPM_PLAINTEXT);
  cout << "username: ";
  newpass.username = getInput(PPM_PLAINTEXT);
  cout << "password: ";
  newpass.password = getInput(PPM_PASSWORD);
  passwordList.push_back(newpass);
  sort(passwordList.begin(), passwordList.end(), lessThenPassword);
  cout << "Added to the password list" << endl;
}    
#endif
