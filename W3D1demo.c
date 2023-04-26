#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for sleep()

int val = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *waiter(void *args) {
    (void)args;

    pthread_mutex_lock(&mutex);
    while (val < 4) {
        printf("Waiter: sleeping because %d < 4\n", val);
        
        pthread_cond_wait(&cond, &mutex);

        printf("Waiter: waking up to see if %d >= 4\n", val);
    }

    int my_val = val;

    pthread_mutex_unlock(&mutex);

    printf("Waiter: all done! val is %d\n", my_val);

    return NULL;
}

int main(void) {
    pthread_t t;

    pthread_create(&t, NULL, waiter, NULL);

    for (int i = 0; i < 5; i++) {
        val = i;

        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

        sleep(1);   
    }

    pthread_join(t, NULL);
}