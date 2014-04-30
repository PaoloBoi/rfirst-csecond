#include "file-reader.h"

File_Reader::File_Reader(string file) {

    file_path = file;
}

void File_Reader::read_file() {

    int a, b, c, d;
    //string s_line = "";

    open_file(); // Apre il file

    /* Legge la prima riga */
    in_file >> a >> b >> c >> d;

    symm_instance.set_customers_number(a);
    symm_instance.set_vehicle_capacity(b);
    symm_instance.set_max_route_time(c);
    symm_instance.set_drop_time(d);

    /* Legge la seconda riga */
    in_file >> a >> b;

    symm_instance.set_depot_x_coord(a);
    symm_instance.set_depot_y_coord(b);

    //    while (!in_file.eof()) {

    //        getline(in_file, s_line);
    //        cout << s_line << endl;
    //    }

    /* Legge le restanti righe */
    while(in_file >> a >> b >> c) {

        symm_instance.add_node(GeomNode(a, b, c));
    }

    close_file();
}

void File_Reader::print_data() { symm_instance.print_data(); }

bool File_Reader::is_file_valid() {

    return in_file.good();
}

bool File_Reader::open_file() {

    if(is_file_valid()) {
        in_file.open(file_path.c_str(), std::ifstream::in);
        return true;
    }

    return false;
}

bool File_Reader::close_file() {

    if(is_file_valid()) {
        in_file.close();
        return true;
    }

    return false;
}
