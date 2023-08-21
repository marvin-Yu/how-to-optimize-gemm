#pragma once

#include <iostream>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>

#define abs(x) ((x) < 0.0 ? -(x) : (x))

#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

template <typename T>
void random_matrix(int m, int n, T *a, int lda)
{
  double drand48();
  int i, j;

  for (j = 0; j < n; j++)
    for (i = 0; i < m; i++)
      A(i, j) = 2.0 * drand48() - 1.0;
}

template <typename T>
void copy_matrix(int m, int n, const T *a, int lda, T *b, int ldb)
{
  int i, j;

  for (j = 0; j < n; j++)
    for (i = 0; i < m; i++)
      B(i, j) = A(i, j);
}

template <typename T>
void print_matrix(int m, int n, const T *a, int lda)
{
  int i, j;

  for (j = 0; j < n; j++)
  {
    for (i = 0; i < m; i++)
      printf("%le ", A(i, j));
    printf("\n");
  }
  printf("\n");
}

template <typename T>
double compare_matrices(int m, int n, const T *a, int lda, const T *b, int ldb)
{
  int i, j;
  double max_diff = 0.0, diff;

  for (j = 0; j < n; j++)
    for (i = 0; i < m; i++)
    {
      diff = abs(A(i, j) - B(i, j));
      max_diff = (diff > max_diff ? diff : max_diff);
    }

  return max_diff;
}

template <typename T>
void REF_MMult(int m, int n, int k, const T *a, int lda,
               const T *b, int ldb,
               T *c, int ldc)
{
  int i, j, p;

  for (i = 0; i < m; i++)
  {
    for (j = 0; j < n; j++)
    {
      for (p = 0; p < k; p++)
      {
        C(i, j) = C(i, j) + A(i, p) * B(p, j);
      }
    }
  }
}

static double gtod_ref_time_sec = 0.0;

double dclock()
{
  double the_time, norm_sec;
  struct timeval tv;

  gettimeofday(&tv, NULL);

  if (gtod_ref_time_sec == 0.0)
    gtod_ref_time_sec = (double)tv.tv_sec;

  norm_sec = (double)tv.tv_sec - gtod_ref_time_sec;

  the_time = norm_sec + tv.tv_usec * 1.0e-6;

  return the_time;
}
