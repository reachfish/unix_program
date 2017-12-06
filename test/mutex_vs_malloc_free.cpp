#include <map>
#include <list>
#include <atomic> 
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <assert.h>

using namespace std;

class MediaMutex
{
public:
	explicit MediaMutex()
	{
		pthread_mutexattr_t mutexAttr;
		pthread_mutexattr_init(&mutexAttr);
		pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_RECURSIVE); //同线程可多次进入
		pthread_mutex_init(&m_mutex, &mutexAttr);
		pthread_mutexattr_destroy(&mutexAttr);
	}

	~MediaMutex()
	{
		pthread_mutex_destroy(&m_mutex);
	}

	void Lock()
	{
		pthread_mutex_lock(&m_mutex);
	}

	void Unlock()
	{
		pthread_mutex_unlock(&m_mutex);
	}

private:
	MediaMutex(const MediaMutex& /*other*/)
	{
		m_mutex = PTHREAD_MUTEX_INITIALIZER;
	}

	pthread_mutex_t m_mutex;
};

const int THREAD_NUM = 10;
const size_t BUFF_SIZE = 0x10000;
std::atomic_int gCount(0);
const size_t MAX_COUNT = 10000000;
const size_t INC_COUNT = 1000;

static MediaMutex gMutex;
static std::map<size_t, std::list<void*>> gM;

void _pause(){
	//usleep(1);
	for(size_t i = 0; i < 10; i++){
	}
}

void *func_1(void*){
	void* p;
	while(true){
		p = NULL;

		gMutex.Lock();

		if(gCount++ > MAX_COUNT){
			gMutex.Unlock();
			pthread_exit(NULL);
		}

		std::list<void*> &lst = gM[BUFF_SIZE];
		if(!lst.empty()){
			p = lst.back();
			lst.pop_back();
		}
		else{
			p = NULL;
		}

		gMutex.Unlock();

		if(!p){
			p = (void*)malloc(BUFF_SIZE);
		}

		_pause();

		gMutex.Lock();
		std::list<void*> &lst2 = gM[BUFF_SIZE];
		if(lst2.size() < 8){
			lst2.push_back(p);
			p = NULL;
		}
		gMutex.Unlock();

		if(p){
			free(p);
		}
	}

	return NULL;
}

void *func_2(void*){
	while(true){
		if(gCount++ > MAX_COUNT){
			pthread_exit(NULL);
		}

		void *p = (void*)malloc(BUFF_SIZE);
		_pause();
		free(p);
	}

	return NULL;
}

int main(){
	pthread_t threads[THREAD_NUM];

	pthread_setconcurrency(20);
	for(int i=0; i<THREAD_NUM; i++){
		pthread_create(threads + i, NULL, func_1, &i);
	}

	for(int i=0; i<THREAD_NUM; i++){
		pthread_join(threads[i], NULL);
	}

	return 0;
}

