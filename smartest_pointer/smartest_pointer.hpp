#include <variant>

template<typename T>
class smartest_pointer;

template<typename T>
class smartest_pointer {
public:
    smartest_pointer(T& ref) : pointer_(&ref) {}
	
	//TODO: small object optimisation for up to 64 byte ?
	smartest_pointer(T&& ref) : pointer_(std::make_unique<T>(std::move(ref))) {}
	
	// Constructor from raw pointer
    smartest_pointer(T* ptr) : pointer_(ptr) {}

    // Constructor from unique_ptr
    smartest_pointer(std::unique_ptr<T>&& ptr) : pointer_(std::shared_ptr<T>(std::move(ptr))) {}

    // Constructor from shared_ptr
    smartest_pointer(std::shared_ptr<T> ptr) : pointer_(std::move(ptr)) {}

	smartest_pointer(const smartest_pointer&) = default;
	smartest_pointer& operator=(const smartest_pointer&) = default;

    smartest_pointer(smartest_pointer&&) = default;
    smartest_pointer& operator=(smartest_pointer&&) = default;

    // Dereference operator
    T& operator*() const {return *getPointer();}

    // Arrow operator
    T* operator->() const {return getPointer();}

    

private:

	// TODO: Remove the variant by making a template specialisation for each element
    std::variant<T*, std::shared_ptr<T>> pointer_;

    // Helper function to retrieve the raw pointer from the variant
	T* getPointer() const {
        switch (pointer_.index()) {
            case 0:  // T* (raw pointer)
                return *std::get_if<T*>(&pointer_);
            case 1:  // std::unique_ptr<T>
                return std::get_if<std::shared_ptr<T>>(&pointer_)->get();
            default:
                return nullptr;  // Should never happen if the variant is properly initialized
        }
    }
};