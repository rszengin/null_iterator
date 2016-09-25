# Null Iterator Adaptor

For pointers there is a **nullptr** definition. If we treat pointers analogous to geometric vectors, iterators may be treated as tensors. So, why don't we have a higher level **nulliter** ? This is the main idea behind this work.

null_iterator_adaptor is an iterator adaptor as its name declares. It converts any STL compatible iterator or simply pointer to a null iterator. So, what a null iterator does? Nothing. Or anything. It doesn't need a list to be used. It only uses type information of the underlying iterator. It has nothing to do with real data. ~~It can be used to fool STL algorithms.~~ It can be used as a null return value or a comparison to null constant for sequence traversing algorithms.

When it is used with STL algorithms as an output iterator it works as a **null device**. When used as an input iterator, it only gives out a default constructed **value_type** object. This behaviour is a bit like a **zero device**. It can be used as a random access iterator, it will access to infinity and beyond.

When a null iterator is assigned to a normal iterator, the assignment make the normal iterator default constructed. When null iterator is compared with a normal iterator, the comparison will be the comparison of the normal iterator with its default constructed state.

`nulliter.hpp` includes the null_iterator_adapter code.
`main.cpp` includes some sample usage.

Tested with MinGW GCC 5.1 (TDM-GCC Distribution)

### Some Examples

#### Sending data to nowhere
```c++
std::vector<int> dizi { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
std::copy(dizi.begin(), dizi.end(), make_null_iterator(dizi.begin()));
```

#### Using as a null return value
```c++
template<typename InputIt, typename T>
InputIt my_found( InputIt first, InputIt last, const T& value ) {
	using namespace nltr;
	InputIt result = std::find(first, last, value);
	return (result != last) ? result : make_null_iterator((nullptr_t*)nullptr);
}

int main() {

	using namespace nltr;

	std::vector<int> dizi { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (int inx = 7; inx < 30; inx += 7) {
		std::cout << (inx % 15) << " is";
		if (my_found(dizi.begin(), dizi.end(), (inx % 15)) == make_null_iterator((nullptr_t*)nullptr))
			std::cout << " not";
		std::cout << " found in dizi" << std::endl;
	}
}
  ```
