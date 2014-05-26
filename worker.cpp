#include <math.h>
#include "worker.h"

/**
 * Istanzia l'oggetto Worker, che viene utilizzato per la costruzione dei risultati.
 * Inizializza le variabili utili all'elaborazione.
 *
 * @param Il piano relativo all'istanza del problema.
 * @param Capacità del mezzo.
 *
 * @author Paolo Boi { paoloboi87@gmail.com }
 */
Worker::Worker(Plane plane, int kParameter) {

    this->instancePlane = plane;
    this->subRoutes.first = 0;
    this->maxCapacity = kParameter;
}

/**
 * Genera i risultati, a seconda del tipo di approccio selezionato (vedere documentazione).
 * Si appoggia alle funzioni di creazione della big route e delle sub-route.
 *
 * Mode = 0: "Route First - Cluster Second" semplice.
 * Mode = 1: "Route First - Cluster Second" iterato.
 * Mode = 2: "Route First - Cluster Second" con rinnovo.
 *
 * @param dep_ID ID del nodo deposito.
 * @param mode Modalità di utilizzo (approccio alla soluzione).
 *
 * @author Diego Marcia { gpimple@gmail.com }
 * @author Paolo Boi { paoloboi87@gmail.com }
 */
void Worker::work(int dep_ID, int mode) {

    this->status = false;

    qDebug("Work iniziato...");

    this->subRoutes.first = 0;

    /* Mode 0: approccio "Route First - Cluster Second" semplice */
    if(mode == 0) {
        /* Genera la big route (salva il risultato) */
        this->bigRoute = this->build_big_route(dep_ID, -1);

        qDebug("Nodi nella Big Route: %d", bigRoute.second.size());
        qDebug("Distanza percorsa nella Big Route: %lf", bigRoute.first);

        /** Genera le sub route. */
        this->subRoutes = this->build_sub_routes(dep_ID, this->bigRoute.second);
    }

    /* Mode 1: approccio "Route First - Cluster Second" iterato */
    if(mode == 1) {

        /* Variabili temporanee */
        double bestBigRoute_SubLength = 0;
        double bestSubRoute_BiggerLength = 0;

        QPair<double, QLinkedList<int> > thisBigRoute;
        QPair<double, QLinkedList<QPair<double, QLinkedList<int> > > > thisSubRouteSet;

        this->bigRoute.first = 10000000;
        this->subRoutes.first = 10000000;

        /* Per ogni nodo della rete (escluso il nodo deposito), calcola la Big Route */
        for(int i = 0; i < instancePlane.get_nodes_number(); ++i) {

            /* Esclude il nodo deposito */
            if(instancePlane.get_node(i).get_id() != dep_ID) {
                /* Calcola la big route, partendo dal nodo corrente */
                thisBigRoute = this->build_big_route(dep_ID, instancePlane.get_node(i).get_id());

                //qDebug("Nodi nella Big Route: %d", thisBigRoute.second.size()); // Stampa di debug
                //qDebug("Distanza percorsa nella Big Route: %lf", thisBigRoute.first);

                /* Calcola il set delle sub-route a partire dalla big route corrente */
                thisSubRouteSet = this->build_sub_routes(dep_ID, thisBigRoute.second);

                /* Sceglie la big route ottima */
                if(thisBigRoute.first < this->bigRoute.first) {
                    this->bigRoute = thisBigRoute;
                    bestBigRoute_SubLength = thisSubRouteSet.first; // info
                }

                /* Sceglie il set di sub-route ottimo */
                if(thisSubRouteSet.first < this->subRoutes.first) {
                    this->subRoutes = thisSubRouteSet;
                    bestSubRoute_BiggerLength = thisBigRoute.first; // info
                }

                instancePlane.init_active_nodes(dep_ID); // Azzero i nodi attivi nel Plane

                //qDebug("This length: %lf", thisSubRouteSet.first); // Stampa di debug
                //qDebug("Best length: %lf", bestSubRouteSet.first);
                //qDebug("---------------------------");
            }
        }

        //qDebug("Big Route migliore:");
        //this->print_route(this->bigRoute.second, 0);
        //qDebug("Costo della Big Route migliore: %lf", this->bigRoute.first);
        //qDebug("Costo della Sub route associata: %lf", bestBigRoute_SubLength);

        //qDebug("----------");

        //qDebug("Costo del Set di sub-route migliore: %lf", this->subRoutes.first);
        //qDebug("Costo della Big Route associata: %lf", bestSubRoute_BiggerLength);
    }

    /* Mode 2: approccio con "Clustering diretto" */
    if(mode == 2) {

        int subRouteRequest = 0, current;
        QPair<bool, QPair<int, double> > first;

        this->subRoutes.first = 0;

        first = this->instancePlane.closest(dep_ID, subRouteRequest, this->maxCapacity);

        current = first.second.first;

        while(true) {

            QPair<int, QPair<double, QLinkedList<int> > > req = this->build_sub_route(current, dep_ID);
            this->subRoutes.second.append(req.second);
            current = req.first;
            this->subRoutes.first += req.second.first;

            if(req.first == -1) break;
        }
    }

    qDebug("Work terminato...");

    this->status = true;
}

