#include <iostream>
#include <DispatchQueue.hpp>
int main()
{
	DispatchQueue q(3);
	q.dispatch(
		[]{std::cout<<"i am 1\n";},
		[]{std::cout<<"i am 2\n";}
	);
	std::cout<<"hello world\n";
	q.dispatch([]{std::cout<<"i am 3\n";});
	int x;
	std::cin>>x;
	return 0;
}
