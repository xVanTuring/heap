#ifndef UTILS_H
#define  UTILS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum
{
	SORT_INCREASING = 1,
	SORT_DECREASING = 2
};
#ifndef TRUE
#define TRUE 1
#endif // !TRUE

#ifndef FALSE
#define FALSE 0
#endif // !FALSE


#ifndef MIN
#define MIN(x,y)   (((x) < (y)) ? (x) : (y))
#endif // !MIN

#ifndef MAX
#define MAX(x,y)   (((x) > (y)) ? (x) : (y))
#endif // !MAX

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
extern void* re_alloc(void**, int, int);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !UTILS_H
