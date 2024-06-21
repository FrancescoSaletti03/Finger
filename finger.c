#include "finger.h"
#include "SOExplorer.h"

int main(int argc, char const *argv[])
{
    struct user *firstUser = explorePwd();
    exploreUTMP(firstUser);
}