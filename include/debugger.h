#ifndef __DEBUGGER_H__
#define __DEBUGGER_H__

#define debug(...)                                                                                                     \
    extern char glob_var;                                                                                              \
    if (glob_var == '1' || glob_var == 'y' || glob_var == 'Y') {                                                       \
        debugLogger(0, __LINE__, __FILE__, __VA_ARGS__);                                                               \
    }

#define error(...) debugLogger(1, __LINE__, __FILE__, __VA_ARGS__)

void debugLogger(unsigned long ulErrorType, int iLine, const char *pszFile, const char *pszFormat, ...);
#endif //__DEBUGGER_H__
