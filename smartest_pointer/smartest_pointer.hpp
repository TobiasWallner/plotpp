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

    // Constructor from unique_ptr
    inline smartest_pointer(std::unique_ptr<T>&& ptr) 
		: _mem(std::shared_ptr<T>(std::move(ptr)))
		, _ptr(this->_mem.get()) {}

    // Constructor from shared_ptr
    inline smartest_pointer(std::shared_ptr<T> ptr)
		: _mem(std::move(ptr))
		, _ptr(this->_mem.get()) {}

	inline smartest_pointer(const smartest_pointer&) = default;
	inline smartest_pointer& operator=(const smartest_pointer&) = default;

    inline smartest_pointer(smartest_pointer&&) = default;
    inline smartest_pointer& operator=(smartest_pointer&&) = default;

    // Dereference operator
    inline auto& operator*() const {return *_ptr;}

    // Arrow operator
    inline auto* operator->() const {return _ptr;}

private:
	std::shared_ptr<T> _mem;
	T* _ptr;
};
