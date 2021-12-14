#ifndef MAP_HPP
# define MAP_HPP

#include <map>
#include <memory>
#include "../utility/utils.hpp"

namespace ft
{
	template <class _Key, class _Tp, class _Compare = ft::less<_Key>,
				class _Allocator = std::allocator< ft::pair< const _Key, _Tp > > >
class map
{
	public:
	typedef	_Key														key_type;
	typedef _Tp															mapped_type;
	typedef ft::pair<key_type, mapped_type>								value_type;
	typedef _Compare													key_compare;
	typedef _Allocator													allocator_type;
	typedef value_type &												reference;
	typedef const value_type & 											const_reference;

	private:

	struct Node
	{
		value_type			__content;
		Node*				__parent;
		Node*				__rigth;
		Node*				__left;

		Node ( const_reference val = value_type() )
			: __content(val),
			  __parent( ft::nullptr_t ),
			  __rigth( ft::nullptr_t ),
			  __left ( ft::nullptr_t ) {}

		Node ( const Node & __other )
			: __content( __other.content ),
			  __parent( ft::nullptr_t ),
			  __rigth( ft::nullptr_t ),
			  __left ( ft::nullptr_t ) {}
	};

	/* Node				*__nodePtr;
	public:

		value_type getNode()
		{
			return __nodePtr->__content;
		}

	map()
	{

	}
 */
};

}

#endif