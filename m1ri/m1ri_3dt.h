 
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
Creates  a struct of 128 bits
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
   
    // wi_t rowstride;  //vbg's in block to traverse to  get to first
    
    
    
    u_int32_t  fblock; //  first block pointed to in a window
    u_int32_t fcol;  //column offset of first block 
    
    
    
    u_int8_t flags;
    
    
    
    
    
} m3d_t;


/*
 Matrix Windows
 ______________
 
 A = [A0 | A1]
     [A2 | A3]
 
 
 
 */
typedef  struct{
    m3d_t  * a0;
    m3d_t  * a1;
    m3d_t  * a2;
    m3d_t  * a3;
    
    
}m3d_qrt;

/*
 Read n bits from a s portion of an element
 x = rows
 y = columns
 M = Matrix read from
 */

vec m3d_rs_bits(m3d_t *, rci_t  , rci_t  , int  );

/*
 Read n bits from units
 x = rows
 y = columns
 M = Matrix read from
 */

vec m3d_ru_bits(m3d_t *, rci_t  , rci_t  , int  );




/*
 Read n elements
 x = rows
 y = columns
 M = Matrix read from 
*/

vbg m3d_read_elems(m3d_t *, rci_t  , rci_t  , int  );



/*
Swap rows in a matrix;
*/

void * m3d_rowswap (m3d_t  * , rci_t , rci_t );



/*
Naive column swapping
*/



void * m3d_colswap(m3d_t *, rci_t , rci_t );




 void   m3d_write_elem( m3d_t * ,rci_t , rci_t , vec , vec  );

vbg  * m3d_block_allocate(vbg * , rci_t  ,  wi_t  );



vbg ** m3d_row_alloc(vbg * , vbg ** , wi_t , rci_t );

m3d_t m3d_create( m3d_t * , rci_t nrows, rci_t );
 

m3d_t m3d_rand(m3d_t * );


/*
 Make an Identity Matrix
 a = Identity matrix 
 n = matrix size (row length and column width)
 
 
*/
m3d_t m3d_identitysixfour(m3d_t *, int, int);

m3d_t    m3d_identity_set(m3d_t * );



m3d_t   m3d_identity(m3d_t  *, rci_t );


m3d_t * m3d_window(m3d_t *, rci_t , rci_t , rci_t , rci_t );


 /*
 Matrix  Windows split into 4 quadrants
 ______________
 
 A = [A0 | A1]
 [A2 | A3]
 
 
 
*/
m3d_qrt    m3d_qtrwindows(m3d_t *);


/*
 Concat b on the end of a, the result is c
 
 
 
   [a] [b] ----->  [a b]   ===  C

*/
m3d_t concat(m3d_t * , m3d_t * , m3d_t * );


/*
    Stacks a on b, resulting matrix is c
    [a]
         ===  C
    [b]
 
*/
m3d_t stack(m3d_t * ,  m3d_t * , m3d_t * );

    
  
/*
 
 Releases a m3d_t into the wilderness.
 */

m3d_t m3d_transpose(m3d_t * );



int m3d_equal(m3d_t *, m3d_t *);





void m3d_free( m3d_t *  );











#endif
