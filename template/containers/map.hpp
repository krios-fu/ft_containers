#ifndef _MAP_HPP
# define _MAP_HPP

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


	public:

	map();

	explicit map( const key_compare & __comp, const allocator_type & __a  = allocator_type() )
	{

	}
};

}

#endif