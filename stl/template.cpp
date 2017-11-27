#include <iostream>

/*********************************************/
// template: 一般化和特殊化设计
//
template<class I, class O>
struct template_foo_1{
	template_foo_1(){
		std::cout<<"<class I, class O>"<<std::endl;
	}
};

template<class T>
struct template_foo_1<T*, T*>{
	template_foo_1(){
		std::cout<<"<T*, T*>"<<std::endl;
	}
};

template<class T>
struct template_foo_1<const T*, T*>{
	template_foo_1(){
		std::cout<<"<const T*, T*>"<<std::endl;
	}
};

void test1(){
	template_foo_1<int, int> foo1;
	template_foo_1<int*, int*> foo2;
	template_foo_1<const int*, int*> foo3;
}

/*********************************************/
// template: template 内部还可以有template

template<class T>
struct template_foo_2{

	typedef T value_type;
	typedef value_type* iterator;

	template<class I>
	void print(iterator position, I first, I end){
		std::cout<<"template_foo_2::print:"<<first<<","<<end<<std::endl;
	}
};

void test2(){
	template_foo_2<int> foo;
	template_foo_2<int>::iterator it;

	foo.print(it, 10, 100);
}
/*********************************************/

int main(){
	test2();
	return 0;
}
