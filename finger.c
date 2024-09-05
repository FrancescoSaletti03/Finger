#include "finger.h"

#include <stdlib.h>
#include <stdio.h>
#include "SOExplorer.h"
#include "Print.h"
#include <string.h>

int main(int argc, const char *argv[])
{
    //inizializzo la mia lista di utenti(struct user) e la popolo con tutti gli utenti del sistema
    struct user *firstUser = explorePwd();

    //prendo le informazioni su tutti gli utenti loggati sul sistema
    exploreUTMP(firstUser);

    //se è finger senza argomenti aggiuntivi, stampo la ¨versione¨ -s
    if(argc == 1)
    {
        printS(firstUser);
        return 0;
    }
    argv[0] = "";

    //ordino i miei argomenti in ordine alfabetico
    qsort(argv,argc,sizeof(const char*),ComparatoreStringa);

    //controllo tutti gli argomenti e vedo se c`è un utente da ricercare tra di essi
    if(argv[argc-1][0] != '-')
    {
        const char *utentiR[argc];
        int k = 0;
        int flag = 0;

        for(int i = 0; i < argc; i = i + 1)
        {   //nel caso c`è un -m imposto ad 1 il flag corrispondente
            if(strcmp(argv[i],"-m")==0)
            {
                flag =1 ;
            }
            //ogni argomento corrispondetne al nome di un utente, viene messo in un vettore
            if(argv[i][0] != '-' && strcmp(argv[i],"") != 0)
            {
                utentiR[i] = argv[i];
            }
            else
            {
                utentiR[i] = NULL;
            }
        }
        //a seconda dei parametri passati in imput, stampo o la versione -l o quella -s degli utenti cercati
        if(strcmp(argv[1],"-s")==0)
        {
            printResearchS(firstUser,flag,utentiR,argc);
        }
        else
        {
            printResearchL(firstUser , flag, utentiR,argc);
        }

        return 0;
    }

    //stampa di tutti gli utenti loggati a seconda dei parametri passati in input
    if(strcmp(argv[1],"-s")==0)
    {
        printS(firstUser);
    }
    else
    {
        printL(firstUser);
    }

}
static int ComparatoreStringa(const void* a, const void* b)
{
    return strcmp (*(const char**)a, *(const char**)b);
}