/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:08:15 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/12 21:09:08 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EQUAL_HPP
#define __EQUAL_HPP

namespace ft
{
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
}

#endif
