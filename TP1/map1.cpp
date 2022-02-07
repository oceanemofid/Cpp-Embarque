//
// header-start
//////////////////////////////////////////////////////////////////////////////////
//
// \file      histogram
//
// \brief     This file belongs to the C++ tutorial project
//
// \author    Jonas Audrey, Ghobrial Sara, Mofid Océane
//
// \copyright Copyright ng2goodies 2015
//            Distributed under the MIT License
//            See http://opensource.org/licenses/MIT
//
//////////////////////////////////////////////////////////////////////////////////
// header-end
//

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using std::string;
using std::vector;

// This simple program reads from a file a set of numbers (double format)
// computes a running mean value, computes the median after sort
// and prints a histogram af all values between 0 and 7999.99 placed into brackets

int main(int argc, char *argv[]) {

    string file_name{argv[1]};
    std::ifstream fin(file_name, std::ios::in);
    string line;

    std::cout << "query > ";
    std::string query;
    std::cin >> query;
    
    while (std::getline(fin, line)) {
        std::cout << line << std::endl;
    }
    



}
