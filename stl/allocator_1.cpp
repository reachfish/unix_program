#include <stddef.h>
#include <stdlib.h>
#include <limit.h>
#include <new>
#include <iostream>

/**
 * allocator: 空间配置器，注意不一定是内存配置器，allocator也可以把数据放到硬盘等中
 */

/*
 * 标准接口：
 * allocator::value_type
 * allocator::pointer
 * allocator::const_pointer
 * allocator::reference
 * allocator::const_reference
 * allocator::size_type
 * allocator::difference_type
 */

/*********************************************/

template<class T>
inline T* _allocate(ptrdiff_t size, T*){
	set_new_handler(0);
	T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
	if (tmp == 0) {
		std::cerr << "out of memory" << std::endl;
		exit(1);
	}
	return tmp;
}

template <class T>
inline void _deallocate(T* buffer){
	::operator delete(buffer);
}

template <class T1, class T2>
inline void _construct(T1* p, const T2& value){
	new(p) T1(value); // placement new. invoke ctor of T1.
}

template <class T>
inline void _destroy(T* ptr){
	ptr->~T();
}

template <class T>
class allocator {
	public:
		typedef Tvalue_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_tdifference_type;

		//rebind allocator of type U
		template <class U>
		struct rebind {
			typedef allocator<U> other;
		};
};
/*********************************************/

int main(){
	return 0;
}
