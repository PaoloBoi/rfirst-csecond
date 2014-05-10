#include <unistd.h>
#include <stdio.h>
#include <errno.h>
//#include <dirent.h>

#include <iostream>
#include <file/file-reader.h>

const char * simmFilePath = "../rfirst-csecond/data/vrpnc1.txt";
const char * aSimmFilePath = "../rfirst-csecond/data/A034-02f.dat";

using namespace std;

int main() {

    File_Reader f_reader(aSimmFilePath);

    f_reader.read_file(false);

    f_reader.print_data();

    return 0;
}

