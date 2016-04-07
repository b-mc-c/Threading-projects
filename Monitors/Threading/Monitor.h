
#include "stdafx.h"
#include <iostream>
#include <SDL.h>			//SDL


using namespace std;



class MonitorBoundedBuffer
{
public :

	int n;
	string buf[5]; //an array of strings
	int front; //index of first full slot
	int rear; //index of the first empty slot
	int count; //number of full slots
	//rear == (front + count) & n
	SDL_sem* not_full = NULL; // signaled when count < n
	SDL_sem* not_empty = NULL; //signalled when count > 0

	MonitorBoundedBuffer()
	{
		n = 5;
		count = 0;
		front = 0; //index of first full slot
		rear = 0; //index of the first empty slot
		//Initialize semaphore
		not_full = SDL_CreateSemaphore(1);
		not_empty = SDL_CreateSemaphore(1);
	}
	

	void Deposit(string data)
	{
		while (count == n)
		{
			SDL_SemWait(not_full);
		}
		buf[rear] = data;
		rear = (rear + 1) % n;
		count++;
		SDL_SemPost(not_empty);
	}
	void Fetch(string &result)
	{
		while (count == 0)
		{
			SDL_SemWait(not_empty);
		}
		result = buf[front];
		front = (front + 1) % n;
		count--;
		SDL_SemPost(not_full);
	}
};