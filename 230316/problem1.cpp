#include <string>
#include <cassert>
#include <iostream>

// Implement Shared_Pointer here
template <typename T>
class Shared_Pointer {
public:
    // initial pointer is important.
    T* pointer = nullptr;
    size_t* cnt_pointer = nullptr;

    Shared_Pointer() = default;

    Shared_Pointer(T* ori_pointer) : pointer(ori_pointer), cnt_pointer(new size_t(1)) {}

    Shared_Pointer(const Shared_Pointer& ori) {
        if (ori.pointer == pointer) return;
        
        pointer = ori.pointer;
        cnt_pointer = ori.cnt_pointer;
        (*cnt_pointer)++;
    }

    Shared_Pointer(Shared_Pointer&& ori) {
       if (ori.pointer == pointer) return;

        // I didn't initial cnt_pointer corretly, and which may cause cnt_pointer point some 
        // unlegal address
        std::swap(pointer, ori.pointer);
        std::swap(cnt_pointer, ori.cnt_pointer); 
    }

    Shared_Pointer<T>& operator=(const Shared_Pointer& ori) {
        if (ori.pointer == pointer) return *this;

        return *this = std::move(Shared_Pointer<T>{ori});
    }

    Shared_Pointer<T>& operator=(Shared_Pointer&& ori) {
        if (ori.pointer == pointer) return *this;

        std::swap(pointer, ori.pointer);
        std::swap(cnt_pointer, ori.cnt_pointer);

        return *this; 
    }

    T& operator*() const {
        return *pointer;
    }
    
    T* operator->() const {
        return pointer;
    }
    

    size_t count() const {
        return *cnt_pointer;
    }

    ~Shared_Pointer() {
        if (cnt_pointer != nullptr) {
            (*cnt_pointer)--;
            if ((*cnt_pointer) <= 0) {
                delete cnt_pointer;
                if (pointer != nullptr)
                    delete pointer;
            }
        }
    }
};

template <typename T, typename... Args>
Shared_Pointer<T> make_shared(Args... args) {
    Shared_Pointer<T> tmp {new T(args...)};
    return tmp;
}

int main()
{
    // Check that the behaviour of default initialized shared pointers is correct
    Shared_Pointer<int> ptr0;
    assert( ptr0.count() == 0 );

    // General functionality test
    {
        auto ptr1 = make_shared<std::string>(3, ' ');

        // Check that operator* works
        assert( *ptr1 == "   " );

        // Check that we have one reference to this object
        assert( ptr1.count() == 1 );

        // Check that operator-> works
        assert( ptr1->size() == 3 );

        // Temporarily add one more reference
        {
            // Testing copy constructor
            auto ptr2 = ptr1;
            assert( ptr2.count() == 2 );

            // Modify the underlying data
            *ptr2 = std::string(4, '+');
        }

        // The underlying data should have changed
        assert( *ptr1 == "++++" );
        assert( ptr1.count() == 1 );
    }

    // Test assignments
    {
        Shared_Pointer<int> ptr3 { make_shared<int>(5) };
        assert( *ptr3 == 5 );
        assert( ptr3.count() == 1 );

        // Test copy assignment
        Shared_Pointer<int> ptr4;
        ptr4 = ptr3;

        assert( ptr3.count() == ptr4.count() );
        assert( ptr3.count() == 2 );
        assert( *ptr3 == *ptr4 );

        Shared_Pointer<int> ptr5 { make_shared<int>(6) };

        // Test move assignment
        ptr5 = std::move(ptr4);

        assert( ptr5.count() == ptr3.count() );
        assert( ptr5.count() == 2 );
    }

    // Test that const works properly
    Shared_Pointer<std::string> const ptr6 { make_shared<std::string>("abc") };
    assert( *ptr6 == "abc" );
    assert( ptr6->size() == 3 );
    assert( ptr6.count() == 1 );
}