/**
 * Viene adottato un semplice algoritmo "Nearest Neighbour": ad ogni nodo visitato, si identifica il più vicino e lo si
 * aggiunge alla route globale. La procedura apre e chiude la route con il nodo deposito.
 *
 * @param dep_ID ID del nodo deposito
 * @param start ID del nodo di partenza (Mode 1)
 *
 * @return Coppia contenente: la distanza percorsa nella route e la lista dei nodi visitati.
 */
QPair<double, QLinkedList<int> > Worker::build_big_route(int dep_ID, int start) {

    /* Variabili temporanee */
    int lastNode = (start == -1 ? dep_ID : start);
    double length = 0;
    QPair<int, double> accum;
    QLinkedList<int> route;

    route.append(dep_ID);
    length += instancePlane.distance(dep_ID, lastNode);

    for (int i = 1; i < this->instancePlane.get_nodes_number(); ++i){   // Tutti i nodi tranne 0
        accum = this->instancePlane.closest(lastNode);      // Trovo il più vicino

        lastNode = accum.first;

        if (lastNode == -1) {
            break;
        }
        else {
            length += accum.second; // Aggiorno la distanza percorsa
            route.append(lastNode); // Aggiungo il nodo trovato alla path
        }
    }

    route.append(dep_ID);
    length += instancePlane.distance(lastNode, dep_ID);

    return qMakePair(length, route);
}

/**
 * Ogni sub-route viene generata dalla big route globale, a partire dal nodo start. La route generata, verrà chiusa
 * rispetto al nodo deposito e rispetterà la capacità massima del mezzo, prevista dall'istanza.
 * La lunghezza della route viene accumulata globalmente.
 *
 * @param bigRoute La big route corrente.
 * @param start ID del nodo da cui cominciare la costruzione della route.
 * @param dep_ID ID del nodo deposito.
 *
 * @return Coppia contenente: il prossimo nodo da utilizzare (o -1), la lista dei nodi visitati.
 */
QPair<int, QPair<double, QLinkedList<int> > > Worker::build_sub_route(QLinkedList<int> &bigRoute, int start, int dep_ID) {

    /* Variabili temporanee */
    int thisSubRouteRequest = 0, current = start, next, nextRequest;
    QPair<double, QLinkedList<int> > thisSubRoute;

    thisSubRoute.first = 0;

    thisSubRoute.second.append(dep_ID);    // Aggiunge il nodo deposito

    if(start != dep_ID) {           // Start diverso dal nodo deposito (Mode = 1) [ottimizzare]
        thisSubRoute.second.append(start); // Aggiunge il primo nodo (è presente come argomento)

        thisSubRoute.first += this->instancePlane.distance(dep_ID, start); // Accumulo la distanza deposito-primo

        thisSubRouteRequest += this->instancePlane.get_node(start).get_capacity();  // Aggiorno la richiesta della sub-route
    }

    /* Ciclo principale di esecuzione */
    while(true){

        next = bigRoute.takeFirst(); // Estrae il primo nodo dalla route

        /* Non ci sono più nodi da visitare (condizione di uscita #1) */
        if (bigRoute.empty()){
            thisSubRoute.second.append(dep_ID);                                  // Aggiunge il deposito (ultimo)
            thisSubRoute.first += this->instancePlane.distance(current, dep_ID); // Accumula la distanza

            /* Genero il risultato: -1 avvisa il chiamante dello STOP */
            return qMakePair(-1, thisSubRoute);
        }

        /* Estrae il nodo seguente */
        nextRequest = this->instancePlane.get_node(next).get_capacity();

        /* La capacità del mezzo verrebbe superata (condizione di uscita #2) */
        if (nextRequest + thisSubRouteRequest > maxCapacity) {
            thisSubRoute.second.append(dep_ID);                                  // Aggiunge il nodo deposito (ultimo)
            thisSubRoute.first += this->instancePlane.distance(current, dep_ID); // Accumula la distanza

            /* Genero il risultato: next è il nodo dal quale partira la prossima sub-route. */
            return qMakePair(next, thisSubRoute);
        } else { /* Elaborazione normale */
            thisSubRoute.first += this->instancePlane.distance(current, next); // Accumulo la distanza

            thisSubRoute.second.append(next);                                           // Aggiungo il nodo estratto
            thisSubRouteRequest += this->instancePlane.get_node(next).get_capacity();   // Aggiorno la domanda della sub-route
            current = next;                                                             // Imposto il nodo estratto come corrente
        }
    }
}

