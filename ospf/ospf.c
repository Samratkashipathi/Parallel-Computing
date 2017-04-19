#include <stdio.h>
#include<omp.h>
#define Infinity 10000  
#define no_of_routers 600


int cost_matrix[no_of_routers][no_of_routers], finished[no_of_routers], notdone[no_of_routers];

void findmymin(int start, int end, int *d, int *v);
void complete_work(int s, int e);


int main()
{  
  int n,  chunk,  md,  mv;  
  int i=0,j=0;

   //Initialisation of cost_matrix
   for (i = 0; i < no_of_routers; i++)  
      for (j = 0; j < no_of_routers; j++)  {
        //Cost for each vertex
        //If i==j that is same router then cost is zero
         if (j == i) cost_matrix[i][i] = 0;
         else if(i-j<50 || j-i<50){
            //Assuming that for each of the router
           // It can reach only 50 other routers
            cost_matrix[i][j]=rand()%50;
            //Cost is random number % 50
            //So that cost is less than 50
            printf("%d %d %d\n",i,j,cost_matrix[i][j]);
         }
         else{
            //Else mark router as not reachced by making cost matrix entry as Infinity 
            // In this case Infinity is 10000
            cost_matrix[i][j]=Infinity;
         }
      }
  

   for (i = 1; i < no_of_routers; i++)  {
      notdone[i] = 1;
      finished[i] = cost_matrix[0][i];
   }

   #pragma omp parallel 
   {  
      int startv,endv,step,mymd,mymv,  
      my_thread = omp_get_thread_num();  

    //For every thread it prints no of available thread and its thread id
     n = omp_get_num_threads();
     //This devides the work among all the threads 
     //Example If there are 400 routers nd 4 threads then 400/4 i.e
     //1/4th of total work will be done by each thread  
     chunk = no_of_routers/n;  
     printf("there are %d threads\n",n);  

     printf("%d:Thread Number\n",my_thread);

      //This part decides which chunk/part should each thread work
      //For example:If there are 400 routers and 4 chunks each of 100 routers
      //Then 1 thread takes 1-100 2nd one 101-200... and so on.
      startv = my_thread * chunk; 
      endv = startv + chunk - 1;
      for (i= 0; i< no_of_routers; i++)  {
         
         #pragma omp single 
         {  
         md = Infinity; 
         mv = 0;  
         }
         
         findmymin(startv,endv,&mymd,&mymv);
         
         #pragma omp critical 
         {  if (mymd < md)  
              {  md = mymd; mv = mymv;  }
         }
         
         #pragma omp single 
         {  notdone[mv] = 0;  }
         
         complete_work(startv,endv);
         
      }
   } 
   
}



void findmymin(int start, int end, int *d, int *v)
{  
      int i;
      *d = Infinity; 
      //#pragma opm parallel for
      //pragma for here cant be used because of race condition
      //Each and every thread is updating *d variable
      for (i = start; i <= end; i++)
         if (notdone[i] && finished[i] < *d)  {
            *d = cost_matrix[0][i];
            *v = i;
         }
}


void complete_work(int start, int end)
{ 
  int i;
  #pragma omp parallel for
   for (i = start; i <= end; i++)
      if (finished[mv] + cost_matrix[mv][i] < finished[i])  
         finished[i] = finished[mv] + cost_matrix[mv][i];
}
