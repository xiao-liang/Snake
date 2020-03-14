#include <iostream>
#include <stack>

struct Coordinate {
	int cor_x;
	int cor_y;
};

class Apple {
private:
	Coordinate position_;
	char icon_;
public:
	Apple();
	const Coordinate & get_position() const {
		return position_;
	}
};

int main()
{
	//Coordinate position = Coordinate({1,2});
	//Apple apple;
	//apple.
	////std::cout<< "Address: " << &test << std::endl;
	////std::cout << "side: " << sizeof(test) << std::endl;
	//std::cout << "cor_x: " << test.cor_x << std::endl;
	//std::cout << "cor_y: " << test.cor_x << std::endl;
	//return 0;

	std::stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	Coordinate a{ 1,2};
	Coordinate b{ 1,2 };

	const Coordinate& x = a;
	const Coordinate& y = b;
	
	
	//std::cout << "mystack.top() is now " << mystack.top() << '\n';
	std::cout << (a == b)  << '\n';

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
