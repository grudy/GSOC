
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
 
m1ri_strassen.c
 */


#include "m1ri_strassen.h"

void  m3d_strassen_(m3d_t *c, m3d_t *a, m3d_t*b)
{
   if(a->ncols == b->nrows)
    {
        m3d_create(c, a->nrows   , b->ncols);
        
        
     if(((a->ncols%m1ri_word) && (b->nrows%m1ri_word)) == 0 )
        {
            
            m3_smt  * a_part = malloc(sizeof(m3_smt *)) ;
            m3d_64_cubes( a_part, a);
           //square
            
            
            
            
            
            ///even width square 64 * 64
            if(a->ncols == m1ri_word)
            {
                mul_64_m3d( c->block, a->block, b->block);
                
                
                
            }
            
        
                
                
             ///even width smt
          
            }
        
        
        }
        
     if((a->ncols%m1ri_word) && (b->nrows%m1ri_word))
     {
     
     
     
     
     
     }
      
    
        
        
        
        
        
     else
     {
        //can't be multiplied
    
    
    }
    
    
    
    
    /*
    m3d_qrt cs =  m3d_qtrwindows(C);
    m3d_qrt bs =  m3d_qtrwindows(B);
    m3d_qrt as =  m3d_qtrwindows(A);
    
   */

}



/*
 Naive multiplication
*/






void  m3d_mul_naive(m3d_t *c, m3d_t *a, m3d_t*b)
{







}










