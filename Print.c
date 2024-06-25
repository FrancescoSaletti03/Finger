//
// Created by francesco-saletti on 24/06/24.
//
#include <stdio.h>
#include "Print.h"
#include <malloc.h>
#include "finger.h"

void printS(struct user *firstUser)
{
    printf("%-32s %-32s %-8s %-8s %-15s \n","Login","Name", "Tty", "Idle", "Login Time");
    struct user *currentUser = firstUser;
    struct log *temp;
    while (currentUser != NULL)
    {
        temp = currentUser -> primoLog;
        while(temp != NULL)
        {
            if(temp-> stato == LOGGATO )
            {
                printf("%-32s %-32s %-8s %-8s %-15s", currentUser -> username, currentUser ->nomeReale, temp -> luogo, printIdle(temp->idleTime), ctime(&temp -> ultimoTempoLog) );
            }
            temp = temp -> prossimoLog;
        }
        currentUser = currentUser -> prossimoUtente;
    }
}
void printL(){}

char *printIdle(time_t idle)
{
    const long ore = idle / 3600;
    const long minuti = (idle-ore*3600)/60;
    char *stringa = malloc(sizeof(char) * 8);
    if(ore != 0)
    {
        sprintf(stringa,"%ld:%ld",ore,minuti);
    }
    else
    {
        sprintf(stringa,"%ld",minuti);
    }
    return  stringa;
}