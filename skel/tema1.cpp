#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <cstring>
#include <iostream>
#include <queue>
#include "process.cpp"


using namespace std;

int main(int argc, char *argv[])
{
    int numberOfFile;
    char data[10];
    std::string filename;
    queue<string> file_q;

    if (argc < 4) {
        perror("Data Input\n");
        exit(-1);
    }

    /*fisierul de input*/
    ifstream  inputFile;
    inputFile.open(argv[3]);
    inputFile >> data;
    numberOfFile = atoi(data);

    /*sortare fisere dupa dimensiune*/
    for (int i = 0; i < numberOfFile; ++i) {
        inputFile >> filename;
        std::cout << filename;
        file_q.push(filename);
    }
    inputFile.close();
    Map_data data1(atoi(argv[1]), atoi(argv[2]), file_q);
    data1.run();

    return 0;
}

