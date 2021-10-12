/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:47:01 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/12 22:22:43 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <memory>

#include <vector>
#include "../utility/utils.hpp"
namespace 
{
	template < class T , class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::refernece				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::difference_Type		difference_type;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::reverse_itertor<iterator>					reverese_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;



			
			// vector(/* args */);
			// ~vector();
	};
}


#endif
