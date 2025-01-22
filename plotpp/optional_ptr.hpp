#pragma once

#include <memory>

/*
	A pointer type that takes posession of the memory if moved into the optional_ptr 
	or holds a non-owning reference/pointer otherwise
*/

template<typename T>
class optional_ptr {
public:
	using element_type = T;

	inline optional_ptr() 
		: _mem()
		, _ptr(nullptr) {}

    //inline optional_ptr(T& ref) 
	//	: _mem(std::make_shared<T>(ref))
	//	, _ptr(this->_mem.get()) {}
	
	inline optional_ptr(T&& ref) 
		: _mem(std::make_shared<T>(std::move(ref)))
		, _ptr(this->_mem.get()) {}

	// Constructor from raw pointer
    inline optional_ptr(T* ptr)
		: _mem()
		, _ptr(ptr) {}

    // Constructor from shared_ptr
    inline optional_ptr(std::shared_ptr<T> ptr)
		: _mem(std::move(ptr))
		, _ptr(this->_mem.get()) {}

	inline optional_ptr(const optional_ptr&) = default;
	inline optional_ptr& operator=(const optional_ptr&) = default;

    inline optional_ptr(optional_ptr&&) = default;
    inline optional_ptr& operator=(optional_ptr&&) = default;

    // Dereference operator
    inline T& operator*() const {return *_ptr;}

    // Arrow operator
    inline T* operator->() const {return _ptr;}

	inline T* get() const {return _ptr;}

	inline operator bool () const {return this->_ptr != nullptr;}

private:
	std::shared_ptr<T> _mem;
	T* _ptr = nullptr;
};


// Concept that checks for correct ways of constructing a smart pointer
template <typename T>
concept PtrOrMoved = 
    std::is_pointer_v<std::remove_reference_t<T>> ||                       					// Raw pointer
    std::is_rvalue_reference_v<T&&> ||              					// Rvalue reference
    std::is_same_v<std::remove_reference_t<T>, std::unique_ptr<typename T::element_type>> || // std::unique_ptr
    std::is_same_v<std::remove_reference_t<T>, std::shared_ptr<typename T::element_type>> || // std::shared_ptr
    std::is_same_v<std::remove_reference_t<T>, std::weak_ptr<typename T::element_type>> ||	// std::weak_ptr
	std::is_same_v<std::remove_reference_t<T>, optional_ptr<typename T::element_type>>;	// optional_ptr


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
struct remove_smart_ptr<optional_ptr<T>> {
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
struct remove_ptr<optional_ptr<T>> {
	using type = T;
};

// Convenience alias
template<typename T>
using remove_ptr_t = typename remove_ptr<T>::type;