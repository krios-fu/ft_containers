/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:40:31 by krios-fu          #+#    #+#             */
/*   Updated: 2022/02/04 18:39:52 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SET_HPP
#define __SET_HPP

#include <memory>
#include "./utility/utils.hpp"
#include "./utility/tree.hpp"

namespace ft
{
template <class _Key, class _Compare = ft::less<_Key>,
				class _Allocator = std::allocator< _Key > >
class set
{

public:

	typedef _Key												key_type;
	typedef const  key_type										value_type;
	typedef _Compare											key_compare;
	typedef key_compare											value_compare;
	typedef _Allocator											allocator_type;

private:

	typedef ft::tree< value_type, key_compare, allocator_type >	__base;

	__base											__tree_;
	ft::pair<key_compare, allocator_type>			__comp_alloc;

public:

	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::size_type					size_type;
	typedef typename allocator_type::difference_type			deifference_type;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;

	typedef typename __base::const_iterator						iterator;
	typedef typename __base::const_iterator						const_iterator;
	typedef typename ft::reverse_iterator<iterator>  			reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

private:

	template < typename __Sw >
		void __swap( __Sw &a, __Sw  &b)
		{
			__Sw  c;
			c = a;
			a = b;
			b = c;
		}

public:

	explicit set( const key_compare & __comp = key_compare(),
				  const allocator_type & __alloc = allocator_type() )
				: __tree_(),
				  __comp_alloc( ft::make_pair(__comp, __alloc) ){}

	template < typename _InputIterator >
	set(
			_InputIterator  __first,
			_InputIterator  __last,
			const key_compare & __comp = key_compare(),
			const allocator_type & __alloc = allocator_type(),
			typename ft::enable_if
			<
				!ft::is_integral<_InputIterator>::value, _InputIterator
			>::type * = NULL
	 )
	: __tree_(),
	  __comp_alloc( ft::make_pair( __comp, __alloc ) )
	{
		for (; __first != __last; ++__first )
			__tree_.insert( *__first );
	}

	set( const set& __other ) { *this = __other; }

	set& operator=( const set& __other )
	{
		if ( this != &__other )
		{
			__comp_alloc = __other.__comp_alloc;
			clear();
			insert(__other.begin(), __other.end() );
		}
		return *this;
	}

	~set() {}

	iterator		begin() { return __tree_.begin(); }
	const_iterator	begin() const { return __tree_.begin(); }

	iterator		end() { return __tree_.end(); }
	const_iterator	end() const { return __tree_.end(); }

	const_reverse_iterator	rbegin() const { return __tree_.rbegin(); }
	reverse_iterator		rbegin() { return  __tree_.rbegin(); }
	
	reverse_iterator		rend() { return  __tree_.rend(); }
	const_reverse_iterator	rend() const { return __tree_.end(); }

	bool empty() const { return __tree_.empty(); };

	size_type max_size() const { return __tree_.max_size(); };

	size_type size()const  { return __tree_.size(); };

	ft::pair<iterator, bool> insert( const value_type& __val )
	{
		return __tree_.insert( __val );
	}

	iterator insert( iterator __pos, const value_type& __val )
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
			__tree_.insert( *__first );

	}

	iterator find( const key_type & __key )
	{
		return __tree_.find( __key );
	}

	const_iterator find( const key_type& __key ) const
	{
		return __tree_.find( __key );
	}

	void erase ( iterator __pos )
	{
		__tree_.remove( *__pos );
	}

	void erase( iterator __first, iterator __last )
	{
		for (; __first != __last; )
			__tree_.remove( *(__first++ ) );
	}

	size_type erase( const key_type & __k )
	{
		iterator __f = find( __k );

		if ( __f != end() )
		{
			__tree_.remove( *__f );
			return 1;
		}
		return 0;
	}

	void clear() { erase(begin(), end() ); }

	size_type count( const key_type & __k ) const { return ( find(__k) != end() ) ? 1 : 0; }

	key_compare key_comp() const { return __comp_alloc.first; };

	value_compare value_comp() const { return __tree_.value_comp(); }

	void swap( set& __other )
	{
		__swap( __comp_alloc, __other.__comp_alloc );
		__tree_.swap(__other.__tree_);
	}

	iterator lower_bound( const _Key& __k )
	{
		iterator __first = begin();
		iterator __last = end();

		for (; __first != __last; ++__first )
			if ( !__comp_alloc.first( *__first, __k ) )
				break;
		return __first;

	}

	const_iterator lower_bound ( const _Key& __k ) const
	{
		const_iterator __first = begin();
		const_iterator __last = end();

		for (; __first != __last; ++__first )
			if ( !__comp_alloc.first( *__first, __k ) )
				break;
		return const_iterator( __first );
	}

	iterator upper_bound( const _Key& __k )
	{
		iterator __first = begin();
		iterator __last = end();

		for (; __first != __last; ++__first )
			if ( __comp_alloc.first( __k, *__first ) )
				break;
		return __first;
	}

	const_iterator upper_bound ( const _Key& __k ) const
	{
		const_iterator __first = begin();
		const_iterator __last = end();

		for (; __first != __last; ++__first )
			if ( __comp_alloc.first( __k, *__first ) )
				break;
		return const_iterator( __first );
	}

	ft::pair<iterator, iterator> equal_range( const _Key& __k )
	{
		return ft::make_pair( lower_bound(__k), upper_bound(__k) );
	}

	ft::pair<const_iterator, const_iterator> equal_range( const _Key& __k ) const
	{
		return ft::make_pair( lower_bound(__k), upper_bound(__k) );
	}

};

	template< typename _Key, typename _Compare, typename _Alloc >
	bool operator==( const ft::set<_Key, _Compare, _Alloc > &__x, const ft::set<_Key, _Compare, _Alloc > &__y)
	{
		return __x.size() == __y.size() && ft::equal( __x.begin(), __x.end(), __y.begin() );
	}


	template< typename _Key, typename _Compare, typename _Alloc >
	bool operator!=( const ft::set<_Key, _Compare, _Alloc > &__x, const ft::set<_Key, _Compare, _Alloc > &__y)
	{
		return !(__x == __y);
	}

	template< typename _Key, typename _Compare, typename _Alloc >
	bool operator<( const ft::set<_Key, _Compare, _Alloc > &__x, const ft::set<_Key, _Compare, _Alloc > &__y)
	{
		return ft::lexicographical_compare( __x.begin(), __x.end(), __y.begin(), __y.end() );
	}
	template< typename _Key, typename _Compare, typename _Alloc >
	bool operator>( const ft::set<_Key, _Compare, _Alloc > &__x, const ft::set<_Key, _Compare, _Alloc > &__y)
	{
		return __y < __x ;
	}
	template< typename _Key, typename _Compare, typename _Alloc >
	bool operator>=( const ft::set<_Key, _Compare, _Alloc > &__x, const ft::set<_Key, _Compare, _Alloc > &__y)
	{
		return !(__x < __y) ;
	}
	template< typename _Key, typename _Compare, typename _Alloc >
	bool operator<=( const ft::set<_Key, _Compare, _Alloc > &__x, const ft::set<_Key, _Compare, _Alloc > &__y)
	{
		return !(__y < __x) ;
	}

	template< typename _Key, typename _Compare, typename _Alloc >
	void swap( const ft::set<_Key, _Compare, _Alloc > &__x, const ft::set<_Key, _Compare, _Alloc > &__y)
	{
		return __x.swap( __y );
	}

	
}

/* void print()
	{
		__tree_.print();
	} */

#endif