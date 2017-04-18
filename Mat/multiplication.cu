#include <stdio.h>
#include <math.h>
#include<cuda.h>


__global__ void matrixMul(A_gpu,B_gpu,C_gpu,K){

    temp = 0
    
    i = blockIdx.y * blockDim.y + threadIdx.y    // Row i of matrix C
    j = blockIdx.x * blockDim.x + threadIdx.x    // Column j of matrix C

    for(int k = 0;k<K-1;k++)
        temp+ =A_gpu(i,k) * B_gpu(k,j)
    end

    C_gpu(i,j) = accu
    
}



void main(){
    

    //Host array
    int A_cpu[N], B_cpu[N], C_cpu[N];

    //Device array
    int *A_gpu, *B_gpu, *C_gpu ;
    

    cudaMalloc((void **)&A_gpu , N*sizeof(int) ) ;
    cudaMalloc((void **)&B_gpu , N*sizeof(int) ) ;
    cudaMalloc((void **)&C_gpu , N*sizeof(int) ) ;


    cudaMemcpy (A_gpu , A_cpu , N*sizeof(int) , cudaMemcpyHostToDevice);
    cudaMemcpy (B_gpu , B_cpu , N*sizeof(int) , cudaMemcpyHostToDevice);

    
    dim3 dimBlock(16, 16);
    dim3 dimGrid(N/dimBlock.x, M/dimBlock.y);

    matrixMul<<<dimGrid, dimBlock>>>(A_gpu,B_gpu,C_gpu,K);
    
    cudaMemcpy(C_cpu , C_gpu , N*sizeof(int) , cudaMemcpyDeviceToHost);
    
    
}


