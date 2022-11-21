#include <bits/stdc++.h>

struct data {
    /*adresa unde sunt stocate fiserele*/
    std::queue<std::string> *file_q;
    /*id thread-ului*/
    int id;
    pthread_barrier_t *barrier;
    pthread_mutex_t *mutex;
    /*numarul de thread-uri de reduce*/
    int reduce;
    /*adresa catre vecorul de set-uri care contine datele finale*/
    std::vector<std::set<int>> *result;

};

void *mapper_f(void *arg);
void *reduce_f(void *arg);