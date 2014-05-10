#include "geom-node.h"

int GeomNode::get_x_coord() const { return x_coord; }

int GeomNode::get_y_coord() const { return y_coord; }

int GeomNode::get_capacity() const { return capacity; }

int GeomNode::get_id() const { return id; }

void GeomNode::print_data() { cout << "node " << id << ": " << x_coord << " " << y_coord << " " << capacity << endl; }
