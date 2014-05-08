#include "file-reader.h"

/**
 * @param file_path Path del file dal quale estrapolare.
 *
 * Inizializza il path del file d'istanza, dal quale verranno lette le informazioni.
 */
File_Reader::File_Reader(string f_path) {

    file_path = f_path;
}

/**
 * Legge il file di input riga per riga, basandosi sulla struttura di rappresentazione delle istanze
 * (simmetriche/asimmetriche). Salva le informazioni all'interno della struttura dati che rappresenta l'istanza.
 *
 */
void File_Reader::read_file() {

    int a = 0, b = 0, c = 0, d = 0; /* Variabili di lettura temporanee */
    int i = 0;

    if(open_file()) { // Apre il file

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

        /* Legge le restanti righe */
        while(in_file >> a >> b >> c) {
            symm_instance.add_node(GeomNode(a, b, c, ++i));
        }

        /* Chiude il file */
        close_file();
    }
    else { cout << "Impossibile aprire il file" << endl; }
}

/**
 * Stampa i dati estrapolati, richiamando la funzione di stampa dell'istanza @link SymmetricalInstance @endlink.
 */
void File_Reader::print_data() { symm_instance.print_data(); }

/**
 * @return L'istanza della struttura dati che contiene i dati estratti dal file.
 */
SymmetricalInstance File_Reader::get_instance() { return symm_instance; }

/**
 * Lancia un controllo di validità sul file, tramite l'istanza di lettura @emph ifstream.
 *
 * @return TRUE se il file esiste ed è leggibile, FALSE altrimenti.
 */
bool File_Reader::is_file_valid() {

    return in_file.good();
}

/**
 * Il file viene aperto in sola lettura.
 *
 * @return TRUE se il file è stato aperto correttamente, FALSE altrimenti.
 */
bool File_Reader::open_file() {

    if(is_file_valid()) {
        in_file.open(file_path.c_str(), std::ifstream::in);
        return true;
    }

    return false;
}

/**
 * @return TRUE se il file viene chiuso correttamente, FALSE altrimenti.
 */
bool File_Reader::close_file() {

    if(is_file_valid()) {
        in_file.close();
        return true;
    }
    return false;
}
