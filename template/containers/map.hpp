/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:19:08 by krios-fu          #+#    #+#             */
/*   Updated: 2022/02/01 22:13:16 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MAP_HPP
# define _MAP_HPP

#include <map>
#include <memory>
#include "../utility/utils.hpp"
#include "../utility/tree.hpp"
#include "../utility/map_iterator.hpp"




namespace ft
{
	template <class _Key, class _Tp, class _Compare = ft::less<_Key>,
				class _Allocator = std::allocator< ft::pair< const _Key, _Tp > > >
class map
{
	public:
	typedef	_Key														key_type;
	typedef _Tp															mapped_type;
	typedef ft::pair<const key_type, mapped_type>						value_type;
	typedef _Compare													key_compare;
	typedef _Allocator													allocator_type;
	typedef value_type&													reference;
	typedef const value_type & 											const_reference;


	class value_compare
	{
		// friend class map;
		protected:
			key_compare comp;
		public:
			bool operator()( const value_type& __x, const value_type& __y ) const
			{
				return comp( __x.first, __y.first );
			}
	};

	private:
		typedef ft::tree< value_type, value_compare, allocator_type >	__base;

		__base __tree_;
		ft::pair<key_compare, allocator_type>			__comp_alloc;

	public:

	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef typename allocator_type::size_type							size_type;
	typedef typename allocator_type::difference_type					deifference_type;
	typedef typename __base::iterator									iterator;
	typedef typename __base::const_iterator								const_iterator;
	typedef typename __base::reverse_iterator							reverse_iterator;
 	typedef typename __base::const_reverse_iterator						const_reverse_iterator;




	explicit map( const key_compare & __comp = key_compare(), const allocator_type & __alloc = allocator_type() )
		:__tree_(),
		__comp_alloc( ft::make_pair(__comp, __alloc) )
	{
	}

	template < typename _InputIterator >
	map(
			_InputIterator  __first,
			_InputIterator  __last,
			const key_compare & __comp = key_compare(),
			const allocator_type & __alloc = allocator_type(),
			typename ft::enable_if
			<
				!ft::is_integral<_InputIterator>::value, _InputIterator
			>::type * = NULL
			
	 )
	:__tree_(),
	 __comp_alloc( ft::make_pair( __comp, __alloc ) )
	{
		for (; __first != __last; ++__first )
			__tree_.insert( *__first );
	}

	map( const map& __other ) 
	{
		*this = __other;
	}

	map& operator=( const map& __other )
	{
		if ( this != &__other )
		{
			__tree_ = __other.__tree_;
			__comp_alloc = __other.__comp_alloc;
		}
		return *this;
	}

	~map() {}

	iterator		begin() { return __tree_.begin(); }
	iterator		end() { return __tree_.end(); }
	const_iterator	begin() const { return __tree_.begin(); }
	const_iterator	end() const { return __tree_.end(); }

	reverse_iterator		rbegin() { return  __tree_.rbegin(); }
	reverse_iterator		rend() { return  __tree_.rend(); }
	const_reverse_iterator	rbegin() const { return __tree_.rbegin(); }
	const_reverse_iterator	rend() const { return __tree_.end(); }

	bool empty() { return __tree_.empty(); };
	size_type max_size(){ return __tree_.max_size(); };
	size_type size() { return __tree_.size(); };


 	mapped_type& operator[]( const key_type& __k )
	{
		iterator	__hunt = find( __k );

		if ( __hunt != end() )
			return __hunt->second;
		else
			return (*insert( ft::make_pair( __k, mapped_type() ) ).first).second;
	} 

	ft::pair<iterator, bool> insert( const value_type& __val )
	{
		return __tree_.insert( __val );
	}

	ft::pair<iterator, bool> insert( iterator __pos, const value_type& __val )
	{
		static_cast< void >( __pos );
		return __tree_.insert( __val ).first;
	}

	template <typename _InputIterator >
	void insert
	(
			_InputIterator  __first,
			_InputIterator  __last,
			typename ft::enable_if
			<
				!ft::is_integral<_InputIterator>::value, _InputIterator
			>::type * = NULL
	)
	{
		for(; __first != __last; ++__first )
			__tree_.insert(  *__first );
		
	}

	iterator find( const key_type & __key )
	{
		return __tree_.find( ft::make_pair( __key, mapped_type() ) );
	}

	const_iterator find( const key_type& __key ) const
	{
		return __tree_.find( ft::make_pair( __key, mapped_type() ) );
	}

	void erase ( iterator __pos )
	{
		__tree_.remove( *__pos );
	}

	void erase( iterator __first, iterator __last )
	{
		for (; __first != __last; ++__first)
			__tree_.remove(  *__first );
	}

	size_type erase( const key_type & __k )
	{
		iterator __f = find( __k );
		
		if ( __k != end() )
		{
			__tree_.remove( *__f );
			return 1;
		}
		return 0;
	}

	void clear() { __tree_.clear(); }

	size_type count( const key_type & __k )
	{
		return ( find(__k) != end() ) ? 1 : 0;
	}

	key_compare key_comp() const { return __comp_alloc.first; };
	
	value_compare value_comp() const { return __tree_.value_comp(); }
	
};

}

#endif