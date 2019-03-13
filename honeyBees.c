#ifndef _REENTRANT
#define _REENTRANT
#endif
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>


#define NO_OF_PRODUCERS 8
#define MAX_BUFFER 5

sem_t mutex;
sem_t cond;
int i;

int buffer[MAX_BUFFER];
int front = 0;
int rear = 0;
bool emptySpace = false;
pthread_t cons;
pthread_t prod[NO_OF_PRODUCERS];

void put(int value)
{
    buffer[front] = value;
    front = (front + 1) % MAX_BUFFER;
}

int get()
{
    int tmp = buffer[rear]; 
    rear = (rear + 1) % MAX_BUFFER;
    return tmp;
}

void *producer(void *arg)
{
  long id = (long) arg;

    while(true){
      sem_wait(&mutex);
      while(emptySpace){
      sem_post(&mutex);
      sem_wait(&cond);
      sem_wait(&mutex);
    }

    int position = front;
    put(i);
    printf("The bee %ld has put honey number %d \n", id, i);
    i++;

    if(position==(MAX_BUFFER-1)){
      emptySpace = true;
    }
    sem_post(&mutex);
    sleep(2);

  }
return NULL;

}

void *consumer(void *arg)
{
int i;
    while(true){
      if(emptySpace){
        sem_wait(&mutex);
        for(i=0;i<MAX_BUFFER; i++){
          get(i);
        }
        printf("Consumer is finshed\n");
        emptySpace = false;
        sem_post(&cond);
        sem_post(&mutex);
      }


}

return NULL;
}

int main()
{


    sem_init(&mutex, 0, 1);
    sem_init(&cond, 0, 0);

    pthread_create(&cons, NULL, consumer, NULL);


    for(long i = 0; i<NO_OF_PRODUCERS; i++){
      pthread_create(&prod[i], NULL, producer, (void *)i);




    }

    pthread_exit(NULL);



}
