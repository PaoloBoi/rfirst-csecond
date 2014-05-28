#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H

#include "file/file-reader.h"
#include "file/file-writer.h"
#include "worker.h"
#include "timer.h"

using namespace std;

class NearestNeighbour {

public:
    NearestNeighbour();
    NearestNeighbour(string filePath, int instanceType, int opMode);

    void exec();
    void write_file(QString path);

private:
    File_Reader *fileReader;
    File_Writer *fileWriter;
    Worker *work;

    Timer *timer;

    int opMode;
    bool instanceType;

    void read_file();
    void start_work();
};

#endif // NEARESTNEIGHBOUR_H
