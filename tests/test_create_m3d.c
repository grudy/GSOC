/** * M1RI
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
 
 test_create_m3d.c
 */ 





#include <m1ri/m1ri.h>

int main(int argc, const char * argv[])
{
 	
 
	m3d_t * a, * b;
	a  = m3d_create(128, 128);
	m3d_rand(a);
	b = m3d_submatrix(b, a, 0, 0, 64, 64 );
	m3d_print(a);
	m3d_print(b);
	
	return 0;
    
    
}

