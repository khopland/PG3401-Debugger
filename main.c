#include <stdio.h>
#include "pgdbglog.h"

char glob_var = 'n';

int main(void){
    pgdebug("test %d", 1);
    pgdebug("test %d", 2);
    pgdebug("test %d", 2);
    pgdebug("test %d", 2);
    pgerror("error test");
    return 0;
}
