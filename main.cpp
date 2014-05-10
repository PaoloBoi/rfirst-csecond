#include <file/file-reader.h>
#include <worker.h>

const char * simmFilePath = "../rfirst-csecond/data/vrpnc1.txt"; // Use TRUE
const char * aSimmFilePath = "../rfirst-csecond/data/A034-02f.dat"; //Use FALSE

using namespace std;

int main() {

    File_Reader f_reader(aSimmFilePath);

    f_reader.read_file(false);

    f_reader.print_data();

    Worker work (f_reader.get_instance().get_plane(), f_reader.get_instance().get_vehicle_capacity());
    QPair<double, QLinkedList<QLinkedList<int> > > res = work.work();

    qDebug("Numero di sub-route generate: %d", res.second.size());
    qDebug("Lunghezza totale percorsa: %lf", res.first);

    return 0;
}

