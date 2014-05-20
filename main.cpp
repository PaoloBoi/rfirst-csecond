#include "file/file-reader.h"
#include "worker.h"
#include "timer.h"

const char * simmFilePath = "../rfirst-csecond/data/simm/vrpnc1.txt"; // Use TRUE
const char * aSimmFilePath = "../rfirst-csecond/data/asimm/A034-02f.dat"; //Use FALSE
const int op_mode = 1;

using namespace std;

int main() {

    Timer timer("Tempo di esecuzione");
    //timer.start();

    File_Reader f_reader(simmFilePath);

    f_reader.read_file(true);

    //f_reader.print_data();

    if(f_reader.is_read()) {

        timer.start();

        Worker work (f_reader.get_instance().get_plane(), f_reader.get_instance().get_vehicle_capacity());
        work.work(f_reader.get_instance().get_depot_id(), op_mode);

        timer.stop_and_print();

        qDebug("Big route generata: ");
        work.print_route(work.get_big_route(), 1);

        qDebug("Distanza Big Route: %lf", work.get_big_route_length());

        qDebug("Numero di sub-route generate: %d", work.get_sub_routes().size());

        qDebug("Lunghezza totale sub route: %lf", work.get_sub_routes_length());
        
        /* Stampa le singole distanze della big route */
        /*Plane myPlane = f_reader.get_instance().get_plane();
        QLinkedList<int> list = work.get_big_route();

        QLinkedList<int>::iterator it = list.begin();
        int prev = *it++;
        for (; it != list.end(); ++it) {
            cout << myPlane.distance(prev, *it) << endl;
            prev = *it;
        }

        cout << "---------------" << endl;
        */
    }

    //timer.stop_and_print();

    return 0;
}
