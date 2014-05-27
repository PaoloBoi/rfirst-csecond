#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <QList>

#include "structures/geom-node.h"
#include "structures/plane.h"

using namespace std;

/**
 * @class SymmetricalInstance
 *
 * @brief Questa classe fornisce una semplice implementazione di una istanza simmetrica del problema.
 *
 * Include le variabili per la memorizzazione dei dati globali, delle informazioni sul punto di deposito e una lista per la gestione dei nodi.
 * Il singolo nodo è gestito attraverso la struttura @link GeomNode @endlink.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 * @author Paolo Boi { paoloboi87@gmail.com }
 */

class Instance {

public:
    /** @brief Costruttore predefinito. */
    Instance();

    /** @brief Rende il numero dei nodi nella rete. */
    int get_customers_number();

    /** @brief Imposta a @em value il numero dei nodi nella rete. */
    void set_customers_number(int);

    /** @brief Rende la capacità massima del veicolo. */
    int get_vehicle_capacity();

    /** @brief Imposta a @em value la capacità massima del veicolo. */
    void set_vehicle_capacity(int);

    /** @brief Rende il tempo massimo di percorrimento per la route. */
    int get_max_route_time();

    /** @brief Imposta a @em value la capacità massima del veicolo. */
    void set_max_route_time(int);

    /** @brief Rende il (...). */
    int get_drop_time();

    /** @brief Imposta a @em value (...). */
    void set_drop_time(int);

    /** @brief Rende l'indice del deposito, all'interno della lista dei nodi. */
    int get_depot_id();

    /** @brief Imposta a @em value l'indice del deposito. */
    void set_depot_id(int value);

    /** @brief Inizializza il piano che contiene i punti della rete. */
    void init_plane(QVector<GeomNode>, double **, bool);

    Plane get_plane();

    /** @brief Stampa a video i dati contenuti nell'istanza. */
    void print_data();

private:
    int customers_number; /**< Numero dei nodi-domanda nell'istanza */
    int vehicle_capacity; /**< Capacità del mezzo di trasporto */
    int max_route_time;   /**< Tempo massimo di attività del mezzo */
    int drop_time;

    //int depot_x_coord;  /**< Coordinate del punto di deposito. */
    //int depot_y_coord;
    int depot_id;

    Plane plane;    /**< Variabile che contiene la rappresentazione dei nodi della rete nel piano. */
};

#endif // INSTANCE_H
