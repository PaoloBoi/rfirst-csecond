#include <file/file-reader.h>
#include <worker.h>

const char * simmFilePath = "../rfirst-csecond/data/simm/vrpnc1.txt"; // Use TRUE
const char * aSimmFilePath = "../rfirst-csecond/data/asimm/A034-02f.dat"; //Use FALSE

using namespace std;

int main() {

    File_Reader f_reader(simmFilePath);

    f_reader.read_file(true);

    //f_reader.print_data();

    if(f_reader.is_read()) {

        Worker work (f_reader.get_instance().get_plane(), f_reader.get_instance().get_vehicle_capacity());
        work.work(f_reader.get_instance().get_depot_id(), 0);

        qDebug("Big route generata: ");
        work.print_route(work.get_big_route());

        qDebug("Distanza Big Route: %lf", work.get_big_route_length());

        qDebug("");


        
//        Plane myPlane = f_reader.get_instance().get_plane();
        
//        QLinkedList<QLinkedList<int> >::iterator jt = res.second.begin();

//        for(; jt != res.second.end(); ++jt) {

//            QLinkedList<int> list = *jt;

//            QLinkedList<int>::iterator it = list.begin();
//            int prev = *it++;
//            for (; it != list.end(); ++it) {
//                cout << myPlane.distance(prev, *it) << endl;
//                prev = *it;
//            }

//            cout << "---------------" << endl;

//        }

        //qDebug("Numero di sub-route generate: %d", res.second.size());
        qDebug("Lunghezza totale percorsa: %lf", work.get_sub_routes_length());
    }

    return 0;
}
