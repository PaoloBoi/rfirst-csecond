#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
//#include <string>

#include <structures/symmetrical-instance.h>
#include <structures/geom-node.h>

using namespace std;

class File_Reader {

public:
    //File_Reader();
    File_Reader(string file);
    void read_file();
    void print_data();

private:
    bool is_file_valid();
    bool open_file();
    bool close_file();

    string file_path;
    ifstream in_file;

    SymmetricalInstance symm_instance;
};

#endif // FILEREADER_H
