/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:11:50 by krios-fu          #+#    #+#             */
/*   Updated: 2021/09/29 20:44:52 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS__HPP
# define __UTILS__HPP

namespace ft
{
	/*	enable_if
	*** If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.
	***
	*/

	template < bool B, typename T = void >
	struct enable_if{};
	
	template< typename T >
	struct enable_if< true, T >
	{
		typedef T type;
	};
}
#endif