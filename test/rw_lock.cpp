#include  <iostream>
#include <pthread.h>
#include <unistd.h>
#include <atomic>

class RWLock
{
public:
	RWLock() : m_lock()
	{
		pthread_rwlock_init(&m_lock, 0);
	}

	~RWLock()
	{
		pthread_rwlock_destroy(&m_lock);
	}

	void acquireLockExclusive()
	{
		pthread_rwlock_wrlock(&m_lock);
	}

	void releaseLockExclusive()
	{
		pthread_rwlock_unlock(&m_lock);
	}

	void rcquireLockShared()
	{
		pthread_rwlock_rdlock(&m_lock);
	}

	void releaseLockShared()
	{
		pthread_rwlock_unlock(&m_lock);
	}

private:
	pthread_rwlock_t m_lock;
};

class ReadLockScoped
{
public:
	explicit ReadLockScoped(RWLock& rwLock)
	: m_rwLock(rwLock)
	{
		m_rwLock.rcquireLockShared();
	}

	~ReadLockScoped()
	{
		m_rwLock.releaseLockShared();
	}

private:
	RWLock& m_rwLock;
};

class WriteLockScoped
{
public:
	explicit WriteLockScoped(RWLock& rwLock)
	: m_rwLock(rwLock) 
	{
		m_rwLock.acquireLockExclusive();
	}

	~WriteLockScoped()
	{
		m_rwLock.releaseLockExclusive();
	}

private:
	RWLock& m_rwLock;
};

RWLock gLock;

void test2(){
	std::cout<<"test2:1"<<std::endl;
	ReadLockScoped readscope(gLock);
	std::cout<<"test2:2"<<std::endl;
	//WriteLockScoped writescope(gLock);
}

void test1(){
	std::cout<<"test1:1"<<std::endl;
	WriteLockScoped writescope(gLock);
	std::cout<<"test1:2"<<std::endl;
	//test2();
	std::cout<<"test1:3"<<std::endl;

	//static unsigned int i = 0;
	//if(i++% 10 == 0)
	{
		//std::cout<<pthread_self()<<" write"<<std::endl;
	}
}

void wait(unsigned int count=10)
{
	usleep(count);
	for(int i=0; i< 1000; i++)
		;
}

void write_func()
{
	std::cout<<"---------------------"<<std::endl;
	std::cout<<"write_func:1"<<std::endl;
	WriteLockScoped writescope(gLock);
	std::cout<<"write_func:2"<<std::endl;
	test1();
	std::cout<<"write_func:3"<<std::endl;

	//wait();
}

void *write_test(void*){
	while(true)
	{
		write_func();
	}
}

void read_func()
{
	ReadLockScoped readscope(gLock);

	wait(1000);

	static std::atomic_int i(0);
	if(i++ % 10000 == 0)
	{
		std::cout<<pthread_self()<<" read"<<std::endl;
		if(i >= 10000 * 5){
			pthread_exit(NULL);
		}
	}
}

void *read_test(void*)
{
	//usleep(1000);
	sleep(10);
	while(true)
	{
		read_func();
	}
}

const int THREAD_NUM = 1;

void func()
{
	WriteLockScoped w1(gLock);
	WriteLockScoped w2(gLock);
	ReadLockScoped r1(gLock);

	WriteLockScoped w3(gLock);
	WriteLockScoped w4(gLock);
	ReadLockScoped r2(gLock);

	WriteLockScoped w5(gLock);
	WriteLockScoped w6(gLock);
	ReadLockScoped r3(gLock);

	WriteLockScoped w7(gLock);
	WriteLockScoped w8(gLock);
	ReadLockScoped r4(gLock);

	std::cout<<"ok"<<std::endl;
	exit(0);
}

void write_test_2_2(pthread_rwlock_t* plock)
{
	//pthread_rwlock_rdlock(plock);
	std::cout<<"Hello World"<<std::endl;
	//pthread_rwlock_unlock(plock);
}

void write_test_2_1(pthread_rwlock_t* plock)
{
	pthread_rwlock_wrlock(plock);
	pthread_rwlock_wrlock(plock);
	write_test_2_2(plock);
	pthread_rwlock_unlock(plock);
	pthread_rwlock_unlock(plock);
}

void write_test_2()
{
	pthread_rwlock_t lock;
	pthread_rwlock_init(&lock, NULL);

	for (int i = 0; i< 10; i++)
	{
		std::cout<<"----------------"<<std::endl;
		write_test_2_1(&lock);
	}
}

int main(){

	write_test(NULL);
	//write_test_2();
	

	//func();

	/*
	pthread_t tids[THREAD_NUM];	

	pthread_setconcurrency(20);
	pthread_create(tids + 0, NULL, write_test, NULL);

	for(int i=1; i<THREAD_NUM; i++)
	{
		pthread_create(tids + i, NULL, read_test, NULL);
	}

	for(int i=0; i<THREAD_NUM; i++){
		pthread_join(tids[i], NULL);
	}
	*/

	return 0;
}
