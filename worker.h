#ifndef WORKER_H
#define WORKER_H

#include <QLinkedList>
#include <QPair>
#include "structures/plane.h"

using namespace std;

/**
 * @class Worker
 *
 * @brief Questa classe genera la soluzione.
 *
 * Utilizza le funzionalità della classe Plane per generare le soluzioni.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 * @author Paolo Boi { paoloboi87@gmail.com }
 */
class Worker {

public:
    /** @brief Costruttore predefinito. */
    Worker();

    /** @brief Costruttore principale. */
    Worker(Plane plane, int kParameter);

    /** @brief Costruisce i risultati. */
    void work(int dep_ID, int mode);  // Costruisce i risultati

    /** @brief Restituisce lo stato del lavoro. */
    bool has_worked() { return this->status; }

    /** @brief Restituisce la big route generata. */
    QLinkedList<int> get_big_route () { return this->bigRoute.second; }

    /** @brief Restituisce la distanza percorsa nella big route. */
    double get_big_route_length () { return this->bigRoute.first; }

    /** @brief Restituisce l'insieme delle sub routes generato. */
    QLinkedList<QPair<double, QLinkedList<int > > > get_sub_routes () { return this->subRoutes.second; }

    /** @brief Restituisce la distanza cumulata percorsa nel set di sub route. */
    double get_sub_routes_length() { return this->subRoutes.first; }

    /** @brief Stampa a video la route in input. */
    void print_route(QLinkedList<int>, int mode);

    /** @brief Restituisce le distanze percorse dalle singole subroutes e le subroutes stesse. */
    QString sub_routes_to_QString();

    /** @brief Restituisce le informazioni generali sul risultato. */
    QString make_QString_header(float time);

    int get_maxCapacity(){return this->maxCapacity;}

private:

    bool status;

    Plane instancePlane;                        // Tutti i nodi
    QPair<double, QLinkedList<int> > bigRoute;  // Big Route (ottima) [distanza percorsa, route]
    int maxCapacity;                            // Capacità del mezzo
    QPair<double, QLinkedList<QPair<double, QLinkedList<int> > > > subRoutes;   // Lista delle subroutes [distanza accumulata, routes]

    /** @brief Costruisce la Big Route a partire dai dati dell'istanza. */
    QPair<double, QLinkedList<int> > build_big_route (int dep_ID, int start);

    /** @brief Costruisce una singola sub-route. */
    QPair<int, QPair<double, QLinkedList<int> > > build_sub_route(QLinkedList<int> &bigRoute, int start, int dep_ID);

    /** @brief Costruisce una singola sub-route. */
    QPair<int, QPair<double, QLinkedList<int> > > build_sub_route(int start, int dep_ID);

    /** @brief Genera il set completo delle sub-routes. */
    QPair<double, QLinkedList<QPair<double, QLinkedList<int> > > > build_sub_routes(int dep_ID, QLinkedList<int> bigRoute);
};

#endif // WORKER_H
