
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
 
 
 Makes the grease table for the method of four russians. 
 
 m1ri_small.c
 */

#include "m1ri_small.h"

void m3d_mul_64(vbg **R, vbg **A, vbg **B)
{
    int i;
    vbg t1, t2, r1, r2, a;
    vec v1, v2;
    
    vbg  tables6[9][64];
    vbg tables5[2][32];
    
	for (i = 0; i < 9; i ++)
    {
        m3d_combine6(&tables6[i][0], &(B [6*i][0]));
    }
   
    for (i = 0; i < 2; i ++)
    {
        m3d_combine5(&tables5[i][0], &(B[54 + (5 * i)][0]));
    }

    for (i = 0; i < 64; i ++  )//i from 0 <= i < 64
    {
        a = A[i][0];
        v2 = a.sign;
    
        v1 = (a.units ^ v2);		
        r1 = tables6[0][v1&63];
        v1 >>= 6;
        r2 = tables6[0][v2&63];
        v2 >>= 6;
        t1 = tables6[1][v1&63]; iadd_vbg(&r1, &t1);v1 >>= 6;
        t2 = tables6[1][v2&63]; iadd_vbg(&r2, &t2); v2 >>= 6;
        t1 = tables6[2][v1&63]; iadd_vbg(&r1, &t1); v1 >>= 6;
        t2 = tables6[2][v2&63]; iadd_vbg(&r2, &t2); v2 >>= 6;
        t1 = tables6[3][v1&63]; iadd_vbg(&r1, &t1); v1 >>= 6;
        t2 = tables6[3][v2&63]; iadd_vbg(&r2, &t2); v2 >>= 6;
        t1 = tables6[4][v1&63]; iadd_vbg(&r1, &t1); v1 >>= 6;
        t2 = tables6[4][v2&63]; iadd_vbg(&r2, &t2); v2 >>= 6;
        t1 = tables6[5][v1&63]; iadd_vbg(&r1, &t1); v1 >>= 6;
        t2 = tables6[5][v2&63]; iadd_vbg(&r2, &t2); v2 >>= 6;
        t1 = tables6[6][v1&63]; iadd_vbg(&r1, &t1); v1 >>= 6;
        t2 = tables6[6][v2&63]; iadd_vbg(&r2, &t2); v2 >>= 6;
        t1 = tables6[7][v1&63]; iadd_vbg(&r1, &t1); v1 >>= 6;
        t2 = tables6[7][v2&63]; iadd_vbg(&r2, &t2); v2 >>= 6;
        t1 = tables6[8][v1&63]; iadd_vbg(&r1, &t1); v1 >>= 6;
        t2 = tables6[8][v2&63]; iadd_vbg(&r2, &t2); v2 >>= 6;
        t1 = tables5[0][v1&31]; iadd_vbg(&r1, &t1); v1 >>= 5;
        t2 = tables5[0][v2&31]; iadd_vbg(&r2, &t2); v2 >>= 5;
        t1 = tables5[1][v1&31]; iadd_vbg(&r1, &t1);
        t2 = tables5[1][v2&31]; iadd_vbg(&r2, &t2);
        
        isub_m3d(&r1, &r2);
        R[i][0] = r1;
       // */
    }
    
}

