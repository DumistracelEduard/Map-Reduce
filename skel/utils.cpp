#include <iostream>
#include <queue>
#include <fstream>
#include <math.h>
#include "utils.h"

/*binary search utilizat pentru cautarea bazei care la o putere
 sa dea numarul dorit*/
int binarySearch( int low, int high, int power, int elem) {
    if (low > high) {
        return 0;
    }
    long int base = (low + high) / 2;
    long long int pow_elem = pow(base, power);
    if (elem == pow_elem)
        return elem;
    else if (pow_elem < elem)
        return binarySearch(base + 1, high, power, elem);
    else if (pow_elem > elem)
        return binarySearch(low, base - 1, power, elem);
    return 0;
}

/*scrierea in fisier a rezultatului final*/
void *reduce_f(void *arg) {
    data *data1 = (data *) arg;
    pthread_barrier_wait(&(*(*data1).barrier));
    std::string filename = "out"+std::to_string((*data1).id) + ".txt";
    std::ofstream outFile(filename);
    outFile << (*(*data1).result)[(*data1).id - 2].size();
    outFile.close();
    pthread_exit(NULL);
}


void *mapper_f(void *arg) {
    data *data1 = (data *) arg;
    /*citim fisierele pana cand nu mai exista fisiere necitite*/
    while(true) {
        pthread_mutex_lock(&(*(*data1).mutex));
        if((*(*data1).file_q).empty()) {
            pthread_mutex_unlock(&(*(*data1).mutex));
            break;
        }
        std::string filename = (*(*data1).file_q).front();
        std::cout << filename << " " << (*data1).id;
        (*(*data1).file_q).pop();
        pthread_mutex_unlock(&(*(*data1).mutex));
        std::ifstream  inputFile;
        inputFile.open(filename);
        int data;
        inputFile >> data;
        int value;
        for (int i = 0; i < data; ++i) {
            inputFile >> value;
            for (int j = 2; j <= (*data1).reduce + 1; ++j) {
                int result = binarySearch(0, sqrt(value), j, value);
                if (result != 0) {
                    (*(*data1).result)[j-2].insert(result);
                }
            }
        }
        inputFile.close();
    }
    pthread_barrier_wait(&(*(*data1).barrier));
    pthread_exit(NULL);
}