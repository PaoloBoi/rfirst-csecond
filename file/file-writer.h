#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <iostream>
#include <fstream>
#include <string>
#include <QDebug>

using namespace std;

/**
 * @class File_Writer
 *
 * @brief Questa classe fornisce un helper per la scrittura delle istanze su file di testo.
 *
 * I dati elaborati vengono estratti dall'istanza e scritti sul file di output.
 *
 * @author Diego Marcia { gpimple@gmail.com }
 * @author Paolo Boi { paoloboi87@gmail.com }
 */
class File_Writer {

public:
    /** @brief Costruttore di default. */
    File_Writer();

    /** @brief Costruttore principale della classe. */
    File_Writer(string filePath);

    /** @brief Avvia la scrittura del file. */
    void write_file(QString header, QString body);

    /** @brief Ritorna lo stato della scrittura su file. */
    bool is_writed() { return this->is_writed(); }

private:
    bool write_state;
    string file_path;
    ofstream out_file;

    /** @brief Apre il file in scrittura. */
    bool open_file();

    /** @brief Chiude il file. */
    bool close_file();
};

#endif // FILEWRITER_H
