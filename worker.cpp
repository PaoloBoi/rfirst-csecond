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
QPair<double, QLinkedList<QLinkedList<int> > > Worker::work() {

    qDebug("Work iniziato...");

    int lastNode = 0;
    QPair<int, double> accum;
    int startingNode;
    QPair<int, QLinkedList<int> > tempSubroute;

    // Prima fase: generiamo la route unica
    for (int i = 1; i < this->instancePlane.get_nodes_number(); ++i){   // Tutti i nodi tranne 0
        accum = this->instancePlane.closest(lastNode);      // Trovo il più vicino

        lastNode = accum.first;

        if (lastNode == -1)
            break;
        else {
            this->pathLength += accum.second;       // Aggiorno la distanza percorsa
            this->bigRoute.append(lastNode);        // Aggiungo il nodo trovato alla path
        }
    }

    // Seconda fase: spezzo in più subroutes
    startingNode = this->bigRoute.takeFirst();
    while (!this->bigRoute.empty()){
        tempSubroute = build_sub_route(startingNode);   // Spezzo le varie sub_route ad ogni iterazione
        this->subRoutes.append(tempSubroute.second);
        startingNode = tempSubroute.first;
    }

    qDebug("Work terminato...");

    return qMakePair(this->pathLength, this->subRoutes);
}


QPair<int, QLinkedList<int> > Worker::build_sub_route(int start){
    QLinkedList<int> thisSubRoute;
    int thisSubRouteRequest = 0;
    QPair<int, QLinkedList<int> > result;
    int current = start;
    int next, nextRequest;

    thisSubRoute.append(0);     // Inizio da 0. Questo andrebbe modificato con Instance.depo_id
    thisSubRoute.append(start); // Il primo nodo ce l'ho come argomento

    this->pathLength += this->instancePlane.distance(0, start);     // Aggiungo la distanza deposito-primo

    thisSubRouteRequest += this->instancePlane.get_node(start).get_capacity();  // Aggiorno la richiesta della sub-route

    while(true){
        if ((this->bigRoute.empty())){
            thisSubRoute.append(0);     // Non ci son più nodi. Torno al deposito
            this->pathLength += this->instancePlane.distance(current, 0);
            result.first = -1;      // Avviso il chiamante
            result.second = thisSubRoute;
            return result;
        }

        next = bigRoute.takeFirst();        // Prossimo nodo
        nextRequest = this->instancePlane.get_node(next).get_capacity();

        if (nextRequest + thisSubRouteRequest > maxCapacity){   // Superiamo la capacità del mezzo
            thisSubRoute.append(0);     // Torno al deposito
            this->pathLength += this->instancePlane.distance(current, 0);
            result.first = next;        // Dico al chiamante da dove partirà la prossima subroute
            result.second = thisSubRoute;
            return result;
        }

        thisSubRoute.append(next);      // Niente di anomalo. Aggiungo il nodo alla subroute e vado avanti.
        thisSubRouteRequest += this->instancePlane.get_node(next).get_capacity();
        current = next;
    }
}
