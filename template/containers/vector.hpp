/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:47:01 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/13 23:14:10 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <memory>

// #include <vector>
#include "../utility/utils.hpp"
namespace ft
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
			typedef typename allocator_type::difference_type		difference_type;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<pointer>				iterator;
			typedef ft::random_access_iterator<const_pointer>		const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			pointer													__begin_;
			pointer													__end_;
			ft::pair<pointer, allocator_type>						__end_cap_;
		
		public: 

		const allocator_type& __alloc() const { return __end_cap_.second(); }
		allocator_type& __alloc() { return __end_cap_.second();  }

		const pointer& __end_cap() const { return __end_cap_.first(); }
		pointer& __end_cap() { return __end_cap_.first(); }

		explicit vector ( const allocator_type & alloc = allocator_type() )
		: 
			__begin_(0),
			__end_(0),
			__end_cap_(ft::make_pair(0, alloc) )
		{}
		
		

	};
}


#endif
