#ifndef PLANE_H
#define PLANE_H

#include <QList>
#include <QPair>
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

    double distance (int nodeA, int nodeB);

    QPair<int, int> closest (int node);     // Polimorfismo: primo approccio
    QPair<bool, QPair<int, int>> closest (int node, int filled);    // Polimorfismo: secondo approccio

    GeomNode get_node(int);


private:
    GeomNode nodes[];
    double distances[][];
    QList<int> activeNodes;
};

#endif // PLANE_H
