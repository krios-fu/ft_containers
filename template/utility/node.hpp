#ifndef NODE_HPP
#define NODE_HPP

# include "./utils.hpp"

namespace ft
{

template<class T>
struct Node
{
	T					content;
	bool				black;
	Node*				parent;
	Node*				right;
	Node*				left;

	Node( T const &  __val = T() )
	: content(__val),
	  black( false ),
	  parent( ft::nullptr_t ),
	  right( ft::nullptr_t ),
	  left( ft::nullptr_t ){}

	Node( Node const &other )
	: content( other.content ),
	  black( false ),
	  parent( ft::nullptr_t ),
	  right( ft::nullptr_t ),
	  left( ft::nullptr_t ){}

	bool isBlack()
	{
			return black;
	}

	void setParent( Node* __p )
	{
		parent = __p;
	}
};

} // namespace ft

#endif