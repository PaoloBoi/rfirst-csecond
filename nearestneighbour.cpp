#include "nearestneighbour.h"

NearestNeighbour::NearestNeighbour() {
}

/**
 * istanza simmetrica = TRUE
 * istanza asimmetrica = FALSE
 */
NearestNeighbour::NearestNeighbour(string filePath, bool instanceType, int opMode) {

    this->fileReader = new File_Reader(filePath);
    this->instanceType = instanceType;
    this->opMode = opMode;

    this->timer = new Timer("Tempo di esecuzione");
}

void NearestNeighbour::exec() {
    this->timer->start();

    this->read_file();

    if(this->fileReader->is_read()) {

        this->start_work();
    }

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

void NearestNeighbour::start_work() {
    this->work = new Worker(this->fileReader->get_instance().get_plane(), this->fileReader->get_instance().get_vehicle_capacity());
    this->work->work(this->fileReader->get_instance().get_depot_id(), this->opMode);
}
