#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"
#include "menu.h"

void processing (int* operation, Cache **cache);
void cachePut(Cache** cache, int key, char* value, char* domen);
void cacheFree(Cache* cache);
void cacheCreate(Cache **cache, int capacity);
void searchIPbyDomen (Cache **cache);
void addNewNote ();
void searchAllDomen ();
void outputAllCache (Cache** cache);
