/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:10:06 by krios-fu          #+#    #+#             */
/*   Updated: 2022/01/26 20:35:52 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEXICOGRAPHICAL_COMPARE_HPP
#define __LEXICOGRAPHICAL_COMPARE_HPP

namespace ft 
{
		/* 
		*	Start ft::lexicographical_compare v.1
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
