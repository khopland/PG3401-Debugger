/**
 * @date:   2022-10-17 14:06:43
 * @lastModifiedTime: 2022-10-24 15:35:45
 * @License: Apache License 2.0, https://www.apache.org/licenses/LICENSE-2.0
 */

#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define _LENGTH_ 256
char glob_var = '1';

void debugLogger(unsigned long ulErrorType, int iLine, const char *pszFile, const char *pszFormat, ...) {

    // need a mutex to increment call counter correct, and not open multiple files
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);

    // needs to be static to keep the value between calls.
    static FILE *fp = NULL, *sp;
    static int iCallCounter = 1;

    char buffer[100];

    char szFileName[_LENGTH_] = {0};
    time_t tTimeAndDate = 0;

    va_list vaArgumentPointer = {0};
    char szOutputString[_LENGTH_] = {0};
    char *pszType = NULL;

    // creates log file if its not created yet.
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
            sp = NULL;
        }
        // early return if its not in debug and caller is calling from debug function
        if (!(glob_var == '1' || glob_var == 'y' || glob_var == 'Y') && ulErrorType == 0) {
            pthread_mutex_unlock(&mutex);
            return;
        }
    }
    pszType = (ulErrorType == 1) ? "Error" : "Debug";

    // reads all extra arguments and works like printf(...).
    va_start(vaArgumentPointer, pszFormat);
    vsnprintf(szOutputString, _LENGTH_ - 1, pszFormat, vaArgumentPointer);
    va_end(vaArgumentPointer);

    // write to file the log statement.
    fprintf(fp, "%04i: %s: %s, at %s:%i\n", iCallCounter++, pszType, szOutputString, pszFile, iLine);
    pthread_mutex_unlock(&mutex);
}
