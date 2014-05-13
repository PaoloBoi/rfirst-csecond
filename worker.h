#ifndef WORKER_H
#define WORKER_H

#include <QLinkedList>
#include <QPair>
#include <plane.h>

using namespace std;

/**
 * @class Worker
 *
 * @brief Questa classe genera la soluzione.
 *
 * Utilizza le funzionalità della classe Plane per generare le soluzioni.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 */

class Worker {

public:

    Worker(Plane plane, int kParameter);
    //Worker(QVector<GeomNode> readNodes, double **readDistances, bool instanceType, int kParameter); // Costruttore
    QPair<double, QLinkedList<QLinkedList<int> > > work(int dep_ID);  // Costruisce i risultati

private:

    Plane instancePlane;        // Tutti i nodi
    QLinkedList<int> bigRoute;  // Route totale della prima fase
    double pathLength; // Distanza percorsa sulle sub route (somma)
    int maxCapacity;            // Capacità mezzo
    QLinkedList<QLinkedList<int> > subRoutes;   // Lista delle subroutes

    QPair<int, QLinkedList<int> > build_sub_route (int start, int dep_ID);  // Costruisce le singole subroutes

    void print_route(QLinkedList<int>);
};

#endif // WORKER_H
