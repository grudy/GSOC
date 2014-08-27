 
/** *
 
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
 
 
 Matrix Represenations and basic operations over GF(3)
 m1ri_permutations.c
 */

#include "m1ri_permutations.h"


/**
 * Construct an identity permutation.
 *
 * \param length Length of the permutation.
 */

m3p_t *m3p_init(rci_t length)
{
  m3p_t * a = m1ri_malloc(sizeof(m3p_t));
  a->values = m1ri_malloc(sizeof(rci_t) * length);
  a->length = length;
  for(rci_t i = 0; i < length; i++)
  {
    a->[i] = i;
  }
  
  
  return a;
}

m5p_t *m5p_init(rci_t length)
{
	m5p_t * a = m1ri_malloc(sizeof(m3p_t));
  	a->values = m1ri_malloc(sizeof(rci_t) * length);
  	a->length = length;
  	for(rci_t i = 0; i < length; i++)
  	{
   	 a->[i] = i;
  	}
  
  
  return a;

}
m7p_t *m7p_init(rci_t length)
{

  m7p_t * a = m1ri_malloc(sizeof(m3p_t));
  a->values = m1ri_malloc(sizeof(rci_t) * length);
  a->length = length;
}

/**
 * Free a permutation.
 *
 * \param P Permutation to free.
 */

void m3p_free(m3p_t *P)
{
  m1ri_free(P->values);
  m1ri_free(P);
}
void m5p_free(m5p_t *P)
{
  m1ri_free(P->values);
  m1ri_free(P);
}
void m7p_free(m7p_t *P)
{
  m1ri_free(P->values);
  m1ri_free(P);
}

/**
 * \brief Create a window/view into the permutation P.
 * \param P Permutation matrix
 * \param begin Starting index (inclusive)
 * \param end   Ending index   (exclusive)
 *
 */

m3p_t * m3p_init_window(m3p_t *P, rci_t begin, rci_t end)
{
  m3p_t* window = ( m1ri_malloc(sizeof(m3p_t)));
  window->values = P->values + begin;
  window->length = end - begin;
  return window;
}

m5p_t * m5p_init_window(m5p_t *P, rci_t begin, rci_t end)
{
  m5p_t* window = ( m1ri_malloc(sizeof(m5p_t)));
  window->values = P->values + begin;
  window->length = end - begin;
  return window;
}
m7p_t * m7p_init_window(m7p_t *P, rci_t begin, rci_t end)
{
  m7p_t* window = ( m1ri_malloc(sizeof(m7p_t)));
  window->values = P->values + begin;
  window->length = end - begin;
  return window;
}

/**
 * \brief Free a permutation window
 * \param condemned Permutation Matrix
 */

void m3p_free_window(m3p_t *condemned)
{
  m1ri_free(condemned->values);
}
void m5p_free_window(m5p_t *condemned)
{
  m1ri_free(condemned->values);
}
void m7p_free_window(m7p_t *condemned)
{
  m1ri_free(condemned->values);
}

/**
 * \brief copy permutation Q to P
 *
 * \param P Target permutation matrix (may be NULL)
 * \param Q Source permutation matrix (must not be NULL)
 */

m3p_t * m3p_copy(m3p_t *P, const m3p_t *Q)
{
  if(Q == NULL)
  {
    m1ri_die("Matrix to be copied is NULL");
  
  }
  
  if(P->values != NULL)
  {
    m1ri_free(P->values);
  }
  
  P->values = m1ri_malloc(sizeof(rci_t) * Q->length);
  P->length = Q->length;
  
  for(int i = 0; i < Q->length; i++)
  {
    P->values[i] = Q->values[i]; 
  
  }
  
  
}
m5p_t * m5p_copy(m5p_t *P, const m5p_t *Q)
{
    if(Q == NULL)
  {
    m1ri_die("Matrix to be copied is NULL");
  
  }
    if(P->values != NULL)
  {
    m1ri_free(P->values);
  }
  
  P->values = m1ri_malloc(sizeof(rci_t) * Q->length);
  P->length = Q->length;
  
  for(int i = 0; i < Q->length; i++)
  {
    P->values[i] = Q->values[i]; 
  
  }
  
}
m7p_t * m7p_copy(m7p_t *P, const m7p_t *Q)
{
    if(Q->values == NULL)
  {
    m1ri_die("Matrix to be copied is NULL");
  
  }
    if(P->values != NULL)
  {
    m1ri_free(P->values);
  }
  
  P->values = m1ri_malloc(sizeof(rci_t) * Q->length);
  P->length = Q->length;
  
  for(int i = 0; i < Q->length; i++)
  {
    P->values[i] = Q->values[i]; 
  
  }
  
}


