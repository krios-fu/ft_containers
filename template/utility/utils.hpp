/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:11:50 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/26 03:34:41 by krios-fu         ###   ########.fr       */
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
# include "iostream"

namespace ft {
	
	static class nullptr_t
	{
		public:

		template<class T>
		operator T*() const { return (0); }

		template<class C, class T>
		operator T C::*() const { return (0); }

		private:
			void operator&() const;

	} nullptr_t = {};

	template <typename T>
		void	swap(T &a, T &b)
		{
			T c;

			c = a;
			a = b;
			b = c;
		}

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
