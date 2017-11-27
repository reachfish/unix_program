#include <iostream>

/*********************************************/
// template: 一般化和特殊化设计
//
template<class I, class O>
struct template_foo{
	template_foo(){
		std::cout<<"<class I, class O>"<<std::endl;
	}
};

template<class T>
struct template_foo<T*, T*>{
	template_foo(){
		std::cout<<"<T*, T*>"<<std::endl;
	}
};

template<class T>
struct template_foo<const T*, T*>{
	template_foo(){
		std::cout<<"<const T*, T*>"<<std::endl;
	}
};

void test1(){
	template_foo<int, int> foo1;
	template_foo<int*, int*> foo2;
	template_foo<const int*, int*> foo3;
}

/*********************************************/
int main(){
	test1();
	return 0;
}
