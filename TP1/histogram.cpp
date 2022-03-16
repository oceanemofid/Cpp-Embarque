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

  vector<double> buf;
  vector<int> all_sizes; //vecteur contenant les size des subvecteurs
  int maxi = 0;
  string line;
  auto mean = 0.0;

  while (std::getline(fin, line)) {
    auto d = std::stod(line);
    //si dans l'intervalle [0;7999.9] on ajoute au buffer et on calcule la moyenne 
    if(d < 7999.99){
      buf.push_back(d);
      //moyenne
      mean = (buf.size() == 1) ? d : mean + (d - mean) / buf.size();
    }
    
  }

  //médiane
  //on trie le vector par ordre croissant 
  std::sort(buf.begin(), buf.end()); 
  auto mid = buf.size() / 2;
  int t = buf.size();
  double median = (buf.size() % 2) ? buf[mid] :
                                     (buf[mid - 1] + buf[mid]) / 2;

  //construction des brackets
  vector<double> subvector;
  for(int i = 0; i<80; ++i){
    for(int m = 0; m<t; ++m){
      //on parcourt tout le buf et 
      //on met dans un sous vector si la valeur est dans l'intervalle
      if(buf[m]<100*i+100 && buf[m]>100*i){
        subvector.push_back(buf[m]);
      }
    }
    //on récupère la taille du subvecteur
    int taille = subvector.size();
    //on compare la size de la bracket actuelle au max précédent
    maxi = std::max(maxi,taille);
    all_sizes.push_back(taille); //on stocke la size du subvecteur
    //on efface le subvecteur
    subvector.clear();
  }
  //infos 
  std::cout << "number of elements = " << buf.size()
            << ", median = " << median
            << ", mean = " << mean << std::endl;

  //affichage
  //affiche le bracket inf puis le nbr d'éléments de la bracket puis les étoiles
  for(int i = 0; i<80 ; ++i){
    //les setw nous permettent d'aligner les éléments
    int nbr = int((all_sizes[i]*60)/maxi);
      std::cout << std::setfill(' ') << std::setw(6) << 100*i << 
      std::setw(6) << all_sizes[i] << ' ' <<std::string(nbr, '*') << std::endl ;
  }
  
}

