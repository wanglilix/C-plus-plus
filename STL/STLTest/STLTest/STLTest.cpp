#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

int main()
{
	vector<string> _vect;
	string temp;
	while(getline(cin, temp))
	{
		_vect.push_back(temp);
		sort(_vect.begin(),_vect.end(),greater<string>());
		copy(_vect.begin(),_vect.end(),ostream_iterator<string>(cout,"\n"));
	}

	return 0;
}