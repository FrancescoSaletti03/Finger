//
// Created by francesco-saletti on 20/06/24.
//
#include <stdio.h>
#include <utmp.h>
#include <pwd.h>
#include <malloc.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "finger.h"
#include "SOExplorer.h"
#include <unistd.h>

struct user *explorePwd(){

    struct user *firstUser,  *currentUser, *lastUser;
    struct passwd *pwd;
    //una volta aperto il file Pwd contenente tutti gli utenti, lo scorro e salvo ogni utente nella mia lista linkata di struct User
    while ((pwd = getpwent()) != NULL)
    {
        //vado a salvarmi tutte le informazion idi cui ho bisogno
        currentUser = NULL;
        currentUser = malloc(sizeof(struct user));

        currentUser -> username = stringCopy( pwd -> pw_name );
        currentUser -> nomeReale = stringCopy( pwd -> pw_gecos );
        currentUser -> directoryPrincipale = stringCopy( pwd -> pw_dir );
        currentUser -> shellUtente = stringCopy( pwd -> pw_shell );
        currentUser -> stato = NONLOGGATO;
        currentUser -> printed = 0;
        currentUser -> primoLog = NULL;
        currentUser -> ultimoLog = NULL;

        //lavoro con i puntatori per ottenere una lista linkata
        if(lastUser != NULL) {
            lastUser -> prossimoUtente = currentUser;
        }

        if(firstUser == NULL){
            firstUser = currentUser;
        }

        lastUser = currentUser;


    }

    lastUser -> prossimoUtente = NULL;

    return firstUser; //testa della mi lista
}

void exploreUTMP(struct user *firstUser){

    struct user *currentUser;
    struct utmp *utmpData;
    //resetto il file UTMP per poi andare a leggerlo
    setutent();

    //Scorro il file utmp per ottenere le informazioni su tutte le shell da cui sono loggati o non gli utenti
    while ((utmpData = getutent()) != NULL) {
        currentUser = firstUser;
        //per ogni shell in UTMP, ricerco l`utente della shell nella mia lista linkata e salvo le informazioni in merito a quella shell
        while(currentUser != NULL)
            {
                if(strcmp(utmpData -> ut_user, currentUser -> username) == 0)
                {
                    struct log *Temp = malloc(sizeof(struct log));
                    Temp -> luogo = stringCopy(utmpData -> ut_line);
                    currentUser -> stato = LOGGATO;
                    Temp -> ultimoTempoLog = utmpData -> ut_time;
                    Temp -> idleTime = calcolateIdle(utmpData -> ut_line);
                    Temp -> private = calcolatePermit(utmpData -> ut_line);
                    Temp -> prossimoLog = NULL;

                    //lavoro con i puntatori per ottenere una lista linkata (delle shell)
                    if(currentUser -> primoLog == NULL)
                    {
                        currentUser -> primoLog = Temp;
                        currentUser -> ultimoLog = Temp;
                    }
                    else
                    {
                        currentUser -> ultimoLog -> prossimoLog = Temp;
                        currentUser -> ultimoLog = Temp;
                    }
                    currentUser = NULL;
                }
                else
                currentUser = currentUser -> prossimoUtente;
        }
    }
}

time_t calcolateIdle(char var2[]){
    //vado a cercare tra le informazioni del file della shell, l`ultima volta in cui l`utente si è loggato
    struct stat *info = malloc(sizeof(struct stat));
    char *temp = malloc(strlen(var2));
    strcpy(temp,_PATH_DEV);
    strcat(temp,var2);
    if(access(temp,F_OK) != 0) return 0; //controllo necessario per vedere se il file esiste (perchè in alcune distribuzioni di linux, ci sono console di accesso non presenti in dev)
    stat(temp,info);

    //per ottenere il tempo in idle, mi basta sottrarre quello corrente, con quello trovato precedentemente
    time_t const result = time(NULL) - info -> st_mtim.tv_sec;

    free(info);
    free(temp);
    return  result;
}

int calcolatePermit(char var2[])
{   //vado a cercare tra le informazioni del file della shell, se quel file dispone di determinati permessi o meno
    struct stat *info = malloc(sizeof(struct stat));
    char *temp = malloc(strlen(var2));
    strcpy(temp,_PATH_DEV);
    strcat(temp,var2);
    if(access(temp,F_OK) != 0) return 1; //controllo se il file esiste
    stat(temp,info);
    if(info -> st_mode & PERMIT)
    {
        return 1;
    }
    free(temp);
    free(info);
    return 0;
}

char *stringCopy(char const *var2)
{   //funzione di copia di una stringa passata in input, in una nuova stringa
    int const size = sizeof(char) * (strlen(var2) + 1);
    char *var1 = malloc(size);
    strcpy(var1,var2);
    return var1;
}