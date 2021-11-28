/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:47:01 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/28 05:47:44 by krios-fu         ###   ########.fr       */
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
	typedef Allocator													allocator_type;
	typedef T															value_type;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef ft::random_access_iterator<pointer>							iterator;
	typedef ft::random_access_iterator<const_pointer>					const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
	typedef typename allocator_type::size_type							size_type;

private:
	size_type							__size_;
	pointer								__begin_;
	pointer								__end_;
	ft::pair< pointer, allocator_type >	__end_cap_;

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
			__size_ = 0;
		}
	}


	void __exceptionRangeVector( bool __is, char const *str )
	{
		if( __is )
			throw std::out_of_range( str );
	}
	void __vconstruct( const pointer&  __newlast, const value_type& __x )
	{
		__alloc().construct( __newlast, __x);
	}

	size_type __recommend( size_type __new_size ) const 
	{
		const size_type __ms = this->max_size();
		if ( __new_size > __ms )
			throw ( std::length_error( "Vector::reserve length error " ) );
		const size_type __cap = this->capacity();
		if ( __cap >= __ms / 2 )
			return __ms;
		return ft::max( (2 * __cap), __new_size );
	}

	template < typename _InputIterator >
	typename ft::enable_if
	<
		!ft::is_integral< typename _InputIterator::value_type >::value,
	   void
	>::type
		__construct_at_end ( _InputIterator __first , _InputIterator __last )
		{
			pointer advance = this->__begin_;
			for (; __first != __last ;  ++__first, ++advance)
				__vconstruct( advance, *__first);
			this->__end_ = advance;
			this->__size_ = this->size();
		}

	template < typename _ForwardIterator >
	typename ft::enable_if
	<
		ft::is_integral< typename _ForwardIterator::value_type >::value,
		void
	>::type
		__construct_at_end ( _ForwardIterator __first , _ForwardIterator __last )
		{
			pointer advance = this->__begin_;
			for (; &(*__first ) != &(*__last) ;  ++__first, ++advance)
			{
				__alloc().construct( advance, *__first );
			}
			this->__end_ = advance;
			this->__size_ = this->size();
		}

public:


/* CONSTRUCTORS
**
** 1 Default constructor Constructs an empty container with a default-constructed allocator.
** 2 Constructs the container with count copies of elements with value value.
** 3 Constructs the container with the contents of the range [first, last).
**
*/
	explicit vector ( const allocator_type & __alloc = allocator_type() )
	: __begin_( ft::nullptr_t ),
	  __end_( __begin_ ),
	  __end_cap_( ft::make_pair( ft::nullptr_t, __alloc) ),
	  __size_( 0 ) {}

	explicit  vector( size_type __n, const value_type & __x = value_type(), const allocator_type& __alloc = allocator_type() )
	: __begin_( ft::nullptr_t ),
	  __end_( __begin_ ),
	  __end_cap_( ft::make_pair( ft::nullptr_t, __alloc ) ),
	  __size_( 0 )
	{
		__vallocate( __n );
		for(; __n > 0 ; ++__end_, --__n )
			__vconstruct( __end_, __x );
	}

	template< class  _InputIterator >
	vector ( _InputIterator __first,  _InputIterator __last, const Allocator& __alloc = Allocator() )
	: __end_cap_( ft::make_pair( ft::nullptr_t, __alloc ) ),
	  __size_( 0 )
	{
		ptrdiff_t __n;
		__n = ft::distance( __first, __last );
		__vallocate( __n);
		for(; __n > 0 ; ++__end_, --__n )
			__vconstruct( __end_, *__first++ );
	}
	
	vector ( vector const & __other )
	: __begin_( ft::nullptr_t ),
	  __end_( __begin_ ),
	  __size_( 0 ) 
	{
		operator=( __other );
	}

	~vector()
	{
		clear();
		__vdeallocate();
	}
	
	vector& operator=( vector const & __other )
	{
		if ( this != &__other )
		{
			iterator __first = __other.__begin_;
			iterator __last =  __other.__end_;
			assign( __first , __last );
		}
		return *this;
	}

	allocator_type get_allocator() const
	{
		return this->__alloc();
	}



