/*
(spoc)基于“python, ruby, C, C++，LISP、JavaScript”等语言模拟实现Eisenberg同步算法
*/

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#define TNUM 5

using namespace std;

enum state {
	IDLE,
	WAITING,
	ACTIVE
};

int turn;
state flag[TNUM];
pthread_t threads[TNUM];

void*thread(void*args)
{
	int index;
	int temp_id = *(int*)args;
	while (1)
	{
		flag[temp_id] = WAITING;
		index = turn;
		while (index != temp_id)
		{
			if (flag[index] != IDLE)
				index = turn;
			else
				index = (index + 1) % TNUM;
		}
		flag[temp_id] = ACTIVE;
		index = 0;
		while (index < TNUM && (index == temp_id || flag[index] != ACTIVE))
			index++;
		if (index >= TNUM && (turn == temp_id || flag[turn] == IDLE))
		{
			break;
		}
	}
	turn = temp_id;
	index = (turn + 1) % TNUM;
	while (flag[index] == IDLE)
		index = (index + 1) % TNUM;
	turn = index;
	flag[temp_id] = IDLE;
	return NULL;

}

int main()
{
	int tr[TNUM];
	for (int i = 0; i < TNUM; i++)
	{
		flag[i] = IDLE;
		tr[i] = i;
	}
	for (int i = 0; i < TNUM; i++)
	{
		pthread_creat(&threads[i],NULL,thread,(void*)&tr[i]);
	}
	for (int i = 0; i < TNUM; i++)
	{
		pthread_join(threads[i],NULL);
	}

	system("pause");
	return 0;
}