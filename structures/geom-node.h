#ifndef GEOM_NODE_H
#define GEOM_NODE_H

#include <iostream>

using namespace std;

/**
 * @class GeomNode
 *
 * @brief Questa classe fornisce la rappresentazione geometrica dei nodi.
 *
 * Include le variabili per la memorizzazione delle coordinate cartesiane e della capacità.
 *
 * @author Paolo Boi { paoloboi87@gmail.com }
 */

class GeomNode {

public:

    /** @brief Costruttore predefinito */
    GeomNode() {}

    /** @brief Costruttore
     * Inizializza, con corrispondenza 1-1 sui dati in input, tutte le variabili del nodo.
     * Si utilizza durante l'elaborazione di un'istanza simmetrica.
     */
    GeomNode(int x, int y, int c, int i) : x_coord(x), y_coord(y), capacity(c), id(i) {}

    /** @brief Costruttore
     * Inizializza le variabili capacità e ID del nodo. Le due coordinate vengono impostate a 0.
     * Si utilizza durante l'elaborazione di un'istanza asimmetrica.
     */
    GeomNode(int c, int i) : x_coord(0), y_coord(0), capacity(c), id(i) {}
    //~GeomNode() {}

    /** @brief Rende la coordinata x del nodo. */
    int get_x_coord() const;

    /** @brief Rende la coordinata y del nodo. */
    int get_y_coord() const;

    /** @brief Rende la capacità del nodo. */
    int get_capacity() const;

    /** @brief Rende l'a capacità'ID del nodo. */
    int get_id() const;

    /** @brief Stampa a video i dati. */
    void print_data();

private:

    /* Variabili del nodo */
    int x_coord;
    int y_coord;
    int capacity;
    int id;
};

#endif // GEOM_NODE_H
