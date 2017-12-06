#include <iostream>
#include <stdlib.h>

struct A{
	int a;
	int b;
	int c;
	char d;
};

int main(){
	A* head = (A*)malloc(157);
	void* tail = head + 1;
	long ihead = (long)head;
	long itail = (long)tail;
	std::cout<<"head: "<<head<<", tail: "<<tail<<std::endl;
	std::cout<<ihead%sizeof(struct A)<<","<<itail%sizeof(struct A)<<std::endl;
	std::cout<<itail - ihead<<", "<<sizeof(struct A)<<std::endl;

	return 0;
}
