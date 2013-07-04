 
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
 
 m1ri_3dt.h
 */

#ifndef M1RIGF3_M1RIGF3_H
#define M1RIGF3_M1RIGF3_H

#include <stdlib.h>
#include "m1riwrappers.h"






/********************************************
Creates  a union of 128 bits
********************************************/

typedef struct {
    
    vec units;
    vec sign;
} vbg;




/*
    GF(3) Matrix structure
 
*/

typedef struct {
    
    rci_t nrows; //< number of rows
    
    rci_t ncols; //< number of columns
    
    wi_t width; //< the number of vbg's needed to hold columns
    
    
    
    vbg * block;  //< block containing the data contiguous in memory
    
    vbg ** rows;  // < pointers to rows of the matrix
    
    
    vec * cero;   //Identifies zeroes (with an XOR statement)a0
   
    u_int32_t * pero; //First block in  a row without all zeroes
    u_int32_t * cnt;  //Number of rows with of each respective width from the start of the row
    
    
    
    u_int8_t flags;
    
    
    
    
    
} m3d_t;


/*
 Matrix Windows
 ______________
 
 A = [A0 | A1]
     [A2 | A3]
 
 
 
 */
typedef  struct{
    m3d_t   a0;
    m3d_t  a1;
    m3d_t a2;
    m3d_t  a3;
    
    
}m3d_qrt;

/*
 Read n bits from a s portion of an element
 x = rows
 y = columns
 M = Matrix read from
 */

