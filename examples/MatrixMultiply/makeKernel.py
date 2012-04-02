import sys

print '__attribute__ ((reqd_work_group_size(8, 8, 1)))'
print '__kernel void sgemmNT(int m,'
print '                      int n,'
print '                      int k,'
print '                      float alpha,'
print '                      __global float* a,'
print '                      int lda,'
print '                      __global float* b,'
print '                      int ldb,'
print '                      float beta,'
print '                      __global float* c,'
print '                      int ldc)'
print '{'

rowRep = 4
colRep = 4
kDim  = 1

print '  int rowBlock = get_group_id(0) * 8 * ',rowRep, ';'
print '  int colBlock = get_group_id(1) * 8 * ',colRep, ';'
print '  int localRow = get_local_id(0);'
print '  int localCol = get_local_id(1);'
print '  int tid = localRow + localCol * 8;';
print '  int kaRow = tid % (' + str(rowRep) + ' * 8);'
print '  int kaCol = tid / (' + str(rowRep) + ' * 8);'
print '  int kbRow = tid % (' + str(colRep) + ' * 8);'
print '  int kbCol = tid / (' + str(colRep) + ' * 8);'
print '  __global float* aPtr = &a[rowBlock + localRow];'
print '  __global float* bPtr = &b[colBlock + localCol];'

for i in range(0, rowRep):
	for j in range(0, colRep):
		print '  float cVal_' + str(i) + '_' + str(j) + ' = 0.0f;'
print '  __local float aLocal[(9 + ', rowRep, ') * ', kDim, '];'
print '  __local float bLocal[(9 + ', colRep, ') * ', kDim, '];'
print ''
print '  #pragma unroll 1'
print '  for(int i = 0; i < k; i++)'
print '  {'
print '    barrier(CLK_LOCAL_MEM_FENCE);'
#for i in range(0, kDim):
#print '    aLocal[kaRow] = a[rowBlock + kaRow + i * lda];';
#	print '    bLocal[kbCol] = b[colBlock + kbCol + i * ldb];';

print '    barrier(CLK_LOCAL_MEM_FENCE);'

for i in range(0, rowRep):
#print '    float a_' + str(i) + ' = aPtr[' + str(8 * i) + '];';
	print '    float a_' + str(i) + ' = ' + str(i) + ';' #aLocal[localRow + ' + str(8*i) + '];';

for i in range(0, colRep):
#print '    float b_' + str(i) + ' = bPtr[' + str(8 * i) + '];';
	print '    float b_' + str(i) + ' = ' + str(i) + ';' #bLocal[localCol + ' + str(8*i) + '];';

print ''

for i in range(0, rowRep):
	for j in range(0, colRep):
		print '    cVal_' + str(i) + '_' + str(j) + ' = fma(a_' + str(i) + ', b_' + str(j) + ', cVal_' + str(i) + '_' + str(j) + ');'
print '    '
print '    aPtr += lda;'
print '    bPtr += ldb;'
print '  }'

#for i in range(0, rowRep):
#	for j in range(0, colRep):
#print '  c[rowBlock + localRow + ' + str(8 * i) + ' + (colBlock + localCol + ' + str(8 * j) + ') * ldc] = alpha * cVal_' + str(i) + '_' + str(j) + ' + beta * c[rowBlock + localRow + ' + str(8 * i) + ' + (colBlock + localCol + ' + str(8 * j) + ') * ldc];'

print '}'
