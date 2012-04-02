#define NO_EDGE_CASES

#ifdef NO_EDGE_CASES

__kernel void SGEMMNTATI(int m,
                         int n,
                         int k,
                         read_only image2d_t a,
                         read_only image2d_t b,
                         __global float4* c,
                         int ldc,
                         float alpha,
                         float beta)
{

#define rowInFloat4 get_global_id(0) * 8 / 4
#define colInFloat4 get_global_id(1) * 8 / 4
#define row get_global_id(0) * 8
#define col get_global_id(1) * 8

  if(row < m && col < n)
  {

    int4 idxA = {rowInFloat4, rowInFloat4 + 1, 0, 0};
    int4 idxB = {colInFloat4, colInFloat4 + 1, 0, 0};
    int4 increment = {0, 0, 1, 1};

    //c(1:4,1:8) of block
    float4 c0_0 = 0.0f;
    float4 c0_1 = 0.0f;
    float4 c0_2 = 0.0f;
    float4 c0_3 = 0.0f;
    float4 c0_4 = 0.0f;
    float4 c0_5 = 0.0f;
    float4 c0_6 = 0.0f;
    float4 c0_7 = 0.0f;

    //c(5:8, 1:8) of block
    float4 c4_0 = 0.0f;
    float4 c4_1 = 0.0f;
    float4 c4_2 = 0.0f;
    float4 c4_3 = 0.0f;
    float4 c4_4 = 0.0f;
    float4 c4_5 = 0.0f;
    float4 c4_6 = 0.0f;
    float4 c4_7 = 0.0f;

    //a(1:8, 1)
    float4 a0_0;
    float4 a4_0;

    //b(1, 1:8) (b is transposed)
    float4 b0_0;
    float4 b0_4;

    //Unroll to use all 8 samplers
    for(;idxA.z < k; idxA += increment, idxB += increment)
    {
      //load a and b for k = 0
      a0_0 = read_imagef(a, s0, idxA.xz);
      a4_0 = read_imagef(a, s1, idxA.yz);

      b0_0 = read_imagef(b, s2, idxB.xz);
      b0_4 = read_imagef(b, s3, idxB.yz);

      c0_0 += a0_0 * b0_0.xxxx;
      c0_1 += a0_0 * b0_0.yyyy;
      c0_2 += a0_0 * b0_0.zzzz;
      c0_3 += a0_0 * b0_0.wwww;
      c0_4 += a0_0 * b0_4.xxxx;
      c0_5 += a0_0 * b0_4.yyyy;
      c0_6 += a0_0 * b0_4.zzzz;
      c0_7 += a0_0 * b0_4.wwww;

      c4_0 += a4_0 * b0_0.xxxx;
      c4_1 += a4_0 * b0_0.yyyy;
      c4_2 += a4_0 * b0_0.zzzz;
      c4_3 += a4_0 * b0_0.wwww;
      c4_4 += a4_0 * b0_4.xxxx;
      c4_5 += a4_0 * b0_4.yyyy;
      c4_6 += a4_0 * b0_4.zzzz;
      c4_7 += a4_0 * b0_4.wwww;
      
      //Second unroll
      idxA += increment;
      idxB += increment;

      //load a and b for k = 0
      a0_0 = read_imagef(a, s4, idxA.xz);
      a4_0 = read_imagef(a, s5, idxA.yz);

      b0_0 = read_imagef(b, s6, idxB.xz);
      b0_4 = read_imagef(b, s7, idxB.yz);

      c0_0 += a0_0 * b0_0.xxxx;
      c0_1 += a0_0 * b0_0.yyyy;
      c0_2 += a0_0 * b0_0.zzzz;
      c0_3 += a0_0 * b0_0.wwww;
      c0_4 += a0_0 * b0_4.xxxx;
      c0_5 += a0_0 * b0_4.yyyy;
      c0_6 += a0_0 * b0_4.zzzz;
      c0_7 += a0_0 * b0_4.wwww;

      c4_0 += a4_0 * b0_0.xxxx;
      c4_1 += a4_0 * b0_0.yyyy;
      c4_2 += a4_0 * b0_0.zzzz;
      c4_3 += a4_0 * b0_0.wwww;
      c4_4 += a4_0 * b0_4.xxxx;
      c4_5 += a4_0 * b0_4.yyyy;
      c4_6 += a4_0 * b0_4.zzzz;
      c4_7 += a4_0 * b0_4.wwww;
    }

    ldc /= 4;

    //Store first 4 rows
    c[(rowInFloat4 + 0) + ldc * (col + 0)] = c0_0;
    c[(rowInFloat4 + 0) + ldc * (col + 1)] = c0_1;
    c[(rowInFloat4 + 0) + ldc * (col + 2)] = c0_2;
    c[(rowInFloat4 + 0) + ldc * (col + 3)] = c0_3;
    c[(rowInFloat4 + 0) + ldc * (col + 4)] = c0_4;
    c[(rowInFloat4 + 0) + ldc * (col + 5)] = c0_5;
    c[(rowInFloat4 + 0) + ldc * (col + 6)] = c0_6;
    c[(rowInFloat4 + 0) + ldc * (col + 7)] = c0_7;

    //Store next 4 rowInFloat4s
    c[(rowInFloat4 + 1) + ldc * (col + 0)] = c4_0;
    c[(rowInFloat4 + 1) + ldc * (col + 1)] = c4_1;
    c[(rowInFloat4 + 1) + ldc * (col + 2)] = c4_2;
    c[(rowInFloat4 + 1) + ldc * (col + 3)] = c4_3;
    c[(rowInFloat4 + 1) + ldc * (col + 4)] = c4_4;
    c[(rowInFloat4 + 1) + ldc * (col + 5)] = c4_5;
    c[(rowInFloat4 + 1) + ldc * (col + 6)] = c4_6;
    c[(rowInFloat4 + 1) + ldc * (col + 7)] = c4_7;
  }
}
#undef row
#undef col
#undef rowInFloat4
#undef colInFloat4

