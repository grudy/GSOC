/*
 Matrix Represenations and basic operations
 TOMAS J. BOOTHBY AND ROBERT W. BRADSHAW "BITSLICING AND THE METHOD OF FOUR
 RUSSIANS OVER LARGER FINITE FIELDS"
 
 Copyright 2013 William Andrew Alumbaugh <williamandrewalumbaugh@gmail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 
 m7d.c
 */

#include "m7d.h"
vec m7d_rm_bits(m7d_t *M, rci_t  x, rci_t  y, int  n) {
    
    
    
    
    
    wi_t  block = (y  ) / 64;
    int  spill = (y  % 64) + n - 64;
    vec bits;
    bits = (spill <= 0) ? M->rows[x][block].middle << -spill : (M->rows[x][block + 1].sign << (64 - spill)) | (M->rows[x][block].middle >> spill);
    return bits;
    
    
}


vec m7d_rs_bits(m7d_t *M, rci_t  x, rci_t  y, int  n) {
    
    
    
    
    
    wi_t  block = (y  ) / 64;
    int  spill = (y  % 64) + n - 64;
    vec bits;
    bits = (spill <= 0) ? M->rows[x][block].sign << -spill : (M->rows[x][block + 1].sign << (64 - spill)) | (M->rows[x][block].sign >> spill);
    return bits;
    
    
}
/*
 Read n bits from units
 x = rows
 y = columns
 M = Matrix read from
 */

vec m7d_ru_bits(m7d_t *M, rci_t  x, rci_t  y, int  n) {

    wi_t  block = (y  ) / 64;
    int  spill = (y  % 64) + n - 64;
    vec bits;
    bits = (spill <= 0) ? M->rows[x][block].units << -spill : (M->rows[x][block + 1].units<< (64 - spill)) | (M->rows[x][block].units>> spill);
    return bits;
    
    
}





/*
 Read n elements
 x = rows
 y = columns
 M = Matrix read from
 */

vtri m7d_read_elems(m7d_t *M, rci_t  x, rci_t  y, int  n) {

    
    wi_t  block = (y  ) / 64;
    int  spill = (y  % 64) + n - 64;
    vtri elem;
    elem.units = (spill <= 0) ? M->rows[x][block].units << -spill : ((M->rows[x][(block + 1)].units<< (64 - spill)) | (M->rows[x][block].units >> spill));
    elem.sign = (spill <= 0) ?  (M->rows[x][block].sign << -spill) : (M->rows[x][block + 1].sign << (64 - spill)) | (M->rows[x][block].sign>> spill);
    elem.middle = (spill <= 0) ?  (M->rows[x][block].middle << -spill) : (M->rows[x][block + 1].middle << (64 - spill)) | (M->rows[x][block].middle>> spill);
    elem.middle = (elem.middle >> (64 - n));
    elem.units = (elem.units >> (64 - n));
    elem.sign = (elem.sign >> (64 - n));
    
    
    
    return elem;
    
    
}





/*
 Swap rows in a matrix;
 */
void m7d_rowswap (m7d_t * M, rci_t row_a, rci_t  row_b)
{
    
    
    if((M->nrows >= (row_a ) && (M->nrows >= row_b)))
    {
        vtri  temp ;
        temp =  *M->rows[row_a -1];
        M->rows[row_a -1] = M->rows[row_b -1];
        M->rows[row_b -1] =  &temp;
        
      
        
    }
    
    else
    {
        
        return;
    }
    
}


/*
 
 */


//unfinished
void *  m7d_write_elem( m7d_t * M,rci_t x, rci_t y, vec s, vec m,  vec u )
{
    wi_t  block = (y  ) / 64;
    int   spill =  (y  % 64) ;
    M->rows[x][block].units  = (u == 0) ? (~(leftbit >> spill) &  (M->rows[x][block].units))  : ((leftbit >> spill) | (M->rows[x][block].units));
    M->rows[x][block].middle  = (m == 0) ? (~(leftbit  >> spill) &  (M->rows[x][block].middle))  : ((leftbit  >> spill) | (M->rows[x][block].middle));
    M->rows[x][block].sign  = (s == 0) ? (~(leftbit  >> spill) &  (M->rows[x][block].sign))  : ((leftbit  >> spill) | (M->rows[x][block].sign));
    return 0;

}


/*
 
 */



