//
// Created by francesco-saletti on 20/06/24.
//

#ifndef FINGER_H
#define FINGER_H
#include <time.h>

enum tipiDiStato {
    LOGGATO,
    NONLOGGATO
};

struct user{
    char *username;
    char *nomeReale;
    char *directoryPrincipale;
    char *shellUtente;
    struct log *primoLog,*ultimoLog; //puntatori al primo  e ultimo log dell`utente nella lista linkata dei log
    struct  user *prossimoUtente; // puntatore al prossimo utente nella lista di utenti
};


struct log{
    char *luogo;
    enum tipiDiStato stato;
    time_t ultimoTempoLog;
    time_t idleTime;
    struct log *prossimoLog; //puntatore al prossimo log dell`utente nella lista linkata dei log
};

#endif //FINGER_H
