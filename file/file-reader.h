#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <string>

#include <structures/symmetrical-instance.h>
#include <structures/geom-node.h>

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

    /** @brief Avvia la lettura dal file. */
    void read_file();

    /** @brief Stampa i dati estratti a video. */
    void print_data();

    /** @brief Restituisce l'istanza estrapolata dal file. */
    SymmetricalInstance get_instance();

private:

    /** @brief Esegue un controllo di esistenza per il file. */
    bool is_file_valid();

    /** @brief Apre il file per la lettura. */
    bool open_file();

    /** @brief Chiude il file. */
    bool close_file();

    string file_path;
    ifstream in_file;

    SymmetricalInstance symm_instance;
};

#endif // FILEREADER_H