vtri  * m7d_block_allocate(vtri * block, rci_t  nrows,  wi_t  width)
{
    
    block  = m1ri_malloc(nrows * width * sizeof(vtri) );
    return block;
}

/*
 
 */




vtri ** m7d_row_alloc(vtri * block, vtri ** rows, wi_t width, rci_t nrows)
{
    rows = m1ri_malloc( nrows * width * sizeof(vtri *));
    for (int i = 0; i <  nrows;  i++ )
    {
        rows[i]  = (block + (i * width));
    };
    return rows;
    
}

/*
 
 */

m7d_t m7d_create( m7d_t * a, rci_t nrows, rci_t ncols)
{
    a->ncols = ncols;
    a->nrows = nrows;
    a->width =  RU64(ncols);
    a->block = m7d_block_allocate(a->block,  a->nrows,    a->width);
    a->rows  = m7d_row_alloc(a->block, a->rows, a->width, a->nrows);
    a->flags = iswindowed;
    
    return *a;
    
}


m7d_t   m7d_window(m7d_t *c, rci_t strow, rci_t stvtri, rci_t sizerows, rci_t sizecols)
{
    
    
    m7d_t  submatrix;
    
    if((strow + sizerows) > c->width)
    {
        
        
        return submatrix;
    }
    
    
    
    
    if((stvtri + sizecols) > c->width)
    {
        
        
        return submatrix;
    }
    
    
    
    submatrix.nrows =   m1ri_word * sizecols;
    submatrix.ncols =  m1ri_word * sizecols;
    submatrix.flags = iswindowed;
    submatrix.width =  sizecols;
    submatrix.block = &c->block[(stvtri * stvtri)];
    submatrix.rows = m1ri_calloc(m1ri_word * sizerows ,  sizecols * sizeof(vtri *));
    submatrix.lblock = ( (sizerows +  strow)  ==  c->width)? c->lblock:  0;
    submatrix.fcol   = 0;
    submatrix.svtri = stvtri;
    
    
    
    int i;
    
    for(  i =   strow; i < (strow + (m1ri_word * sizerows)) ; i++)
    {
        
        submatrix.rows[i - strow] = c->rows[i];
        
    }
    
    return submatrix;
    
}

void   m7d_window_create(m7d_t *c, m7d_t * submatrix, rci_t strow, rci_t stvtri, rci_t sizerows, rci_t sizecols)
{
    
    
    submatrix->nrows =   m1ri_word * sizecols;
    submatrix->ncols =  m1ri_word * sizecols;
    submatrix->flags = iswindowed;
    submatrix->width = 1 * sizecols;
    submatrix->block = &c->block[(stvtri * stvtri)];
    submatrix->rows = m1ri_calloc(m1ri_word * sizerows ,  sizecols * sizeof(vtri *));
    submatrix->lblock = ( (sizerows +  strow)  ==  c->width)? c->lblock:  0;
    submatrix->fcol   = 0;
    submatrix->svtri = stvtri;
    
    
    int i;
    
    for(  i =   strow; i < strow + (m1ri_word * sizerows) ; i++)
    {
        
        submatrix->rows[i - strow] = c->rows[i];
        
    }
    
    
    
}

/*
 
 */
vtri * m7d_allone(m7d_t * a)
{
    
    for(int i = 0; i < (a->nrows * a->width); i++)
    {
        
        a->block[i].sign = 0xffffffffffffffff;
        
        
        a->block[i].middle = 0xffffffffffffffff;
        
        a->block[i].units = 0xffffffffffffffff;
        
        
        
        
    }
    return a->block;
}

m7d_t  m7d_rand(m7d_t * a)
{
    
    for(int i = 0; i < (a->nrows * a->width); i++)
    {
        
        a->block[i].sign = m1ri_rand();
        a->block[i].middle = m1ri_rand() ;
        a->block[i].units = m1ri_rand();
   
    }
    return *a;
}








/*
 
 Releases a m7d_t into the wilderness.
 */



void m7d_free( m7d_t *  tofree)
{
    
    
    m1ri_free(tofree->rows);
    m1ri_free(tofree->block);
    
}


void addgf7(vtri * r, vtri * x, vtri * y)

