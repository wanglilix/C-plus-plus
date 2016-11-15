#include <iostream>

//�����ʾ��ٵ���
struct _true_type{};
struct _false_type{};


template<typename T>
struct type_traits
{
	//��������T���涨��_bool_type�������о����ػ�������������ʲô
	typedef typename T :: _bool_type _Iscopiable;
};

template<>
struct type_traits<int>
{
	typedef _true_type _Iscopiable;
};

template<>
struct type_traits<char>
{
	typedef _false_type _Iscopiable;
};

//type_traits��ƫ�ػ��汾
template<typename T>
struct type_traits<T*>
{
	typedef _false_type _Iscopiable;
};

struct Sahpe{
	typedef _true_type _bool_type;
};

struct Square
{
	typedef _false_type _bool_type;
};

//�Զ������͵��ػ��汾
// template<>
// struct type_traits<Sahpe>
// {
// 	typedef _true_type _Iscopiable;
// };

template<class T>
void doSomething_aux(T& t, _true_type)
{
	std::cout<<"copibale!"<<std::endl;
}

template<class T>
void doSomething_aux(T& t, _false_type)
{
	std::cout<<"noncopibale!"<<std::endl;
}

template<class T>
void doSomething(T& t)
{
	//typedef typename T::copiable copiable;
	typedef typename type_traits<T>::_Iscopiable IsCopiable;
	doSomething_aux(t, IsCopiable());
}

int main()
{

	int a;
	char c;
	Sahpe s;
	Sahpe* _ps;
	Square sq;
	//doSomething<_true_type>(_true_type());
	doSomething(a);
	doSomething(c);
	doSomething(s);
	doSomething(_ps);
	doSomething(sq);
	return 0;
}