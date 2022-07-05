#include <stdio.h>
#include "pgdbglog.h"

//* set to 1 for debug or 0 for error only,
//* a file name "settings.txt" with the value can also be made but keep glob_var = 1 then
char glob_var = 'y';

int main(void)
{
    pgdebug("test %d", 1);
    pgdebug("test %d", 2);
    pgdebug("test %d", 2);
    pgdebug("test %d", 2);
    pgerror("error test");
    return 0;
}