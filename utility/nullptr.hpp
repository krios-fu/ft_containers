/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nullptr.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:02:52 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/27 01:05:15 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NULLPTR__HPP
# define __NULLPTR__HPP

namespace ft
{
	
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

} // namespace ft

#endif
