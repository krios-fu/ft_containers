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



/* 	class value_compare	: std::binary_function< value_Type, value_type, bool >
	{
		friend class map;
		protected:
			key_compare comp;
		
		value_compare( key_compare c ) : comp ( c ) {}
		public:

		bool operator()( const value_type & __x ,  const value_type & __y ) const 
		{
			return comp( __x.first , __y.first );
		}
	}; */

};

}

#endif