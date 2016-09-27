//============================================================================
// Name        : main.cpp
// Author      : Rahman Salim Zengin
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "nulliter.hpp"


// The Universal Null Iterator
nltr::null_iterator<nullptr_t*> nulliter {nullptr};

template<typename InputIt, typename T>
InputIt my_find( InputIt first, InputIt last, const T& value ) {
	using namespace nltr;
	InputIt result = std::find(first, last, value);
//	return (result != last) ? result : make_null_iterator((nullptr_t*)nullptr);
	return (result != last) ? result : nulliter;
}

int main() {

	using namespace nltr;

	std::vector<int> dizi { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (int inx = 7; inx < 30; inx += 7) {
		std::cout << (inx % 15) << " is";
//		if (my_find(dizi.begin(), dizi.end(), (inx % 15)) == make_null_iterator((nullptr_t*)nullptr))
		if (my_find(dizi.begin(), dizi.end(), (inx % 15)) == nulliter)
			std::cout << " not";
		std::cout << " found in dizi" << std::endl;
	}

	std::cout << std::endl;

	const size_t size = 10;
	int dizgi[size] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (int inx = 7; inx < 30; inx += 7) {
		std::cout << (inx % 15) << " is";
//		if (my_find(&dizgi[0], &dizgi[size], (inx % 15)) == make_null_iterator((nullptr_t*)nullptr))
		if (my_find(&dizgi[0], &dizgi[size], (inx % 15)) == nulliter)
			std::cout << " not";
		std::cout << " found in dizgi" << std::endl;
	}



	std::copy(dizi.begin(), dizi.end(), make_null_iterator(dizi.begin()));
	std::cout << std::endl;
	std::fill_n(make_null_iterator(dizi.begin()), 10, 100);
	std::cout << std::endl;
	std::copy_n(make_null_iterator(dizi.begin()), 10, make_null_iterator(dizi.begin()));
	std::cout << std::endl;
	std::copy_n(dizi.begin(), 10, make_null_iterator(dizi.begin()));

	std::cout << "\n----------" << std::endl;

	std::copy(&dizgi[0], &dizgi[size], make_null_iterator(dizi.begin()));
	std::cout << std::endl;
	std::fill_n(make_null_iterator(&dizgi[0]), 10, 100);
	std::cout << std::endl;
	std::copy_n(make_null_iterator(&dizgi[0]), 10, make_null_iterator(&dizgi[0]));
	std::cout << std::endl;
	std::copy_n(&dizgi[0], 10, make_null_iterator(&dizgi[0]));


	return 0;
}
