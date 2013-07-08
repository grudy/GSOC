/* M1RI
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
 
 m1ri_io.c
 
 
 */

#include "m1ri_io.h"



/*
 
 Print a block of an m3d
 a = the unit bits
 b =  the sign bits
 l_unused = space to the left of block unused in the matrix
 r_unused =  space to the right of block unused in the matrix
 */
void print_m3d_block(vec a, vec b, u_int32_t l_unused, u_int32_t r_unused)
{
    
    
    bool out;
    for(int x = (0  + l_unused); x < (64 - r_unused); x = x + 1)
    {
        
        
        
        
    
        out = (( a & (leftbit >>  x)) == (b & (leftbit  >> x))) ? 0:  1;
        if((out == 1) && (b & (leftbit  >> x)))
        {
               printf("[-%d ]", out);
            
        }
        else
        {
           printf("[ %d ]", out);
        }
     
        
        
        
        
        
        
        
        
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
}

void m3d_print(m3d_t *a)
{
    int i, m;
   
        printf("\n \n");

    for( i  = 0; i < a->nrows ; i++)
    {
        
         if(a->width > 1)
         {
         print_m3d_block(a->rows[i][0].units, a->rows[i][0].sign, a->fcol, 0);
             
             m = 1;
             while(m < (a->width -1))
             {
                 print_m3d_block(a->rows[i][m].units, a->rows[i][m].sign, 0, 0);
                 ++m;
             }
             
             
             
             if(a->ncols%64 == 0)
             {
                 print_m3d_block(a->rows[i][m].units, a->rows[i][m].sign, a->fcol, 0 );
             }
             
             if(a->ncols%64 != 0)
             {
              print_m3d_block(a->rows[i][m].units, a->rows[i][m].sign, 0, (64 - a->ncols%64) );
             }
             
             
         }
    
        if(a->width  ==  1)
        {
            
         if(a->ncols%64 != 0)
         {
             
         print_m3d_block(a->rows[i][0].units, a->rows[i][0].sign, a->fcol, (64 - a->ncols%64) );
         }
        if(a->ncols%64 == 0)
        {
             print_m3d_block(a->rows[i][0].units, a->rows[i][0].sign, a->fcol, 0 );
        }
      
        }
    
   
        printf("\n");
 
}
       printf("\n \n \n ");
}


void print_m7d_block(vec a, vec b, vec c,  u_int32_t l_unused, u_int32_t r_unused)
{
    bool out[3];
    short value ;
    for(int x = (0  + l_unused); x < (64 - r_unused); x = x + 1)
    {
        
        
        
        
        out[0] = (( a & (leftbit >>  x)));
        out[1] =  (( b & (leftbit >>  x)));
        out[2]  = (( c & (leftbit >>  x)));
        
        if (out[0]) {
            value = 1;
        }
        
        
        if (out[1]) {
            value = value + 2;
        }
        
        
        if(out[2])
        {
            value = value + 4;
        
        
        }
            
        
        
        
        
        
        
        
        
        
        
    }
    
    

}


void print_m5_block(vec a, vec b, vec c,  u_int32_t l_unused, u_int32_t r_unused)
{
    bool out[3];
    short value ;
    for(int x = (0  + l_unused); x < (64 - r_unused); x = x + 1)
    {
        
        
        
        
        out[0] = (( a & (leftbit >>  x)));
        out[1] =  (( b & (leftbit >>  x)));
        out[2]  = (( c & (leftbit >>  x)));
        
        if (out[0]) {
            value = 1;
        }
        
        
        if (out[1]) {
            value = value + 2;
        }
        
        
        if(out[2])
        {
            value = value + 4;
            
            
        }
        printf("w");
        
        
        
        
        
        
        
        
        
        
    }
    
    
    



}

void m5d_print(m5d_t * a)
{
    int i, m;
    
    printf("\n \n");
    
    for( i  = 0; i < a->nrows ; i++)
    {
        
        if(a->width > 1)
        {
            print_m5d_block(a->rows[i][m].units, a->rows[i][m].middle,  a->rows[i][m].sign, a->fcol, 0);
        }
        m = 0;
        while((m + 1)< (a->width -2))
        {
           // print_m5d_block(a->rows[i][m].units, a->rows[i][m].middle,  a->rows[i][m].sign, 0, 0);
            ++m;
        }
        if(m == 0)
        {
           // print_m5d_block(a->rows[i][m].units, a->rows[i][m].middle,  a->rows[i][m].sign, a->fcol, (64 - a->ncols%64) );
            
            
        }
        
        if(m > 0)
        {
            
          //  print_m5d_block(a->rows[i][m].units, a->rows[i][m].middle,  a->rows[i][m].sign, 0, (64 - a->ncols%64) );
        }
        printf("\n");
        
    }
    printf("\n \n \n ");


}





