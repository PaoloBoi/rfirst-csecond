#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H

#include "file/file-reader.h"
#include "file/file-writer.h"
#include "worker.h"
#include "timer.h"

using namespace std;

/**
 * @class NearestNeighbour
 *
 * @brief Questa classe si occupa dell'intera esecuzione, fase per fase.
 *
 * Utilizza le funzionalità di lettura/scrittura dal/sul file, inizializza le istanze che descrivono i problemi,
 * utilizza la classe @link Worker @endlink per eseguire le procedure algoritmiche.
 *
 * @author Paolo Boi { paoloboi87@gmail.com }
 */
class NearestNeighbour {

public:

    /** @brief Costruttore. */
    NearestNeighbour(string filePath, int instanceType, int opMode);

    /** @brief Lancia l'esecuzione globale delle procedure. */
    void exec();

    /** @brief Esegue la scrittura sul file di output. */
    void write_file(QString path);

private:
    File_Reader *fileReader;
    File_Writer *fileWriter;
    Worker *work;

    Timer *timer;

    int opMode;
    bool instanceType;

    /** @brief Lancia la lettura del file di input. */
    void read_file();

    /** @brief Lancia l'esecuzione dell'algoritmo. */
    void start_work();
};

#endif // NEARESTNEIGHBOUR_H
