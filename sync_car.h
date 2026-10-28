#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station{
    pthread_mutex_t mutex;
    pthread_cond_t condicao;
    pthread_cond_t embarque;

    int passageiros_esperando;
    int vagas_disponiveis;
    int passageiros_autorizados;
    int passageiros_embarcados;
    
    int passageiros_meta;
};

void station_init(struct station *station);
void station_load_car(struct station *station, int count);
void station_wait_for_car(struct station *station);
void station_on_board(struct station *station);

#endif