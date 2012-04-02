#pragma once
#ifdef __DEVICE__
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define LDAS 33
#define LDBS 9

__attribute__((reqd_work_group_size(8, 8, 1)))
__kernel void dgemmNN(int n, int m, int k, double alpha, __global double* a, int lda, __global double* b, int ldb, double beta, __global double* c, int ldc)
{
  double c0_0 = 0.0;
  double c0_8 = 0.0;
  double c0_16 = 0.0;
  double c0_24 = 0.0;
  double c8_0 = 0.0;
  double c8_8 = 0.0;
  double c8_16 = 0.0;
  double c8_24 = 0.0;
  double c16_0 = 0.0;
  double c16_8 = 0.0;
  double c16_16 = 0.0;
  double c16_24 = 0.0;
  double c24_0 = 0.0;
  double c24_8 = 0.0;
  double c24_16 = 0.0;
  double c24_24 = 0.0;

  double a0;
  double a8;
  double a16;
  double a24;

  double b0;
  double b8;
  double b16;
  double b24;

  __local double aShared[LDAS * 8];
  __local double bShared[LDBS * 32];

  const int rowBlock = get_local_id(0);
  const int colBlock = get_local_id(1);

  const int rowC = get_group_id(0) * 32;
  const int colC = get_group_id(1) * 32;

  __global double* blockC;

  for(int i = 0; i < k; i+= 8)
  {
    for(int l = 0; l < 32; l+= 8)
    {
      aShared[rowBlock + l + LDAS * colBlock] = a[rowC + rowBlock + l + (colBlock + i) * lda];
      bShared[colBlock + LDBS * (rowBlock + l)] = b[colBlock + i + (colC + rowBlock + l) * ldb];
    }

barrier(CLK_LOCAL_MEM_FENCE);

    for(int l = 0; l <8; l++)
    {
      a0 = aShared[rowBlock + 0 + LDAS * l];
      a8 = aShared[rowBlock + 8 + LDAS * l];
      a16 = aShared[rowBlock + 16 + LDAS * l];
      a24 = aShared[rowBlock + 24 + LDAS * l];

      b0 = bShared[l + LDBS * (colBlock + 0)];
      b8 = bShared[l + LDBS * (colBlock + 8)];
      b16 = bShared[l + LDBS * (colBlock + 16)];
      b24 = bShared[l + LDBS * (colBlock + 24)];

      c0_0 = fma(a0, b0, c0_0);
      c0_8 = fma(a0, b8, c0_8);
      c0_16 = fma(a0, b16, c0_16);
      c0_24 = fma(a0, b24, c0_24);
      c8_0 = fma(a8, b0, c8_0);
      c8_8 = fma(a8, b8, c8_8);
      c8_16 = fma(a8, b16, c8_16);
      c8_24 = fma(a8, b24, c8_24);
      c16_0 = fma(a16, b0, c16_0);
      c16_8 = fma(a16, b8, c16_8);
      c16_16 = fma(a16, b16, c16_16);
      c16_24 = fma(a16, b24, c16_24);
      c24_0 = fma(a24, b0, c24_0);
      c24_8 = fma(a24, b8, c24_8);
      c24_16 = fma(a24, b16, c24_16);
      c24_24 = fma(a24, b24, c24_24);
    }

    barrier(CLK_LOCAL_MEM_FENCE);
  }

  blockC = &c[rowC + ldc * (colC + colBlock)];

  blockC[rowBlock + 0] = alpha * c0_0 + beta * blockC[rowBlock + 0];
  blockC[rowBlock + 8] = alpha * c8_0 + beta * blockC[rowBlock + 8];
  blockC[rowBlock + 16] = alpha * c16_0 + beta * blockC[rowBlock + 16];
  blockC[rowBlock + 24] = alpha * c24_0 + beta * blockC[rowBlock + 24];

  blockC += 8 * ldc;

  blockC[rowBlock + 0] = alpha * c0_8 + beta * blockC[rowBlock + 0];
  blockC[rowBlock + 8] = alpha * c8_8 + beta * blockC[rowBlock + 8];
  blockC[rowBlock + 16] = alpha * c16_8 + beta * blockC[rowBlock + 16];
  blockC[rowBlock + 24] = alpha * c24_8 + beta * blockC[rowBlock + 24];

  blockC += 8 * ldc;

  blockC[rowBlock + 0] = alpha * c0_16 + beta * blockC[rowBlock + 0];
  blockC[rowBlock + 8] = alpha * c8_16 + beta * blockC[rowBlock + 8];
  blockC[rowBlock + 16] = alpha * c16_16 + beta * blockC[rowBlock + 16];
  blockC[rowBlock + 24] = alpha * c24_16 + beta * blockC[rowBlock + 24];

  blockC += 8 * ldc;

  blockC[rowBlock + 0] = alpha * c0_24 + beta * blockC[rowBlock + 0];
  blockC[rowBlock + 8] = alpha * c8_24 + beta * blockC[rowBlock + 8];
  blockC[rowBlock + 16] = alpha * c16_24 + beta * blockC[rowBlock + 16];
  blockC[rowBlock + 24] = alpha * c24_24 + beta * blockC[rowBlock + 24];

  blockC += 8 * ldc;


}

#else
#define DGEMMTHREADROWS 8
#define DGEMMTHREADCOLS 8
#define DGEMMROWREP4
#define DGEMMCOLREP4
#endif
