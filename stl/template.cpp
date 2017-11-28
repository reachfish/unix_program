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
// template: __STL_NULL_TMPL_ARGS<>

#ifndef __STL_NULL_TMPL_ARGS 
#define __STL_NULL_TMPL_ARGS <>
#endif

template<class T>
struct template_foo_3{
	//friend bool operator==__STL_NULL_TMPL_ARGS (const template_foo_3&, const template_foo_3&);
	//friend bool operator<__STL_NULL_TMPL_ARGS (const template_foo_3&, const template_foo_3&);

	//展开后就变成了
	//friend bool operator==<> (const template_foo_3&, const template_foo_3&);
	//friend bool operator<<> (const template_foo_3&, const template_foo_3&);
	
	//写成这样是可以的
	//friend bool operator==<T> (const template_foo_3<T>&, const template_foo_3<T>&);
	//friend bool operator< <T> (const template_foo_3<T>&, const template_foo_3<T>&);
	
	//写成这样也是可以的
	//friend bool operator==<T> (const template_foo_3&, const template_foo_3&);
	//friend bool operator< <T> (const template_foo_3&, const template_foo_3&);
	
	//写成这样也是可以的
	//friend bool operator==<> (const template_foo_3&, const template_foo_3&);
	//friend bool operator< <> (const template_foo_3&, const template_foo_3&);
	
	//写成这样是不可以的
	//friend bool operator== (const template_foo_3&, const template_foo_3&);
	//friend bool operator< (const template_foo_3&, const template_foo_3&);
};
/*********************************************/
// template: __STL_TEMPLATE_NULL 展开为  template<>

#ifndef __STL_TEMPLATE_NULL 
#define __STL_TEMPLATE_NULL template<>
#endif

template<class T>
struct template_foo_4{
	void operator()() {
		std::cout<<"template_foo_4:"<<std::endl;
	}
};

// explicit specialization
__STL_TEMPLATE_NULL
struct template_foo_4<char>{
	void operator()() {
		std::cout<<"template_foo_4: template<char>"<<std::endl;
	}
};

void test4(){
	template_foo_4<int> t1;
	template_foo_4<char> t2;

	t1();
	t2();
};
/*********************************************/

int main(){
	test4();
	return 0;
}
