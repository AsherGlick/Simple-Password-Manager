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
#ifndef _config_file_h_
#define _config_file_h_
void help () {
  std::cout << "InputMode      - Changes the method that input is collected" << std::endl;
  std::cout << "SetDefaultPath - Changes the default path of the password file" << std::endl;
  std::cout << "listPassword   - Show passwords whenever 'list' or 'find' is run" << std::endl;
  std::cout << "Save-Config    - Saves the current configuration to a file" << std::endl;
  std::cout << "exit           - Exits the configuration menu" << std::endl;
}
#endif
