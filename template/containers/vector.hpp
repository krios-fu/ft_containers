/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:47:01 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/25 05:12:25 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <memory>

#include <vector>
#include "../utility/utils.hpp"
namespace ft
{
	template < class T , class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::difference_type		difference_type;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<pointer>				iterator;
			typedef ft::random_access_iterator<const_pointer>		const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		 private:
			pointer													__begin_;
			pointer													__end_;
			ft::pair<pointer, allocator_type>						__end_cap_;
			size_type												__size_;
		

		const allocator_type& __alloc() const { return __end_cap_.second; }
		allocator_type& __alloc() { return __end_cap_.second;  }

		const pointer& __end_cap() const { return __end_cap_.first; }
		pointer& __end_cap() { return __end_cap_.first; }

		public: 

		explicit vector ( const allocator_type & __alloc = allocator_type() )
		:
			__begin_( ft::nullptr_t ),
			__end_( __begin_ ),
			__end_cap_( ft::make_pair(ft::nullptr_t, __alloc) ),
			__size_( 0 )
		{
			std::cout << "Default vector, capacity:  "  << this->capacity() << std::endl;
		}

		explicit  vector( size_type __n, const value_type & __x = value_type(), const allocator_type& __alloc = allocator_type() )
			:
			__begin_( ft::nullptr_t ),
			__end_( __begin_ ),
			__end_cap_( ft::make_pair( ft::nullptr_t, __alloc ) ),
			__size_( __n )
		{
			__begin_ = this->__alloc().allocate( __n );
			this->__end_cap() = __begin_ + __n;
			__end_ = __begin_;
			for(; __n > 0 ; ++__end_, --__n )
				this->__alloc().construct( __end_, __x );
		}

		template< class  _InputIterator >
			vector( _InputIterator __first,  _InputIterator __last, const Allocator& __alloc = Allocator(),
					typename ft::enable_if<!ft::is_integral<_InputIterator>::value, _InputIterator>::type* = ft::nullptr_t )
				:
				__end_cap_( ft::make_pair( ft::nullptr_t, __alloc ) )
			{

				ptrdiff_t __n = ft::distance( __first, __last );
				
				__size_ = __n ;
				__begin_ = this->__alloc().allocate( __n );
				this->__end_cap() = __begin_ + __n;
				__end_ = __begin_;

				for(; __n > 0 ; ++__end_, --__n )
					this->__alloc().construct( __end_, *__first++ );
			}




			iterator				begin()			{ return this->__begin_; }
			iterator				end()			{ return this->__end_; }

			const_iterator			end()	const	{ return this->__end_; }
			const_iterator			begin()	const	{ return this->__begin_; }

			reverse_iterator		rbegin()		{ return reverse_iterator( this->__end_ ); }
			reverse_iterator		rend()			{ return reverse_iterator( this->__begin_ ); }

			const_reverse_iterator	rbegin()	const	{ return reverse_iterator( this->__end_ ); }
			const_reverse_iterator	rend()		const	{ return reverse_iterator( this->__begin_ ); }

			size_type				size () const		{ return static_cast<size_type> ( this->__end_ - this->__begin_ ); };
			size_type				max_size() const	{ return static_cast<size_type> ( allocator_type().max_size() ); };
			size_type				capacity() const	{ return static_cast<size_type> ( __end_cap() - this->__begin_ ) ; };


			
		void assign( size_type __n , const_reference __u )
		{
			if ( __n == 0 )
				return ;
			if ( __n <= capacity() )
			{
				// clear();
				size_type __s = size();
				std::fill_n( this->__begin_, std::min( __n, __s ), __u );
				__end_ = __begin_ + __n;
				std::cout << " __n <= capacity \n";
			}
			else
			{
				std::cout << " __n > capacity \n";

				__alloc().deallocate( __begin_, capacity() );
				__begin_  = __alloc().allocate( __n );
				__end_cap() = __begin_ + __n;
				__end_ = __begin_;
				for(; __n > 0 ; ++__end_, --__n )
					__alloc().construct( __end_, __u );
			}
		}

		void clear()
		{
			size_type __old_size = size();
			
			for (size_type i = 0; i < __old_size ; ++i , --__end_)
				__alloc().destroy(__end_);
		}
	};
}


#endif