{
    
    vec s;
    r->sign = x->sign ^ y->sign;
    r->middle = ~r->sign^ x->middle ^ y->middle;
    r->units = ~r->middle^ x->units ^ y->units;
    s = ~r->units;
    r->sign = s ^ x->sign ^ y->sign;
    r->middle = ~r->sign^ x->middle ^ y->middle;
    r->units = ~r->middle^ x->units ^ y->units;
    
    
}



vtri addgf7r(vtri  *x, vtri *y)
{
    vtri  r;
    r.sign = x->sign ^ y->sign;
    r.middle = (~r.sign)^ x->middle ^ y->middle;
    r.units =( ~r.middle)^ x->units ^ y->units;
    r.sign =( ~r.units) ^ x->sign ^ y->sign;
    r.middle = (~r.sign)^ x->middle ^ y->middle;
    r.units = (~r.middle)^ x->units ^ y->units;
    
    return r;
}

void subgf7( vtri *r, vtri *x, vtri *y)               //multiply matrix x by by matrix y.   The product is matrix r.

{
   
    
    
   
    
    
}
void reduce_vtri( vtri * a)
{
    vtri b = *a ;
    
    a->units  = b.units ^ (b.units  | b.sign | b.middle) ;//  )
    a->middle  = b.middle ^ (b.units  | b.sign | b.middle) ;
    a->sign  = b.units ^ (b.units  | b.sign | b.middle) ;
}


vtri subgf7r(vtri x, vtri y)               //multiply matrix x by by matrix y.   The product is matrix r.

{
    vtri r;
    return r;
}




/********************************************
 matrix r = (direct sum matrix r + matrix x)
 ********************************************/
void iaddgf7(vtri *r,vtri *x)
{
    
    
    
    
    
    
    
}

void isubgf7(vtri *r,vtri *x)  //vector  r = (vector r - vector x)
{
    
    
    
}



void  m7d_mul( vtri *r, vtri *x, vtri *y)             //multiply vector x by y assinging the output to r
{
    
}




//return the value of the vector multiplied


vtri m7d_mul_i(vtri x, vtri y)
{
    
    vtri r;
    r.units = x.units & y.units;
    r.sign  = (y.sign ^ x.sign) & (r.units);
    
    return r;
    
}




vtri m7d_mul_2(vtri a)
{
    vec temp;
    temp = a.units;
    a.units = a.middle;
    a.middle = a.sign;
    a.sign = temp;
    return a;
    
}
vtri m7d_mul_3(vtri a)
{
  
    vec z = a.units | a.middle | a.sign;
    vec temp = a.units;
   a.units =  a.sign ^ z;
    a.sign =   a.middle  ^ z;
    a.middle = temp ^ z;
   
    return a;
    
}
vtri m7d_mul_4(vtri a)
{
    vec temp = a.units;
    a.units = a.sign;
    a.sign = a.middle;
    a.middle = temp;
    
    return a;
    
    
}
vtri m7d_mul_5(vtri a)
{
    vec z = a.units| a.middle | a.sign;
    vec temp = a.units;
    a.units = a.middle ^ z;
    a.middle = a.sign ^ z;
    a.sign = z ^ temp;
    return a;
    
}
vtri m7d_mul_6(vtri a)
{
    vec z = a.units | a.middle | a.sign;

    a.units =  a.units ^ z;
    a.sign =   a.sign  ^ z;
    a.middle = a.middle ^ z;
    
    return a;
    
    
}


int m7d_equal(m7d_t const *a, m7d_t const *b)
{
    //  for a->nrows
    if ((a->nrows != b->nrows)    || ( a->ncols != b->ncols)  )
    {
        return 0;
    }
    int i, j;
    for( i = 0; i < a->nrows; i++)
    {
        
        for(j = 0; j < b->width; j++)
        {
            if((a->rows[i][j].sign != b->rows[i][j].sign) || (a->rows[i][j].units != b->rows[i][j].units ) || (a->rows[i][j].middle != b->rows[i][j].middle ))
            {
                return 0;
            }
            
        }
    }
    return 1;
}

void sub_64gf7(vtri *R, vtri *A, vtri *B)
{
    int i;
    for (i = 0; i < (sizeof(vec)); i++ )
    {
        R[i] = subgf7r(A[i], B[i]);
    }
}


void add_64gf7(vtri *R, vtri *A, vtri *B)
{
    int i;
    for (i = 0; i < (sizeof(vec)); i++ )
    {
        R[i] = addgf7r(&A[i], &B[i]);
    }
    
}

