/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:11:50 by krios-fu          #+#    #+#             */
/*   Updated: 2021/12/13 14:03:00 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS__HPP
# define __UTILS__HPP

# include "./enable_if.hpp"
# include "./equal.hpp"
# include "./is_integral.hpp"
# include "./pair.hpp"
# include "./lexicographical_compare.hpp"
# include "./iterator.hpp"
# include "./nullptr.hpp"
# include "iostream"

namespace ft {
	
	template <typename T>
		T min(T a, T b)
		{
			if (a >= b)
				return b;
			else 
				return a;
		}

	template <typename T>
		T max(T a, T b)
		{
			if (a <= b)
				return b;
			else
				return a;
		}


/*
** Binary function object class whose call returns whether
** the its first argument compares less than the second (as returned by operator <).
*/
	template < typename T >
	struct less : std::binary_function< T, T, bool >
	{
		bool operator()( const T & __x, const T & __y ) const 
		{
			return __x < __y ;
		}
	};

	template< typename value_type >
	bool less_than( const value_type & __x , const value_type & __y )
	{
		return __x < __y ;
	}

	template< typename value_type >
	bool more_than( const value_type & __x , const value_type & __y )
	{
		return __x > __y ;
	}



}
#endif 
