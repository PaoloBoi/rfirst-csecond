#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H

#include "file/file-reader.h"
#include "worker.h"
#include "timer.h"

class NearestNeighbour {

public:
    NearestNeighbour();
    NearestNeighbour(string filePath, bool instanceType, int opMode);

    void exec();

private:
    File_Reader *fileReader;
    Worker *work;

    Timer *timer;

    int opMode;
    bool instanceType;

    void read_file();
    void start_work();
};

#endif // NEARESTNEIGHBOUR_H
