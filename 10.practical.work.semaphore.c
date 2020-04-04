#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;

void *prime() {
	int n = 2000, i, j, check; // prime number between 1 and 2000 because fibonacci will finish running first anyway
	for(i=1; i<=n; i++){
		check = 0;
		for(j=1; j<=n; j++){
			if(i%j==0){
				check++;
			}
		}
		if(check==2){
			sem_wait(&s);
			printf("Prime: %d \n", i);
			sem_post(&s);
		}
	}
	return NULL;
}

void *fibo() {
	long long n1 = 1, n2 = 2;
	for(int i=1; i<=50; i++){  //50 first fibonacci number to (hopefully) avoid overflow
		sem_wait(&s);
		printf("Fibo: %llo \n", n2);
		sem_post(&s);
		long long next = n1 + n2;
		n1 = n2;
		n2 = next;
	}
	return NULL;
}

int main() {
	sem_init(&s,0,1);
	int thred1, thred2;
	pthread_t tid1, tid2;
	thred1 = pthread_create(&tid1, NULL, prime, NULL);
	thred2 = pthread_create(&tid2, NULL, fibo, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	sem_destroy(&s);
	return 0;
}