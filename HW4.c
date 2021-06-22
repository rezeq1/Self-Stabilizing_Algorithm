
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>


int Get_Option();
void Pulse(int* values , int size); 
void Print_Values(int* values , int size);
void Set_Random_Values(int* values , int size);
void Change_Leader_Process_Value(int* values , int size);
void Change_Regular_Process_Value(int* values , int size,int num_process);
int PID;

int main()
{
	
    int num_processes,option,*values,i;

    // Get the number of processes to create 
    printf("Please enter number of processes to create : "); 
    scanf("%d",&num_processes);
    
    // set random values between 0 to 10 for each process
    values=malloc(sizeof(int)*num_processes);
    Set_Random_Values(values,num_processes);
      	    

    option=Get_Option();
    while (option!= 0)
    {
        
    	if(option == 1)
    	   Print_Values(values,num_processes);
    	else if(option == 2)    	
	   Pulse(values,num_processes);
        else
            printf("You enterd wrong option number .\n");
    		
    
       option=Get_Option();
       
       if(option==0)
           kill(PID,15);
    }
    
    
    free(values);
    exit(0);
    
}



int Get_Option()
{
     int option;
     printf("------------------------------------\n");
     printf("Menu\n");
     printf("1. Show values\n");
     printf("2. Pulse\n");
     printf("0. Exit\n");
     printf(">>");
     scanf("%d",&option);

     return option;
}

void Print_Values(int* values , int size)
{
    for(int i=0;i<size;i++)
    	if(i==size-1)
	    printf("The process %d has value %d.(Leader)\n",size-i-1,values[size-i-1]); 
	else
	    printf("The process %d has value %d.\n",size-i-1,values[size-i-1]);   	

}

void Set_Random_Values(int* values , int size)
{

    srand(time(NULL));
    for(int i=0;i<size;i++) 
	values[i]=rand()%11;

}

void Change_Leader_Process_Value(int* values , int size)
{
	int Process_Before_Value , Process_Value;
	
	Process_Value=values[0];
	Process_Before_Value=values[size-1];
	
	if(Process_Value == Process_Before_Value)
	{
	      printf("Permition to write at process %d\n",0);
	      values[0]=(Process_Value+1) % size ;
	
	}   

}

void Change_Regular_Process_Value(int* values , int size,int num_process)
{
	int Process_Before_Value , Process_Value;
	
	Process_Value=values[num_process];
	Process_Before_Value=values[num_process-1];
	
	if(Process_Value != Process_Before_Value)
	{
	      printf("Permition to write at process %d\n",num_process);
	      values[num_process]=Process_Before_Value;
	
	}   

}
void Pulse(int* values , int size)
{
    pid_t pid;
    int *indxs,indx,count=size,proc_num;
    
    indxs=malloc(sizeof(int)*size);
    for(int i=0;i<size;i++)
       indxs[i]=i;
       
    
    for(int i=0;i<size;i++) // create n processes
    {
        pid = fork();
        PID=pid;
        srand(time(NULL));
	indx=rand()%count;
	proc_num=indxs[indx];
	for(int k=indx;k<count-1;k++)
	    indxs[k]=indxs[k+1];
	count--;
	    
	if(pid == 0)
	   if(proc_num==0)
	      Change_Leader_Process_Value(values,size);
	   else
              Change_Regular_Process_Value(values,size,proc_num);
	else
	   waitpid(pid,NULL,0);
    }
   

}





