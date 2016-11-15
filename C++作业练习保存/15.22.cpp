// test.cpp : 定义控制台应用程序的入口点。
//
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
using namespace std;
using namespace std::placeholders;

class Figure
{
public:
	Figure(double, double);

protected:
	double xSize, ySize;
};

class Figure_2D :public Figure
{
public:
	Figure_2D(double, double);
	virtual double area() = 0;
	virtual double pcrimeter() = 0;
};

class Figure_3D :public Figure{
public:
	Figure_3D(double, double, double);
	virtual double cubage() = 0;
protected:
	double zSize;
};



class Rectangle : public Figure_2D{
public:
	Rectangle(double, double);
	virtual double area();
	virtual double perimeter();
};

class Circle :public Figure_2D
{
	Circle(double, double);
	virtual double area();
	virtual double perimeter();
};

class Cone :public Figure_3D
{
public:
	Cone(double, double, double);
	virtual double cubage();
};

void main()
{

	system("PAUSE");
	return;
}