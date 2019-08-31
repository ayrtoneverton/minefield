/* WARNING if type checker is not performed, translation could contain errors ! */

#include "Minefield.h"

/* Clause CONCRETE_CONSTANTS */
/* Basic constants */

#define Minefield__MINE -2
#define Minefield__NONE -1
#define Minefield__TOTAL 449
/* Array and record constants */
/* Clause CONCRETE_VARIABLES */

static int32_t Minefield__sizeX;
static int32_t Minefield__sizeY;
static int32_t Minefield__FIELD[Minefield__TOTAL+1];
/* Clause INITIALISATION */
void Minefield__INITIALISATION(void)
{
    
    Minefield__sizeX = 30;
    Minefield__sizeY = 15;
    {
        int32_t ii;
        int32_t mm;
        
        ii = 0;
        mm = Minefield__sizeX * Minefield__sizeY;
        while((ii) < (mm))
        {
            Minefield__FIELD[ii] = Minefield__NONE;
            ii = ii+1;
        }
    }
    Minefield__FIELD[2] = Minefield__MINE;
    Minefield__FIELD[9] = Minefield__MINE;
}

/* Clause OPERATIONS */

void Minefield__select(int32_t xx, int32_t yy, Minefield__MSG *rr)
{
    int32_t ii;
    int32_t jj;
    int32_t kk;
    int32_t ll;
    int32_t llMax;
    int32_t kkMax;
    int32_t count;
    int32_t ray;
    int32_t rayX;
    int32_t rayY;
    int32_t rayXp;
    int32_t rayYp;
    int32_t fim;
    int32_t ct;
    int32_t ex;
    int32_t maxT;
    int32_t aux;
    int32_t aux2;
    
    maxT = Minefield__TOTAL * 3;
    fim = 0;
    ct = 0;
    ex = 0;
    ray = 0;
    count = 0;
    kk = 0;
    kkMax = 0;
    ll = 0;
    llMax = 0;
    aux2 = 0;
    rayX = xx;
    rayY = yy;
    rayXp = xx;
    rayYp = yy;
    ii = xx;
    jj = yy;
    aux = Minefield__FIELD[xx+Minefield__sizeX * yy];
    if(aux == Minefield__MINE)
    {
        (*rr) = Minefield__KILLED;
    }
    else
    {
        if(aux == Minefield__NONE)
        {
            while((fim == 0) &&
            ((maxT) > (ct)))
            {
                aux = Minefield__FIELD[ii+Minefield__sizeX * jj];
                if((ray == 0) ||
                ((aux) != (Minefield__NONE)))
                {
                    count = 0;
                }
                else
                {
                    count = 1;
                    if((ii) > (0))
                    {
                        kk = ii-1;
                    }
                    else
                    {
                        kk = 0;
                    }
                    if((jj) > (0))
                    {
                        ll = jj-1;
                    }
                    else
                    {
                        ll = 0;
                    }
                    aux2 = Minefield__sizeX-1;
                    if((ii) < (aux2))
                    {
                        kkMax = ii+2;
                    }
                    else
                    {
                        kkMax = Minefield__sizeX;
                    }
                    aux2 = Minefield__sizeY-1;
                    if((jj) < (aux2))
                    {
                        llMax = jj+2;
                    }
                    else
                    {
                        llMax = Minefield__sizeY;
                    }
                    while((kk) < (kkMax))
                    {
                        while((ll) < (llMax))
                        {
                            aux2 = Minefield__FIELD[kk+Minefield__sizeX * ll];
                            if(aux2 == 0)
                            {
                                count = 0;
                            }
                            ll = ll+1;
                        }
                        if((jj) > (0))
                        {
                            ll = jj-1;
                        }
                        else
                        {
                            ll = 0;
                        }
                        kk = kk+1;
                    }
                }
                if((count == 0) &&
                (aux == Minefield__NONE))
                {
                    if((ii) > (0))
                    {
                        kk = ii-1;
                    }
                    else
                    {
                        kk = 0;
                    }
                    if((jj) > (0))
                    {
                        ll = jj-1;
                    }
                    else
                    {
                        ll = 0;
                    }
                    aux2 = Minefield__sizeX-1;
                    if((ii) < (aux2))
                    {
                        kkMax = ii+2;
                    }
                    else
                    {
                        kkMax = Minefield__sizeX;
                    }
                    aux2 = Minefield__sizeY-1;
                    if((jj) < (aux2))
                    {
                        llMax = jj+2;
                    }
                    else
                    {
                        llMax = Minefield__sizeY;
                    }
                    while((kk) < (kkMax))
                    {
                        while((ll) < (llMax))
                        {
                            aux2 = Minefield__FIELD[kk+Minefield__sizeX * ll];
                            if(aux2 == Minefield__MINE)
                            {
                                count = count+1;
                            }
                            ll = ll+1;
                        }
                        if((jj) > (0))
                        {
                            ll = jj-1;
                        }
                        else
                        {
                            ll = 0;
                        }
                        kk = kk+1;
                    }
                    Minefield__FIELD[ii+Minefield__sizeX * jj] = count;
                    if(count == 0)
                    {
                        ex = 1;
                    }
                }
                if(((ii == rayX) &&
                    (jj == rayY)) &&
                (ex == 0))
                {
                    fim = 1;
                }
                else
                {
                    if(((ii == rayX) &&
                        (jj == rayY)) &&
                    (ex == 1))
                    {
                        ray = ray+1;
                        ex = 0;
                        rayX = xx-ray;
                        rayY = yy-ray;
                        rayXp = xx+ray;
                        rayYp = yy+ray;
                        if((rayX) < (0))
                        {
                            rayX = 0;
                        }
                        if((rayY) < (0))
                        {
                            rayY = 0;
                        }
                        if((rayXp) >= (Minefield__sizeX))
                        {
                            rayXp = Minefield__sizeX-1;
                        }
                        if((rayYp) >= (Minefield__sizeY))
                        {
                            rayYp = Minefield__sizeY-1;
                        }
                        ii = rayX;
                        jj = rayY;
                    }
                    aux = 0;
                    if((jj == rayY) &&
                    ((ii) != (rayXp)))
                    {
                        aux = 1;
                        ii = ii+1;
                    }
                    if(((aux == 0) &&
                        (ii == rayXp)) &&
                    ((jj) != (rayYp)))
                    {
                        aux = 1;
                        jj = jj+1;
                    }
                    if(((aux == 0) &&
                        (jj == rayYp)) &&
                    ((ii) != (rayX)))
                    {
                        aux = 1;
                        ii = ii-1;
                    }
                    if(((aux == 0) &&
                        (ii == rayX)) &&
                    ((jj) != (rayY)))
                    {
                        jj = jj-1;
                    }
                }
                ct = ct+1;
            }
        }
        (*rr) = Minefield__OK;
    }
}

void Minefield__isWinner(Minefield__MSG *rr)
{
    int32_t ii;
    int32_t len;
    int32_t aux;
    
    ii = 0;
    len = Minefield__sizeX * Minefield__sizeY-1;
    aux = Minefield__FIELD[ii];
    if(aux == Minefield__NONE)
    {
        (*rr) = Minefield__ERROR;
    }
    else
    {
        (*rr) = Minefield__OK;
    }
    while((ii) < (len))
    {
        ii = ii+1;
        aux = Minefield__FIELD[ii];
        if(aux == Minefield__NONE)
        {
            (*rr) = Minefield__ERROR;
        }
    }
}

void Minefield__initField(int32_t *ff)
{
    memmove(Minefield__FIELD,ff,(Minefield__TOTAL+1)* sizeof(int32_t));
}

