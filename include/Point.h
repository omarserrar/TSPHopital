#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>
class Point
{
    public:
        Point(int id, float x, float y, std::string nom);
        float distance(Point* point);
        float distanceDijkstra(Point* arrivee, std::vector<std::vector<float>> matrice);
        float x,y;
        int id;
        std::string nom;
        std::vector<Point*> voisin;
    protected:

    private:
};

#endif // POINT_H
