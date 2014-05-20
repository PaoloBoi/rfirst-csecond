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
    /** @brief Costruttore principale. */
    Worker(Plane plane, int kParameter);

    /** @brief Costruisce i risultati. */
    void work(int dep_ID, int mode);  // Costruisce i risultati

    QLinkedList<int> get_big_route () { return this->bigRoute.second; }

    double get_big_route_length () { return this->bigRoute.first; }

    QLinkedList<QLinkedList<int > > get_sub_routes () { return this->subRoutes.second; }

    double get_sub_routes_length() { return /*pathLength*/this->subRoutes.first; }

    /** @brief Stampa a video la route in input. */
    void print_route(QLinkedList<int>, int mode);

private:

    Plane instancePlane;                        // Tutti i nodi
    QPair<double, QLinkedList<int> > bigRoute;  // Big Route (ottima) [distanza percorsa, route]
    //double pathLength;                        // Distanza percorsa nel set di sub-route (somma)
    int maxCapacity;                            // Capacità del mezzo
    QPair<double, QLinkedList<QLinkedList<int> > > subRoutes;   // Lista delle subroutes [distanza accumulata, routes]

    /** @brief Costruisce la Big Route a partire dai dati dell'istanza. */
    QPair<double, QLinkedList<int> > build_big_route (int dep_ID, int start);

    /** @brief Costruisce una singola sub-route. */
    QPair<int, QLinkedList<int> > build_sub_route (QLinkedList<int> &bigRoute, int start, int dep_ID, double &length_acc);

    /** @brief Genera il set completo delle sub-routes. */
    QPair<double, QLinkedList<QLinkedList<int> > > build_sub_routes(int dep_ID, QLinkedList<int> bigRoute);
};

#endif // WORKER_H
