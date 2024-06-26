#include "finger.h"

#include "SOExplorer.h"
#include "Print.h"

int main(int argc, char const *argv[])
{
    struct user *firstUser = explorePwd();
    exploreUTMP(firstUser);
    printL(firstUser);
    //printS(firstUser);

}