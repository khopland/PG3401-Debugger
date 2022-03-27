#include <stdio.h>
#include "pgdbglog.h"

char glob_var = NULL;

void main(void){
    pgdebug("test");
    pgerror("error test");
    return;
}
