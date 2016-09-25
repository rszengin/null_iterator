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
#include <string>
#include <functional>
#include <iterator>
#include "nulliter.hpp"


template<typename InputIt, typename T>
InputIt my_find( InputIt first, InputIt last, const T& value ) {

	using namespace nltr;

	InputIt result = std::find(first, last, value);
	InputIt return_value;

//	return_value = result != last ? result : InputIt {} ;
//	return_value = result != last ? result : null_iterator<InputIt> {};
//	return_value = result != last ? result : static_cast<InputIt>(null_iterator<InputIt> {});
//	return_value = result != last ? result : make_null_iterator(result);
	return_value = result != last ? result : nulliter;

	return return_value;
}

int main() {

	using namespace nltr;

	int dizgi[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> dizi { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (int inx = 0; inx < 20; inx += 3) {
		if (my_find(dizi.begin(), dizi.end(), inx) == nulliter) {
			std::cout << inx << " is not found in dizi" << std::endl;
		}
		else {
			std::cout << inx << " is found in dizi" << std::endl;
		}

		if (nulliter == my_find(&dizgi[0], &dizgi[(sizeof(dizgi) / sizeof(dizgi[0]))], inx)) {
			std::cout << inx << " is not found in dizgi" << std::endl;
		}
		else {
			std::cout << inx << " is found in dizgi" << std::endl;
		}
	}


	std::copy(dizi.begin(), dizi.end(), make_null_iterator(dizi.begin()));
	std::cout << std::endl;
	std::fill_n(make_null_iterator(dizi.begin()), 10, 100);
	std::cout << std::endl;
	// Because source and target is same doesnt run any operations
	std::copy_n(make_null_iterator(dizi.begin()), 10, make_null_iterator(dizi.begin()));
	std::copy_n(dizi.begin(), 10, make_null_iterator(dizi.begin()));
	std::cout << std::endl;

	std::copy(&dizgi[0], &dizgi[(sizeof(dizgi) / sizeof(dizgi[0]))], make_null_iterator(dizi.begin()));
	std::cout << std::endl;
	std::fill_n(make_null_iterator(&dizgi[0]), 10, 100);
	std::cout << std::endl;
	// Because source and target is same doesnt run any operations
	std::copy_n(make_null_iterator(&dizgi[0]), 10, make_null_iterator(&dizgi[0]));
	std::copy_n(&dizgi[0], 10, make_null_iterator(&dizgi[0]));
	std::cout << std::endl;



	return 0;
}
