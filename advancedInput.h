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
#ifndef _advancedInput_h_
#define _advancedInput_h_
#include <string>
#include <iostream>
#include <termios.h> //allows you to change the terminal settings

/*************************** Terminal Manipulation ***************************\
| terminal manipulation functions
\*****************************************************************************/

static struct termios oldt;
void restore_terminal_settings(void)
{
  tcsetattr(0, TCSANOW, &oldt);
}
void disable_waiting_for_enter(void)
{
  struct termios newt;
  tcgetattr(0, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(0, TCSANOW, &newt);
  atexit(restore_terminal_settings);
}

/******************************* Advanced Input *******************************\
| This function handles whitespace reduction and password hiding
\******************************************************************************/
std::string getInput2(bool isPassword) {
  std::string input;
  //std::cout << "<>";
  // Make the terminal not echo
  if (isPassword) {
    disable_waiting_for_enter();
  }
  getline (std::cin, input);
  if (input != "") {
    // remove leading and trailing whitespace
    while (input[0] == ' ') {
      input = input.substr(1,input.size()-1);
    }
    while (input[input.size()-1] == ' ') {
      input = input.substr(0,input.size()-1);
    }
    // turn all other whitespace into a single space
    /*
    for (int i = 0; i < input.size()-1; i++) {
      if (input[i] == ' ' && input[i+1] == ' ') {
        for (int j = i+1; j < input.size()-1; j++) {
          input[j] = input[j+1];
        }
        input = input.substr(0,input.size()-1);
        i--;
      }
    }*/
  }
  // Return terminal to normal mode
  if (isPassword) {
    restore_terminal_settings();
    std::cout << std::endl;
  }
  return input;
}
#endif
