//简单仿函数的应用
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>	//accumulate
#include <deque>
#include <iterator>

using namespace std;

template<class T>
struct MAX
{
	T operator()(const T& x, const T& y){return (x < y) ? y : x;}
};

template<class T>
struct ADD
{
	T operator()(const T& x, const T& y){return x + y;}
};

template<class T>
T funMax(int a, int b, MAX<T> _max)
{
	return _max(a,b);
}

template<class T>
T funcAdd(int a, int b, ADD<T> _add)
{
	return _add(a,b);
}


int main()
{
	plus<int> _plus; //STL内建仿函数
	cout<<_plus(2,5)<<endl;
	int a[] = {1,2,3,5,6,4};
	vector<int> _vetor(a,a+6);
	copy(_vetor.begin(),_vetor.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	accumulate(_vetor.begin(),_vetor.end(),5,plus<int>());
	copy(_vetor.begin(),_vetor.end(),ostream_iterator<int>(cout," "));
	cout<<endl;

	MAX<int> _max;
	ADD<int> _add;
	cout<<funMax<int>(5,3,_max)<<endl;
	cout<<MAX<int>()(8,12)<<endl;
	cout<<_max(5,6)<<endl;
	cout<<ADD<int>()(5,6)<<endl;
	cout<<_add(2,3)<<endl;
	cout<<funcAdd(2,9,_add)<<endl;

	//接配器
	deque<int> _deque(a,a+6);
	ostream_iterator<int> outLine(cout," ");
	copy(_deque.begin(),_deque.end(),outLine);
	cout<<endl;

	copy(a+1,a+2,front_inserter(_deque));
	copy(_deque.begin(),_deque.end(),outLine);
	cout<<endl;

	copy(a+3,a+4,back_inserter(_deque));
	copy(_deque.begin(),_deque.end(),outLine);
	cout<<endl;

	deque<int>::iterator iter  = find(_deque.begin(),_deque.end(),5);
	copy(a+1,a+4,inserter(_deque,iter));
	copy(_deque.begin(),_deque.end(),outLine);
	cout<<endl;

	copy(_deque.rbegin(),_deque.rend(),outLine);
	cout<<endl;

	return EXIT_SUCCESS;
}