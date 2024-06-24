#include "finger.h"

#include <stdio.h>
#include <stdlib.h>

#include "SOExplorer.h"
#include "Print.h"

int main(int argc, char const *argv[])
{
    struct user *firstUser = explorePwd();
    exploreUTMP(firstUser);
    printS(firstUser);

}