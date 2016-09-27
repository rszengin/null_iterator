/*
 * nulliter.hpp
 *
 *  Created on: 22 Sept 2016
 *      Author: Rahman Salim Zengin
 *      E-mail: rsz@gufatek.com
 *
 *
 * The null iterator adaptor converts an STL iterator to a nullified
 * iterator.
 * Every two null iterators of the same type compares equal.
 * When dereferenced it returns a default constructed object which
 * has same type of the base iterator's value type. That value is refreshed
 * for every dereferencing so that data written to it is discarded. Reading that
 * value gives a default initialized value_type object. It works a bit like
 * a null device.
 */

#ifndef NULL_ITERATOR_ADAPTOR_HPP_
#define NULL_ITERATOR_ADAPTOR_HPP_

#include <iterator>

namespace nltr {


template<typename Iter>
class null_iterator {

protected:
	typedef Iter iterator_type;
	typedef std::iterator_traits<Iter> traits_type;

public:
	typedef typename traits_type::iterator_category iterator_category;
	typedef typename traits_type::value_type value_type;
	typedef typename traits_type::difference_type difference_type;
	typedef typename traits_type::pointer pointer;
	typedef typename traits_type::reference reference;

//protected:
	Iter current;

	// A valid assignment value is required for nullified dereferencing
	value_type null_value;

public:

	// Default constructible
	null_iterator() : current() {}

	null_iterator(nullptr_t* np) : current(nullptr) {}

	// Copy constructible
	null_iterator(const null_iterator<Iter>& nit) : current() {}

	~null_iterator() {}

	/* Initialization construction from base iterator causes dual way
	 * type conversion ambiguity. Not to be placed. */

	// Copy assignable
	null_iterator<Iter>& operator=(const null_iterator<Iter>& nit) {
		return *this;
	}

    // The underlying iterator
	iterator_type base() const {
		return current;
	}

	// Implicit Convertible
    inline
	operator iterator_type() {
    	return iterator_type {};
    }

    template<typename OtherIter>
    inline
	operator null_iterator<OtherIter>() {
    	return null_iterator<OtherIter> {};
    }

    template<typename OtherIter>
    inline
	operator OtherIter() {
    	return OtherIter {};
    }

	// Iterator concept requires dereferenceable
    // OutputIterator concept requires assignment to dereferenced value
    // Dereferencing the null iterator works as "/dev/null" of the linux
	reference operator*() {
		std::cout << "*"; // Dereferencing indicator
		null_value = value_type {}; // Nullifying
		return null_value;
	}

	// InputIterator concept requires structure dereferenceable
	pointer operator->() const {
		return &null_value;
	}

	// ForwardIterator concept requires incrementable
	null_iterator& operator++() { // Prefix
		return *this;
	}
	null_iterator& operator++(int) { // Postfix
		return *this;
	}

	// BidirectionalIterator concept requires decrementable
	null_iterator& operator--() { // Prefix
		return *this;
	}
	null_iterator& operator--(int) { // Postfix
		return *this;
	}

	// RandomAccessIterator concept requires these
	null_iterator operator+(difference_type n) const {
		return *this;
	}
	null_iterator& operator+=(difference_type n) {
		return *this;
	}
	null_iterator operator-(difference_type n) const {
		return *this;
	}
	null_iterator& operator-=(difference_type n) {
		return *this;
	}
	reference operator[](difference_type n) const {
		return *this;
	}

	// This function accesses a protected member
	template<typename OtherIter>
	friend inline
	bool operator==(const null_iterator<OtherIter>& lhs, const OtherIter& rhs);
};



// Null iterato to null iterator comparisons
template<typename Iter1, typename Iter2>
inline constexpr
bool operator==(const null_iterator<Iter1>& lhs, const null_iterator<Iter2>& rhs) {
	return std::is_same<Iter1, Iter2>::value;
}

template<typename Iter1, typename Iter2>
inline constexpr
bool operator!=(const null_iterator<Iter1>& lhs, const null_iterator<Iter2>& rhs) {
	return !(lhs == rhs);
}

template<typename Iter1, typename Iter2>
inline constexpr
bool operator<=(const null_iterator<Iter1>& lhs, const null_iterator<Iter2>& rhs) {
	return lhs == rhs;
}

template<typename Iter1, typename Iter2>
inline constexpr
bool operator>=(const null_iterator<Iter1>& lhs, const null_iterator<Iter2>& rhs) {
	return lhs == rhs;
}

template<typename Iter1, typename Iter2>
inline constexpr
bool operator<(const null_iterator<Iter1>& lhs, const null_iterator<Iter2>& rhs) {
	return false;
}

template<typename Iter1, typename Iter2>
inline constexpr
bool operator>(const null_iterator<Iter1>& lhs, const null_iterator<Iter2>& rhs) {
	return false;
}

template<typename Iter>
inline typename null_iterator<Iter>::difference_type
operator-(const null_iterator<Iter>& lhs, const null_iterator<Iter>& rhs) {
	return lhs.base() - rhs.base();
}

// Null to base comparisons
template<typename OtherIter>
inline
bool operator==(const null_iterator<OtherIter>& lhs, const OtherIter& rhs) {
	return lhs.current == rhs;
}
template<typename OtherIter>
inline
bool operator!=(const null_iterator<OtherIter>& lhs, const OtherIter& rhs) {
	return !(lhs == rhs);
}
template<typename OtherIter>
inline
bool operator==(const OtherIter& lhs, const null_iterator<OtherIter>& rhs) {
	return rhs == lhs;
}
template<typename OtherIter>
inline
bool operator!=(const OtherIter& lhs, const null_iterator<OtherIter>& rhs) {
	return !(rhs == lhs);
}

template<typename Iter1, typename Iter2>
inline
auto operator-(const null_iterator<Iter1>& lhs, const null_iterator<Iter2>& rhs)
-> decltype(lhs.base() - rhs.base()) {
	// Null is null, just return the default
	return decltype(lhs.base() - rhs.base()) {};
}

template<typename Iter>
inline
null_iterator<Iter> operator+(typename null_iterator<Iter>::difference_type n, const null_iterator<Iter>& nit) {
	return null_iterator<Iter> {};
}

// Convenience function template that constructs a null_iterator
// with the type deduced from the type of the argument
template<typename Iter>
inline constexpr
null_iterator<Iter> make_null_iterator(const Iter& it) {
	return null_iterator<Iter> {};
}


// The Universalization

// The Universal Null Iterator Type
using nulliter_t = null_iterator<nullptr_t*>;

// The Universal Null Iterator
//nulliter_t nulliter {};

template<typename Iter>
bool operator==(const nulliter_t& nulliter, const Iter& it) {
	return it == Iter {};
}
template<typename Iter>
bool operator==(const Iter& it, const nulliter_t& nulliter) {
	return it == Iter {};
}
template<typename Iter>
bool operator!=(const nulliter_t& nulliter, const Iter& it) {
	return !(it == Iter {});
}
template<typename Iter>
bool operator!=(const Iter& it, const nulliter_t& nulliter) {
	return !(it == Iter {});
}



} // namespace nltr

#endif /* NULL_ITERATOR_ADAPTOR_HPP_ */
