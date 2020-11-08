#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <semaphore.h>
#include <getopt.h>  //allow analyse of arguments

int NTHREADS1;
int NTHREADS2;
int N=8;
int *buffer;
int * first;
int * last;
int total;
int in=0;
int out=0;
pthread_mutex_t mutex ;   // mutex bind with the buffer

sem_t empty ;  // sémaphore qui compte le nombre de places vides dans le premier buffer
sem_t full ;   // sémaphore qui compte le nombre  de places occupées dans le premier buffer


void addbuffer(int p){
  /*
  *Description: ajoute un élemement dans buffer
  */
    buffer[(*last)]=p;
    (*last)=((*last)+1)%N;
    return;
}

int *removebuffer(){
  /*
  *Description: retire un élément de buffer
  */
    int *p = (int *)malloc(sizeof(int));
    *p=buffer[*first];
    buffer[*first]=0;
    *first = ((*first)+1)%N;
    return p;
}

void freebuffer(){
  free(last);
  free(first);
  free(buffer);
}

void *producer(void *param){
    int err_p;
    while (in<total){
        int a=rand();
        err_p = sem_wait(&empty);
        if(err_p!=0) printf("erreur  read wait e.1\n");
        err_p = pthread_mutex_lock(&mutex);
        if(err_p!=0) printf("erreur  read lock m.1 \n");
        if (in<total)
        {
        printf("%d:%d\n",in,a);
        addbuffer(a);
        in++;   
        }
        err_p= pthread_mutex_unlock(&mutex);
        if(err_p!=0) printf("erreur  read unlock 1 \n");
        err_p = sem_post(&full);
        if(err_p!=0) printf("erreur read post f.1 \n");
    }
    err_p = sem_post(&full);
    if(err_p!=0) printf("erreur read post 1.2 \n");
    printf("end of producer with %d products\n",in);
    return NULL;
}


void *consumer(void *param){
    int err_c;
    int *value;
    while (out<total)
    {
       err_c = sem_wait(&full);
        if(err_c!=0) printf("erreur  read wait e.1\n");
        err_c = pthread_mutex_lock(&mutex);
        if(err_c!=0) printf("erreur  read lock m.1 \n");
        if (out<total){
            value=removebuffer();
            printf("%d:%d\n",out,*value);
            out++;
            free(value);
        }
        err_c= pthread_mutex_unlock(&mutex);
        if(err_c!=0) printf("erreur  read unlock 1 \n");
        err_c = sem_post(&empty);
        if(err_c!=0) printf("erreur read post f.1 \n"); 
    }
    err_c = sem_post(&full);
    if(err_c!=0) printf("erreur prime post f.1\n");

    printf("end of consumer with %d consumer\n",out);
    return NULL;
    
}

int main(int argc, char const *argv[]){
    total=60;
    NTHREADS1=7;
    NTHREADS2=2;
    first = (int *)calloc(1,sizeof(int *));
    if(!first) printf("%s\n","erreur calloc first" );

    last = (int *)calloc(1,sizeof(int *));
    if(!last) printf("%s\n","erreur calloc last" );

    buffer =(int *) calloc(N*sizeof(int),sizeof(int));

      int err = pthread_mutex_init(&mutex,NULL);
      if(err!=0) printf("%s\n","error mutex" );
      err =  sem_init(&empty,0,NTHREADS1);
      if(err!=0) printf("%s\n","error empty" );
      err = sem_init(&full,0,0);
      if(err!=0) printf("%s\n","error full" );



      pthread_t threads1[NTHREADS1];
      int i;
      for (i = 0; i < NTHREADS1; i++){
      err = pthread_create(&threads1[i],NULL,&producer,NULL);
      if(err!=0) printf("%s\n", "error thread_create" );
      }

      pthread_t threads2[NTHREADS2];
      for (i = 0; i < NTHREADS2; i++){
      err = pthread_create(&threads2[i],NULL,&consumer,NULL);
      if(err!=0) printf("%s\n", "error thread_create" );
      }
    int j;
    for ( j = 0; j < NTHREADS1; j++) {
        err = pthread_join(threads1[j], NULL);
        if(err!=0) printf("%s\n", "error thread_join" );
    }


    for ( j = 0; j < NTHREADS2; j++) {
        err = pthread_join(threads2[j], NULL);
        if(err!=0) printf("%s\n", "error thread_join" );
    }



    
    int err2;
    err2 = pthread_mutex_destroy(&mutex);
    if(err2!=0)  printf("%s\n", "error destroy_mutex" );
    err2 =sem_destroy(&empty);
    if(err2!=0)  printf("%s\n", "error destroy_sem_empty" );
    err2 =sem_destroy(&full);
    if(err2!=0)  printf("%s\n", "error destroyy_sem_full" );


    freebuffer();
    return 0;
}
