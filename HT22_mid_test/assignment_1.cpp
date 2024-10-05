#include <ostream>
#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>

template <typename T>
class Stack {
private:
    std::vector<T> st {};

public:
	template <typename... Args>
	Stack(Args&&... args) {
		(st.emplace_back(std::forward<Args>(args)), ...);
	}

	Stack& operator <<(T&& element) {
		st.emplace_back(std::forward<T>(element));
		return *this;
	}

    Stack& operator >>(T& element) {
        if (st.empty()) {
            std::cerr << "Stack is empty" << '\n';
            return *this;
        }

        element = std::move(st.back());
        st.pop_back();
		return *this;
    }

    bool operator ==(const T&& element) {
        return (*st.rbegin()) == element;
    }

    friend std::ostream& operator << (std::ostream& os, const Stack& stack) {
        for (auto it = stack.st.rbegin(); it != stack.st.rend(); ++it) {
            os << *it << " ";
        }
		return os;
    }

    bool is_empty() const {
        return st.empty();
    }
    

};
// Originally taken from: 2022-03-17 Assignment #4
// Modified so that it doesn't require type converting operators.

int main()
{
    {
	Stack<int> st { 6, 5, 4 };

	// 4 should be at the top of the stack
	assert( st == 4 );
	
	// pushing 3, 2 and 1 to the stack
	st << 3 << 2 << 1;

	// now 1 should be at the top
	assert( st == 1 );

	std::ostringstream oss { };
	oss << st;
	
	assert( oss.str() == "1 2 3 4 5 6 ");

	// popping into a, b and c as a chained operator call.
	int a, b, c;
	st >> a >> b >> c;

	assert( a == 1 );
	assert( b == 2 );
	assert( c == 3 );

	// pop the values one by one
	int i { 4 };
	while (st.is_empty())
	{
	    int x;
	    st >> x;

	    assert(x == i);
	    ++i;
	}
    }


    {
	Stack<std::string> st { "f", "e", "d" };

	assert( st == "d" );
        
	st << "c" << "b" << "a";
        
	assert( st == "a" );
	
	std::ostringstream oss { };
	oss << st;
	
	assert( oss.str() == "a b c d e f ");

	// popping into a, b and c as a chained operator call.
        std::string a, b, c;
	st >> a >> b >> c;

	assert( a == "a" );
	assert( b == "b" );
	assert( c == "c" );
    }
}