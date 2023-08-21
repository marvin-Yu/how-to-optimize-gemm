#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>

#include "parameters.hpp"
#include "util.hpp"

#define GHz_of_processor 2.0

template <typename T>
void MY_MMult(int, int, int, const T *, int, const T *, int, T *, int);

template <typename T>
void test()
{
  int
      p,
      m, n, k,
      lda, ldb, ldc,
      rep;

  double
      dtime,
      dtime_best,
      gflops,
      diff;

  T
      *a,
      *b, *c, *cref, *cold;

  printf("MY_MMult = [\n");

  for (p = PFIRST; p <= PLAST; p += PINC)
  {
    m = (M == -1 ? p : M);
    n = (N == -1 ? p : N);
    k = (K == -1 ? p : K);

    gflops = GHz_of_processor * m * n * k * 1.0e-09;

    lda = (LDA == -1 ? m : LDA);
    ldb = (LDB == -1 ? k : LDB);
    ldc = (LDC == -1 ? m : LDC);

    /* Allocate space for the matrices */
    /* Note: I create an extra column in A to make sure that
       prefetching beyond the matrix does not cause a segfault */
    a = (T *)malloc(lda * (k + 1) * sizeof(T));
    b = (T *)malloc(ldb * n * sizeof(T));
    c = (T *)malloc(ldc * n * sizeof(T));
    cold = (T *)malloc(ldc * n * sizeof(T));
    cref = (T *)malloc(ldc * n * sizeof(T));

    /* Generate random matrices A, B, Cold */
    random_matrix(m, k, a, lda);
    random_matrix(k, n, b, ldb);
    random_matrix(m, n, cold, ldc);

    copy_matrix(m, n, cold, ldc, cref, ldc);

    /* Run the reference implementation so the answers can be compared */

    REF_MMult(m, n, k, a, lda, b, ldb, cref, ldc);

    /* Time the "optimized" implementation */
    for (rep = 0; rep < NREPEATS; rep++)
    {
      copy_matrix(m, n, cold, ldc, c, ldc);

      /* Time your implementation */
      dtime = dclock();

      MY_MMult(m, n, k, a, lda, b, ldb, c, ldc);

      dtime = dclock() - dtime;

      if (rep == 0)
        dtime_best = dtime;
      else
        dtime_best = (dtime < dtime_best ? dtime : dtime_best);
    }

    diff = compare_matrices(m, n, c, ldc, cref, ldc);

    printf("%d %le %le \n", p, gflops / dtime_best, diff);
    fflush(stdout);

    free(a);
    free(b);
    free(c);
    free(cold);
    free(cref);
  }

  printf("];\n");
}

int main()
{
  // test<double>();
  test<float>();

  return 0;
}
