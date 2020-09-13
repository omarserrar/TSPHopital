
#include <iostream>
#include <queue>

using namespace std;


#include "../include/Trajet.h"
#include "../include/Hopital.h"
Trajet::Trajet(int nombreDeChambreAVisite)
{
    distanceTotale = 0;
    visitee = map<int,int>();
}
void Trajet::ajouterChambre(Point* chambre, float temp){
    chemin.push(chambre);
    distanceTotale += temp;
    visitee[chambre->id] = 1;
}
bool Trajet::isVisited(Point* chambre){
    return visitee[chambre->id]==1;
}
float Trajet::getDistanceTotale(){
    return distanceTotale;
}
queue<Point*> Trajet::getTrajet(){
    return chemin;
}
string Trajet::toString(){
    Point* chambre;
    string output = "";
    while(!chemin.empty()){
        chambre = chemin.front();
        chemin.pop();
        output += "Chambre: "+(chambre->nom)+"("+to_string(chambre->id)+")\n";

    }
    output+= "Distance = "+to_string(distanceTotale)+"\n";
    return output;
}
Trajet::~Trajet()
{

}
