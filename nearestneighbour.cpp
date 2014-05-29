#include "nearestneighbour.h"

/**
 * Inizializza le variabili principali della procedura.
 *
 * @param filePath Path del file dal quale leggere l'input.
 * @param instanceType TRUE per l'istanza simmetrica, FALSE per l'istanza asimmetrica.
 * @param opMode Work-mode dell'algoritmo (0, 1, 2).
 *
 */
NearestNeighbour::NearestNeighbour(string filePath, int instanceType, int opMode) {

    /* Inizializza la lettura dal file. */
    this->fileReader = new File_Reader(filePath);

    /* Imposta la tipologia dell'istanza. */
    switch (instanceType) {
    case 0:
        this->instanceType = true;
        break;

    case 1:
        this->instanceType = false;
        break;
    }

    this->opMode = opMode;

    /* Inizializza il timer. */
    this->timer = new Timer("Tempo di esecuzione");
}

/**
 * Lancia la lettura dal file di input.
 * Se questa è andata a buon fine, lancia l'esecuzione della procedura algoritmica prescelta.
 */
void NearestNeighbour::exec() {

    /* Lancia il timer. */
    this->timer->start();

    /* Legge dal file di input. */
    this->read_file();

    /* Se il file è stato letto correttamente... */
    if(this->fileReader->is_read()) {

        /* Lancia la procedura di calcolo. */
        this->start_work();
    }

    /* Ferma il timer. */
    this->timer->stop_and_print();

    if(this->work->has_worked()) {

        //QPair<double, QLinkedList<int> > thisBigRoute = work.get_big_route();

        if(this->opMode != 2) qDebug("Distanza big route: %lf", this->work->get_big_route_length());

        qDebug("Sub Route generate: %d", this->work->get_sub_routes().size());

        qDebug("Distanza percorsa nelle sub route: %lf", this->work->get_sub_routes_length());
    }
}

void NearestNeighbour::read_file() {
    this->fileReader->read_file(this->instanceType);
}

/**
 * Inizializza la variabile @link Worker @endlink e lancia le operazioni algoritmiche.
 */
void NearestNeighbour::start_work() {
    this->work = new Worker(this->fileReader->get_instance().get_plane(), this->fileReader->get_instance().get_vehicle_capacity());
    this->work->work(this->fileReader->get_instance().get_depot_id(), this->opMode);
}

/**
 * Inizializza una istanza di @link File_Writer @endlink e scrive in output i risultati dell'algoritmo.
 */
void NearestNeighbour::write_file(QString path) {
    this->fileWriter = new File_Writer(path.toStdString());
    this->fileWriter->write_file(this->work->make_QString_header(this->timer->delay()), this->work->sub_routes_to_QString());
}
