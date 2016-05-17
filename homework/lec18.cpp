#include <iostream>
#include <cstdlib>
#include <window.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

using namespace std;

const int N = 4;
sem_t mutex;
sem_t qa;
sem_t qb;
sem_t qc;
int counta;
int countb;
int countc;
int free = 1;

void init()
{
	sem_init(&mutex,0,1);
	sem_init(&qa,0,0);
	sem_init(&qb,0,0);
	sem_init(&qc,0,0);
}

void*a_fun(void*arg)
{
	sem_wait(mutex);
	if(free == 1){
		free = 0;
		sem_post(mutex);
	}
	else
	{
		counta++;
		sem_post(mutex);
		sem_wait(qa);
	}
	sem_wait(mutex);
	if(countb>0){
		countb--;
		sem_post(qb);
	}
	else
	{
	    if(countc>0){
	        countc--;
	        sem_post(qc);
	    }
	    else{
	        if(counta>0){
	            counta--
	            sem_post(qa);
	        }
	        else{ 
	        	free=1;
	        }
	    }
	}
}

void*b_fun(void*arg)
{
	sem_wait(mutex);
	if(free==1){
		free=0;
		sem_post(mutex);
	}
	else
	{
		countb++;
		sem_post(mutex);
		sem_wait(qb);
	}
	sem_wait(mutex);
	if(countc>0){
		countc--;
		sem_post(qc);
	}
	else
	{
	    if(counta>0){
	        counta--;
	        sem_post(qa);
	    }
	    else{
	        if(countb>0){
	            countb--
	            sem_post(qb);
	        }
	        else{ 
	        	free=1;
	        }
	    }
	}
}

void*c_fun(void*arg)
{
	sem_wait(mutex);
	if(free==1){
		free=0;
		sem_post(mutex);
	}
	else
	{
		countc++;
		sem_post(mutex);
		sem_wait(qc);
	}
	sem_wait(mutex);
	if(counta>0){
		counta--;
		sem_post(qa);
	}
	else
	{
	    if(countb>0){
	        countb--;
	        sem_post(qb);
	    }
	    else{
	        if(countc>0){
	            countc--
	            sem_post(qc);
	        }
	        else{ 
	        	free=1;
	        }
	    }
	}
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	init();
	pthread_t thread[N];
	pthread_create(&thread[0],0,mutex,NULL);
	pthread_create(&thread[0],0,qa,NULL);
	pthread_create(&thread[0],0,qb,NULL);
	pthread_create(&thread[0],0,qc,NULL);

	for (int i = 0; i < N; i++)
	{
		pthread_join(thread[i],0);
	}
	return 0;
}