#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& data)
{
	while (first != last && *first != data)
	{
		first++;
	}
	return first;
}

int main()
{
	const int arraySize = 8;
	int a[arraySize] = {1,2,3,4,5,6,7,8};
	vector<int> _vector(a, a + arraySize);
//	list<int> _list(a, a+arraySize);
	vector<int>::iterator vIter = find(_vector.begin(), _vector.end(), 4);
	if(vIter == _vector.end())
		cout<<"4 is not found"<<endl;
	else
		cout<<"found 4 "<<*vIter<<endl;

	return 0;
}