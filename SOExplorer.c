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

    while ((pwd = getpwent()) != NULL)
    {
        currentUser = NULL;
        currentUser = malloc(sizeof(struct user));

        currentUser -> username = stringCopy( pwd -> pw_name );
        currentUser -> nomeReale = stringCopy( pwd -> pw_gecos );
        currentUser -> directoryPrincipale = stringCopy( pwd -> pw_dir );
        currentUser -> shellUtente = stringCopy( pwd -> pw_shell );
        currentUser -> primoLog = NULL;
        currentUser -> ultimoLog = NULL;

        if(lastUser != NULL) {
            lastUser -> prossimoUtente = currentUser;
        }

        if(firstUser == NULL){
            firstUser = currentUser;
        }

        lastUser = currentUser;


    }

    lastUser -> prossimoUtente = NULL;

    return firstUser;
}

void exploreUTMP(struct user *firstUser){

    struct user *currentUser;
    struct utmp *utmpData;

    setutent();
    while ((utmpData = getutent()) != NULL) {
        currentUser = firstUser;

        while(currentUser != NULL) {
            if(strcmp(utmpData -> ut_user, currentUser -> username) == 0)
            {
                struct log *Temp = malloc(sizeof(struct log));
                Temp -> luogo = stringCopy(utmpData -> ut_line);
                Temp -> stato = LOGGATO;
                Temp -> ultimoTempoLog = utmpData -> ut_time;
                Temp -> idleTime = calcolateIdle(utmpData -> ut_line);
                Temp -> prossimoLog = NULL;

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
            }else
            currentUser = currentUser -> prossimoUtente;
        }
    }
}

time_t calcolateIdle(char var2[]){
    struct stat *info = malloc(sizeof(struct stat));
    char *temp;
    int size = sizeof(char) * (strlen(var2) + strlen(_PATH_DEV) + 1 );
    time_t result;
    temp = malloc(strlen(var2));
    strcpy(temp,_PATH_DEV);
    strcat(temp,var2);
    if(access(temp,F_OK) != 0) return 0; //controllo necessario per vedere se il file esiste (perchè in alcune distribuzioni di linux, ci sono console di accesso non presenti in dev)
    stat(temp,info);
    result = time(NULL) - info -> st_mtim.tv_sec;
    return  result;
}

char *stringCopy(char *var2)
{
    char *var1;
    int size = sizeof(char) * (strlen(var2) + 1);
    var1 = malloc(size);
    strcpy(var1,var2);
    return var1;
}