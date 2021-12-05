/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:11:50 by krios-fu          #+#    #+#             */
/*   Updated: 2021/12/05 09:19:57 by krios-fu         ###   ########.fr       */
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


}
#endif 
