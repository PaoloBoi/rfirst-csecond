#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>

#include <iostream>
#include <file/file-reader.h>

const char * filePath = "../rfirst-csecond/data/vrpnc1-.txt";

using namespace std;

int main() {

    File_Reader f_reader(filePath);

    f_reader.read_file();

    f_reader.print_data();

    return 0;
}

