#include "instance.h"

Instance::Instance() { }

int Instance::get_customers_number() { return customers_number; }

void Instance::set_customers_number(int value) { customers_number = value; }

int Instance::get_vehicle_capacity() { return vehicle_capacity; }

void Instance::set_vehicle_capacity(int value) { vehicle_capacity = value; }

int Instance::get_max_route_time() { return max_route_time; }

void Instance::set_max_route_time(int value) { max_route_time = value; }

int Instance::get_drop_time() { return drop_time; }

void Instance::set_drop_time(int value) { drop_time = value; }

/*int SymmetricalInstance::get_depot_x_coord() { return depot_x_coord; }

//void SymmetricalInstance::set_depot_x_coord(int value) { depot_x_coord = value; }

//int SymmetricalInstance::get_depot_y_coord() { return depot_y_coord; }

//void SymmetricalInstance::set_depot_y_coord(int value) { depot_y_coord = value; }*/

int Instance::get_depot_id() { return depot_id; }

void Instance::set_depot_id(int value) { depot_id = value; }

/**
 * I dati in input corrispondono ai dati necessari all'inizializzazione di una nuova istanza di @link Plane @endlink.
 *
 * @param readNodes I nodi letti dal file.
 * @param readDistances La matrice delle distanze (istanza asimmetrica).
 * @param instanceType Il tipo di istanza (TRUE se simmetrica, FALSE se assimmetrica).
 */
void Instance::init_plane(QVector<GeomNode> readNodes, double **readDistances, bool instanceType) {
    plane = Plane(readNodes, readDistances, instanceType);
}

void Instance::print_data() {

    cout << "Nodi domanda: " << customers_number << endl;
    cout << "Capacità del veicolo: " << vehicle_capacity << endl;
    cout << "Tempo max: " << max_route_time << endl;
    cout << "Soglia di stop: " << drop_time << endl;

    plane.print_data();
}
