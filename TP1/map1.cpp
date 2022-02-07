//
// header-start
//////////////////////////////////////////////////////////////////////////////////
//
// \file      map1
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

// This simple program reads from a file a set of numbers (double format)
// computes a running mean value, computes the median after sort
// and prints a histogram af all values between 0 and 7999.99 placed into brackets

int main(int argc, char *argv[]) {

    string file_name{argv[1]};
    std::ifstream fin(file_name, std::ios::in);
    string line;
    string qin;
    std::map<std::string, double> identifierKey;

    while (std::getline(fin, line)) {

            std::istringstream stream(line);
            string s;
            double f;
            stream >> s >> f ;
            identifierKey.insert({s, f});
            // extract the rest using the streambuf overload
            stream >> std::cout.rdbuf();
        }

    while(qin.compare("END")){
        std::cout << "query > ";
        std::cin >> qin;
        
            if(identifierKey.find(qin) != identifierKey.end()){
                std::cout << "value[" << identifierKey.find(qin)->first << "] = "
                << identifierKey.find(qin)->second << std::endl;
            }

            else {
                //à voir 
                if(qin == "END"){
                    break;
                }
                std::cout << "This ID does not exist" << std::endl;
            }
        
    }
    std::cout << "Bye..." << std::endl;
}
