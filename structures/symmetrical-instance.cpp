#include "symmetrical-instance.h"

SymmetricalInstance::SymmetricalInstance() { }

int SymmetricalInstance::get_customers_number() { return customers_number; }

void SymmetricalInstance::set_customers_number(int value) { customers_number = value; }

int SymmetricalInstance::get_vehicle_capacity() { return vehicle_capacity; }

void SymmetricalInstance::set_vehicle_capacity(int value) { vehicle_capacity = value; }

int SymmetricalInstance::get_max_route_time() { return max_route_time; }

void SymmetricalInstance::set_max_route_time(int value) { max_route_time = value; }

int SymmetricalInstance::get_drop_time() { return drop_time; }

void SymmetricalInstance::set_drop_time(int value) { drop_time = value; }

int SymmetricalInstance::get_depot_x_coord() { return depot_x_coord; }

void SymmetricalInstance::set_depot_x_coord(int value) { depot_x_coord = value; }

int SymmetricalInstance::get_depot_y_coord() { return depot_y_coord; }

void SymmetricalInstance::set_depot_y_coord(int value) { depot_y_coord = value; }

/** Il nodo @em node è un'istanza della classe @link GeomNode @endlink. */
void SymmetricalInstance::add_node(GeomNode node) { nodes_list.append(node); }

void SymmetricalInstance::print_data() {

    cout << customers_number << " " << vehicle_capacity << " " << max_route_time << " " << drop_time << endl;

    cout << depot_x_coord << " " << depot_y_coord << endl;

    for(int i = 0; i < nodes_list.size(); i++) { nodes_list[i].print_data(); }
}