/**
 * \brief Set the permutation P to the identity permutation. The only
 * allowed value is 1.
 *
 *
 * \param P Permutation
 * \param value 1
 *

 */

void m3p_set_ui(m3p_t *P, unsigned int value)
{
  assert(value == 1);
  for(int i = 0; i < P->length; i++)
  {
     P->values[i] = i;
  }
}
void m5p_set_ui(m5p_t *P, unsigned int value)
{ 
   assert(value == 1);
  for(int i = 0; i < P->length; i++)
  {
     P->values[i] = i;
  }
}
void m7p_set_ui(m7p_t *P, unsigned int value)
{
  assert(value == 1);
  for(int i = 0; i < P->length; i++)
  {
     P->values[i] = i;
  }
  
  
}

/**
 * Apply the permutation P to A from the left.
 *
 * This is equivalent to row swaps walking from 0 to length-1.
 *
 * \param A Matrix.
 * \param P Permutation.
 */

void m3d_apply_p_left(m3d_t *A, m3p_t const *P)
{
  
  for(int i = 0; i < P->length; i++)
  {
     m3d_rowswap(A, i, P->values[i]);
  }
}
void m5d_apply_p_left(m5d_t *A, m5p_t const *P)
{
   for(int i = 0; i < P->length; i++)
  {
     m5d_rowswap(A, i, P->values[i]);
  }
}
void m7d_apply_p_left(m7d_t *A, m7p_t const *P)
{
  for(int i = 0; i < P->length; i++)
  {
     m7d_rowswap(A, i, P->values[i]);
     
  }
}

/**
 * Apply the permutation P to A from the left but transpose P before.
 *
 * This is equivalent to row swaps walking from length-1 to 0.
 *
 * \param A Matrix.
 * \param P Permutation.
 */

void m3d_apply_p_left_trans(m3d_t *A, m3p_t const *P)
{
  for(int i = P->length - 1;i >= P->length; i--)
  {
    m3d_rowswap(A, i , P->values[i]);
  
  }
  

}
void m5d_apply_p_left_trans(m5d_t *A, m5p_t const *P)
{  
  for(int i = P->length - 1;i >= P->length; i--)
  {
    m5d_rowswap(A, i , P->values[i]);
  
  }
  


}
void m7d_apply_p_left_trans(m7d_t *A, m7p_t const *P)
{
   for(int i = P->length - 1;i >= P->length; i--)
  {
    m7d_rowswap(A, i , P->values[i]);
  
  }
}

/**
 * Apply the permutation P to A from the right.
 *
 * This is equivalent to column swaps walking from length-1 to 0.
 *
 * \param A Matrix.
 * \param P Permutation.
 */

void m3d_apply_p_right(m3d_t *A, m3p_t const *P)
{
  
   
  for(rci_t i = (P->length - 1); i >= 0; i--)
  {
    
      m3d_colswap( A, i, P->values[i]);
     
     
  }
}
void m5d_apply_p_right(m5d_t *A, m5p_t const *P)
{
    for(rci_t i = (P->length - 1); i >= 0; i--)
  {
    
       m5d_colswap( A, i, P->values[i]);
     
     
  }
}
void m7d_apply_p_right(m7d_t *A, m7p_t const *P)
{

  for(rci_t i = (P->length - 1); i >= 0; i--)
  {
    
      m7d_colswap( A, i, P->values[i]);
     
     
  }

}




