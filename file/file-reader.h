#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <string>

#include "structures/instance.h"
#include "structures/geom-node.h"
#include "structures/plane.h"

using namespace std;

/**
 * @class File_Reader
 *
 * @brief Questa classe fornisce un helper per la lettura delle istanze da file di testo.
 *
 * Il contenuto viene estratto dal file, e poi memorizzato nell struttura [], delegata alla memorizzazione dei dati.
 *
 * @author Paolo Boi { paoloboi87@gmail.com }
 */

class File_Reader {

public:
    //File_Reader();
    /** @brief Costruttore principale della classe. */
    File_Reader(string f_path);

    /** @brief Lancia la lettura del file. */
    void read_file(bool instanceType);

    /** @brief Controllo sulla effettiva lettura del file. */
    bool is_read();

    /** @brief Stampa i dati estratti a video. */
    void print_data();

    /** @brief Restituisce l'istanza estrapolata dal file. */
    Instance get_instance();

private:

    /** @brief Esegue un controllo di esistenza per il file. */
    bool is_file_valid();

    /** @brief Chiude il file. */
    bool close_file();

    /** @brief Avvia la lettura dal file, istanza simmetrica. */
    void read_symm_file();

    /** @brief Avvia la lettura dal file, istanza asimmetrica. */
    void read_asymm_file();

    bool read_state;
    string file_path;
    ifstream in_file;

    Instance instance;
};

#endif // FILEREADER_H
