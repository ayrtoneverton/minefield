#ifndef _Minefield_h
#define _Minefield_h

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Clause SETS */
typedef enum
{
    Minefield__OK,
    Minefield__ERROR,
    Minefield__KILLED
    
} Minefield__MSG;
#define Minefield__MSG__max 3

/* Clause CONCRETE_VARIABLES */


/* Clause CONCRETE_CONSTANTS */
/* Basic constants */
#define Minefield__MINE -2
#define Minefield__NONE -1
#define Minefield__TOTAL 449
/* Array and record constants */



extern void Minefield__INITIALISATION(void);

/* Clause OPERATIONS */

extern void Minefield__select(int32_t xx, int32_t yy, Minefield__MSG *rr);
extern void Minefield__isWinner(Minefield__MSG *rr);
extern void Minefield__initField(int32_t *ff);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _Minefield_h */
