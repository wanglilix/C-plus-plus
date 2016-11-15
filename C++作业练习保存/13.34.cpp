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

class Message;
class Folder
{
public:
	void addMsg(Message*);
	void remMsg(Message*);
private:
	set<Message*> messages;
};
void Folder::addMsg(Message* msg)
{
	messages.insert(msg);
}
void Folder::remMsg(Message* msg)
{
	messages.erase(msg);
}
///////////////////////////////



class Message
{
	friend class Folder;
	friend void swap(Message &, Message &);
public:
	explicit Message(const string &str = "") :contents(str) {};
	Message(const Message&);
	Message &operator=(const Message&);
	~Message();

	void save(Folder &);
	void remove(Folder &);
private:
	string contents;
	set<Folder*> folders;
	void add_to_Folders(const Message &);
	void remove_from_Folders();
};

Message::Message(const Message& m) :contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}
Message& Message::operator=(const Message& rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}
Message::~Message()
{
	remove_from_Folders();
}
void Message::save(Folder & f)
{
	folders.insert(&f);
	f.addMsg(this);
}
void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
	for (auto f : m.folders)
		f->addMsg(this);
}
void Message::remove_from_Folders()
{
	for (auto f : folders)
	{
		f->remMsg(this);
	}
}

void swap(Message &lhs, Message &rhs)
{
	using std::swap;
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	swap(lhs.contents, rhs.contents);
	swap(lhs.folders, rhs.folders);
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}

///////////////////////////////////////////////////////////////////////////

void main()
{
	Folder f1, f2, f3;
	Message m1, m2, m3;
	m1.save(f1);

	system("PAUSE");
	return;
}