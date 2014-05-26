#include <QApplication>
#include "nearestneighbour.h"
#include "window/mainwindow.h"

//const char * simmFilePath = "../rfirst-csecond/data/simm/vrpnc2.txt"; // Use TRUE
//const char * aSimmFilePath = "../rfirst-csecond/data/asimm/A071-03f.dat"; //Use FALSE
//const int op_mode = 0;

//using namespace std;

int main(int argc, char *argv[]) {

    //NearestNeighbour nB(simmFilePath, true, op_mode);

    //nB.exec();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
