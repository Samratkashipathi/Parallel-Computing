#include <stdio.h>
#include <stdlib.h>



int x[150],h[150],y[150];


void main()
{                 int i,j,m,n;


                printf("\n enter value for m");       
                scanf("%d",&m); 
                printf("\n enter value for n");
                scanf("%d",&n);
                time_t t;
                printf("Enter values for i/p x(n):\n");
                srand((unsigned) time(&t));
                for(i=0;i<m;i++)                           
                           //scanf("%d",&x[i]);
                           x[i]=rand()%50;   
                for(i=0;i<m;i++)

                        printf("\n The Value x[%d]=%d",i,x[i]);
               srand(getpid());
               printf("Enter Values for i/p h(n) \n");
               for(i=0;i<n; i++)         
                           //scanf("%d",&h[i]);
                             h[i]=rand()%50;  

                for(i=0;i<m;i++)

                        printf("\n The Value h[%d]=%d",i,h[i]);

            // padding of zeors

            for(i=m;i<=m+n-1;i++)

                        x[i]=0;

            for(i=n;i<=m+n-1;i++)

                        h[i]=0;



            /* convolution operation */

            for(i=0;i<m+n-1;i++)

            {          

                        y[i]=0;

                        for(j=0;j<=i;j++)

                        {

                                    y[i]=y[i]+(x[j]*h[i-j]);

                        }

            }

            //displaying the o/p

            for(i=0;i<m+n-1;i++)

                        printf("\n The Value of output y[%d]=%d",i,y[i]);

}