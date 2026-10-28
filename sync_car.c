#include <pthread.h>
#include "sync_car.h"

void station_init(struct station *station){
    
    pthread_mutex_init(&station->mutex,NULL);
    pthread_cond_init(&station->condicao, NULL);
    pthread_cond_init(&station->embarque, NULL);

    station->passageiros_esperando = 0;
    station->vagas_disponiveis = 0;
    station->passageiros_autorizados = 0;
    station->passageiros_embarcados = 0;

    station->passageiros_meta = 0;
}

void station_wait_for_car(struct station *station){

    pthread_mutex_lock(&station->mutex);

    station->passageiros_esperando++;

    while(station->vagas_disponiveis == 0){
        pthread_cond_wait(&station->condicao, &station->mutex);
    }

    station->passageiros_esperando--;
    station->vagas_disponiveis--;
    station->passageiros_autorizados++;

    pthread_mutex_unlock(&station->mutex);

}

void station_load_car(struct station *station, int count){

    if(count <= 0){
        return;
    }

    pthread_mutex_lock(&station->mutex);

    station->passageiros_embarcados = 0;

    if(count < station->passageiros_esperando){
        station->passageiros_meta = count;
    }

    else{
        station->passageiros_meta = station->passageiros_esperando;
    }

    station->vagas_disponiveis = station->passageiros_meta;

    pthread_cond_broadcast(&station->condicao);

    while(station->passageiros_embarcados < station->passageiros_meta){
        pthread_cond_wait(&station->embarque, &station->mutex);
    }

    station->vagas_disponiveis = 0;

    pthread_mutex_unlock(&station->mutex);

}

void station_on_board(struct station *station){

    pthread_mutex_lock(&station->mutex);

    station->passageiros_embarcados++;

    pthread_cond_signal(&station->embarque);

    pthread_mutex_unlock(&station->mutex);
}