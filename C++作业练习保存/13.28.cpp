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

using namespace std;
using namespace std::placeholders;

class TreeNode
{
public:
	TreeNode() :value(""), left(nullptr), right(nullptr) {};
	TreeNode(const TreeNode &a) :value(a.value), left(a.left), right(a.right) {};
	TreeNode &operator=(TreeNode &a) { value = a.value; left = a.left; right = a.right; return *this; };
private:
	string value;
	shared_ptr<TreeNode> left;
	shared_ptr<TreeNode> right;
};

void main()
{
	system("PAUSE");
	return;
}