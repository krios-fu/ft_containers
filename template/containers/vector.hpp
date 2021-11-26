/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:47:01 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/26 05:35:36 by krios-fu         ###   ########.fr       */
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
			typedef Allocator														allocator_type;
			typedef T																value_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef ft::random_access_iterator<pointer>								iterator;
			typedef ft::random_access_iterator<const_pointer>						const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type			difference_type;
			typedef typename allocator_type::size_type								size_type;

		 private:
			pointer													__begin_;
			pointer													__end_;
			ft::pair<pointer, allocator_type>						__end_cap_;
			size_type												__size_;
		
		protected: 
		const allocator_type& __alloc() const { return __end_cap_.second; }
		
		allocator_type& __alloc() { return __end_cap_.second;  }

		const pointer& __end_cap() const { return __end_cap_.first; }
		
		pointer& __end_cap() { return __end_cap_.first; }

		void __vallocate( size_type __n )
		{
			__begin_ = __alloc().allocate( __n );
			__end_cap() = __begin_ + __n;
			__end_ = __begin_;
			__size_ = __n;
		}

		void __vdeallocate()
		{
			if ( __begin_ != ft::nullptr_t )
			{
				__alloc().deallocate( __begin_, capacity() );
				__begin_ = ft::nullptr_t;
				__size_ =  0;
			}
		}

		void __vconstruct( const pointer&  __newlast, const value_type & __x )
		{
			__alloc().construct( __newlast, __x );
		}

		void __recommend( size_type __new_size ) const 
		{
			const size_type __ms = this->max_size();
			
			if ( __new_size > __ms )
				throw (std::length_error("Vector::reserve"));
			
			const size_type __cap = this->capacity();
			
			if ( __cap >= __ms / 2 )
				return __ms;
			return ft::max(2 * __cap, __new_size );
		}


		template < typename _InputIterator>
			void __construct_at_end ( _InputIterator __begin , _InputIterator __end )
			{
				pointer advance = this->__begin_;

				for (; __begin != __end ;  ++__begin, ++advance)
					__vconstruct(advance, *__begin);
				this->__end_ = advance;
			}

		public: 

		explicit vector ( const allocator_type & __alloc = allocator_type() )
			:
			__begin_( ft::nullptr_t ),
			__end_( __begin_ ),
			__end_cap_( ft::make_pair( ft::nullptr_t, __alloc) ),
			__size_( 0 )
		{
			std::cout << "Default vector, capacity:  "  << this->capacity() << std::endl;
		}

		explicit  vector( size_type __n, const value_type & __x = value_type(), const allocator_type& __alloc = allocator_type() )
			:
			__begin_( ft::nullptr_t ),
			__end_( __begin_ ),
			__end_cap_( ft::make_pair( ft::nullptr_t, __alloc ) ),
			__size_( 0 )
		{
			__size_ = __n;
			__vallocate( __size_ );
			for(; __n > 0 ; ++__end_, --__n )
				__vconstruct( __end_, __x );
		}

		template< class  _InputIterator >
			vector( _InputIterator __first,  _InputIterator __last, const Allocator& __alloc = Allocator(),
					typename ft::enable_if<!ft::is_integral<_InputIterator>::value, _InputIterator>::type* = ft::nullptr_t )
				:
				__end_cap_( ft::make_pair( ft::nullptr_t, __alloc ) ),
				__size_( 0 )
			{
				ptrdiff_t __n;
				__n = ft::distance( __first, __last );
				__size_ = __n;
				__vallocate( __size_ );
				for(; __n > 0 ; ++__end_, --__n )
					__vconstruct( __end_, *__first++ );
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
			size_type				max_size() const { return this->__alloc().max_size(); };
			
			size_type				capacity() const	{ return static_cast<size_type> ( __end_cap() - this->__begin_ ) ; };

		void assign( size_type __n , const_reference __u )
		{
			size_type __s = size();
			clear();
			if ( __n == 0 )
				return ;
			if ( __n <= capacity() )
			{
				std::fill_n( this->__begin_, ft::min( __n, __s ), __u );
				__end_ = __begin_ + __n;
			}
			else
			{
				__vdeallocate();
				__vallocate( __n );
				for(; __n > 0 ; ++__end_, --__n )
					__alloc().construct( __end_, __u );
			}
		}

		template < typename _InputIterator>
		typename ft::enable_if
		<
			ft::is_input_it_tag< _InputIterator >::value &&
			!ft::is_integral< typename  _InputIterator::value_type >::value,
			void
		>::type
			assign( _InputIterator __first, _InputIterator __last )
			{
				clear();
				for (; __first != __last; ++__first )
				{
					std::cout << ft::is_integral< typename _InputIterator::value_type >::value << std::endl;
				}
				
			}



		void swap( vector& __x )
		{
			ft::swap( this->__begin_, __x.__begin_ );
			ft::swap( this->__end_, __x.__end_ );
			ft::swap( this->__end_cap_, __x.__end_cap_ );
			ft::swap( this->__size_ , __x.__size_ );
		}
		


		void reserve ( size_type __n )
		{

			if ( __n > this->capacity() )
			{
				vector __v(this->__alloc());
				__v.__vallocate(__n);
				__v.__construct_at_end( this->begin(), this->end() );
				swap(__v);
				__v.__vdeallocate();
			}
		}

		void push_back( const value_type& __x )
		{
			 if  ( this->__size_ == this->capacity() )
			++this->__size_;
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
