/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:11:50 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/06 00:18:06 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS__HPP
# define __UTILS__HPP

namespace ft
{
	/*	enable_if
	***	If B is true, std::enable_if has a public member typedef type,
	***	equal to T; otherwise, there is no member typedef.
	***
	*/

	template < bool B, typename T = void >
	struct enable_if{};
	
	template < typename T >
	struct enable_if< true, T >
	{
		typedef T type;
	};

	
	/* Is integral start  */

	template < bool is_integral, typename T >
	struct is_integral_check
	{
		typedef T type;
		static const bool value = is_integral;
	};

	template < typename >
		struct is_integral_type : public is_integral_check< false, bool> {};

	template <> struct is_integral_type < bool >					: public is_integral_check < true, bool>						{};
	template <> struct is_integral_type < char >					: public is_integral_check < true, char>						{};
	template <> struct is_integral_type < char16_t >				: public is_integral_check < true, char16_t >					{};
	template <> struct is_integral_type < char32_t >				: public is_integral_check < true, char32_t >					{};
	template <> struct is_integral_type < wchar_t >					: public is_integral_check < true, wchar_t >					{};
	template <> struct is_integral_type < signed char >				: public is_integral_check < true, signed char >				{};
	template <> struct is_integral_type < short int >				: public is_integral_check < true, short int >					{};
	template <> struct is_integral_type < int >						: public is_integral_check < true, int >						{};
	template <> struct is_integral_type < long int >				: public is_integral_check < true, long int >					{};
	template <> struct is_integral_type < long long int >			: public is_integral_check < true, long long int >				{};
	template <> struct is_integral_type < unsigned char >			: public is_integral_check < true, unsigned char >				{};
	template <> struct is_integral_type < unsigned short int >		: public is_integral_check < true, unsigned short int >			{};
	template <> struct is_integral_type < unsigned int >			: public is_integral_check < true, unsigned int >				{};
	template <> struct is_integral_type < unsigned long int >		: public is_integral_check < true, unsigned long int >			{};
	template <> struct is_integral_type < unsigned long long int >	: public is_integral_check < true, unsigned long  long int >	{};

	template <typename T>
		struct is_integral : public is_integral_type<T> {};
	/* Is integral end  */


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

		/* End ft::pair */

		/* Start ft::make_pair */

		template <class _T1, class _T2>
			ft::pair < _T1, _T2 > make_pair( _T1 __x, _T2 __y )
			{
				return pair< _T1, _T2 >( __x, __y );
			}

		/* End ft::make_pair */

		/*	Start Ft::Equals
		**
		**	Compares the elements in the range [first1,last1) with those in the range beginning at first2,
		**	and returns true if all of the elements in both ranges match.
		**
		*/

		template < class _InputIterator1 , class _IntputIterartor2 >
			bool equal( _InputIterator1 __first1, _InputIterator1 __last1, _IntputIterartor2 __first2)
			{
				for(; __first1 != __last1; __first1++, __first2++)
					if( !(*__first1 == *__first2) )
						return false;
				return true;
			}

		template < class _InputIterator1 , class _IntputIterartor2, class _BinaryPredicate >
			bool equal ( _InputIterator1 __first1, _InputIterator1 __last1,
						_IntputIterartor2 __first2, _BinaryPredicate __pred )
			{
				for(; __first1 != __last1; __first1++, __first2++)
					if( !__pred( *__first1 , *__first2 ) )
						return false;
				return true;
			}
		/* End Ft::Equals  */
		

		/* 
		**	Start ft::lexicographical_compare v.1
		**	Lexicographical comparison is a operation with the following properties:
		**	Two ranges are compared element by element.
		**	The first mismatching element defines which range is lexicographically less or greater than the other.
		**	If one range is a prefix of another, the shorter range is lexicographically less than the other.
		**	If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
		**	An empty range is lexicographically less than any non-empty range.
		**	Two empty ranges are lexicographically equal.
		*/

		template < class _InputIterator1 , class _InputIterator2 >
			bool lexicographical_compare( _InputIterator1 __first1, _InputIterator1 __last1,
										_InputIterator2 __first2, _InputIterator1 __last2 )
			{
				for(; ( __first1 != __last1 ) && ( __first2 != __last2 ); __first1++, __first2++)
				{
					if ( *__first1 < *__first2 ) return true;
					if ( *__first2 < *__first1 ) return false;
				}
				return ( __first1 == __last1) && (__first2 != __last2 );
			}

		/*
		**  Start ft::lexicographical_compare v.2 comapre function 
		**
		**
		*/
		template < class _InputIterator1, class _InputIterator2, class _Compare >
			bool lexicographical_compare( _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2,
										_InputIterator2 __last2, _Compare __compare )
			{
				for(; ( __first1 != __last1 ) && ( __first2 != __last2 ); __first1++, __first2++ )
				{
					if ( __compare( *__first1, *__first2 ) ) return true;
					if ( __compare( *__first2, *__first1 ) ) return false;
				}
				return ( __first1 == __last1 ) && ( __first2 != __last2 );
			}

		/*  END ft::lexicographical_compare  */
}
#endif
