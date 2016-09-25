# Null Iterator Adaptor

For pointers there is a **nullptr** definition. If we treat pointers analogous to geometric vectors, iterators may be treated as tensors. So, why don't we have a higher level **nulliter** ? This is the main idea behind this work.

null_iterator_adaptor is an iterator adaptor as its name declares. It converts any STL compatible iterator or simply pointer to a null iterator. So, what a null iterator does? Nothing. Or anything. When it is used with STL algorithms as an output iterator it works as a **null device**. When used as an input iterator, it only gives out a default constructed **value_type** object. This behaviour is a bit like a **zero device**. It can be used as a random access iterator, it will access to infinity and beyond.

When a null iterator is assigned to a normal iterator, the assignment make the normal iterator default constructed. When null iterator is compared with a normal iterator, the comparison will be the comparison of the normal iterator with its default constructed state.

`nulliter.hpp` includes the null_iterator_adapter code.
`main.cpp` includes some sample usage.

Tested with MinGW GCC 5.1 (TDM-GCC Distribution)