/**
 * Apply the permutation P to A from the right starting at start_row.
 */

void m3d_apply_p_right_even_capped(m3d_t *A, m3p_t const *P, rci_t start_row, rci_t start_col)
{

  int s = start_col%64;
   
  for(rci_t i = start_row; i >= 0; i--)
  {
     if(P->values[i] >= start_col)
     {
       m3d_colswap_capped_row( A, i, P->values[i], start_row  );
     
     }   
  }
  
  
}
void m5d_apply_p_right_even_capped(m5d_t *A, m5p_t const *P, rci_t start_row, rci_t start_col)
{  

   int s = start_col%64;
   
  for(rci_t i = start_row; i >= 0; i--)
  {
     if(P->values[i] >= start_col)
     {
       m5d_colswap_capped_row( A, i, P->values[i], start_row  );
     
     }   
  }
  
}
void m7d_apply_p_right_even_capped(m7d_t *A, m7p_t const *P, rci_t start_row, rci_t start_col)
{
   int s = start_col%64;
   
  for(rci_t i = start_row; i >= 0; i--)
  {
     if(P->values[i] >= start_col)
     {
      m7d_colswap_capped_row( A, i, P->values[i], start_row  );
     
     }   
  }
  
}


void m3d_apply_p_right_trans_even_capped(m3d_t *A, m3p_t const *P, rci_t start_row, rci_t start_col)
{
  int s = start_col%64;
   
  for(rci_t i = start_row; i >= 0; i--)
  {
     if(P->values[i] >= start_col)
     {
      m3d_colswap_capped_row( A, i, P->values[i], start_row  );
     
     }   
  }
}
void m5d_apply_p_right_trans_even_capped(m5d_t *A, m5p_t const *P, rci_t start_row, rci_t start_col)
{
   int s = start_col%64;
   
  for(rci_t i = start_row; i >= 0; i--)
  {
     if(P->values[i] >= start_col)
     {
      m5d_colswap_capped_row( A, i, P->values[i], start_row  );
     
     }   
  }
}
void m7d_apply_p_right_trans_even_capped(m7d_t *A, m7p_t const *P, rci_t start_row, rci_t start_col)
{
   int s = start_col%64;
   
  for(rci_t i = start_row; i >= 0; i--)
  {
     if(P->values[i] >= start_col)
     {
      m7d_colswap_capped_row( A, i, P->values[i], start_row  );
     
     }   
  }
}


/**
 * Apply the permutation matrix P to A from the right but transpose P before.
 *
 * This is equivalent to column swaps walking from 0 to length-1.
 *
 * \param A Matrix.
 * \param P Permutation.
 */

void m3d_apply_p_right_trans(m3d_t *A, m3p_t const *P)
{
  for(int i = 0; i < P->length; i++)
  {
     
  
  }
}

void m5d_apply_p_right_trans(m5d_t *A, m5p_t const *P)
{   
   for(int i = 0; i < P->length; i++)
  {
    
  
  }
  

}

void m7d_apply_p_right_trans(m7d_t *A, m7p_t const *P)
{
    for(int i = 0; i < P->length; i++)
  {
    
  
  }
}



void  m3d_apply_p_right_trans_tri(m3d_t *A, m3p_t const *Q)
{
        
}



void  m5d_apply_p_right_trans_tri(m3d_t *A, m3p_t const *Q)
{

}

void  m7d_apply_p_right_trans_tri(m3d_t *A, m3p_t const *Q)
{

}





void _m3d_compress_l(m3d_t *A, rci_t r1, rci_t n1, rci_t r2)
{
  
}
void _m5d_compress_l(m5d_t *A, rci_t r1, rci_t n1, rci_t r2)
{

}
void _m7d_compress_l(m7d_t *A, rci_t r1, rci_t n1, rci_t r2)
{

}


   


 

 

