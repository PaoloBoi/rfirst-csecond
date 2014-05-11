#include <file/file-reader.h>
#include <worker.h>

const char * simmFilePath = "../rfirst-csecond/data/simm/vrpnc1.txt"; // Use TRUE
const char * aSimmFilePath = "../rfirst-csecond/data/asimm/A034-02f.dat"; //Use FALSE

using namespace std;

int main() {

    File_Reader f_reader(simmFilePath);

    f_reader.read_file(true);

    f_reader.print_data();

    if(f_reader.is_read()) {

        Worker work (f_reader.get_instance().get_plane(), f_reader.get_instance().get_vehicle_capacity());
        QPair<double, QLinkedList<QLinkedList<int> > > res = work.work();

        qDebug("Numero di sub-route generate: %d", res.second.size());
        qDebug("Lunghezza totale percorsa: %lf", res.first);
    }

    return 0;
}
