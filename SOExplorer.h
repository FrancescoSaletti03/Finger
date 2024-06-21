//
// Created by francesco-saletti on 20/06/24.
//

#ifndef SOEXPLORER_H
#define SOEXPLORER_H
#include "finger.h"
#include <time.h>

struct user *explorePwd();

void exploreUTMP(struct user *firstUser);

time_t calcolateIdle(char var2[]);

char *stringCopy(char *var2);

#endif //SOEXPLORER_H