#ifndef NVIDIA_CORPORATION

__kernel void DGEMMNTATI(int m,
                         int n,
                         int k,
                         read_only image2d_t a,
                         read_only image2d_t b,
                         __global double2* c,
                         int ldc,
                         double alpha,
                         double beta)
{

#define rowInDouble2 get_global_id(0) * 4 / 2
#define colInDouble2 get_global_id(1) * 4 / 2
#define row get_global_id(0) * 4
#define col get_global_id(1) * 4

  if(row < m && col < n)
  {

    int4 idxA = {rowInDouble2, rowInDouble2 + 1, 0, 0};
    int4 idxB = {colInDouble2, colInDouble2 + 1, 0, 0};
    int4 increment = {0, 0, 1, 1};

    //c(1:2,1:4) of block
    double2 c0_0 = 0.0;
    double2 c0_1 = 0.0;
    double2 c0_2 = 0.0;
    double2 c0_3 = 0.0;

    //c(3:4, 1:4) of block
    double2 c2_0 = 0.0;
    double2 c2_1 = 0.0;
    double2 c2_2 = 0.0;
    double2 c2_3 = 0.0;

    //a(1:4, 1)
    double2 a0_0;
    double2 a2_0;

    //b(1, 1:4) (b is transposed)
    double2 b0_0;
    double2 b0_2;

    //Unroll to use all 8 samplers
    for(;idxA.z < k; idxA += increment, idxB += increment)
    {
      //load a and b for k = 0
      a0_0 = as_double2(read_imagef(a, s0, idxA.xz));
      a2_0 = as_double2(read_imagef(a, s1, idxA.yz));

      b0_0 = as_double2(read_imagef(b, s2, idxB.xz));
      b0_2 = as_double2(read_imagef(b, s3, idxB.yz));

      c0_0 = fma(a0_0, b0_0.xx, c0_0);
      c0_1 = fma(a0_0, b0_0.yy, c0_1);
      c0_2 = fma(a0_0, b0_2.xx, c0_2);
      c0_3 = fma(a0_0, b0_2.yy, c0_3);

      c2_0 = fma(a2_0, b0_0.xx, c2_0);
      c2_1 = fma(a2_0, b0_0.yy, c2_1);
      c2_2 = fma(a2_0, b0_2.xx, c2_2);
      c2_3 = fma(a2_0, b0_2.yy, c2_3);

      //Second unroll
      idxA += increment;
      idxB += increment;

      //load a and b for k = 0
      a0_0 = as_double2(read_imagef(a, s4, idxA.xz));
      a2_0 = as_double2(read_imagef(a, s5, idxA.yz));

      b0_0 = as_double2(read_imagef(b, s6, idxB.xz));
      b0_2 = as_double2(read_imagef(b, s7, idxB.yz));

      c0_0 = fma(a0_0, b0_0.xx, c0_0);
      c0_1 = fma(a0_0, b0_0.yy, c0_1);
      c0_2 = fma(a0_0, b0_2.xx, c0_2);
      c0_3 = fma(a0_0, b0_2.yy, c0_3);

      c2_0 = fma(a2_0, b0_0.xx, c2_0);
      c2_1 = fma(a2_0, b0_0.yy, c2_1);
      c2_2 = fma(a2_0, b0_2.xx, c2_2);
      c2_3 = fma(a2_0, b0_2.yy, c2_3);
    }

    ldc /= 2;

		//Store first 2 rows
		c[(rowInDouble2 + 0) + ldc * (col + 0)] = c0_0;
		c[(rowInDouble2 + 0) + ldc * (col + 1)] = c0_1;
		c[(rowInDouble2 + 0) + ldc * (col + 2)] = c0_2;
		c[(rowInDouble2 + 0) + ldc * (col + 3)] = c0_3;

		//Store next 2 rowInDouble2s
		c[(rowInDouble2 + 1) + ldc * (col + 0)] = c2_0;
		c[(rowInDouble2 + 1) + ldc * (col + 1)] = c2_1;
		c[(rowInDouble2 + 1) + ldc * (col + 2)] = c2_2;
		c[(rowInDouble2 + 1) + ldc * (col + 3)] = c2_3;
  }
}
#undef row
#undef col
#undef rowInDouble2
#undef colInDouble2

