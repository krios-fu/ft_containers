/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:56:26 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/12 21:12:45 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ENABLE_IF_HPP_
#define _ENABLE_IF_HPP_

namespace ft
{
	/* enable_if
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
}

#endif
