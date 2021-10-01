#include <iostream>
#include <iterator>
#include <cstddef>

#include "dl_list.h"
using namespace std;

int main()
{
	int four = 4;
	dl_list<int> list;
	dl_list<int> secondList = {1, 2, 3};
	cout << secondList << endl;
	
	list.push_front(four);
	list.push_back(5);
	list.push_back(5);
	list.push_front(3);

	cout << list << endl;

	//list.append(secondList);

	/*dl_list<int> third;
	
	third = secondList;*/

	//third.front() = 3;
	
	cout << secondList << endl;

	cout << secondList.front() << endl;
	
	//cout << third << endl;

	//cout << third.front() << endl;


	
	for(auto element : list)
	{
		element+=1;
		cout << element;
	}
	cout << '\n' << list << endl;
	
	/*cout << list << endl;
	list.insert(2, 2);
	cout << list << endl;

	cout << list[2] << endl;
	list[2] = 3;
	cout << list[2] << endl;
	cout << list << endl;*/
}