#endif

#else

//These kernels handle any 

__kernel void SGEMMNTATI(int m,
                         int n,
                         int k,
                         read_only image2d_t a,
                         read_only image2d_t b,
                         __global float* c,
                         int ldc,
                         double alpha,
                         double beta)
{

#define rowInFloat4 get_global_id(0) * 8 / 4
#define colInFloat4 get_global_id(1) * 8 / 4
#define row get_global_id(0) * 8
#define col get_global_id(1) * 8

  if(row < m && col < n)
  {

    int4 idxA = {rowInFloat4, rowInFloat4 + 1, 0, 0};
    int4 idxB = {colInFloat4, colInFloat4 + 1, 0, 0};
    int4 increment = {0, 0, 1, 1};

    //c(1:4,1:8) of block
    float4 c0_0 = 0.0f;
    float4 c0_1 = 0.0f;
    float4 c0_2 = 0.0f;
    float4 c0_3 = 0.0f;
    float4 c0_4 = 0.0f;
    float4 c0_5 = 0.0f;
    float4 c0_6 = 0.0f;
    float4 c0_7 = 0.0f;

    //c(5:8, 1:8) of block
    float4 c4_0 = 0.0f;
    float4 c4_1 = 0.0f;
    float4 c4_2 = 0.0f;
    float4 c4_3 = 0.0f;
    float4 c4_4 = 0.0f;
    float4 c4_5 = 0.0f;
    float4 c4_6 = 0.0f;
    float4 c4_7 = 0.0f;

    //a(1:8, 1)
    float4 a0_0;
    float4 a4_0;

    //b(1, 1:8) (b is transposed)
    float4 b0_0;
    float4 b0_4;

    //Unroll to use all 8 samplers
    for(;idxA.z < k; idxA += increment, idxB += increment)
    {
      //load a and b for k = 0
      a0_0 = read_imagef(a, s0, idxA.xz);
      a4_0 = read_imagef(a, s1, idxA.yz);

      b0_0 = read_imagef(b, s2, idxB.xz);
      b0_4 = read_imagef(b, s3, idxB.yz);

      c0_0 += a0_0 * b0_0.xxxx;
      c0_1 += a0_0 * b0_0.yyyy;
      c0_2 += a0_0 * b0_0.zzzz;
      c0_3 += a0_0 * b0_0.wwww;
      c0_4 += a0_0 * b0_4.xxxx;
      c0_5 += a0_0 * b0_4.yyyy;
      c0_6 += a0_0 * b0_4.zzzz;
      c0_7 += a0_0 * b0_4.wwww;

      c4_0 += a4_0 * b0_0.xxxx;
      c4_1 += a4_0 * b0_0.yyyy;
      c4_2 += a4_0 * b0_0.zzzz;
      c4_3 += a4_0 * b0_0.wwww;
      c4_4 += a4_0 * b0_4.xxxx;
      c4_5 += a4_0 * b0_4.yyyy;
      c4_6 += a4_0 * b0_4.zzzz;
      c4_7 += a4_0 * b0_4.wwww;
      
      //Second unroll
      idxA += increment;
      idxB += increment;

      //load a and b for k = 0
      a0_0 = read_imagef(a, s4, idxA.xz);
      a4_0 = read_imagef(a, s5, idxA.yz);

      b0_0 = read_imagef(b, s6, idxB.xz);
      b0_4 = read_imagef(b, s7, idxB.yz);

      c0_0 += a0_0 * b0_0.xxxx;
      c0_1 += a0_0 * b0_0.yyyy;
      c0_2 += a0_0 * b0_0.zzzz;
      c0_3 += a0_0 * b0_0.wwww;
      c0_4 += a0_0 * b0_4.xxxx;
      c0_5 += a0_0 * b0_4.yyyy;
      c0_6 += a0_0 * b0_4.zzzz;
      c0_7 += a0_0 * b0_4.wwww;

      c4_0 += a4_0 * b0_0.xxxx;
      c4_1 += a4_0 * b0_0.yyyy;
      c4_2 += a4_0 * b0_0.zzzz;
      c4_3 += a4_0 * b0_0.wwww;
      c4_4 += a4_0 * b0_4.xxxx;
      c4_5 += a4_0 * b0_4.yyyy;
      c4_6 += a4_0 * b0_4.zzzz;
      c4_7 += a4_0 * b0_4.wwww;
    }

    // **. If in top left,
    // **. Store top left
    // ...
    if(row + 7 < m && col + 7 < n)
    {
      //Store first 4 rows
      c[(row + 0) + ldc * (col + 0)] = c0_0.x;
      c[(row + 1) + ldc * (col + 0)] = c0_0.y;
      c[(row + 2) + ldc * (col + 0)] = c0_0.z;
      c[(row + 3) + ldc * (col + 0)] = c0_0.w;
      c[(row + 0) + ldc * (col + 1)] = c0_1.x;
      c[(row + 1) + ldc * (col + 1)] = c0_1.y;
      c[(row + 2) + ldc * (col + 1)] = c0_1.z;
      c[(row + 3) + ldc * (col + 1)] = c0_1.w;
      c[(row + 0) + ldc * (col + 2)] = c0_2.x;
      c[(row + 1) + ldc * (col + 2)] = c0_2.y;
      c[(row + 2) + ldc * (col + 2)] = c0_2.z;
      c[(row + 3) + ldc * (col + 2)] = c0_2.w;
      c[(row + 0) + ldc * (col + 3)] = c0_3.x;
      c[(row + 1) + ldc * (col + 3)] = c0_3.y;
      c[(row + 2) + ldc * (col + 3)] = c0_3.z;
      c[(row + 3) + ldc * (col + 3)] = c0_3.w;
      c[(row + 0) + ldc * (col + 4)] = c0_4.x;
      c[(row + 1) + ldc * (col + 4)] = c0_4.y;
      c[(row + 2) + ldc * (col + 4)] = c0_4.z;
      c[(row + 3) + ldc * (col + 4)] = c0_4.w;
      c[(row + 0) + ldc * (col + 5)] = c0_5.x;
      c[(row + 1) + ldc * (col + 5)] = c0_5.y;
      c[(row + 2) + ldc * (col + 5)] = c0_5.z;
      c[(row + 3) + ldc * (col + 5)] = c0_5.w;
      c[(row + 0) + ldc * (col + 6)] = c0_6.x;
      c[(row + 1) + ldc * (col + 6)] = c0_6.y;
      c[(row + 2) + ldc * (col + 6)] = c0_6.z;
      c[(row + 3) + ldc * (col + 6)] = c0_6.w;
      c[(row + 0) + ldc * (col + 7)] = c0_7.x;
      c[(row + 1) + ldc * (col + 7)] = c0_7.y;
      c[(row + 2) + ldc * (col + 7)] = c0_7.z;
      c[(row + 3) + ldc * (col + 7)] = c0_7.w;
      
      //Store next 4 rows
      c[(row + 4) + ldc * (col + 0)] = c4_0.x;
      c[(row + 5) + ldc * (col + 0)] = c4_0.y;
      c[(row + 6) + ldc * (col + 0)] = c4_0.z;
      c[(row + 7) + ldc * (col + 0)] = c4_0.w;
      c[(row + 4) + ldc * (col + 1)] = c4_1.x;
      c[(row + 5) + ldc * (col + 1)] = c4_1.y;
      c[(row + 6) + ldc * (col + 1)] = c4_1.z;
      c[(row + 7) + ldc * (col + 1)] = c4_1.w;
      c[(row + 4) + ldc * (col + 2)] = c4_2.x;
      c[(row + 5) + ldc * (col + 2)] = c4_2.y;
      c[(row + 6) + ldc * (col + 2)] = c4_2.z;
      c[(row + 7) + ldc * (col + 2)] = c4_2.w;
      c[(row + 4) + ldc * (col + 3)] = c4_3.x;
      c[(row + 5) + ldc * (col + 3)] = c4_3.y;
      c[(row + 6) + ldc * (col + 3)] = c4_3.z;
      c[(row + 7) + ldc * (col + 3)] = c4_3.w;
      c[(row + 4) + ldc * (col + 4)] = c4_4.x;
      c[(row + 5) + ldc * (col + 4)] = c4_4.y;
      c[(row + 6) + ldc * (col + 4)] = c4_4.z;
      c[(row + 7) + ldc * (col + 4)] = c4_4.w;
      c[(row + 4) + ldc * (col + 5)] = c4_5.x;
      c[(row + 5) + ldc * (col + 5)] = c4_5.y;
      c[(row + 6) + ldc * (col + 5)] = c4_5.z;
      c[(row + 7) + ldc * (col + 5)] = c4_5.w;
      c[(row + 4) + ldc * (col + 6)] = c4_6.x;
      c[(row + 5) + ldc * (col + 6)] = c4_6.y;
      c[(row + 6) + ldc * (col + 6)] = c4_6.z;
      c[(row + 7) + ldc * (col + 6)] = c4_6.w;
      c[(row + 4) + ldc * (col + 7)] = c4_7.x;
      c[(row + 5) + ldc * (col + 7)] = c4_7.y;
      c[(row + 6) + ldc * (col + 7)] = c4_7.z;
      c[(row + 7) + ldc * (col + 7)] = c4_7.w;
    }
    // ..* If in bottom right,
    // ..* Store botton right
    // ***
    else
    {
      int colsLeft = col + 7 < n ? 0 : n % 8;

      //How many rows remain?
      switch(row + 7 < m ? 0 : m % 8)
      {
        case 0:
          //How many cols remain?
          switch(colsLeft)
          {
            case 0:
              c[(row + 7) + ldc * (col + 7)] = c4_7.w;
            case 7:
              c[(row + 7) + ldc * (col + 6)] = c4_6.w;
            case 6:
              c[(row + 7) + ldc * (col + 5)] = c4_5.w;
            case 5:
              c[(row + 7) + ldc * (col + 4)] = c4_4.w;
            case 4:
              c[(row + 7) + ldc * (col + 3)] = c4_3.w;
            case 3:
              c[(row + 7) + ldc * (col + 2)] = c4_2.w;
            case 2:
              c[(row + 7) + ldc * (col + 1)] = c4_1.w;
            case 1:
              c[(row + 7) + ldc * (col + 0)] = c4_0.w;
          }
        case 7:
          switch(colsLeft)
          {
            case 0:
              c[(row + 6) + ldc * (col + 7)] = c4_7.z;
            case 7:
              c[(row + 6) + ldc * (col + 6)] = c4_6.z;
            case 6:
              c[(row + 6) + ldc * (col + 5)] = c4_5.z;
            case 5:
              c[(row + 6) + ldc * (col + 4)] = c4_4.z;
            case 4:
              c[(row + 6) + ldc * (col + 3)] = c4_3.z;
            case 3:
              c[(row + 6) + ldc * (col + 2)] = c4_2.z;
            case 2:
              c[(row + 6) + ldc * (col + 1)] = c4_1.z;
            case 1:
              c[(row + 6) + ldc * (col + 0)] = c4_0.z;
          }
        case 6:
          switch(colsLeft)
          {
            case 0:
              c[(row + 5) + ldc * (col + 7)] = c4_7.y;
            case 7:
              c[(row + 5) + ldc * (col + 6)] = c4_6.y;
            case 6:
              c[(row + 5) + ldc * (col + 5)] = c4_5.y;
            case 5:
              c[(row + 5) + ldc * (col + 4)] = c4_4.y;
            case 4:
              c[(row + 5) + ldc * (col + 3)] = c4_3.y;
            case 3:
              c[(row + 5) + ldc * (col + 2)] = c4_2.y;
            case 2:
              c[(row + 5) + ldc * (col + 1)] = c4_1.y;
            case 1:
              c[(row + 5) + ldc * (col + 0)] = c4_0.y;
          }
        case 5:
          switch(colsLeft)
          {
            case 0:
              c[(row + 4) + ldc * (col + 7)] = c4_7.x;
            case 7:
              c[(row + 4) + ldc * (col + 6)] = c4_6.x;
            case 6:
              c[(row + 4) + ldc * (col + 5)] = c4_5.x;
            case 5:
              c[(row + 4) + ldc * (col + 4)] = c4_4.x;
            case 4:
              c[(row + 4) + ldc * (col + 3)] = c4_3.x;
            case 3:
              c[(row + 4) + ldc * (col + 2)] = c4_2.x;
            case 2:
              c[(row + 4) + ldc * (col + 1)] = c4_1.x;
            case 1:
              c[(row + 4) + ldc * (col + 0)] = c4_0.x;
          }
        case 4:
          switch(colsLeft)
          {
            case 0:
              c[(row + 3) + ldc * (col + 7)] = c0_7.w;
            case 7:
              c[(row + 3) + ldc * (col + 6)] = c0_6.w;
            case 6:
              c[(row + 3) + ldc * (col + 5)] = c0_5.w;
            case 5:
              c[(row + 3) + ldc * (col + 4)] = c0_4.w;
            case 4:
              c[(row + 3) + ldc * (col + 3)] = c0_3.w;
            case 3:
              c[(row + 3) + ldc * (col + 2)] = c0_2.w;
            case 2:
              c[(row + 3) + ldc * (col + 1)] = c0_1.w;
            case 1:
              c[(row + 3) + ldc * (col + 0)] = c0_0.w;
          }
        case 3:
          switch(colsLeft)
          {
            case 0:
              c[(row + 2) + ldc * (col + 7)] = c0_7.z;
            case 7:
              c[(row + 2) + ldc * (col + 6)] = c0_6.z;
            case 6:
              c[(row + 2) + ldc * (col + 5)] = c0_5.z;
            case 5:
              c[(row + 2) + ldc * (col + 4)] = c0_4.z;
            case 4:
              c[(row + 2) + ldc * (col + 3)] = c0_3.z;
            case 3:
              c[(row + 2) + ldc * (col + 2)] = c0_2.z;
            case 2:
              c[(row + 2) + ldc * (col + 1)] = c0_1.z;
            case 1:
              c[(row + 2) + ldc * (col + 0)] = c0_0.z;
          }
        case 2:
          switch(colsLeft)
          {
            case 0:
              c[(row + 1) + ldc * (col + 7)] = c0_7.y;
            case 7:
              c[(row + 1) + ldc * (col + 6)] = c0_6.y;
            case 6:
              c[(row + 1) + ldc * (col + 5)] = c0_5.y;
            case 5:
              c[(row + 1) + ldc * (col + 4)] = c0_4.y;
            case 4:
              c[(row + 1) + ldc * (col + 3)] = c0_3.y;
            case 3:
              c[(row + 1) + ldc * (col + 2)] = c0_2.y;
            case 2:
              c[(row + 1) + ldc * (col + 1)] = c0_1.y;
            case 1:
              c[(row + 1) + ldc * (col + 0)] = c0_0.y;
          }
        case 1:
          switch(colsLeft)
          {
            case 0:
              c[(row + 0) + ldc * (col + 7)] = c0_7.x;
            case 7:
              c[(row + 0) + ldc * (col + 6)] = c0_6.x;
            case 6:
              c[(row + 0) + ldc * (col + 5)] = c0_5.x;
            case 5:
              c[(row + 0) + ldc * (col + 4)] = c0_4.x;
            case 4:
              c[(row + 0) + ldc * (col + 3)] = c0_3.x;
            case 3:
              c[(row + 0) + ldc * (col + 2)] = c0_2.x;
            case 2:
              c[(row + 0) + ldc * (col + 1)] = c0_1.x;
            case 1:
              c[(row + 0) + ldc * (col + 0)] = c0_0.x;
          }
      }
    }
  }
}
#undef row
#undef col
#undef rowAsFloat4
#undef colAsFloat4

