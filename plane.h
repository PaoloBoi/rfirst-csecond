#ifndef PLANE_H
#define PLANE_H

#include <QList>
#include <QPair>
#include <QVector>
#include <structures/geom-node.h>

using namespace std;

/**
 * @class Plane
 *
 * @brief Questa classe rappresenta il piano che contiene i vari nodi.
 *
 * Permette di accedere alle proprietà dei nodi ed alle relaizoni tra essi.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 */

class Plane {

public:

    Plane();
    Plane(QVector<GeomNode> readNodes, double **readDistances, bool instanceType);

    double distance (int nodeA, int nodeB);

    QPair<int, double> closest (int node);     // Overloading: primo approccio
    QPair<bool, QPair<int, double> > closest (int node, int filled);    // Overloading: secondo approccio

    GeomNode get_node(int);

    void print_data();


private:
    QVector<GeomNode> nodes;
    double **distances;
    QList<int> activeNodes;
    bool symmetricInstance;

    double squared_distance(int nodeA, int nodeB);
};

#endif // PLANE_H
