
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;
#include "../include/Hopital.h"
#include "../include/Trajet.h"
// Supprime BOM
void SkipBOM(ifstream &file)
{
    char first3char[3] = {0};
    file.read(first3char, 3);
    if(!((unsigned char)first3char[0] == 0xEF && (unsigned char)first3char[1] == 0xBB && (unsigned char)first3char[2] == 0xBF))
    {
         file.seekg(0);
    }
}
// Split Un String
vector<string> split(string text,char separator){
    vector<string> result;
    stringstream ss(text);
    string colonne;
    int i=0;
    while(getline(ss, colonne, separator)){
        result.push_back(colonne);
    }
    return result;
}

Hopital::Hopital(char* filepath, char* chambresAVisiterString)
{
    readData(filepath); // Recupere les donnees du fichier

    creerMatriceAdjacence(); // Cree la matrice d'adjacence a partir des donnees

	recupererChambreAVisiter(chambresAVisiterString); // Recupere les chambres a visiter
}
// Recupere les donnees du fichier
void Hopital::readData(char* filepath){
    ifstream file(filepath);
    cout<<"Ouverture du fichier "<<filepath<<endl;
    if(!file.is_open()) throw std::runtime_error("Le fichier n'existe pas !");
    SkipBOM(file);
    string ligne;
    int i = 0;
    Point* point;
    while(getline(file, ligne)){
        vector<string> colonnes = split(string(ligne), ';');
        int id = stoi(colonnes[0]); // On recupere l'ID
        vector<string> coordString = split(colonnes[1],',');
        float x = stof(coordString[0]); // On recupere les coordonnees
        float y = stof(coordString[1]);
        if(colonnes.size()>3){ // On verifie si le point a un nom
            string nom= colonnes[3];
            point = new Point(id,x,y,nom);
        }
        else{
                point = new Point(id,x,y,"");
        }
        listesPoints.push_back(point); // On stock le point
        vector<string> pointsVoisin = split(colonnes[2],','); // On recupere les id des point voisin
        for(string pointVoisin: pointsVoisin){
            int voisinId = stoi(pointVoisin);
            if(voisinId<id){
                listesPoints[voisinId]->voisin.push_back(point);
                point->voisin.push_back(listesPoints[voisinId]);
            }
        }
    }
	file.close();
}
// Cree la matrice d'adjacence a partir des donnees
void Hopital::creerMatriceAdjacence(){
    distances = vector<vector<float>>(listesPoints.size());
    int c=0;
    for(Point* point: listesPoints){
        distances[c] = vector<float>(listesPoints.size());
        for(int i=0;i<listesPoints.size();i++){
            if(find(point->voisin.begin(), point->voisin.end(), listesPoints[i]) != point->voisin.end()){
                distances[c][i] = point->distance(listesPoints[i]);
            }
            else{
                distances[c][i] = 0;
            }
        }
        c++;
    }
    listesPoints[0]->distanceDijkstra(listesPoints[0], distances);
}
// Recupere les chambres a visiter
void Hopital::recupererChambreAVisiter(string chambreLigne){
    stringstream ss(chambreLigne);
    string colonne;
    int i=0;
    while(getline(ss, colonne, ';')){
        chambresAVisite.push_back(listesPoints[stoi(colonne)]);
        i++;
    }
}
// Trouve parmi les chambres a visiter la chambre la plus proche de "chambreDepart"
Trajet Hopital::chambreLaPlusProche(Point* chambreDepart, Trajet* trajetAct){
    Point* prochaineChambre = new Point(-1,0,0,"");
    float distMin = 99999;
    for(Point* chambre: chambresAVisite){
        if(chambre->id==chambreDepart->id || trajetAct->isVisited(chambre)) continue; // Continue si la chambre actuelle egale celle de depart ou si la chambre actuelle a deja ete visitee
        float distance=chambreDepart->distanceDijkstra(chambre, this->distances); // Calcul la distance entre chambreDepart et chambre en utilisant l'algorithme du plus court chemin de Dijkstra
        if(distance<distMin){
            prochaineChambre = chambre;
            distMin = distance;
        }
    }
    Trajet trajet = Trajet(1);
    trajet.ajouterChambre(prochaineChambre, distMin);
    return trajet;
}
// Calcul le trajet Optimal pour parcourir tous les chambres à partir d'une chambre de depart specifique
float Hopital::minTrajet(Point* depart, Point* chambre, Trajet* trajet)
{
	int i;
	Point* prochaineChambre;
    if(depart==chambre)
        (trajet)->ajouterChambre(chambre,0);
    Trajet trajetProchaineChambre = chambreLaPlusProche(chambre, trajet);
	prochaineChambre= trajetProchaineChambre.getTrajet().front();

	if(prochaineChambre==NULL || trajet->isVisited(prochaineChambre) || prochaineChambre->id == -1){ // Toutes les chambres sont visitees
        return -2;
	}
	if(trajetOpt != NULL && (trajet)->getDistanceTotale() > trajetOpt->getDistanceTotale()){ // Si la distance de ce trajet depasse celle du trajet optimal actuel on arrete
		return -1;
	}


    (trajet)->ajouterChambre(prochaineChambre,trajetProchaineChambre.getDistanceTotale()); // Ajoute la chambre trouvee au trajet
    minTrajet(depart , prochaineChambre, trajet);

}
// Prend a chaque fois une chambre de depart parmis les chambres a visiter puis calcul le trajet optimal pour parcourir
// tous les chambres
// On change a chaque fois la chambre de depart puis on choisi le trajet le plus optimal.
Trajet Hopital::calculerChemin(){
    trajetOpt = NULL;
    for(Point* point: chambresAVisite){

        Trajet* trajet = new Trajet(chambresAVisite.size());

        minTrajet(point, point, trajet);

        if(trajet==NULL) continue;
        if((trajetOpt == NULL || trajetOpt->getDistanceTotale() > trajet->getDistanceTotale())&&trajet->getDistanceTotale()!=0){
            trajetOpt = trajet;
        }

    }
    return *trajetOpt;
}
