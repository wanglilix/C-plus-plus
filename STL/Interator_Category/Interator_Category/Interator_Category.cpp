/*
traits应用之迭代器类型判断
*/
#include <iostream>

using namespace std;

struct Input_Interator_tag{};
struct Output_Interator_tag{};
struct Forward_Interator_tag : public Input_Interator_tag{};
struct Bidirect_Interator_tag : public Forward_Interator_tag{};
struct Random_Interator_tag : public Forward_Interator_tag{};


template<typename T>
struct Inter_type_traits
{
	//根据类型T里定义的类型决定萃取出哪一个类型
	typedef typename T :: Interator_tag Interator_category;
};

//针对原生指针的偏特化
template<typename T>
struct Inter_type_traits<T*>
{
	typedef Random_Interator_tag Interator_category;
};

template<typename T>
struct Inter_type_traits<const T*>
{
	typedef Random_Interator_tag Interator_category;
};

template<typename InputInterator, typename DistanceN>
inline void _distance(InputInterator& I, DistanceN n, Input_Interator_tag)
{
	cout<<"InputInterator"<<endl;
}

template<typename OutputInterator, typename DistanceN>
inline void _distance(OutputInterator& O, DistanceN n, Output_Interator_tag)
{
	cout<<"OutputInterator"<<endl;
}

template<typename ForwardInterator, typename DistanceN>
inline void _distance(ForwardInterator& F, DistanceN n, Forward_Interator_tag)
{
	cout<<"forwardInterator"<<endl;
}

template<typename BidirectInterator, typename DistanceN>
inline void _distance(BidirectInterator& B, DistanceN n, Bidirect_Interator_tag)
{
	cout<<"BidirectInterator"<<endl;
}

template<typename RandomInterator, typename DistanceN>
inline void _distance(RandomInterator& O, DistanceN n, Random_Interator_tag)
{
	cout<<"RandomInterator"<<endl;
}

template<typename InputInterator, typename DistanceN>
inline void distance(InputInterator& I, DistanceN n)
{
	_distance(I,n,Inter_type_traits<InputInterator>::Interator_category());
}

class InputInter
{
public:
	typedef Input_Interator_tag Interator_tag;
};
class OutputInter
{
public:
	typedef Output_Interator_tag Interator_tag;
};
class FowardInter
{
public:
	typedef Forward_Interator_tag Interator_tag;
};
class BidirectInter
{
public:
	typedef Bidirect_Interator_tag Interator_tag;
};

int main()
{
	InputInter i;
	int a = 6;
	InputInter* ii;
	int* iii;
	OutputInter o;
	FowardInter f;
	BidirectInter b;
	distance(i,a);
	distance(ii,a);
	distance(iii,a);
	distance(o,a);
	distance(f,a);
	distance(b,a);
	return 0;
}