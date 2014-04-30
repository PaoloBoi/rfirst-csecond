#include "geom-node.h"

int GeomNode::get_x_coord() { return x_coord; }

int GeomNode::get_y_coord() { return y_coord; }

int GeomNode::get_capacity() { return capacity; }

void GeomNode::print_data() { cout << x_coord << " " << y_coord << " " << capacity << endl; }
