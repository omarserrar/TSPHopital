#include "../include/Point.h"
#include <iostream>
#include <cmath>
using namespace std;
Point::Point(int id, float x, float y, string nom)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->nom = nom;
}
// Calcul la distance entre deux noeud en utilisant l'algorithme de Dijkstra
float Point::distanceDijkstra(Point* arrivee, vector<vector<float>> matrice){
    int size = matrice.size();
     float dist[size];

    bool visite[size];
    for (int i = 0; i < size; i++)
        dist[i] = 99999, visite[i] = false;

    dist[id] = 0;

    for (int count = 0; count < size - 1; count++) {

        int prochainNoeud;
        int min = 99999, min_index;
        for (int v = 0; v < size; v++)
            if (visite[v] == false && dist[v] <= min){
                min = dist[v], prochainNoeud = v;
            }
        if(prochainNoeud==arrivee->id) return dist[prochainNoeud];

        visite[prochainNoeud] = true;
        for (int v = 0; v < size; v++)
           if (!visite[v] && matrice[prochainNoeud][v] && dist[prochainNoeud] != 99999
                && dist[prochainNoeud] + matrice[prochainNoeud][v] < dist[v]
                 && matrice[prochainNoeud][v] != 0){
                dist[v] = dist[prochainNoeud] + matrice[prochainNoeud][v];
            }
    }
}
// Calcul la distance entre deux noeud voisin
float Point::distance(Point* point){
    return sqrt(pow(point->x - this->x, 2) +
                pow(point->y - this->y, 2) * 1.0);
}
