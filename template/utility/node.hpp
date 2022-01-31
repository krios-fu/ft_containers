#ifndef NODE_HPP
#define NODE_HPP

# include "./utils.hpp"

namespace ft
{

template<typename T>
struct Node
{
	public : 
	typedef T			value_type;
	value_type			content;
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

	~Node(){}

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