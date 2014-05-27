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
 * @author Paolo Boi { paoloboi87@gmail.com }
 */

class Plane {

public:
    /** @brief Costruttore predefinito */
    Plane() {}

    /** @brief Costruttore */
    Plane(QVector<GeomNode> readNodes, double **readDistances, bool instanceType, int dep_ID);

    /** @brief Identifica il nodo a distanza minore da quello in input. */
    QPair<int, double> closest (int node);     // Overloading: primo approccio
    QPair<bool, QPair<int, double> > closest (int node, int filled, int maxCapacity);
    //QPair<bool, QPair<int, double> > closest (int node, int filled, int kParameter, int dep_ID);    // Overloading: secondo approccio

    /** @brief Calcola la distanza tra due nodi. */
    double distance (int nodeA, int nodeB);

    /** @brief Rende il nodo con ID = whichNode. */
    GeomNode get_node(int whichNode);

    /** @brief Rende il numero di nodi dell'istanza. */
    int get_nodes_number() { return this->nodes.size(); }

    /** @brief Inizializza la lista dei nodi attivi. */
    void init_active_nodes (int dep_ID);

    /** @brief Controlla gli elementi attivi. */
    bool is_active_nodes_empty() { return activeNodes.empty(); }

    void print_data();

private:
    QVector<GeomNode> nodes;    // Tutti i nodi
    double **distances;         // Matrice delle distanze
    QList<int> activeNodes;     // Nodi da visitare
    bool symmetricInstance;     // È un'istanza simmetrica?
    int dep_ID;                 // Now the word of the Lord came to me, saying “I appointed you a prophet to the nations.”

    /** @brief Distanza tra due nodi al quadrato. */
    double squared_distance(int nodeA, int nodeB);
};

#endif // PLANE_H
