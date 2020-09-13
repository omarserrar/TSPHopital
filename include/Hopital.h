#ifndef HOPITAL_H
#define HOPITAL_H

#include<string>
#include <vector>


#include "./Trajet.h"
#include "./Point.h"


class Hopital
{
    public:
        Hopital(char* filepath, char* chambresAVisiteString);
        void readData(char* filepath);
        void creerMatriceAdjacence();
        void recupererChambreAVisiter(std::string chambreLigne);
        Trajet calculerChemin();
        Trajet chambreLaPlusProche(Point* chambre, Trajet* trajet);
        float minTrajet(Point* depart, Point* chambre, Trajet* trajet);
        std::vector<Point*> getChambreAVisite();
        std::vector<Point*> listesPoints;
        std::vector<vector<float>> distances;
    protected:

    private:

        std::vector<Point*> chambresAVisite;
        Trajet* trajetOpt;
};

#endif // HOPITAL_H
