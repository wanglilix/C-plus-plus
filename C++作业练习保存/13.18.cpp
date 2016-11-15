// test.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <iostream>
#include <list> 
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <forward_list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <time.h>
//#include <initalizer_list.h>
#include <stdexcept>
#include <new>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace std::placeholders;

class Employee
{
public:
	Employee() :name(""), number(n++) {};
	Employee(string str) :name(str), number(n++) {};
	Employee(Employee & a) :name(a.name), number(n++) {};
	Employee & operator= (Employee &a) { name = a.name; number = n++; return *this; };
public:
	const string& get_name() { return name; };
	const int& get_number() { return number; };
private:
	string name;
	int number;
private:
	static int n;
};
int Employee::n = 0;

void main()
{
	Employee person1;
	Employee person2(person1);
	Employee person3;
	person3 = person2;
	system("PAUSE");
	return;
}