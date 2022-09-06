
#include <stdio.h>
#include <pthread.h>
#include <iostream>
using namespace std;

pthread_mutex_t mutex;

void *count(void *file)
{
	while (pthread_mutex_lock(&mutex) != 0);
	cout << pthread_self() << endl;
	cout << (char *)file << endl;
	pthread_mutex_unlock(&mutex);
	return (void *)0;
}

int
main(int argc, char *argv[])
{
	pthread_mutex_init(&mutex, NULL);
	const char *s = "si";
	const char *t = "ti";

	pthread_t t1, t2;

	pthread_create(&t1, NULL, count, (void *)s);
	pthread_create(&t2, NULL, count, (void *)t);

	cout << "hello"  <<  endl;
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	cout << "end" << endl;

	return 0;

}
	
