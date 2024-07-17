#include "finger.h"

#include <stdlib.h>
#include <stdio.h>
#include "SOExplorer.h"
#include "Print.h"
#include <string.h>

int main(int argc, const char *argv[])
{
    struct user *firstUser = explorePwd();
    exploreUTMP(firstUser);
    if(argc == 1)
    {
        printS(firstUser);
        return 0;
    }
    argv[0]=""; // mi permette di non considerare il nome del programma negli argomenti da ordinare
    qsort(argv,argc,sizeof(const char*),ComparatoreStringa);

    if(argv[argc-1][0] != '-')
    {
        const char *utentiR[argc];
        int k = 0;
        int flag = 0;

        for(int i = 0; i < argc; i = i + 1)
        {
            if(strcmp(argv[i],"-m")==0)
            {
                flag =1 ;
            }
            if(argv[i][0] != '-')
            {
                utentiR[k] = argv[i];
                k = k + 1;
            }
        }
        //funzione per la ricerca
    }

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