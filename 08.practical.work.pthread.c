#include <stdio.h>
#include <pthread.h>

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
			printf("Prime: %d \n", i);
		}
	}
}

void *fibo() {
	long long n1 = 1, n2 = 2;
	for(int i=1; i<=50; i++){  //50 first fibonacci number to (hopefully) avoid overflow
		printf("Fibo: %llo \n", n2);
		long long next = n1 + n2;
		n1 = n2;
		n2 = next;
	}
}

int main() {
	int thred1, thred2;
	pthread_t tid1, tid2;
	thred1 = pthread_create(&tid1, NULL, prime, NULL);
	thred2 = pthread_create(&tid2, NULL, fibo, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}