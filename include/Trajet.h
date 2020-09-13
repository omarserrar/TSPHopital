
#ifndef TRAJET_H
#define TRAJET_H

class Hopital;
#include<queue>
#include<map>
#include<string>

#include "./Point.h"
// Un objet trajet stock les chambre d'un trajet specifique dans l'ordre aisni que la distance total du trajet
class Hopital;
class Trajet
{
    public:
        Trajet(int nombreDeChambreAVisite);
        void ajouterChambre(Point* chambre, float dist);
        float getDistanceTotale();
        std::queue<Point*> getTrajet();
        bool isVisited(Point* chambre);

        std::string toString();
        virtual ~Trajet();

    protected:

    private:
        float distanceTotale;
        std::queue<Point*> chemin;
        std::map<int, int> visitee;
};

#endif // TRAJET_H
