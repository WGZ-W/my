
#include <iostream>
#include <fstream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct node{
	string str;
	int nu;
};

bool cmp(node &p1, node &p2)
{
	return p1.nu > p2.nu;
}

int cnt;
pthread_mutex_t mutex;
map <string, int> mp;
void *count(void *filename)
{
	char *file = (char *)filename;
	FILE *fp = fopen(file, "r");
	char c;
	c = fgetc(fp);
	string w = "";
	int i = 0;
	while (c != EOF){
		if (isalpha(c))
			w += c;
		else {
			if (w == ""){
				c = fgetc(fp);
				continue;
			}
			// while (pthread_mutex_lock(&mutex) != 0);
			pthread_mutex_lock(&mutex);
			mp[w]++;
			cnt++;
			w = "";
			pthread_mutex_unlock(&mutex);
		}
		c = fgetc(fp);
	}
	fclose(fp);

	return (void *)0;
}


int main(int argc, char *argv[])
{
	cnt = 0;
	pthread_t tid[100];
	pthread_mutex_init(&mutex, NULL);
	for (int i = 1; i < argc; i++)
		pthread_create(&tid[i], NULL, count, (void *)argv[i]);

	for (int i = 1; i < argc; i++)
		pthread_join(tid[i], NULL);
		
	pthread_mutex_destroy(&mutex);
	printf("total number of words: %d\n", cnt);

	vector<node> v;
	node tmp;
	for (auto i : mp){
		tmp.str = i.first;
		tmp.nu = i.second;
		v.push_back(tmp);
	}
	sort(v.begin(), v.end(), cmp);

	for (int i = 0; i <= v.size(); i++){
		cout << v[i].str << " " << v[i].nu << endl; 
	}				
}	
