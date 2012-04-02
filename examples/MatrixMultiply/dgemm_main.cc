#include <clUtil.h>
#include <memory>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <exception>
#include "blas.h"

using namespace clUtil;
using namespace std;

int m;
int n;
int k;

#define IDX(row, col, ld) (row + col * ld)
//#define VERIFY

static double time()
{
  timeval curTime;

  gettimeofday(&curTime, NULL);

  return (double)curTime.tv_sec + (double)curTime.tv_usec / 1e6;
}

static void usage()
{
  cout << "Usage: gemm m n k" << endl;
  exit(1);
}

void fillMatrix(float* a, int m, int n)
{
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < n; j++)
    {
      a[j * m + i] = (float)drand48();
    }
  }
}

void fillMatrix(double* a, int m, int n)
{
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < n; j++)
    {
      a[j * m + i] = drand48();
    }
  }
}

void copy(double* a, double* b, int n)
{
  for(int i = 0; i < n; i++)
  {
    a[i] = b[i];
  }
}

int main(int argc, char** argv)
{
  const char* kernels[] = {"dgemm.cl", "xgemmRef.cl"};

  if(argc < 4)
  {
    usage();
  }

  m = atoi(argv[1]);
  n = atoi(argv[2]);
  k = atoi(argv[3]);

  unique_ptr<double[]> a(new double[m * k]);
  unique_ptr<double[]> b(new double[k * n]);
  unique_ptr<double[]> c(new double[m * n]);
  unique_ptr<double[]> cRef(new double[m * n]);

  fillMatrix(&a[0], m, k);
  fillMatrix(&b[0], k, n);
  fillMatrix(&c[0], m, n);
  copy(&cRef[0], &c[0], n * m);

  Device::InitializeDevices(kernels, 2, NULL, "-D__DEVICE__");
  //Device::SetCurrentDevice(3);

  char transA = 'N';
  char transB = 'N';
  
  try
  {

    Buffer aDev(sizeof(a[0]) * m * k);
    Buffer bDev(sizeof(b[0]) * k * n);
    Buffer cDev(sizeof(c[0]) * m * n);
    Buffer cRefDev(sizeof(cRef[0]) * m * n);

    aDev.put(&a[0]);
    bDev.put(&b[0]);
    cDev.put(&c[0]);
    cRefDev.put(&cRef[0]);

    dgemm_reference(&transA,
                    &transB, 
                    m, 
                    n, 
                    k, 
                    1.0,
                    aDev, 
                    m, 
                    bDev, 
                    k, 
                    0.0, 
                    cRefDev, 
                    m);

    double time1 = time();

    dgemm(&transA,
          &transB, 
          m, 
          n, 
          k, 
          1.0,
          aDev, 
          m, 
          bDev, 
          k, 
          0.0, 
          cDev, 
          m);

    double time2 = time();

    cDev.get(&c[0]);
    cRefDev.get(&cRef[0]);

    clFinish(Device::GetCurrentDevice().getCommandQueue());

#ifdef VERIFY
    for(int i = 0; i < m; i++)
    {
      for(int j = 0; j < n; j++)
      {
        float c1 = c[j * m + i];
        float c2 = cRef[j * m + i];

        if(fabs((c1-c2) / c1) > 1e-15)
        {
          cout << "Error row " << i << " col " << j 
            << " calc " << c1 << " ref " << c2 << endl;
          exit(1);
        }
      }
    }
#endif

    printf("%d\t%E\n", m, 2.0 * m * n * k / (time2 - time1));

  }
  catch(clUtilException& err)
  {
    cout << err.what() << endl;
    exit(1);
  }
  return 0;
}
