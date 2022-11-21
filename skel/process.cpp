#include <iostream>
#include <queue>
#include <fstream>
#include "utils.h"

class Map_data {
    public:
        int number_map, number_red;
        /*queue in care realizam stocarea fisierelor*/
        std::queue<std::string> file_q;



    Map_data(int map_number, int red_number,
             std::queue<std::string> file_queue) {
            number_map = map_number;
            number_red = red_number;
            file_q = file_queue;
    }


    void run() {
        /*thread-urile de map si reduce*/
        pthread_t threads[number_map + number_red];
        /*vectorul de structuri care contine informatii necesere prelucrari*/
        data data_th[number_map + number_red];
        /*vectorul de set-uri pe care stocam rezultatele finale ca sa nu
        avem duplicari*/
        std::vector<std::set<int>> result(number_red);

        /*initializarea mutexului si barierelor*/
        pthread_barrier_t barrier;
        pthread_mutex_t mutex;
        pthread_mutex_init(&mutex, NULL);
        pthread_barrier_init(&barrier, NULL, number_map + number_red);

        int r;
        void *status;
        /*crearea threadurilor*/
        for (int i = 0; i < (number_map + number_red); ++i) {
            data_th[i].barrier = &barrier;
            data_th[i].result = &result;
            if (i < number_map) {
                data_th[i].id = i;
                data_th[i].file_q = &file_q;
                data_th[i].reduce = number_red;
                data_th[i].mutex = &mutex;
                data_th[i].result = &result;
                r = pthread_create(&threads[i], NULL, mapper_f, (void *) &data_th[i]);
            }
            if (i >= number_map) {
                data_th[i].id = i - number_map + 2;
                r = pthread_create(&threads[i], NULL, reduce_f, (void *) &data_th[i]);
            }
            if (r) {
                printf("Error create thread\n");
                exit(-1);
            }
        }
        for (int i = 0; i < (number_map + number_red); ++i) {
            r = pthread_join(threads[i], &status);
            if (r) {
                printf("Error create thread\n");
                exit(-1);
            }
        }
        /*distrugerea mutexului si barierei*/
        pthread_mutex_destroy(&mutex);
        pthread_barrier_destroy(&barrier);
    }
};