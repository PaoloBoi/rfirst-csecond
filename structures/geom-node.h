#ifndef GEOM_NODE_H
#define GEOM_NODE_H

#include <iostream>

using namespace std;

/**
 * @class GeomNode
 *
 * @brief Questa classe fornisce una rappresentazione geometrica dei nodi.
 *
 * Include le variabili per la memorizzazione delle coordinate cartesiane e della capacità.
 *
 * @author Paolo Boi { paoloboi87@gmail.com }
 */

class GeomNode {

public:
    //Geom_Node();
    GeomNode(int x, int y, int c) : x_coord(x), y_coord(y), capacity(c) {}

    int get_x_coord();
    int get_y_coord();
    int get_capacity();

    void print_data();

private:
    int x_coord;
    int y_coord;
    int capacity;
};

#endif // GEOM_NODE_H
