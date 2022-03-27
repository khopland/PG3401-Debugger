#include <stdio.h>
#include "pgdbglog.h"

char glob_var = '1';

void main(void){
    pgdebug("test %d", 1);
    pgdebug("test %d", 2);
    pgdebug("test %d", 2);
    pgdebug("test %d", 2);
    pgerror("error test");
    return;
}
