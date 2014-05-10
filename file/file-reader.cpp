#include "file-reader.h"

/**
 * @param file_path Path del file dal quale estrapolare.
 *
 * Inizializza il path del file d'istanza, dal quale verranno lette le informazioni.
 */
File_Reader::File_Reader(string f_path) { file_path = f_path; }

/**
 * A seconda dell'input, lancia la lettura dell'uno o dell'altro tipo di istanza.
 *
 * @param instanceType TRUE per l'istanza simmetrica, FALSE per l'istanza asimmetrica.
 */
void File_Reader::read_file(bool instanceType) {

    if(open_file()) { // Apre il file

        if(instanceType) { this->read_symm_file(); }
        else { this->read_asymm_file(); }

        /* Chiude il file */
        close_file();

    } else { qErrnoWarning("Impossibile aprire il file"); }
}

/**
 * Stampa i dati estrapolati, richiamando la funzione di stampa dell'istanza @link SymmetricalInstance @endlink.
 */
void File_Reader::print_data() { instance.print_data(); }

/**
 * @return L'istanza della struttura dati che contiene i dati estratti dal file.
 */
Instance File_Reader::get_instance() { return instance; }

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

/**
 * Legge il file di input riga per riga, basandosi sulla struttura di rappresentazione delle istanze
 * (simmetriche/asimmetriche). Salva le informazioni all'interno della struttura dati che rappresenta l'istanza.
 *
 */
void File_Reader::read_symm_file() {

    /* Variabili di lettura temporanee */
    int a = 0, b = 0, c = 0, d = 0;
    int i = 0, matrix_dim = 0;

    QVector<GeomNode> nodes(0);

    /* Legge la prima riga */
    in_file >> a >> b >> c >> d;

    matrix_dim = a + 1; // Dimensione della matrice

    /* Imposta le caratteristiche globali dell'istanza */
    instance.set_customers_number(a);
    instance.set_vehicle_capacity(b);
    instance.set_max_route_time(c);
    instance.set_drop_time(d);

    /* Legge la seconda riga */
    in_file >> a >> b;

    /* Inserisce il nodo deposito */
    instance.set_depot_id(i); // ID del deposito: nell'istanza simmetrica è 0
    nodes.append(GeomNode(a, b, 0, i));

    /* Legge le restanti righe e inserisce i dati nel vettore. */
    while(in_file >> a >> b >> c) { nodes.append(GeomNode(a, b, c, ++i)); }

    cout << "Nodes size: " << nodes.size() << endl;

    /* Il numero totale dei nodi è dato da: customers_number + 1 */
    instance.init_plane(nodes, NULL, true);
}

/**
 * Legge il file di input riga per riga, basandosi sulla struttura di rappresentazione delle istanze
 * (simmetriche/asimmetriche). Salva le informazioni all'interno della struttura dati che rappresenta l'istanza.
 *
 */
void File_Reader::read_asymm_file() {

    /* Variabili di lettura temporanee */
    int a = 0, b = 0, c = 0;
    int i = 0, j = 0, matrix_dim = 0;

    double **matrix; // Matrice delle distanze

    string aa, bb, line;

    QVector<GeomNode> nodes(0); // Vettore dei nodi

    /* Informazioni non disponibili per le istanze asimmetriche */
    instance.set_max_route_time(-1);
    instance.set_drop_time(-1);

    /* Salta le prime 3 righe */
    for(i = 0; i < 3; i++) { std::getline(in_file, line); }

    /* Numero dei nodi-domanda */
    in_file >> aa >> bb >> c;
    instance.set_customers_number(c-1);
    matrix_dim = c;

    /* Inizializza la matrice */
    matrix = new double* [matrix_dim];

    /* Salta altre 4 righe */
    for(i = 0; i < 4; i++) { std::getline(in_file, line); }

    /* Capacità del mezzo */
    in_file >> aa >> bb >> c;
    instance.set_vehicle_capacity(c);

    /* Numero dei veicoli */
    //in_file >> aa >> bb >> c;
    //symm_instance.set_vehicle_capacity(c);

    /* Salta altre 3 righe */
    for(i = 0; i < 3; i++) { std::getline(in_file, line); }

    /* Legge la matrice */
    for(i = 0; i < matrix_dim; i++) {
        matrix[i] = new double[matrix_dim]; // Istanzia la riga corrente

        for(j = 0; j < matrix_dim; j++) {
            in_file >> a;
            matrix[i][j] = a;
            //cout << a << " ";
        }
    }

    /* Salta altre 2 righe */
    for(i = 0; i < 2; i++) { std::getline(in_file, line); }

    /* Legge le domande relative ai nodi */
    for(i = 0; i < matrix_dim; i++) {
        in_file >> a >> b;
        nodes.append(GeomNode(b, a-1));
    }

    /* Legge l'indice del nodo deposito */
    in_file >> aa >> b;
    instance.set_depot_id(b-1);

    cout << "Nodi acquisiti: " << nodes.size() << endl;

    /* Lancia l'inizializzazione del piano.
         * Il numero totale dei nodi è dato da: customers_number + 1 */
    instance.init_plane(nodes, matrix, false);
}
