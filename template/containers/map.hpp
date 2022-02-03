/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:19:08 by krios-fu          #+#    #+#             */
/*   Updated: 2022/02/03 13:45:28 by krios-fu         ###   ########.fr       */
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

		template < typename __Sw >
		void __swap( __Sw &a, __Sw  &b)
		{
			__Sw  c;
			c = a;
			a = b;
			b = c;
		}

	public:

	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
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
			//  __comp_alloc = __other.__comp_alloc;
			//  __tree_ = __other.__tree_;
			clear();
			insert(__other.begin(), __other.end() );
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

	bool empty() const { return __tree_.empty(); };
	size_type max_size() const { return __tree_.max_size(); };
	size_type size()const  { return __tree_.size(); };


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
		for (; __first != __last; )
			erase( __first++ );
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

	size_type count( const key_type & __k ) const
	{
		return ( find(__k) != end() ) ? 1 : 0;
	}

	key_compare key_comp() const { return __comp_alloc.first; };

	value_compare value_comp() const { return __tree_.value_comp(); }

	void swap( map& __other )
	{
		__swap( __comp_alloc, __other.__comp_alloc );
		__tree_.swap(__other.__tree_);
	}


	iterator lower_bound( const _Key& __k )
	{
		iterator __first = begin();
		iterator __last = end();

		for (; __first != __last; ++__first )
			if ( !__comp_alloc.first( (*__first).first, __k ) )
				break;
		return __first;

	}

	const_iterator lower_bound ( const _Key& __k ) const
	{
		const_iterator __first = begin();
		const_iterator __last = end();

		for (; __first != __last; ++__first )
			if ( !__comp_alloc.first( (*__first).first, __k ) )
				break;
		return const_iterator( __first );
	}


	iterator upper_bound( const _Key& __k )
	{
		iterator __first = begin();
		iterator __last = end();

		for (; __first != __last; ++__first )
			if ( __comp_alloc.first( __k, (*__first).first ) )
				break;
		return __first;

	}

	const_iterator upper_bound ( const _Key& __k ) const
	{
		const_iterator __first = begin();
		const_iterator __last = end();

		for (; __first != __last; ++__first )
			if ( __comp_alloc.first( __k, (*__first).first) )
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


	void print()
	{
		__tree_.print();
	}
};

	template< typename _Key, typename _Tp, typename _Compare, typename _Alloc >
	bool operator==( const ft::map<_Key, _Tp, _Compare, _Alloc > &__x, const ft::map<_Key, _Tp, _Compare, _Alloc > &__y)
	{
		return __x.size() == __y.size() && ft::equal( __x.begin(), __x.end(), __y.begin() );
	}


	template< typename _Key, typename _Tp, typename _Compare, typename _Alloc >
	bool operator!=( const ft::map<_Key, _Tp, _Compare, _Alloc > &__x, const ft::map<_Key, _Tp, _Compare, _Alloc > &__y)
	{
		return !(__x == __y);
	}

	template< typename _Key, typename _Tp, typename _Compare, typename _Alloc >
	bool operator<( const ft::map<_Key, _Tp, _Compare, _Alloc > &__x, const ft::map<_Key, _Tp, _Compare, _Alloc > &__y)
	{
		return ft::lexicographical_compare( __x.begin(), __x.end(), __y.begin(), __y.end() );
	}
	template< typename _Key, typename _Tp, typename _Compare, typename _Alloc >
	bool operator>( const ft::map<_Key, _Tp, _Compare, _Alloc > &__x, const ft::map<_Key, _Tp, _Compare, _Alloc > &__y)
	{
		return __y < __x ;
	}
	template< typename _Key, typename _Tp, typename _Compare, typename _Alloc >
	bool operator>=( const ft::map<_Key, _Tp, _Compare, _Alloc > &__x, const ft::map<_Key, _Tp, _Compare, _Alloc > &__y)
	{
		return !(__x < __y) ;
	}
	template< typename _Key, typename _Tp, typename _Compare, typename _Alloc >
	bool operator<=( const ft::map<_Key, _Tp, _Compare, _Alloc > &__x, const ft::map<_Key, _Tp, _Compare, _Alloc > &__y)
	{
		return !(__y < __x) ;
	}

	template< typename _Key, typename _Tp, typename _Compare, typename _Alloc >
	void swap( const ft::map<_Key, _Tp, _Compare, _Alloc > &__x, const ft::map<_Key, _Tp, _Compare, _Alloc > &__y)
	{
		return __x.swap( __y );
	}


}

#endif