/* 
** ELEMENTS ACCESS
**
*/


	reference at( size_t __n )
	{
		__exceptionRangeVector( __n >= this->__size_, "Vector index out of range" );
		return this->__begin_[ __n ];
	}
	
	const_reference at( size_t __n ) const
	{
		__exceptionRangeVector( __n >= this->__size_, "Vector index out of range" );
		return this->__begin_ [ __n ];
	}

	reference operator[] ( size_t __n )
	{
		__exceptionRangeVector( __n >= this->__size_ , "vector[] index out of bounds" );
		return this->__begin_[ __n ];
		
	}

	const_reference operator[] ( size_t __n ) const 
	{
		__exceptionRangeVector( __n >= this->__size_, "vector[] index out of bounds" );
		return this->__begin_[ __n ];
		
	}

	reference	front() { return *(this->__begin_); }
	reference	back()  { return *( this->__end_ - 1); }

	const_reference	back()  const  { return *( this->__begin_ - 1 ); }
	const_reference	front() const  { return *( this->__begin_ ); }

	T* data() { return pointer( this->__begin_ ); };
	const T* data() const { return pointer( this->__begin_ ); };


/*
** ITERATORS
**
*/

	iterator begin() { return  this->__begin_; }
	iterator end()   { return this->__end_; }

	const_iterator cend()   const  { return this->__end_; }
	const_iterator cbegin() const  { return this->__begin_; }

	reverse_iterator rbegin() { return reverse_iterator( this->__end_ ); }
	reverse_iterator rend()   { return reverse_iterator( this->__begin_ ); }

	const_reverse_iterator crbegin() const { return reverse_iterator( this->__end_ ); }
	const_reverse_iterator crend()   const { return reverse_iterator( this->__begin_ ); }

/*
** ASSIGN
** Replaces the contents of the container.
** 1  Replaces the contents with count copies of value value
** 2 Replaces the contents with copies of those in the range [first, last). The behavior is undefined if either argument is an iterator into *this.
*/

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
			this->__size_ = __n;
		}
		else
		{
			__vdeallocate();
			__vallocate( __n );
			for(; __n > 0 ; ++__end_, --__n )
				__vconstruct( __end_, __u );
		}
	}

	template < typename _InputIterator >
	typename ft::enable_if
	<
		ft::is_input_it_tag< typename _InputIterator::iterator_category >::value &&
		!ft::is_integral< typename _InputIterator::value_type >::value,
	   void
	>::type
	assign( _InputIterator __first, _InputIterator __last )
	{
		clear();
		for (; __first != __last; ++__first )
			push_back( *__first );
	}

	template < typename _InputIterator >
	typename ft::enable_if
	<
		ft::is_integral< typename _InputIterator::value_type >::value,
	   void
	>::type
		assign( _InputIterator __first, _InputIterator __last )
		{
			clear();
			difference_type __ns = ft::distance( __first , __last );
			const size_t __n = static_cast<size_type>( __ns );
			if ( __n )
			{
				if ( __n > capacity() )
				{
					__vdeallocate();
					__vallocate( __n );
				}
				__construct_at_end(__first, __last);
			}
		}

/*
** Capacity
**
** empty: checks whether the container is empty
** size: returns the number of elements
** max_size: returns the maximum possible number of elements
** reserve: reserves storage N
** capacity: returns the number of elements that can be held in currently allocated storage
**
*/

	size_type size () const
	{
		return static_cast< size_type > ( this->__end_ - this->__begin_ ); 
	}

	size_type max_size() const
	{
		return this->__alloc().max_size();
	}

	size_type capacity() const
	{
		return static_cast< size_type > ( __end_cap() - this->__begin_ );
	}

	bool empty() const
	{
		return this->__size_ == 0;
	}

	void reserve ( size_type __n )
	{
		if ( __n > this->capacity() )
		{
			vector __v( this->__alloc() );
			__v.__vallocate( __n );
			__v.__construct_at_end( this->begin(), this->end() );
			swap( __v );
		}
	}
/*
** MODIFIERS
** clear: Erases all elements from the container. After this call, size() returns zero
** push_back : Appends the given element value to the end of the container.
** swap Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
**	All iterators and references remain valid. The past-the-end iterator is invalidated.
*/
	void clear()
	{
		size_type __old_size = size();
		for ( size_type i = 0; i < __old_size ; ++i )
		{
			 --__end_;
			__alloc().destroy( __end_ );
		}
		this->__size_ = 0;
	}


	iterator erase( iterator pos )
	{
		
	}

	void push_back( const value_type& __x )
	{
		 if  ( this->__size_ == this->capacity() )
		 	reserve( __recommend( this->__size_ + 1 ) );
		++this->__size_;
		__vconstruct( this->__end_++, __x );
	}

	void pop_back()
	{
		__alloc().destroy( &back() );
		this->__end_--;
		this->__size_--;
	}

	void swap( vector& __x )
	{
		ft::swap( this->__begin_, __x.__begin_ );
		ft::swap( this->__end_, __x.__end_ );
		ft::swap( this->__end_cap_, __x.__end_cap_ );
		ft::swap( this->__size_ , __x.__size_ );
	}
};

}

#endif
