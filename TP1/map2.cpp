// header-start
//////////////////////////////////////////////////////////////////////////////////
//
// \file      map2
//
// \brief     This file belongs to the C++ tutorial project
//
// \author    Ghobrial Sara, Jonas Audrey, Mofid Océane
//
// \copyright Copyright ng2goodies 2015
//            Distributed under the MIT License
//            See http://opensource.org/licenses/MIT
//
//////////////////////////////////////////////////////////////////////////////////
// header-end 
//

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>

using std::string;

// This program reads from a file a set of pairs (string and double) and takes queries as input:
// either a string (identifier) and returns its associated value
// or a value v and returns all identifiers witch associated values are included in [v - 1%; v + 1%]

int main(int argc, char *argv[]) {

   string file_name{argv[1]};
   std::ifstream fin(file_name, std::ios::in);
   string line;
   string qin;
   std::map<std::string, double> identifierKey;
   std::multimap<double, std::string> keyByValueMap;

   while (std::getline(fin, line)) {
       std::istringstream stream(line);
       string s;
       double f;
       stream >> s >> f ;
       identifierKey.insert({s, f});
       keyByValueMap.insert({f, s});
   }

   for(;;) { // boucle infinie
       std::cout << "query > ";
       std::cin >> qin;
       if(qin == "END"){
           break;
       }

       if (qin[0] == '+') { // reading a double from qin string
           try {
               double din = std::stod(qin);
               double dmin = .99 * din;
               double dmax = 1.01 * din;
               bool found = false;

               for(auto it = keyByValueMap.lower_bound(dmin); it != keyByValueMap.end(); ++it) {
                   if(it->first > dmax)
                       break;

                   std::cout << "value[" << it->second << "] = " << it->first << std::endl;
                   found = true;
               }

               if(!found)
                   std::cout<< " No identifier found for specified value: " << qin << std::endl;

           } catch(std::invalid_argument&) {
               std::cerr << qin << " is not a valid key value" << std::endl;
           }
           
       } else { // reading a key from qin string
           auto it = identifierKey.find(qin);
           if(it != identifierKey.end()) {
               std::cout << "value[" << qin << "] = "
                         << it->second << std::endl;
           } else {
              std::cout << "This ID does not exist" << std::endl;
          }
       }
   }
   std::cout << "Bye..." << std::endl;
}

