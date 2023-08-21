/* Create macros so that the matrices are stored in column-major order */

#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

/* Routine for computing C = A * B + C */

template <typename T>
void AddDot(int, const T *, int, const T *, T *);

template <typename T>
void MY_MMult(int m, int n, int k, const T *a, int lda,
              const T *b, int ldb, T *c, int ldc)
{
  int i, j;

  for (j = 0; j < n; j += 1)
  { /* Loop over the columns of C */
    for (i = 0; i < m; i += 1)
    { /* Loop over the rows of C */
      /* Update the C( i,j ) with the inner product of the ith row of A
   and the jth column of B */

      AddDot(k, &A(i, 0), lda, &B(0, j), &C(i, j));
    }
  }
}

/* Create macro to let X( i ) equal the ith element of x */

#define X(i) x[(i)*incx]

template <typename T>
void AddDot(int k, const T *x, int incx, const T *y, T *gamma)
{
  /* compute gamma := x' * y + gamma with vectors x and y of length n.

     Here x starts at location x with increment (stride) incx and y starts at location y and has (implicit) stride of 1.
  */

  int p;

  for (p = 0; p < k; p++)
  {
    *gamma += X(p) * y[p];
  }
}

template void MY_MMult<double>(int, int, int, const double*, int, const double*, int, double*, int);
template void MY_MMult<float>(int, int, int, const float*, int, const float*, int, float*, int);