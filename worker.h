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
    QPair<double, QLinkedList<QLinkedList<int> > > work();  // Costruisce i risultati CAZZOMERDA: non rendo la distanza totale! >:( Da aggiungere.

private:

    Plane instancePlane;        // Tutti i nodi
    QLinkedList<int> bigRoute;  // Route totale della prima fase
    double pathLength;             // Distanza percorsa
    int maxCapacity;            // Capacità mezzo
    QLinkedList<QLinkedList<int> > subRoutes;   // Lista delle subroutes

    QPair<int, QLinkedList<int> > build_sub_route (int start);  // Costruisce le singole subroutes
};

#endif // WORKER_H
