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
    //scorro tutti gli utenti nella mia lista linkata
    while (currentUser != NULL)
    {
        if(currentUser -> stato == LOGGATO )
        {
            temp = currentUser -> primoLog;

            //scorro tutte le shell di ogni utente, e per ciascuna stampo le informazioni in formato -s
            while(temp != NULL)
            {
                printf("%-32s %-32s ", currentUser -> username, splitStringa(currentUser -> nomeReale));
                //se quella shell non ha permessi, stampa * di fianco
                if(temp -> private == 0)
                {
                    printf("*");
                }
                printf("%-8s %-8s %-15s",temp -> luogo, printIdle(temp->idleTime , 's'), ctime(&temp -> ultimoTempoLog) );
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

    //scorro tutti gli utenti nella mia lista linkata
    while (currentUser != NULL)
    {
        temp = currentUser -> primoLog;
        if(currentUser -> stato == LOGGATO ){
            printf("Login: %-28s Name: %s \n",currentUser -> username, splitStringa(currentUser -> nomeReale));
            printf("Directory: %-24s Shell: %s",currentUser -> directoryPrincipale, currentUser -> shellUtente);

            //scorro tutte le shell di ogni utente, e per ciascuna stampo le informazioni in formato -l
            while(temp != NULL)
            {
                strncpy(stringa,ctime(&temp -> ultimoTempoLog), 16);
                printf("\nOn Since %s on ",stringa);
                //se quella shell non ha permessi, stampa * di fianco
                if(temp -> private == 0)
                {
                    printf("*");
                }
                printf("%s",temp->luogo);
                printf("%s",printIdle(temp->idleTime , 'l'));
                temp = temp -> prossimoLog;
            }
        }
        currentUser = currentUser -> prossimoUtente;
    }
    free(stringa);
}
void printResearchL(struct user *firstUser, int flag,  const char *utentiR[], int n)
{
    struct user *currentUser = firstUser;
    struct log *temp;
    char *stringa = malloc(sizeof(char)* 32);
    int check;

    //scorro la mia lista di utenti da Trovare
    for(int i = 0; i < n; i = i+1 )
    {   check = 0;
        //scorro la lista linkata di Utenti Del Sistema
        while (currentUser != NULL)
        {
            //quando trovo l`utente nella lista linkata stampo le informazioni su tutte le sue shell (loggate e non) in formato -s
            if(utentiR[i] != NULL && (strcmp(currentUser->username,utentiR[i]) == 0 || (strcasestr(currentUser->username,utentiR[i]) != NULL && flag == 0)))
            {
                check = 1;
                //controllo per vedere se quell`utente è già stato stampato o meno
                if(currentUser->printed == 0)
                {
                    printf("Login: %-28s Name: %s",currentUser -> username, splitStringa(currentUser -> nomeReale));
                    printf("\nDirectory: %-24s Shell: %s",currentUser -> directoryPrincipale, currentUser -> shellUtente);

                    currentUser -> printed = 1;
                    temp = currentUser -> primoLog;

                    //se l`utente è loggato da quella shell, stampa le informazioni sul tempo, altrimeni stampa ¨Non è loggato¨
                    if(currentUser -> stato == LOGGATO ){
                        while(temp != NULL)
                        {
                            strncpy(stringa,ctime(&temp -> ultimoTempoLog), 16);
                            printf("\nOn Since %s on ",stringa);
                            if(temp -> private == 0)
                            {
                                printf("*");
                            }
                            printf("%s",temp->luogo);
                            printf("%s",printIdle(temp->idleTime , 'l'));
                            temp = temp -> prossimoLog;
                        }
                    }
                    else
                    {
                        printf("\nNever Logged In.\n");
                    }
                }
            }
            currentUser = currentUser -> prossimoUtente;
        }
        //se non viene trovato nessun utente, stampa il messaggio ¨nessun utente trovato¨
        if(check == 0 && utentiR[i] != NULL)
        {
            printf("finger: %s: no such user.\n", utentiR[i]);
        }
        currentUser = firstUser;
    }
    free(stringa);
}

void printResearchS(struct user *firstUser, int flag, const char *utentiR[], int n)
{
    struct user *currentUser = firstUser;
    struct log *temp;
    int check;

    printf("%-32s %-32s %-8s %-8s %-15s \n","Login","Name", "Tty", "Idle", "Login Time");

    //scorro la mia lista di utenti da Trovare
    for(int i = 0; i < n; i = i+1 )
    {   check = 0;
        //scorro la lista linkata di Utenti Del Sistema
        while (currentUser != NULL)
        {
            //quando trovo l`utente nella lista linkata stampo le informazioni su tutte le sue shell (loggate e non) in formato -l
            if(utentiR[i] != NULL && (strcmp(currentUser->username,utentiR[i]) == 0 || (strcasestr(currentUser->username,utentiR[i]) != NULL && flag == 0)))
            {
                check = 1;
                //controllo per vedere se quell`utente è già stato stampato o meno
                if(currentUser->printed == 0)
                {
                    currentUser -> printed = 1;
                    temp = currentUser -> primoLog;

                    //se l`utente è loggato da quella shell, stampa le informazioni sul tempo, altrimeni stampa ¨No Logins¨
                    if(currentUser -> stato == LOGGATO ){
                        while(temp != NULL)
                        {
                            printf("%-32s %-32s ", currentUser -> username, splitStringa(currentUser -> nomeReale));
                            if(temp -> private == 0)
                            {
                                printf("*");
                            }
                            printf("%-8s %-8s %-15s",temp -> luogo, printIdle(temp->idleTime , 's'), ctime(&temp -> ultimoTempoLog) );
                            temp = temp -> prossimoLog;
                        }
                    }
                    else
                    {   printf("%-32s %-32s ", currentUser -> username, splitStringa(currentUser -> nomeReale));
                        char t = '*';
                        char st[]="No Logins";
                        printf("%-8c %-8c %-15s \n",t, t, st);
                    }
                }
            }
            currentUser = currentUser -> prossimoUtente;
        }
        //se non viene trovato nessun utente, stampa il messaggio ¨nessun utente trovato¨
        if(check == 0 && utentiR[i] != NULL)
        {
            printf("finger: %s: no such user.\n", utentiR[i]);
        }
        currentUser = firstUser;
    }
}


char *printIdle(time_t idle, const char p)
{
    //effettuo il calcolo per trasfrormare i millisecondi in ore, minuti e secondi
    const long ore = idle / 3600;
    const long minuti = (idle-ore*3600)/60;
    const long secondi = (idle - (ore*3600 + minuti*60));
    char *stringa = malloc(sizeof(char) * 8);
    // a seconda del formato di stampa che ho, creo una stringa con il formato più corretto
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
            sprintf(stringa,"\n%ld hours %ld minutes %ld seconds idle\n",ore,minuti,secondi);
        }
        else if(minuti !=0)
        {
            sprintf(stringa,"\n%ld minutes %ld seconds idle\n",minuti,secondi);
        }
        else if(secondi != 0)
        {
            sprintf(stringa,"\n%ld seconds idle\n",secondi);
        }
        else stringa = "";

    }

    return  stringa;
}

char *splitStringa(char *s)
{   //funzione per la divisione di una stringa in base ad un separatore
    char *token = strtok(s,",");
    return token;
}