//32 * 64,2048 bit, 256 byte matrix(slice) multiplication
void mul_32_m3d(vbg *R, vbg *A, vbg *B)
{
    long i;
    vbg t1, t2, r1, r2, a;
    long v1, v2;
    
    vbg tables5[4][32];
    vbg tables4[3][16];
    for (i = 1; i < 4; i ++)
        
        m3d_combine5(tables5[i], B + 0 + 5*i);
    for (i = 0; i < 3; i++)
        m3d_combine4(tables4[i], B + 20 + 4*i);
    
    for (i = 0;i < 32; i++)
    {
        
        a = A[i];
        v2 = a.sign;
        v1 = a.units ^ v2;
        t1 = tables5[0][v1&31]; v1 >>= 5;
        t2 = tables5[0][v2&31]; v2 >>= 5;
        t1 = tables5[1][v1&31]; iadd_vbg(&r1, &t1); v1 >>= 5;
        t2 = tables5[1][v2&31]; iadd_vbg(&r2, &t2); v2 >>= 5;
        t1 = tables5[2][v1&31]; iadd_vbg(&r1, &t1); v1 >>= 5;
        t2 = tables5[2][v2&31]; iadd_vbg(&r2, &t2); v2 >>= 5;
        t1 = tables5[3][v1&31]; iadd_vbg(&r1, &t1); v1 >>= 5;
        t2 = tables5[3][v2&31]; iadd_vbg(&r2, &t2); v2 >>= 5;
        t1 = tables4[0][v1&15]; iadd_vbg(&r1, &t1); v1 >>= 4;
        t2 = tables4[0][v2&15]; iadd_vbg(&r2, &t2); v2 >>= 4;
        t1 = tables4[1][v1&15]; iadd_vbg(&r1, &t1); v1 >>= 4;
        t2 = tables4[1][v2&15]; iadd_vbg(&r2, &t2); v2 >>= 4;
        t1 = tables4[2][v1&15]; iadd_vbg(&r1, &t1);
        t2 = tables4[2][v2&15]; iadd_vbg(&r2, &t2);
        
        isub_m3d(&r1, &r2);
        R[i] = r1;
    }
    
}

//16 * 64,1024 bit, 128 byte matrix(slice) multiplication
void mul_16_m3d(vbg *R, vbg *A, vbg *B)
{
    long i;
    vbg t1, t2, r1, r2, a;
    long v1, v2;
    
    vbg tables4[4][16];
    for (i = 0; i < 4; i++)
        m3d_combine4(tables4[i], B + (4*i));
    for (i = 0;  i < 16; i++)
    {
        a = A[i];
        v2 = a.sign;
        v1 = a.units ^ v2;
        r1 = tables4[0][v1&15]; v1 >>= 4;
        r2 = tables4[0][v2&15]; v2 >>= 4;
        t1 = tables4[1][v1&15]; iadd_vbg(&r1, &t1); v1 >>= 4;
        t2 = tables4[1][v2&15]; iadd_vbg(&r2, &t2); v2 >>= 4;
        t1 = tables4[2][v1&15]; iadd_vbg(&r1, &t1); v1 >>= 4;
        t2 = tables4[2][v2&15]; iadd_vbg(&r2, &t2); v2 >>= 4;
        t1 = tables4[3][v1&15]; iadd_vbg(&r1, &t1);
        t2 = tables4[3][v2&15]; iadd_vbg(&r2, &t2);
    
        isub_m3d(&r1, &r2);
        R[i] = r1;
    }
}

//8 * 64,512 bit, m1ri_word byte matrix(slice) multiplication
void mul_8_m3d(vbg *R, vbg *A, vbg *B)

{
    int i;
    vbg t1, t2, r1, r2, a;
    vec v1, v2;
    
    vbg tables4[2][16];
    for (i = 0; i < 2; i++)
        m3d_combine4(tables4[i], B + (4*i));
    for (i = 0; i < 8; i++)
    {
        a = A[i];
    v2 = a.sign;
    v1 = a.units ^ v2;
    r1 = tables4[0][v1&15]; v1 >>= 4;
    r2 = tables4[0][v2&15]; v2 >>= 4;
    t1 = tables4[1][v1&15]; iadd_vbg(&r1, &t1);
    t2 = tables4[1][v2&15]; iadd_vbg(&r2, &t2);
    
    isub_m3d(&r1, &r2);
    R[i] = r1;
    }
}






//4 * 64,256 bit, 32 byte matrix(slice) multiplication
void mul_4_m3d(vbg *R, vbg *A, vbg *B)
{
    int i;
    vbg r1, r2, a;
    vec v1, v2;
    
    vbg table4[16];
    for (i = 0; i < 1; i++)
        m3d_combine4(table4, B + (4*i));
    for(i = 0; i < 4; i++)
    {
        a = A[i];
        v2 = a.sign;
        v1 = a.units ^ v2;
        r1 = table4[v1&15];
        r2 = table4[v2&15];
        
        isub_m3d(&r1, &r2);
        R[i] = r1;
    }
    
}


