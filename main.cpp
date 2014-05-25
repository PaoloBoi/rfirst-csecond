#include "file/file-reader.h"
#include "worker.h"
#include "timer.h"

const char * simmFilePath = "../rfirst-csecond/data/simm/vrpnc2.txt"; // Use TRUE
const char * aSimmFilePath = "../rfirst-csecond/data/asimm/A071-03f.dat"; //Use FALSE
const int op_mode = 0;

using namespace std;

int main() {

    Timer timer("Tempo di esecuzione");

    //File_Reader f_reader(simmFilePath);
    //f_reader.read_file(true);

    File_Reader f_reader(aSimmFilePath);
    f_reader.read_file(false);

    /* Se il file è stato letto */
    if(f_reader.is_read()) {

        timer.start();

        /* Esegue il calcolo */
        Worker work (f_reader.get_instance().get_plane(), f_reader.get_instance().get_vehicle_capacity());
        work.work(f_reader.get_instance().get_depot_id(), op_mode);

        timer.stop_and_print();

        if(work.has_worked()) {

            //QPair<double, QLinkedList<int> > thisBigRoute = work.get_big_route();

            if(op_mode != 2) qDebug("Distanza big route: %lf", work.get_big_route_length());

            qDebug("Sub Route generate: %d", work.get_sub_routes().size());

            qDebug("Distanza percorsa nelle sub route: %lf", work.get_sub_routes_length());
        }
    }

    return 0;
}
