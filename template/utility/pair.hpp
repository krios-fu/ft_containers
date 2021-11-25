/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:06:35 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/24 18:53:55 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __PAIR_HPP
#define __PAIR_HPP

namespace ft
{

	/* Pair start */

	template < class _T1, class _T2 >
	struct pair
	{
		typedef _T1	first_type;
		typedef _T2	second_type;

		_T1 first;
		_T2 second;

		pair()
			: first() , second() {};

		pair ( _T1 const& __t1, _T2 const& __t2 )
			: first( __t1 ), second( __t2 ){}

		template < class _U1, class _U2 >
			pair ( const pair< _U1, _U2 > & __p )
				: first( __p.first ) , second ( __p.second ) {}

		pair& operator= (pair const& __p)
		{
			first = __p.first;
			second = __p.second;
			return *this;
		}
	};

	template <class _T1, class _T2>
		bool operator== ( const ft::pair < _T1, _T2 >& __x, const ft::pair < _T1, _T2 > & __y )
		{
			return __x.first == __y.first && __x.second == __y.second;
		}

	template <class _T1, class _T2>
		bool operator!= ( const ft::pair < _T1, _T2 >& __x, const ft::pair < _T1, _T2 > & __y )
		{
			return !( __x == __y );
		}

	template <class _T1, class _T2>
		bool operator< ( const ft::pair < _T1, _T2 >& __x, const ft::pair < _T1, _T2 > & __y )
		{
			return __x.first < __y.first || ( !(__y.first < __x.first) && __x.second < __y.second );
		}

	template < class _T1, class _T2 >
		bool operator> ( const ft::pair < _T1, _T2 >& __x, const ft::pair < _T1, _T2 > & __y )
		{
			return __y < __x;
		}

	template < class _T1, class _T2 >
		bool operator>= ( const ft::pair < _T1, _T2 >& __x, const ft::pair < _T1, _T2> & __y )
		{
			return !(__x < __y);
		}

	template < class _T1, class _T2 >
		bool operator<= ( const ft::pair < _T1, _T2 >& __x, const ft::pair < _T1, _T2> & __y )
		{
			return !(__y < __x);
		}

		/* Start ft::make_pair */

	template <class _T1, class _T2>
		ft::pair < _T1, _T2 > make_pair( _T1 __x, _T2 __y )
		{
			return ft::pair< _T1, _T2 >( __x, __y );
		}

		/* End ft::make_pair */
}

#endif