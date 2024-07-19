//
// Created by francesco-saletti on 24/06/24.
//

#ifndef PRINT_H
#define PRINT_H
#include <time.h>
#include "finger.h"
void printS(struct user *firstUser);
void printL(struct user *firstUser);
char *printIdle(time_t idle,char p);
void printResearchL(struct user *firstUser, int flag,  char *utentiR[], int n);
void printResearchS(struct user *firstUser, int flag,  char *utentiR[], int n);
char *splitStringa(char *s);
#endif //PRINT_H
