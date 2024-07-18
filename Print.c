//
// Created by francesco-saletti on 24/06/24.
//
#include <stdio.h>
#include "Print.h"

#include <ctype.h>
#include <malloc.h>
#include <string.h>

#include "finger.h"

void printS(struct user *firstUser)
{
    printf("%-32s %-32s %-8s %-8s %-15s \n","Login","Name", "Tty", "Idle", "Login Time");
    struct user *currentUser = firstUser;
    struct log *temp;
    while (currentUser != NULL)
    {
        if(currentUser -> stato == LOGGATO ){
        temp = currentUser -> primoLog;
            while(temp != NULL)
            {
                printf("%-32s %-32s %-8s %-8s %-15s", currentUser -> username, currentUser -> nomeReale, temp -> luogo, printIdle(temp->idleTime , 's'), ctime(&temp -> ultimoTempoLog) );
                temp = temp -> prossimoLog;
            }
        }
        currentUser = currentUser -> prossimoUtente;
    }
}
void printL(struct user *firstUser)
{

    struct user *currentUser = firstUser;
    struct log *temp;
    char *stringa = malloc(sizeof(char)* 32);
    while (currentUser != NULL)
    {
        temp = currentUser -> primoLog;
        if(currentUser -> stato == LOGGATO ){
            printf("Login: %-28s Name: %s \n",currentUser -> username, currentUser->nomeReale);
            printf("Directory: %-24s Shell: %s \n",currentUser -> directoryPrincipale, currentUser -> shellUtente);
            while(temp != NULL)
            {
                strncpy(stringa,ctime(&temp -> ultimoTempoLog), 16);
                printf("On Since %s on %s",stringa,temp->luogo);
                printf("%s",printIdle(temp->idleTime , 'l'));
                temp = temp -> prossimoLog;
            }
        }
        currentUser = currentUser -> prossimoUtente;
    }
}
void printResearch(struct user *firstUser, int flag,  char *utentiR[], int n)
{
    struct user *currentUser = firstUser;
    struct log *temp;
    char *stringa = malloc(sizeof(char)* 32);
    int check;


    for(int i = 0; i < n; i = i+1 )
    {   check = 0;
        while (currentUser != NULL)
        {
            if(utentiR[i] != NULL && currentUser -> printed == 0 && (strcmp(currentUser->username,utentiR[i]) == 0 || (strcasestr(currentUser->username,utentiR[i]) != NULL && flag == 0)))
            {
                check = 1;
                printf("\nLogin: %-28s Name: %s",currentUser -> username, currentUser->nomeReale);
                printf("\nDirectory: %-24s Shell: %s",currentUser -> directoryPrincipale, currentUser -> shellUtente);

                currentUser -> printed = 1;
                temp = currentUser -> primoLog;

                if(currentUser -> stato == LOGGATO ){
                    while(temp != NULL)
                    {
                        strncpy(stringa,ctime(&temp -> ultimoTempoLog), 16);
                        printf("\nOn Since %s on %s",stringa,temp->luogo);
                        printf("%s",printIdle(temp->idleTime , 'l'));
                        temp = temp -> prossimoLog;
                    }
                }
                else
                {
                    printf("\nNever Logged In.");
                }
            }
            currentUser = currentUser -> prossimoUtente;
        }
        if(check == 0 && utentiR[i] != NULL)
        {
            printf("\nfinger: %s: no such user.", utentiR[i]);
        }
        currentUser = firstUser;
    }
}


char *printIdle(time_t idle, const char p)
{
    const long ore = idle / 3600;
    const long minuti = (idle-ore*3600)/60;
    const long secondi = (idle - (ore*3600 + minuti*60));
    char *stringa = malloc(sizeof(char) * 8);
    if (p=='s')
    {
        if(ore != 0 )
        {
            sprintf(stringa,"%ld:%ld",ore,minuti);
        }
        else
        {
            sprintf(stringa,"%ld",minuti);
        }
    }
    else
    {
        if(ore != 0)
        {
            sprintf(stringa,"\n%ld hours %ld minutes %ld seconds idle",ore,minuti,secondi);
        }
        else if(minuti !=0)
        {
            sprintf(stringa,"\n%ld minutes %ld seconds idle",minuti,secondi);
        }
        else if(secondi != 0)
        {
            sprintf(stringa,"\n%ld seconds idle",secondi);
        }
        else stringa = "";

    }

    return  stringa;
}