#pragma once

#include <memory>

/*
	A pointer type that takes posession of the memory if moved into the smartest_pointer 
	or holds a non-owning reference/pointer otherwise
*/

template<typename T>
class smartest_pointer {
public:
    inline smartest_pointer(T& ref) 
		: _mem()
		, _ptr(&ref) {}
	
	inline smartest_pointer(T&& ref) 
		: _mem(std::make_shared<T>(std::move(ref)))
		, _ptr(this->_mem.get()) {}
	
	// Constructor from raw pointer
    inline smartest_pointer(T* ptr)
		: _mem()
		, _ptr(ptr) {}

    // Constructor from shared_ptr
    inline smartest_pointer(std::shared_ptr<T> ptr)
		: _mem(std::move(ptr))
		, _ptr(this->_mem.get()) {}

	inline smartest_pointer(const smartest_pointer&) = default;
	inline smartest_pointer& operator=(const smartest_pointer&) = default;

    inline smartest_pointer(smartest_pointer&&) = default;
    inline smartest_pointer& operator=(smartest_pointer&&) = default;

    // Dereference operator
    inline T& operator*() const {return *_ptr;}

    // Arrow operator
    inline T* operator->() const {return _ptr;}

	inline T* get() const {return _ptr;}

private:
	std::shared_ptr<T> _mem;
	T* _ptr;
};


// Custom type trait to remove pointer types
template<typename T>
struct remove_smart_ptr {
	using type = T;
};

template<typename T>
struct remove_smart_ptr<std::unique_ptr<T>> {
	using type = T;
};

template<typename T>
struct remove_smart_ptr<std::shared_ptr<T>> {
	using type = T;
};

template<typename T>
struct remove_smart_ptr<std::weak_ptr<T>> {
	using type = T;
};

template<typename T>
struct remove_smart_ptr<smartest_pointer<T>> {
	using type = T;
};

// Convenience alias
template<typename T>
using remove_smart_ptr_t = typename remove_smart_ptr<T>::type;





// Custom type trait to remove pointer types
template<typename T>
struct remove_ptr {
	using type = std::remove_pointer_t<T>;
};

template<typename T>
struct remove_ptr<std::unique_ptr<T>> {
	using type = T;
};

template<typename T>
struct remove_ptr<std::shared_ptr<T>> {
	using type = T;
};

template<typename T>
struct remove_ptr<std::weak_ptr<T>> {
	using type = T;
};

template<typename T>
struct remove_ptr<smartest_pointer<T>> {
	using type = T;
};

// Convenience alias
template<typename T>
using remove_ptr_t = typename remove_ptr<T>::type;