/*  Cube Form 
 //  
 //  m1riproject
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
 
 //  Copyright (c) 2013 William Alumbaugh. All rights reserved.
 
 m1ri_cubes.h
 */


#ifndef m1riproject_m1ri_cubes_h
#define m1riproject_m1ri_cubes_h
#include "m1riwrappers.h"
#include "m1ri_3dt.h"


typedef struct
{
    rci_t nrows;
    wi_t width;
    
    m3d_t * blocks;
    m3d_t ** rows;
    
}m3_smt;




typedef struct
{
    rci_t nrows;
    wi_t width;
    
    vbg * blocks;
    vbg ** rows;
    rci_t lastcol;
}m3_slice;
void * m3d_64_cubes(m3_smt *, m3d_t  * );

void * m3d_64_cubes_take2(m3_slice *, m3d_t  * );
m3d_t m3d_transpose(m3d_t  * );


#endif
