#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <queue>
#include <sstream>
#include <algorithm>
using namespace std;

#include "./include/Hopital.h"


int main(int argc, char *argv[])
{

   if(argc<3){
        cout<<"Utilisation:\n\tmain.exe fichier_des_chambres chambres_a_visite [output_file]"<<endl;
        cout<<"\tfichier_des_chambres: Le fichier des chambres et leur coordonnees"<<endl;
        cout<<"\tchambres_a_visite: Les chambres a visitees doivent etres separees par ';'"<<endl;
        cout<<"\toutput_file: La sortie par defaut est la console"<<endl;
        cout<<"Exemple:\n\t main.exe data.txt 101;102;103 output.txt"<<endl;
        return 1;
    }

    Hopital hopital = Hopital(argv[1], argv[2]);
    Trajet trajetOptimal = hopital.calculerChemin();
    cout<<"Here"<<endl;
    string output = trajetOptimal.toString();
    cout<<output<<endl;

    if(argc>3){
        ofstream ofs (argv[3], ofstream::out);

        ofs << output;

        ofs.close();
    }
    else{
        cout<<"Aucun fichier de sortie defini"<<endl;
    }

    return 0;
}