/*
Everything past here has functions that still need to be tuned for 
their specific Galois field
*/  

/****************************************************************************
								GF(5)
*****************************************************************************/


void m5d_mul_64(vfd **R, vfd **A, vfd **B)
{
    int i;
    vfd t1, t2, t3,  r1, r2, r3 , a;
    vec v1, v2, v3;
    
    vfd  tables6[9][64];
    vfd tables5[2][32];
    
    for (i = 0; i < 9; i ++)
    {
        m5d_combine6(&tables6[i][0], &(B [6*i][0]));
    }
      
    for (i = 0; i < 2; i ++)
    {
        m5d_combine5(&tables5[i][0], &(B[54 + (5 * i)][0]));
    }
  
    
    for (i = 0; i < 64; i ++  )//i from 0 <= i < 64
    {
        a = A[i][0];
        
  		v3 = a.sign;
        v2 = a.sign & a.middle;
    	v1 = v2 & a.units;
        r1 = tables6[0][v1&63];
        v1 >>= 6;
        r2 = tables6[0][v2&63];
        v2 >>= 6;
        t1 = tables6[1][v1&63]; iadd_vfd(&r1, &t1);v1 >>= 6;
        t2 = tables6[1][v2&63]; iadd_vfd(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vfd(&r3, &t3); v3 >>= 6;
        t1 = tables6[2][v1&63]; iadd_vfd(&r1, &t1); v1 >>= 6;
        t2 = tables6[2][v2&63]; iadd_vfd(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vfd(&r3, &t3); v3 >>= 6;
        t1 = tables6[3][v1&63]; iadd_vfd(&r1, &t1); v1 >>= 6;
        t2 = tables6[3][v2&63]; iadd_vfd(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vfd(&r3, &t3); v3 >>= 6;
        t1 = tables6[4][v1&63]; iadd_vfd(&r1, &t1); v1 >>= 6;
        t2 = tables6[4][v2&63]; iadd_vfd(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vfd(&r3, &t3); v3 >>= 6;
        t1 = tables6[5][v1&63]; iadd_vfd(&r1, &t1); v1 >>= 6;
        t2 = tables6[5][v2&63]; iadd_vfd(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vfd(&r3, &t3); v3 >>= 6;
        t1 = tables6[6][v1&63]; iadd_vfd(&r1, &t1); v1 >>= 6;
        t2 = tables6[6][v2&63]; iadd_vfd(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vfd(&r3, &t3); v3 >>= 6;
        t1 = tables6[7][v1&63]; iadd_vfd(&r1, &t1); v1 >>= 6;
        t2 = tables6[7][v2&63]; iadd_vfd(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vfd(&r3, &t3); v3 >>= 6;
        t1 = tables6[8][v1&63]; iadd_vfd(&r1, &t1); v1 >>= 6;
        t2 = tables6[8][v2&63]; iadd_vfd(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vfd(&r3, &t3); v3 >>= 6;
        t1 = tables5[0][v1&31]; iadd_vfd(&r1, &t1); v1 >>= 5;
        t2 = tables5[0][v2&31]; iadd_vfd(&r2, &t2); v2 >>= 5;
        t1 = tables5[1][v1&31]; iadd_vfd(&r1, &t1);
        t2 = tables5[1][v2&31]; iadd_vfd(&r2, &t2);
        t3 = tables5[1][v3&31]; iadd_vfd(&r3, &t3);
        
        iadd_vfd(&r1, &r2);
        m5d_add2_i(&r1, &r3);
        R[i][0] = r1;
    }   
}

//32 * 64,2048 bit, 256 byte matrix(slice) multiplication
void m5d_mul_32(vfd *R, vfd *A, vfd *B)
{
    long i;
    vfd t1, t2, t3, r1, r2, r3, a;
    long v1, v2, v3;
    
    vfd tables5[4][32];
    vfd tables4[3][16];
    for (i = 1; i < 4; i ++)
        
        m5d_combine5(tables5[i], B + 0 + 5*i);
    for (i = 0; i < 3; i++)
        m5d_combine4(tables4[i], B + 20 + 4*i);
    
    for (i = 0;i < 32; i++)
    {
        a = A[i];
 		v3 = a.sign;
        v2 = a.sign & a.middle;
    	v1 = v2 & a.units;
        t1 = tables5[0][v1&31]; v1 >>= 5;
        t2 = tables5[0][v2&31]; v2 >>= 5;
        t3 = tables5[0][v3&31]; v3 >>= 5;
        t1 = tables5[1][v1&31]; iadd_vfd(&r1, &t1); v1 >>= 5;
        t2 = tables5[1][v2&31]; iadd_vfd(&r2, &t2); v2 >>= 5;
        t3 = tables5[0][v3&31]; iadd_vfd(&r3, &t3); v3 >>= 5;
        t1 = tables5[2][v1&31]; iadd_vfd(&r1, &t1); v1 >>= 5;
        t2 = tables5[2][v2&31]; iadd_vfd(&r2, &t2); v2 >>= 5;
        t3 = tables5[0][v3&31]; iadd_vfd(&r3, &t3); v3 >>= 5;
        t1 = tables5[3][v1&31]; iadd_vfd(&r1, &t1); v1 >>= 5;
        t2 = tables5[3][v2&31]; iadd_vfd(&r2, &t2); v2 >>= 5;
        t3 = tables5[0][v3&31]; iadd_vfd(&r3, &t3); v3 >>= 5;
        t1 = tables4[0][v1&15]; iadd_vfd(&r1, &t1); v1 >>= 4;
        t2 = tables4[0][v2&15]; iadd_vfd(&r2, &t2); v2 >>= 4;
        t3 = tables5[0][v3&31]; iadd_vfd(&r3, &t3); v3 >>= 5;
        t1 = tables4[1][v1&15]; iadd_vfd(&r1, &t1); v1 >>= 4;
        t2 = tables4[1][v2&15]; iadd_vfd(&r2, &t2); v2 >>= 4;
        t3 = tables5[0][v3&31]; iadd_vfd(&r3, &t3); v3 >>= 5;
        t1 = tables4[2][v1&15]; iadd_vfd(&r1, &t1);
        t2 = tables4[2][v2&15]; iadd_vfd(&r2, &t2);
        t3 = tables4[2][v3&15]; iadd_vfd(&r3, &t3);
        // m5d_sub_i(&r1, &r2);
        iadd_vfd(&r1, &r2);
        m5d_add2_i(&r1, &r3);
        
        R[i] = r1;
    }
    
}

//16 * 64,1024 bit, 128 byte matrix(slice) multiplication
void m5d_mul_16(vfd *R, vfd *A, vfd *B)
{
    long i;
    vfd t1, t2, t3, r1, r2, r3, a;
    long v1, v2, v3;
    
    vfd tables4[4][16];
    for (i = 0; i < 4; i++)
        m5d_combine4(tables4[i], B + (4*i));
    for (i = 0;  i < 16; i++)
    {
        a = A[i];
  		v3 = a.sign;
        v2 = a.sign & a.middle;
    	v1 = v2 & a.units;
        r1 = tables4[0][v1&15]; v1 >>= 4;
        r2 = tables4[0][v2&15]; v2 >>= 4;
        r3 = tables4[0][v3&15]; v3 >>= 4;
        t1 = tables4[1][v1&15]; iadd_vfd(&r1, &t1); v1 >>= 4;
        t2 = tables4[1][v2&15]; iadd_vfd(&r2, &t2); v2 >>= 4;
        t3 = tables4[1][v3&15]; iadd_vfd(&r3, &t3); v3 >>= 4;
        t1 = tables4[2][v1&15]; iadd_vfd(&r1, &t1); v1 >>= 4;
        t2 = tables4[2][v2&15]; iadd_vfd(&r2, &t2); v2 >>= 4;
        t3 = tables4[1][v3&15]; iadd_vfd(&r3, &t3); v3 >>= 4;
        t1 = tables4[3][v1&15]; iadd_vfd(&r1, &t1);
        t2 = tables4[3][v2&15]; iadd_vfd(&r2, &t2);
        t3 = tables4[3][v3&15]; iadd_vfd(&r3, &t3);
    
    	iadd_vfd(&r1, &r2);
        m5d_add2_i(&r1, &r3);
            
        R[i] = r1;
    }
}

//8 * 64,512 bit, m1ri_word byte matrix(slice) multiplication
void m5d_mul_8(vfd *R, vfd *A, vfd *B)

{
    int i;
    vfd t1, t2, t3 ,  r1, r2, r3,a;
    vec v1, v2, v3;
    
    vfd tables4[2][16];
    for (i = 0; i < 2; i++)
        m5d_combine4(tables4[i], B + (4*i));
    for (i = 0; i < 8; i++)
    {
    	a = A[i];
     	v3 = a.sign;
        v2 = a.sign & a.middle;
    	v1 = v2 & a.units;
    	r1 = tables4[0][v1&15]; v1 >>= 4;
    	r2 = tables4[0][v2&15]; v2 >>= 4;
    	r3 = tables4[0][v3&15]; v3 >>= 4;
   	 	t1 = tables4[1][v1&15]; iadd_vfd(&r1, &t1);
    	t2 = tables4[1][v2&15]; iadd_vfd(&r2, &t2);
    	t3 = tables4[1][v3&15]; iadd_vfd(&r3, &t3);
    	// m5d_sub_i((&r1, &r2);
    	
    	iadd_vfd(&r1, &r2);
		m5d_add2_i(&r1, &r3);
        
        R[i] = r1;
    }
}

//4 * 64,256 bit, 32 byte matrix(slice) multiplication
void m5d_mul_4(vfd *R, vfd *A, vfd *B)
{
    int i;
    vfd r1, r2, r3,  a;
    vec v1, v2, v3;
    
    vfd table4[16];
    for (i = 0; i < 1; i++)
        m5d_combine4(table4, B + (4*i));
    for(i = 0; i < 4; i++)
    {
        a = A[i];
        v3 = a.sign;
        v2 = a.sign & a.middle;
    	v1 = v2 & a.units;
		v2  = a.sign & a.middle;
		v3 =  v2 & a.units; 
        r1 = table4[v1&15];
        r2 = table4[v2&15];
        r3 = table4[v3&15];
     	
     	iadd_vfd(&r1, &r2);
        m5d_add2_i(&r1, &r3);
        
        R[i] = r1;
    }
    
}


/****************************************************************************
								GF(7)
*****************************************************************************/

void m7d_mul_64(vtri **R, vtri **A, vtri **B)
{
    int i;
    vtri t1, t2, t3,  r1, r2, r3,  a;
    vec v1, v2, v3;
    vtri  tables6[9][64];
    vtri tables5[2][32];
     
    for (i = 0; i < 9; i ++)
    {
        m7d_combine6(&tables6[i][0], &(B [6*i][0]));
    }
     
    for (i = 0; i < 2; i ++)
    {
        m7d_combine5(&tables5[i][0], &(B[54 + (5 * i)][0]));
    }
   
    for (i = 0; i < 64; i ++  )//i from 0 <= i < 64
    {
        a = A[i][0];
        v2 = a.sign;
    	v1 = (a.units ^ v2);
        r1 = tables6[0][v1&63];
        v1 >>= 6;
        r2 = tables6[0][v2&63];
        v2 >>= 6;
        t1 = tables6[1][v1&63]; iadd_vtri(&r1, &t1);v1  >>= 6;
        t2 = tables6[1][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); v3 >>= 6;
        t1 = tables6[2][v1&63]; iadd_vtri(&r1, &t1); v1 >>= 6;
        t2 = tables6[2][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t2 = tables6[1][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); v3 >>= 6;
        t1 = tables6[3][v1&63]; iadd_vtri(&r1, &t1); v1 >>= 6;
        t2 = tables6[3][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t2 = tables6[1][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); v3 >>= 6;
        t1 = tables6[4][v1&63]; iadd_vtri(&r1, &t1); v1 >>= 6;
        t2 = tables6[4][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t2 = tables6[1][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); v3 >>= 6;
        t1 = tables6[5][v1&63]; iadd_vtri(&r1, &t1); v1 >>= 6;
        t2 = tables6[5][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t2 = tables6[1][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); v3 >>= 6;
        t1 = tables6[6][v1&63]; iadd_vtri(&r1, &t1); v1 >>= 6;
        t2 = tables6[6][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t2 = tables6[1][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); v3 >>= 6;
        t1 = tables6[7][v1&63]; iadd_vtri(&r1, &t1); v1 >>= 6;
        t2 = tables6[7][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t2 = tables6[1][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); v3 >>= 6;
        t1 = tables6[8][v1&63]; iadd_vtri(&r1, &t1); v1 >>= 6;
        t2 = tables6[8][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t2 = tables6[1][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); v3 >>= 6;
        t1 = tables5[0][v1&31]; iadd_vtri(&r1, &t1); v1 >>= 5;
        t2 = tables5[0][v2&31]; iadd_vtri(&r2, &t2); v2 >>= 5;
        t2 = tables6[1][v2&63]; iadd_vtri(&r2, &t2); v2 >>= 6;
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); v3 >>= 6;
        t1 = tables5[1][v1&31]; iadd_vtri(&r1, &t1);
        t2 = tables5[1][v2&31]; iadd_vtri(&r2, &t2);
        t3 = tables6[1][v3&63]; iadd_vtri(&r3, &t3); 
       
        m7d_add_2r(&r1, &r2);
		m7d_add_4r(&r1 ,&r3);
        
        R[i][0] = r1;
       // */
    }
    
}

//32 * 64,2048 bit, 256 byte matrix(slice) multiplication
void m7d_mul_32(vtri *R, vtri *A, vtri *B)
{
    long i;
    vtri t1, t2, t3,  r1, r2, r3,  a;
    long v1, v2, v3;
    
    vtri tables5[4][32];
    vtri tables4[3][16];
    for (i = 1; i < 4; i ++)
        
        m7d_combine5(tables5[i], B + 0 + 5*i);
    for (i = 0; i < 3; i++)
        m7d_combine4(tables4[i], B + 20 + 4*i);
    
    for (i = 0;i < 32; i++)
    {
        
        a = A[i];
        v3 = a.sign;
        v2 = a.middle;
        v1 = a.units ^ v2;
        t1 = tables5[0][v1&31]; v1 >>= 5;
        t2 = tables5[0][v2&31]; v2 >>= 5;
        t3 = tables5[0][v2&31]; v3 >>= 5;
        t1 = tables5[1][v1&31]; iadd_vtri(&r1, &t1); v1 >>= 5;
        t2 = tables5[1][v2&31]; iadd_vtri(&r2, &t2); v2 >>= 5;
        t3 = tables5[1][v3&31]; iadd_vtri(&r3, &t3); v2 >>= 5;
        t1 = tables5[2][v1&31]; iadd_vtri(&r1, &t1); v1 >>= 5;
        t2 = tables5[2][v2&31]; iadd_vtri(&r2, &t2); v2 >>= 5;
        t3 = tables5[2][v3&31]; iadd_vtri(&r3, &t3); v2 >>= 5;
        t1 = tables5[3][v1&31]; iadd_vtri(&r1, &t1); v1 >>= 5;
        t2 = tables5[3][v2&31]; iadd_vtri(&r2, &t2); v2 >>= 5;
        t3 = tables5[3][v3&31]; iadd_vtri(&r3, &t3); v2 >>= 5;
        t1 = tables4[0][v1&15]; iadd_vtri(&r1, &t1); v1 >>= 4;
        t2 = tables4[0][v2&15]; iadd_vtri(&r2, &t2); v2 >>= 4;
        t3 = tables4[0][v3&15]; iadd_vtri(&r3, &t3); v2 >>= 4;
        t1 = tables4[1][v1&15]; iadd_vtri(&r1, &t1); v1 >>= 4;
        t2 = tables4[1][v2&15]; iadd_vtri(&r2, &t2); v2 >>= 4;
        t3 = tables4[1][v3&15]; iadd_vtri(&r3, &t3); v2 >>= 4;
        t1 = tables4[2][v1&15]; iadd_vtri(&r1, &t1);
        t2 = tables4[2][v2&15]; iadd_vtri(&r2, &t2);
        t3 = tables4[3][v3&15]; iadd_vtri(&r3, &t3);
    
    	m7d_add_2r(&r1, &r2);
		m7d_add_4r(&r1 ,&r3);
        R[i] = r1;
    }
    
}

//16 * 64,1024 bit, 128 byte matrix(slice) multiplication
void m7d_mul_16(vtri *R, vtri *A, vtri *B)
{
    long i;
    vtri t1, t2, t3,  r1, r2, r3,  a;
    long v1, v2, v3;
    
    vtri tables4[4][16];
    for (i = 0; i < 4; i++)
        m7d_combine4(tables4[i], B + (4*i));
    for (i = 0;  i < 16; i++)
    {
        a = A[i];
        v2 = a.middle;
        v3 = a.sign;
        v1 = a.units;
        r1 = tables4[0][v1&15]; v1 >>= 4;
        r2 = tables4[0][v2&15]; v2 >>= 4;
        r3 = tables4[0][v3&15]; v2 >>= 4;
        t1 = tables4[1][v1&15]; iadd_vtri(&r1, &t1); v1 >>= 4;
        t2 = tables4[1][v2&15]; iadd_vtri(&r2, &t2); v2 >>= 4;
        t3 = tables4[1][v3&15]; iadd_vtri(&r3, &t3); v3 >>= 4;
        t1 = tables4[2][v1&15]; iadd_vtri(&r1, &t1); v1 >>= 4;
        t2 = tables4[2][v2&15]; iadd_vtri(&r2, &t2); v2 >>= 4;
        t3 = tables4[1][v3&15]; iadd_vtri(&r3, &t3); v3 >>= 4;
        t1 = tables4[3][v1&15]; iadd_vtri(&r1, &t1);
        t2 = tables4[3][v2&15]; iadd_vtri(&r2, &t2);
        t3 = tables4[1][v3&15]; iadd_vtri(&r3, &t3);
    	
     	m7d_add_2r(&r1, &r2);
		m7d_add_4r(&r1 ,&r3);
        R[i] = r1;
    }
}

//8 * 64,512 bit, m1ri_word byte matrix(slice) multiplication
void m7d_mul_8(vtri *R, vtri *A, vtri *B)

{
    int i;
    vtri t1, t2, t3,  r1, r2, r3,  a;
    vec v1, v2, v3;
    
    vtri tables4[2][16];
    for (i = 0; i < 2; i++)
        m7d_combine4(tables4[i], B + (4*i));
    for (i = 0; i < 8; i++)
    {
        a = A[i];
    v3 = a.sign;
    v2 = a.middle;
    v1 = a.units;
    r1 = tables4[0][v1&15]; v1 >>= 4;
    r2 = tables4[0][v2&15]; v2 >>= 4;
    r3 = tables4[0][v3&15]; v3 >>= 4;
    t1 = tables4[1][v1&15]; iadd_vtri(&r1, &t1);
    t2 = tables4[1][v2&15]; iadd_vtri(&r2, &t2);
    t3 = tables4[1][v3&15]; iadd_vtri(&r3, &t3);
    
    m7d_add_2r(&r1, &r2);
	m7d_add_4r(&r1 ,&r3);
    R[i] = r1;
    }
}


//4 * 64,256 bit, 32 byte matrix(slice) multiplication
void m7d_mul_4(vtri *R, vtri *A, vtri *B)
{
    int i;
    vtri r1, r2, r3 ,  a;
    vec v1, v2, v3;
    
    vtri table4[16];
    for (i = 0; i < 1; i++)
        m7d_combine4(table4, B + (4*i));
    for(i = 0; i < 4; i++)
    {
        a = A[i];
        v2 = a.middle;
        v3 = a.sign;
        v1 = a.units;
        r1 = table4[v1&15];
        r2 = table4[v2&15];
        r3 = table4[v3&15];
    
    	m7d_add_2r(&r1, &r2);
		m7d_add_4r(&r1 ,&r3);
        
        R[i] = r1;
    }
    
}

