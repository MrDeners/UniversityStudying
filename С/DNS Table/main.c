#include "function.h"



int main() {
    Cache *cache = malloc(sizeof(Cache));
    cacheCreate(&cache, 3);
    programWork(&cache);
    cacheFree(cache);
    return 0;
}
