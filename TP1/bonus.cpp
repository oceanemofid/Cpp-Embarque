//
// header-start
//////////////////////////////////////////////////////////////////////////////////
//
// \file      bonus
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

#include <fstream>
#include <iostream>
#include <random>


int main(int argc, char *argv[]) {


    const double nrolls=100000;  // nombre de réels à générer
    std::ofstream outfile ("test.txt");

    std::default_random_engine generator; //générateur
    std::normal_distribution<double> distribution(1715.81,500.0); //moyenne et variance

    for (int i=0; i<nrolls; ++i) {
        double number = distribution(generator); //on génère un nombre selon la distribution spécifiée
        outfile << number << std::endl; //on l'écrit dans le fichier
    }

    
    outfile.close();
  
  }