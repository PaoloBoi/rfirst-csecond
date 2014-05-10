#include <plane.h>
#include <math.h>

/**
 * @brief Costruttore
 *
 * Inizializza il flag per le istanze simmetriche, la matrice delle distanze (usata per istanze asimmetriche), il vettore dei nodi e la lista dei nodi attivi.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 */
Plane::Plane(QVector<GeomNode> readNodes, double **readDistances, bool instanceType){
    this->symmetricInstance = instanceType;
    this->distances = readDistances;
    this->nodes = readNodes;


    QVectorIterator<GeomNode> i(this->nodes);
    while (i.hasNext())
        this->activeNodes.append(i.next().get_id());
}

/**
 * @brief Nodo a distanza minore.
 *
 * Dato l'ID di un nodo, rende l'ID del nodo più vicino e la distanza tra essi.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 */
QPair<int, double> Plane::closest (int node){
    QPair<int, double> min; // Il nodo più vicino e la distanza da quello ricevuto.

    if (!this->nodes.empty()){  // Ci sono ancora nodi attivi?

        double calcDist;

        int minPos=0;     // Assumo che il più vicino sia il primo dei nodi attivi
        double minDist;
        if (this->symmetricInstance){
            minDist = this->squared_distance(node, this->activeNodes.at(0));
        } else {    // Caso asimmetrico
            minDist = distances[node][0];
        }

        // Per tutti i nodi attivi...
        for (int i=1; i<this->activeNodes.size(); i++){
            if (this->symmetricInstance){
                calcDist = squared_distance(node, this->activeNodes.at(i));   // ... Calcolo la distanza al quadrato dal nodo ricevuto
                if (calcDist < minDist){    // Se ho trovato un nodo più vicino, aggiorno i riferimenti
                    minDist = calcDist;
                    minPos = i;
                }
            } else {    // Caso asimmetrico
                calcDist = distances[node][this->activeNodes.at(i)];   // ... Ricavo la distanza esatta dal nodo ricevuto
                if (calcDist < minDist){    // Se ho trovato un nodo più vicino, aggiorno i riferimenti
                    minDist = calcDist;
                    minPos = i;
                }
            }
        }

        if (this->symmetricInstance) minDist=sqrt(minDist);   // Distanza effettiva
        min.first = this->activeNodes.takeAt(minPos);    // Rimuovo il nodo dalla lista degli attivi
        min.second = minDist;

        return min;
    } else {
        min.first = -1;
        min.second = -1;
        return min;
    }
}

/**
 * @brief Distanza tra due nodi
 *
 * Dati gli ID di due nodi, rende la distanza euclidea tra essi.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 */
double Plane::distance (int nodeA, int nodeB){
    if (this->symmetricInstance) {

        double x_dist = nodes.at(nodeA).get_x_coord() - nodes.at(nodeB).get_x_coord();
        double y_dist = nodes.at(nodeA).get_y_coord() - nodes.at(nodeB).get_y_coord();

        return sqrt((x_dist * x_dist) + (y_dist * y_dist));
    } else {    // Caso asimmetrico
        return this->distances[nodeA][nodeB];
    }
}

/**
 * @brief Distanza tra due nodi al quadrato
 *
 * Dati gli ID di due nodi, rende la distanza al quadrato. Utile per confrontare più distanze senza dover ricorrere alla funzione sqrt.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 */
double Plane::squared_distance(int nodeA, int nodeB){
    double x_dist = nodes.at(nodeA).get_x_coord() - nodes.at(nodeB).get_x_coord();
    double y_dist = nodes.at(nodeA).get_y_coord() - nodes.at(nodeB).get_y_coord();

    return (x_dist * x_dist) + (y_dist * y_dist);
}

/**
 * @brief Recupera un nodo
 *
 * Dato l'ID di un nodo, rende l'oggetto GeomNode associato.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 */
GeomNode Plane::get_node(int whichNode){
    if ((whichNode >-1) && (whichNode < this->nodes.size()))
        return this->nodes.at(whichNode);
    else {
        qCritical("Richiesto un nodo inesistente! %d", whichNode);
        return GeomNode(-1, -1, -1, -1);    // Trovare un altro modo che non implichi eccezioni e non sia ambiguo.
    }
}


int Plane::get_nodes_number(){
    return this->nodes.size();
}
