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
            if(strcmp(utmpData -> ut_user, currentUser -> username) == 0){
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
            }
            currentUser = currentUser -> prossimoUtente;
        }
    }
}

time_t calcolateIdle(char var2[]){
    struct stat *info;
    char *temp;
    int size = sizeof(char) * (strlen(var2) + strlen(_PATH_DEV) + 1 );
    temp = malloc(size);
    strcat(temp,_PATH_DEV);
    strcat(temp,var2);
    stat(temp,info);
    return time(NULL) - info -> st_mtim.tv_sec;
}

char *stringCopy(char *var2)
{
    char *var1;
    int size = sizeof(char) * (strlen(var2) + 1);
    var1 = malloc(size);setutent();
    strcpy(var1,var2);
    return var1;
}