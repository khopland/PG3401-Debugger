#include <stdarg.h>
#include <stdio.h>
#include <time.h>

char glob_var = '1';
#define _LENGTH_ 256

void debugLogger(unsigned long ulErrorType, int iLine, const char *pszFile, const char *pszFormat, ...) {
    static FILE *fp = NULL, *sp;
    static int iCallCounter = 1;

    char buffer[100];

    char szFileName[_LENGTH_] = {0};
    time_t tTimeAndDate = 0;

    if (fp == NULL) {
        tTimeAndDate = time(NULL) - 1601399931;
        snprintf(szFileName, _LENGTH_ - 1, "debug_%li.txt", tTimeAndDate);
        fp = fopen(szFileName, "a");

        sp = fopen("settings.txt", "r");
        if (sp == NULL) {
            glob_var = '0';
        } else {
            int amountRes = fscanf(sp, "%[^\n\n]", buffer);
            glob_var = (amountRes > 0) ? buffer[0] : '0';
            fclose(sp);
        }

        if (!(glob_var == '1' || glob_var == 'y' || glob_var == 'Y') && ulErrorType == 0) {
            return;
        }
    }

    va_list vaArgumentPointer;
    char szOutputString[_LENGTH_] = {0};
    char *pszType = (ulErrorType == 1) ? "Error" : "Debug";

    va_start(vaArgumentPointer, pszFormat);
    vsnprintf(szOutputString, _LENGTH_ - 1, pszFormat, vaArgumentPointer);
    va_end(vaArgumentPointer);

    fprintf(fp, "%04i: %s: %s, at %s:%i\n", iCallCounter++, pszType, szOutputString, pszFile, iLine);
}