vec m3d_rs_bits(m3d_t *M, rci_t  x, rci_t  y, int  n) {
    
    
    
    
    
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

vec m3d_ru_bits(m3d_t *M, rci_t  x, rci_t  y, int  n) {
    
    
    
    
    
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

vbg m3d_read_elems(m3d_t *M, rci_t  x, rci_t  y, int  n) {
   
    
    
  
    wi_t  block = (y  ) / 64;
    
    int  spill = (y  % 64) + n - 64;
    
    vbg elem;
    
    elem.units = (spill <= 0) ? M->rows[x][block].units << -spill : ((M->rows[x][(block + 1)].units<< (64 - spill)) | (M->rows[x][block].units >> spill));
    
    elem.sign = (spill <= 0) ?  (M->rows[x][block].sign << -spill) : (M->rows[x][block + 1].sign << (64 - spill)) | (M->rows[x][block].sign>> spill);
    
    elem.units = (elem.units >> (64 - n));
   
    elem.sign = (elem.sign >> (64 - n));
    
    
    
    return elem;
    
    
}





/*
Swap rows in a matrix;
*/

void * m3d_rowswap (m3d_t * M, rci_t row_a, rci_t  row_b)
{
    
    
    if((M->nrows >= (row_a ) && (M->nrows >= row_b)))
       {
           vbg * temp =  m1ri_malloc(M->width * sizeof(vbg));
           temp =  M->rows[row_a -1];
           M->rows[row_a -1] = M->rows[row_b -1];
           M->rows[row_b -1] =  temp;
           
           
       
       }
    
    
   
    return 0;
}





/*
Naive column swapping
*/



void * m3d_colswap(m3d_t *M, rci_t col_a, rci_t col_b)
{
    if((M->ncols >= (col_a ) && (M->nrows >= col_b)))
    {
        
       rci_t block_a = col_a/64;
       rci_t block_b = col_b/64;
        rci_t dif_a = col_a%64;
        rci_t dif_b = col_b%64;
       rci_t a_place =  rightbit >>  (dif_a - 1);
        rci_t b_place =  rightbit >> (dif_b - 1);
        vbg tempa;
        vbg tempb;
        for(int i = 0; i > M->nrows; i++)
        {
           
            
            
            tempa.sign = (M->rows[i][block_a].sign) & a_place;
            tempa.units = (M->rows[i][block_a].units) & a_place;
            tempb.units = (M->rows[i][block_b].units) & b_place;
            tempb.sign = (M->rows[i][block_b].sign) & b_place;
            
            
            M->rows[i][block_b].units = (tempa.sign == 0)? (M->rows[i][block_b].units &  ~b_place): (M->rows[i][block_b].units | b_place);
            M->rows[i][block_b].sign = (tempa.units == 0)? (M->rows[i][block_b].sign &  ~b_place): (M->rows[i][block_b].sign   | b_place);
            
            M->rows[i][block_a].units = (tempa.sign == 0)? (M->rows[i][block_a].units &  ~a_place): (M->rows[i][block_a].units | a_place);
            M->rows[i][block_a].sign = (tempa.units == 0)? (M->rows[i][block_a].sign &  ~a_place): (M->rows[i][block_a].sign  | a_place);
            
            
            
            

        
        }
        
        
        
        
        
        
    }

    return M;
}

/*
 
 */




void *  m3d_write_elem( m3d_t * M,rci_t x, rci_t y, vec s, vec u )
{
    
    
    
    wi_t  block = (y  ) / 64;
    
    int   spill = (y  % 64) - 63;
    
    
    
     s = ~(s == 0);
     u = ~(u == 0);
    
    
    M->rows[x][block].units  = (u == 0) ? (~(rightbit << -spill) &  (M->rows[x][block].units))  : ((u << (64 - spill)) | (M->rows[x][block].units));
    
    M->rows[x][block].sign  = (s == 0) ? (~(rightbit << -spill) &  (M->rows[x][block].units))  : ((u << (64 - spill)) | (M->rows[x][block].units));
    
    return 0;
    
    
}


/*
 
 */



vbg  * m3d_block_allocate(vbg * block, rci_t  nrows,  wi_t  width)
{
    
    
     block  = m1ri_malloc(nrows * width * sizeof(vbg) );
    

    
    return block;
    
    
    
}

/*
 
 */




vbg ** m3d_row_alloc(vbg * block, vbg ** rows, wi_t width, rci_t nrows)
{
    
    
    
   
    rows = m1ri_malloc( nrows * width * sizeof(vbg *));
    
    
    for (int i = 0; i <  nrows;  i++ )
    {
                rows[i]  = (block + (i * width));
        
    
    };
        
    return rows;
}

/*
     
 */

m3d_t m3d_create( m3d_t * a, rci_t nrows, rci_t ncols)
{
    
    
    a->ncols = ncols;
    a->nrows = nrows;
    a->width =  RU64(ncols);
    a->block = m3d_block_allocate(a->block,  a->nrows,    a->width);
    a->rows  = m3d_row_alloc(a->block, a->rows, a->width, a->nrows);
    a->flags = iswindowed;
    
    return *a;
    
}

/*
 
 */

vbg * m3d_rand(m3d_t * a)
{
   
    for(int i = 0; i < (a->nrows * a->width); i++)
    {
        
        a->block[i].sign = m1ri_rand();
        
        
        
        
        a->block[i].units = m1ri_rand();
    
        
        
        
    }
    return a->block;
}


/*
 Make an Identity Matrix
 a = Identity matrix 
 n = matrix size (row length and column width)
 
 
*/


m3d_t    m3d_identity_set(m3d_t * a)

{
    if (a->nrows == a->ncols)
    {
        
        
        
        for(int i = 0; i < (a->nrows/64); i++ )
        {
            
            a->rows[i][i].units = ibits;
            
        }
        
        
    }
    return *a;
}

/*
 
 */


m3d_t   m3d_identity(m3d_t  *a, rci_t n)
{
    *a = m3d_create(a, n, n);
    *a = m3d_identity_set(a);
  
    return *a;
    
    
}


/*
 
 */



/*
 Upper triangular
 */




m3d_t m3d_re(m3d_t *a)
{
    
    
    int i, j, x;
	vec temp;
  	a->cero = m1ri_malloc(a->nrows * sizeof(vec * ) );
	a->pero = m1ri_malloc(a->nrows * a->ncols * sizeof(u_int32_t));
    a->cnt = m1ri_malloc(a->width * sizeof(u_int32_t));
   
                              
                              
                              
         for (i = 0; i < a->nrows; i++)
                {
                    //Records first  vbg without all zeroes
                    //initial value is a placeholder
                a->pero[i] = a->width ;
                                  
                                  
                              }
                              
            for (i = 0; i < a->nrows; i ++)
   {
                                  
                                  
                for (j = 0; j < a->width; j++)
                    {
                        temp = (a->rows[i][j].units ^ a->rows[i][j].sign);
                                      
                                      
                    if (temp > 0)
                            {
                                
                        if ( a->pero[i]  > j  )
                        {
                                              
                                a->cero[i] =  temp;
                                a->pero[i] =  j;  //'width  to a  nonzero'
                                a->cnt[j] ++;
                                              
                        }
                                          
                              }
                                      
                       }
                                  
}


    
    
    for ( i = 0; i < a->width; i++)
                              
        {
            if ( a->cnt[i] > 0){
                
                
                x = 1;
                
                
                
                
                                      
                }
                                  
                                  
                                  
        }
                              
                              
            m1ri_free(a->cero);
            m1ri_free(a->pero);
            m1ri_free(a->cnt);
                              
                              
                              
            return *a;
                              
    
                              

}

m3d_qrt m3d_lwindows(m3d_t *c)
{
    m3d_qrt b;
    
    b.a0  = b.a1 = b.a2 =b.a3 = *c;
    b.a0.ncols = b.a1.ncols = b.a2.ncols = b.a3.ncols = DN(c->ncols,2);
    
    b.a0.nrows = b.a1.nrows = b.a2.nrows = b.a3.nrows = DN(c->nrows, 2);
    
    b.a0.flags = b.a1.flags = b.a2.flags = b.a3.flags = notwindowed;
    
    b.a0.width = b.a1.width = b.a2.width = b.a3.width = DN(c->width, 2);
    
    
    
    
    
    return b;

}



 /*
 Matrix Windows
 ______________
 
 A = [A0 | A1]
 [A2 | A3]
 
 
 
*/
m3d_qrt  m3d_swindows(m3d_t *c)
{
    m3d_qrt b;
   
    int demi= DN((c->width * c->nrows  * sizeof(vbg)), 4 );
  
    int inim = DN((c->width * c->nrows * sizeof(vbg * )), 4);
    
    b.a0.block =  m1ri_malloc(demi);
    
    b.a1.block =  m1ri_malloc(demi);
    
    b.a2.block =  m1ri_malloc(demi);
    
    b.a3.block =  m1ri_malloc(demi);
    
    b.a0.ncols = b.a1.ncols = b.a2.ncols = b.a3.ncols = DN(c->ncols,2);
    
    b.a0.nrows = b.a1.nrows = b.a2.nrows = b.a3.nrows = DN(c->nrows, 2);
    
    b.a0.flags = b.a1.flags = b.a2.flags = b.a3.flags = notwindowed;
    
    b.a0.width = b.a1.width = b.a2.width = b.a3.width = DN(c->width, 2);
    
    b.a0.rows = m1ri_malloc(inim);
    
     b.a1.rows = m1ri_malloc(inim);
    
    b.a2.rows = m1ri_malloc(inim);
    
    b.a3.rows = m1ri_malloc(inim);
    
    int  xtrbts = b.a0.ncols%64;
        
        if (xtrbts == 0)
        {
        for( int i = 0; i < b.a0.nrows; i++)
        {
            
            
            
            b.a0.rows[i] =   c->rows[i];
            
            b.a1.rows[i] =   c->rows[i] +(i * b.a1.width);
            
            b.a2.rows[i] =   c->rows[i + b.a1.nrows] ;
            
            b.a3.rows[i] =   c->rows[i + b.a1.nrows] +(i * b.a3.width);
            
            
            
            
        }
        
        }
    
    return b;



}


/*
 Concat b on the end of a, the result is c
 
 
 
   [a] [b] ----->  [a b]   ===  C

*/
m3d_t concat(m3d_t * c, m3d_t * a, m3d_t * b)
{
    if (a->nrows != b->nrows)
    {
        /*if concat hath failed*/
        return *c;

    }
    
    if(a->nrows == b->nrows)
    {
          *c = m3d_create(c, a->nrows , a->ncols + b->ncols);
        int x, y;
        x =  0;
        
        
        while (x < a->nrows) {
            
            
            for(y = 0; y < a->width; y++)
            {
                c->rows[x] = a->rows[x];
            }
            
            
            for(y = a->width; y  < c->width; y++)
            {
                
                
                
            }
            x++;
        }
      
        
        
        
    }
return  *c;
}


/*
    Stacks a on b, resulting matrix is c
    [a]
         ===  C
    [b]
 
*/
 m3d_t stack(m3d_t * c,  m3d_t * a, m3d_t * b)
{
    
    
    if (a->ncols != b->ncols)
    {
       /*If a stacked matrix cannot be created*/
        return *c;
        
    }
    
    
    if(a->ncols == b->ncols)
    {
        *c = m3d_create(c, (a->nrows + b->nrows), a->ncols);
        int x =  0;
        while (x < a->nrows) {
            
            c->rows[x] = a->rows[x];
            
            
            x++;
        }
        while(x < (a->nrows + b->nrows)){
        
            c->rows[x] = a->rows[x - a->nrows];
        
            x++;
        }
              
              
        
     
    }
    
      return *c;
    
    
}
        
    
    
    
  
/*
 
 Releases a m3d_t into the wilderness.
 */

m3d_t m3d_transpose(m3d_t * a)
{
    m3d_t b = m3d_create(a, a->ncols , a->nrows);
    int i, j;
    
    for(i = 0; i < a->nrows; i++)
        
        
        for(j = 0; j < a->ncols; j++)
        {
            a->rows[i][j] = b.rows[j][i];
        
        
        
        }
            
            
    return b;
    

}



int m3d_equal(m3d_t *a, m3d_t *b)
{
  //  for a->nrows
    if ((a->nrows != b->nrows)    || ( a->ncols != b->ncols)  )
    {
        return 0; 
    }
    int i, j;
    for( i = 0; i < a->nrows; i++)
    {

        for(j = 0; j < a->width; j++)
        {
    if((a->rows[i][j].sign != b->rows[i][j].sign) || (a->rows[i][j].sign != b->rows[i][j].sign))
    {
    return 0;
    }
        
        }
}
    return 1;
}





void m3d_free( m3d_t *  tofree)
{
    
    
    m1ri_free(tofree->rows);
    m1ri_free(tofree->block);
   
}












#endif
