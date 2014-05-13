#include "worker.h"
#include <math.h>

/**
 * @brief Costruttore
 *
 * Istanzia l'oggetto Plane, che rappresenta la distribuzione dei nodi nello spazio.
 *
 * @author Paolo Boi { paoloboi87@gmail.com }
 */
Worker::Worker(Plane plane, int kParameter) {

    this->instancePlane = plane;
    this->pathLength = 0;
    this->maxCapacity = kParameter;

}

/**
 * @brief Costruisce le path
 *
 * Questa classe opera in due fasi: genera una route unica con l'algoritmo Nearest Neighbour, e la divide per ogni mezzo
 *
 * @author Diego Marcia { gpimple@gmail.com }
 */
QPair<double, QLinkedList<QLinkedList<int> > > Worker::work(int dep_ID) {

    qDebug("Work iniziato...");

    //int lastNode = 0;
    int lastNode = dep_ID;
    QPair<int, double> accum;
    int startingNode;
    QPair<int, QLinkedList<int> > tempSubroute;

    // Prima fase: generiamo la route unica
    for (int i = 1; i < this->instancePlane.get_nodes_number(); ++i){   // Tutti i nodi tranne 0
        accum = this->instancePlane.closest(lastNode);      // Trovo il più vicino

        lastNode = accum.first;

        if (lastNode == -1) {
            break;
        }
        else {
            this->pathLength += accum.second;       // Aggiorno la distanza percorsa
            this->bigRoute.append(lastNode);        // Aggiungo il nodo trovato alla path
        }
    }

    qDebug("Nodi nella Big Route: %d", bigRoute.size());
    this->print_route(bigRoute);

    // Seconda fase: spezzo in più subroutes
    startingNode = this->bigRoute.takeFirst();
    while (!this->bigRoute.empty()){
        tempSubroute = build_sub_route(startingNode, dep_ID);   // Spezzo le varie sub_route ad ogni iterazione

        qDebug("Sub route corrente:");
        this->print_route(tempSubroute.second);

        this->subRoutes.append(tempSubroute.second);
        startingNode = tempSubroute.first;
    }

    qDebug("Work terminato...");

    // Restituisce la somma del costo delle sub-route, e la lista delle sub-route
    return qMakePair(this->pathLength, this->subRoutes);
}


QPair<int, QLinkedList<int> > Worker::build_sub_route(int start, int dep_ID){
    QLinkedList<int> thisSubRoute;
    int thisSubRouteRequest = 0;
    QPair<int, QLinkedList<int> > result;
    int current = start;
    int next, nextRequest;

    thisSubRoute.append(dep_ID);     // Inizio da 0. Questo andrebbe modificato con Instance.depo_id
    if(start != dep_ID) {
        thisSubRoute.append(start); // Il primo nodo ce l'ho come argomento
        this->pathLength += this->instancePlane.distance(dep_ID, start);     // Aggiungo la distanza deposito-primo
        thisSubRouteRequest += this->instancePlane.get_node(start).get_capacity();  // Aggiorno la richiesta della sub-route
    }

    while(true){
        if ((this->bigRoute.empty())){
            thisSubRoute.append(dep_ID);     // Non ci son più nodi. Torno al deposito
            this->pathLength += this->instancePlane.distance(current, dep_ID);
            result.first = -1;      // Avviso il chiamante
            result.second = thisSubRoute;
            return result;
        }

        next = bigRoute.takeFirst();        // Prossimo nodo
        nextRequest = this->instancePlane.get_node(next).get_capacity();

        if (nextRequest + thisSubRouteRequest > maxCapacity){   // Superiamo la capacità del mezzo
            thisSubRoute.append(dep_ID);     // Torno al deposito
            this->pathLength += this->instancePlane.distance(current, dep_ID);
            result.first = next;        // Dico al chiamante da dove partirà la prossima subroute
            result.second = thisSubRoute;
            return result;
        }

        thisSubRoute.append(next);      // Niente di anomalo. Aggiungo il nodo alla subroute e vado avanti.
        thisSubRouteRequest += this->instancePlane.get_node(next).get_capacity();
        current = next;
    }
}

void Worker::print_route(QLinkedList<int> route) {

    QLinkedList<int>::iterator it = route.begin();
    cout << *it++;
    for (; it != route.end(); ++it) { cout << " -> " << *it; }
    cout << endl;
}
