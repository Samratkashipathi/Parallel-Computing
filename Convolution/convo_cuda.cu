#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

const short N = 100 ;

// CUDA Kernel for Convolution
__global__ void convolution ( const int *dev_a , const int *dev_b , int *dev_c)
{
      //Get the id of thread within a block
      unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x ; 
     /*for(i=0;i<m+n-1;i++){          
			y[i]=0;
            for(j=0;j<=i;j++){
			       y[i]=y[i]+(x[j]*h[i-j]);
	        }
     }*/
	  int j=0;
      if ( tid < N ) // check the boundry condition for the threads
            dev_c [tid] = 0 ;
        	for(j=0;j<=tid;j++){
        		dev_c[tid]=dev_c[tid]+dev_a[j]*dev_b[tid-j];
        	}

}

int main (void)
{

      //Host array
      int Host_a[N], Host_b[N], Host_c[N];

      //Device array
      int *dev_a , *dev_b, *dev_c ;
      time_t t;
      //Allocate the memory on the GPU
      cudaMalloc((void **)&dev_a , N*sizeof(int) ) ;
      cudaMalloc((void **)&dev_b , N*sizeof(int) ) ;
      cudaMalloc((void **)&dev_c , N*sizeof(int) ) ;
      srand((unsigned) time(&t));

      //fill the Host array with random elements on the CPU
      for ( int i = 0; i <N ; i++ )
      {
            Host_a[i] = dev_a[i]=rand()%50;//sin(i)*sin(i); 
      }

      for ( int i = 0; i <N ; i++ )
      {
            Host_b[i] =  dev_b[i]=rand()%50;//cos(i)*cos(i); 
      }


      //Copy Host array to Device array
      cudaMemcpy (dev_a , Host_a , N*sizeof(int) , cudaMemcpyHostToDevice);
      cudaMemcpy (dev_b , Host_b , N*sizeof(int) , cudaMemcpyHostToDevice);

      //Make a call to GPU kernel
      convolution <<<(N)/512, 512>>> (dev_a , dev_b , dev_c ) ;

      //Copy back to Host array from Device array
      cudaMemcpy(Host_c , dev_c , N*sizeof(int) , cudaMemcpyDeviceToHost);

      //Display the result
      for ( int i = 0; i<N; i++ )
                  printf ("%d + %d = %d\n", Host_a[i] , Host_b[i] , Host_c[i] ) ;

      //Free the Device array memory
      cudaFree (dev_a) ;
      cudaFree (dev_b) ;
      cudaFree (dev_c) ;


      return 0 ;

}
