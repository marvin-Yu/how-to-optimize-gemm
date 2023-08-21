/* Create macros so that the matrices are stored in column-major order */

#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

/* Routine for computing C = A * B + C */
template <typename T>
void MY_MMult(int m, int n, int k, const T *a, int lda,
              const T *b, int ldb, T *c, int ldc)
{
  int i, j, p;

  for (i = 0; i < m; i++)
  { /* Loop over the rows of C */
    for (j = 0; j < n; j++)
    { /* Loop over the columns of C */
      for (p = 0; p < k; p++)
      { /* Update C( i,j ) with the inner
product of the ith row of A and
the jth column of B */
        C(i, j) = C(i, j) + A(i, p) * B(p, j);
      }
    }
  }
}

template void MY_MMult<double>(int, int, int, const double*, int, const double*, int, double*, int);
template void MY_MMult<float>(int, int, int, const float*, int, const float*, int, float*, int);