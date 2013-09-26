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
 
 m7d_tests.c
 */

#include <m1ri/m1ri.h>
#include "time.h"
int main(int argc, const char * argv[])
{
    
    
    m7d_t * a, * b, *c,  *d, *e, *f, *g, *h, *i;
    a =  m1ri_malloc(sizeof(m7d_t));
    b = m1ri_malloc(sizeof(m7d_t));
    c = m1ri_malloc(sizeof(m7d_t));
    d =  m1ri_malloc(sizeof(m7d_t));
    e =  m1ri_malloc(sizeof(m7d_t));
    f = m1ri_malloc(sizeof(m7d_t));
    g = m1ri_malloc(sizeof(m7d_t));
    h = m1ri_malloc(sizeof(m7d_t));
    i = m1ri_malloc(sizeof(m7d_t));
    m7d_rand(a);
    m7d_rand(b);
    m7d_rand(c);
    
    
    
    m7d_t test_m7d_output  = m7d_create( &test_m7d_output, 3   ,3);
    
    m7d_rand(&test_m7d_output);
    
    m7d_print(&test_m7d_output);
    
    m7d_write_elem(&test_m7d_output, 1, 1, 1, 0, 1);
    
    
    m7d_identity(d,64);
    m7d_identity(e,64);
    int isequal = m7d_equal(d, e);
    
    if(isequal)
    {
        printf("Equaltest: passed ");
        
    }
    
    if(!isequal)
    {
        printf("Equaltest: failed ");
        return 1;
        
    }
    m7d_print(&test_m7d_output);
    
    m7d_create(f, 256, 256);
    m7d_create(g, 256, 256);
     m7d_create(h, 256, 256);
	m7d_window_create(f, i, 0, 0, 64, 64);
    m7d_rand(f);
    m7d_rand(g);
   	
   	m7d_classic_mul(h, f, g);
   //	    m7d_strassen(h, f, g);
   	m7d_print(g);
   m7d_print(h);
    
    return 0;
}

