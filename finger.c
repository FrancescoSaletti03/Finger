#include "finger.h"

#include <stdio.h>
#include <stdlib.h>

#include "SOExplorer.h"

int main(int argc, char const *argv[])
{
    struct user *firstUser = explorePwd();
    exploreUTMP(firstUser);
    printf("fatto");
}