//
// Created by francesco-saletti on 20/06/24.
//

#ifndef SOEXPLORER_H
#define SOEXPLORER_H
#include "finger.h"
#include <time.h>
#define PERMIT 00220

struct user *explorePwd();

void exploreUTMP(struct user *firstUser);

time_t calcolateIdle(char var2[]);

char *stringCopy(char const *var2);

int calcolatePermit(char var2[]);

#endif //SOEXPLORER_H
