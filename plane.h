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

    Plane() {}

    Plane(QVector<GeomNode> readNodes, double **readDistances, bool instanceType, int dep_ID);

    QPair<int, double> closest (int node);     // Overloading: primo approccio
    // QPair<bool, QPair<int, double> > closest (int node, int filled);    // Overloading: secondo approccio

    double distance (int nodeA, int nodeB);

    GeomNode get_node(int);
    int get_nodes_number();

    bool is_active_nodes_empty() { return activeNodes.empty(); }

    void print_data();


private:
    QVector<GeomNode> nodes;    // Tutti i nodi
    double **distances;         // Matrice delle distanze
    QList<int> activeNodes;     // Nodi da visitare
    bool symmetricInstance;     // È un'istanza simmetrica?

    double squared_distance(int nodeA, int nodeB);
};

#endif // PLANE_H
