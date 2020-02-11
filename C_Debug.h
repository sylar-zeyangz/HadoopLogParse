#ifndef ___C_DEBUG_H___
#define ___C_DEBUG_H___

#include <stdio.h>

#define C_DBG_OUT(_s) fprintf(stdout,"%s\tFile: %s\n\tFunction: %s\n\tLine: %d\n",(_s),__FILE__,__func__,__LINE__)
#define C_DBG_ERR(_s) fprintf(stderr,"%s\tFile: %s\n\tFunction: %s\n\tLine: %d\n",(_s),__FILE__,__func__,__LINE__)

#endif //___C_DEBUG_H___