/**
 * Ogni sub route viene generata indipendentemente dalle precedenti.
 * Ognuna comincia con il nodo più vicino al nodo deposito.
 *
 * @param start ID del nodo da cui cominciare la costruzione della route.
 * @param dep_ID ID del nodo deposito.
 *
 * @return La coppia (ID del prossimo nodo da visitare, route generata).
 */
QPair<int, QPair<double, QLinkedList<int> > > Worker::build_sub_route(int start, int dep_ID) {

    /* Variabili temporanee */
    int thisSubRouteRequest = 0, current = start;
    QPair<bool, QPair<int, double> > next;
    QPair<double, QLinkedList<int> > thisSubRoute;
    thisSubRoute.first = 0;

    thisSubRoute.second.append(dep_ID);     // Aggiunge il nodo deposito
    if(start != dep_ID) {                   // Start diverso dal nodo deposito (Mode = 1) [ottimizzare]
        thisSubRoute.second.append(start);  // Aggiunge il primo nodo (è presente come argomento)
        thisSubRoute.first += this->instancePlane.distance(dep_ID, start);          // Accumulo la distanza deposito-primo
        thisSubRouteRequest += this->instancePlane.get_node(start).get_capacity();  // Aggiorno la richiesta della sub-route
    }

    /* Ciclo principale di esecuzione */
    while(true){

        /* Estrae il primo nodo dalla route */
        next = instancePlane.closest(current, thisSubRouteRequest, this->maxCapacity);

        /* Non ci sono più nodi da visitare (condizione di uscita #1) */
        if(next.second.first == -1) {
            thisSubRoute.second.append(dep_ID);

            thisSubRoute.first += this->instancePlane.distance(current, dep_ID);

            return qMakePair(-1, thisSubRoute);
        }

        current = next.second.first;

        /* flag TRUE */
        if(next.first) { // Sforo il mezzo

            thisSubRoute.second.append(dep_ID);         // Aggiunge il deposito (ultimo)
            thisSubRoute.first += next.second.second;   // Accumula la distanza

            return qMakePair(next.second.first, thisSubRoute);

        } else {
            thisSubRoute.second.append(next.second.first);  // Nodo più vicino

            thisSubRoute.first += next.second.second;       // Accumula la distanza

            thisSubRouteRequest += this->instancePlane.get_node(next.second.first).get_capacity(); // Aggiorna la domanda soddisfatta
        }
    }
}

/**
 * Iterativamente, viene percorsa l'intera big route. Le sub-route generate vengono accumulate e restituite in coppia
 * alla distanza percorsa (accumulata).
 *
 * @param La big route corrente.
 * @param dep_ID ID del nodo deposito.
 * @return Coppia contenente: distanza percorsa (cumulativa), set di tutte le sub-route generate.
 */
QPair<double, QLinkedList<QPair<double, QLinkedList<int> > > > Worker::build_sub_routes (int dep_ID, QLinkedList<int> bigRoute) {

    /* Variabili temporanee */
    int startingNode;
    double thisLength = 0;
    QPair<int, QPair<double, QLinkedList<int> > > tempSubroute;
    QLinkedList<QPair<double, QLinkedList<int> > > subRouteSet;
    QLinkedList<int> tempBigRoute = bigRoute;

    /* Estrae il primo nodo dalla big route (è il nodo deposito). */
    startingNode = tempBigRoute.takeFirst();

    /* Esecuzione principale. Condizione di uscita: non ci sono più nodi da visitare. */
    while (!tempBigRoute.empty()){
        tempSubroute = build_sub_route(tempBigRoute, startingNode, dep_ID/*, thisLength*/); // Genera una sub-route ad ogni iterazione.

        subRouteSet.append(tempSubroute.second);    // Accumula la sub-route generata
        thisLength += tempSubroute.second.first;    // Accumula la sitanza
        startingNode = tempSubroute.first;          // Estrae il nodo da cui partirà la sub-route successiva
    }

    return qMakePair(thisLength, subRouteSet);
}

void Worker::print_route(QLinkedList<int> route, int mode) {

    if(mode == 0) {
        QLinkedList<int>::iterator it = route.begin();
        cout << *it++;
        for (; it != route.end(); ++it) { cout << " -> " << *it; }
        cout << endl;
    }

    if(mode == 1) {
        QLinkedList<int>::iterator it = route.begin();
        //cout << *it++;
        for (it = route.begin(); it != route.end(); ++it) { cout << *it << endl; }
        //cout << endl;
    }
}