__kernel void DGEMMNTATI(int m,
                         int n,
                         int k,
                         read_only image2d_t a,
                         read_only image2d_t b,
                         __global float* c,
                         int ldc,
                         float alpha,
                         float beta)
{

#define rowInDouble2 get_global_id(0) * 4 / 2
#define colInDouble2 get_global_id(1) * 4 / 2
#define row get_global_id(0) * 4
#define col get_global_id(1) * 4

  if(row < m && col < n)
  {

    int4 idxA = {rowInDouble2, rowInDouble2 + 1, 0, 0};
    int4 idxB = {colInDouble2, colInDouble2 + 1, 0, 0};
    int4 increment = {0, 0, 1, 1};

    //c(1:2,1:4) of block
    double2 c0_0 = 0.0;
    double2 c0_1 = 0.0;
    double2 c0_2 = 0.0;
    double2 c0_3 = 0.0;

    //c(3:4, 1:4) of block
    double2 c2_0 = 0.0;
    double2 c2_1 = 0.0;
    double2 c2_2 = 0.0;
    double2 c2_3 = 0.0;

    //a(1:4, 1)
    double2 a0_0;
    double2 a2_0;

    //b(1, 1:4) (b is transposed)
    double2 b0_0;
    double2 b0_2;

    //Unroll to use all 8 samplers
    for(;idxA.z < k; idxA += increment, idxB += increment)
    {
      //load a and b for k = 0
      a0_0 = as_double2(read_imagef(a, s0, idxA.xz));
      a2_0 = as_double2(read_imagef(a, s1, idxA.yz));

      b0_0 = as_double2(read_imagef(b, s2, idxB.xz));
      b0_2 = as_double2(read_imagef(b, s3, idxB.yz));

      c0_0 += a0_0 * b0_0.xx;
      c0_1 += a0_0 * b0_0.yy;
      c0_2 += a0_0 * b0_2.xx;
      c0_3 += a0_0 * b0_2.yy;

      c2_0 += a2_0 * b0_0.xx;
      c2_1 += a2_0 * b0_0.yy;
      c2_2 += a2_0 * b0_2.xx;
      c2_3 += a2_0 * b0_2.yy;
      
      //Second unroll
      idxA += increment;
      idxB += increment;

      //load a and b for k = 0
      a0_0 = as_double2(read_imagef(a, s4, idxA.xz));
      a2_0 = as_double2(read_imagef(a, s5, idxA.yz));

      b0_0 = as_double2(read_imagef(b, s6, idxB.xz));
      b0_2 = as_double2(read_imagef(b, s7, idxB.yz));

      c0_0 += a0_0 * b0_0.xx;
      c0_1 += a0_0 * b0_0.yy;
      c0_2 += a0_0 * b0_2.xx;
      c0_3 += a0_0 * b0_2.yy;

      c2_0 += a2_0 * b0_0.xx;
      c2_1 += a2_0 * b0_0.yy;
      c2_2 += a2_0 * b0_2.xx;
      c2_3 += a2_0 * b0_2.yy;
    }

    // **. If in top left,
    // **. Store top left
    // ...
    if(row + 7 < m && col + 7 < n)
    {
      //Store first 4 rows
      c[(row + 0) + ldc * (col + 0)] = c0_0.x;
      c[(row + 1) + ldc * (col + 0)] = c0_0.y;
      c[(row + 0) + ldc * (col + 1)] = c0_1.x;
      c[(row + 1) + ldc * (col + 1)] = c0_1.y;
      c[(row + 0) + ldc * (col + 2)] = c0_2.x;
      c[(row + 1) + ldc * (col + 2)] = c0_2.y;
      c[(row + 0) + ldc * (col + 3)] = c0_3.x;
      c[(row + 1) + ldc * (col + 3)] = c0_3.y;
      
      //Store next 4 rows
      c[(row + 2) + ldc * (col + 0)] = c2_0.x;
      c[(row + 3) + ldc * (col + 0)] = c2_0.y;
      c[(row + 2) + ldc * (col + 1)] = c2_1.x;
      c[(row + 3) + ldc * (col + 1)] = c2_1.y;
      c[(row + 2) + ldc * (col + 2)] = c2_2.x;
      c[(row + 3) + ldc * (col + 2)] = c2_2.y;
      c[(row + 2) + ldc * (col + 3)] = c2_3.x;
      c[(row + 3) + ldc * (col + 3)] = c2_3.y;
    }
    // ..* If in bottom right,
    // ..* Store botton right
    // ***
    else
    {
      int colsLeft = col + 3 < n ? 0 : n % 4;

      //How many rows remain?
      switch(row + 3 < m ? 0 : m % 4)
      {
        case 0:
          //How many cols remain?
          switch(colsLeft)
          {
            case 0:
              c[(row + 3) + ldc * (col + 3)] = c2_3.y;
            case 3:
              c[(row + 3) + ldc * (col + 2)] = c2_2.y;
            case 2:
              c[(row + 3) + ldc * (col + 1)] = c2_1.y;
            case 1:
              c[(row + 3) + ldc * (col + 0)] = c2_0.y;
          }
        case 3:
          switch(colsLeft)
          {
            case 0:
              c[(row + 2) + ldc * (col + 3)] = c2_3.x;
            case 3:
              c[(row + 2) + ldc * (col + 2)] = c2_2.x;
            case 2:
              c[(row + 2) + ldc * (col + 1)] = c2_1.x;
            case 1:
              c[(row + 2) + ldc * (col + 0)] = c2_0.x;
          }
        case 2:
          switch(colsLeft)
          {
            case 0:
              c[(row + 1) + ldc * (col + 3)] = c0_3.y;
            case 3:
              c[(row + 1) + ldc * (col + 2)] = c0_2.y;
            case 2:
              c[(row + 1) + ldc * (col + 1)] = c0_1.y;
            case 1:
              c[(row + 1) + ldc * (col + 0)] = c0_0.y;
          }
        case 1:
          switch(colsLeft)
          {
            case 0:
              c[(row + 0) + ldc * (col + 3)] = c0_3.x;
            case 3:
              c[(row + 0) + ldc * (col + 2)] = c0_2.x;
            case 2:
              c[(row + 0) + ldc * (col + 1)] = c0_1.x;
            case 1:
              c[(row + 0) + ldc * (col + 0)] = c0_0.x;
          }
      }
    }
  }
}
#undef row
#undef col
#undef rowAsFloat4
#undef colAsFloat4

#endif
