/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:47:01 by krios-fu          #+#    #+#             */
/*   Updated: 2022/01/24 19:49:29 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <memory>

#include "../utility/utils.hpp"
namespace ft
{

template < class T , class Allocator = std::allocator<T> >
class vector
{
public:
	typedef Allocator													allocator_type;
	typedef T															value_type;
	typedef typename allocator_type::reference  						reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef ft::random_access_iterator<pointer>							iterator;
	typedef ft::random_access_iterator<const_pointer>					const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type 	difference_type;
	typedef typename allocator_type::size_type							size_type;

private:
	pointer     						__begin_;
	pointer     						__end_;
	size_type   						__size_;
	ft::pair< pointer, allocator_type > __end_cap_;

/*
** AUX FUNCTIONS
**
*/
	const allocator_type& __alloc() const { return __end_cap_.second; }

	allocator_type& __alloc() { return __end_cap_.second;  }

	const pointer& __end_cap() const { return __end_cap_.first; }

	pointer& __end_cap() { return __end_cap_.first; }

	void __vallocate( size_type __n )
	{
		__begin_ = __alloc().allocate( __n );
		__end_cap() = __begin_ + __n;
		__end_ = __begin_;
	}

	void __vconstruct(const value_type& __x )
	{
		__alloc().construct( this->__end_, __x );
		this->__size_++;
	}

	void __vdeallocate()
	{
		if ( __begin_ != ft::nullptr_t )
		{
			__alloc().deallocate( __begin_, capacity() );
			__begin_ = ft::nullptr_t;
			__end_ = __begin_;
			__end_cap() = __begin_;
			__size_ = 0;
		}
	}

	template < typename __Sw >
	void __swap( __Sw &a, __Sw  &b)
	{
		__Sw  c;
		c = a;
		a = b;
		b = c;
	}
	
	void __exceptionRangeVector( bool __is, char const *str ) const 
	{
		if( __is )
			throw std::out_of_range( str );
	}


	size_type __recommend( size_type __new_size ) const 
	{
		const size_type __ms = this->max_size();
		if ( __new_size > __ms )
			throw ( std::length_error( "Vector::reserve length error " ) );
		const size_type __cap = this->capacity();
		if ( __cap >= __ms / 2 )
			return __ms;
		return ft::max( (2 * __cap ), __new_size );
	}

	template < typename _InputIterator >
	void __construct_at_end ( _InputIterator __first , _InputIterator __last )
	{
		for (; __first != __last ;  ++__first, ++__end_ )
			__vconstruct( *__first );
	}

	void __construct_at_end ( size_type __n , const_reference __x )
	{
		for (size_type i = 0; i < __n ; ++this->__end_ , ++i )
			__vconstruct( __x );
	}
	
	pointer __move( pointer __first, pointer __last, pointer __result )
	{
		const size_t __n = std::distance (__first , __last);
		if ( __n > 0 )
			std::memmove(__result, __first, __n * sizeof( __result ) );
		return __result + __n;
	}

public:

/*
** CONSTRUCTORS
** 1 Default constructor Constructs an empty container with a default-constructed allocator.
** 2 Constructs the container with count copies of elements with value value.
** 3 Constructs the container with the contents of the range [first, last).
** 4 Copy constructor
** 5 Destructor Destructs the vector. The destructors of the elements are called and the used storage is deallocated.
**		Note, that if the elements are pointers, the pointed-to objects are not destroyed.
** 6 operator= assigns values to the container
** 7 get_allocator returns the associated allocator
*/
	explicit vector ( const allocator_type & __alloc = allocator_type() )
	: __begin_( ft::nullptr_t ),
	  __end_( __begin_ ),
	  __size_( 0 ),
	  __end_cap_( ft::make_pair( ft::nullptr_t, __alloc) )
	{
			__end_cap() = __begin_;
	}

	explicit vector( size_type __n, const value_type & __x = value_type(), const allocator_type& __alloc = allocator_type() )
	: __begin_( ft::nullptr_t ),
	  __end_( __begin_ ),
	  __size_( 0 ),
	  __end_cap_( ft::make_pair( ft::nullptr_t, __alloc ) )
	{
		__vallocate( __n );
		for(; __n > 0 ; ++__end_, --__n )
			__vconstruct( __x );
	}

	template< class  _InputIterator >
	vector  (
				_InputIterator __first,
				_InputIterator __last,
				const Allocator& __alloc = Allocator(),
				typename ft::enable_if
				<
					!ft::is_integral<_InputIterator>::value, _InputIterator
				>::type * = NULL
			)
	:__size_( 0 ),
	 __end_cap_( ft::make_pair( ft::nullptr_t, __alloc ) )
	{
		ptrdiff_t __n;
		__n = std::distance( __first, __last );
		__vallocate( __n );
		__construct_at_end( __first, __last );
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
		if ( __begin_ != ft::nullptr_t )
		{
			clear();
			__vdeallocate();
		}
	}

	vector& operator=( vector const & __other )
	{
		if ( this != &__other )
		{
			__vdeallocate();
			insert( this->__end_, __other.__begin_ , __other.__end_);
		}
		return *this;
	}

	allocator_type get_allocator() const
	{
		return this->__alloc();
	}

/* 
** ELEMENTS ACCESS
** at access specified element with bounds checking
** operator[] access specified element
** front access the first element
** back access the last element
** data direct access to the underlying array
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

	reference	front() { return *( this->__begin_ ); }
	reference	back()  { return *( this->__end_ - 1); }

	const_reference	back()  const  { return *( this->__end_ - 1 ); }
	const_reference	front() const  { return *( this->__begin_ ); }

	T* data() { return pointer( this->__begin_ ); };
	const T* data() const { return pointer( this->__begin_ ); };

/*
** ITERATORS
** return an specific iterator
*/

	iterator begin() { return this->__begin_ ; }
	iterator end()   { return this->__end_ ; }

	const_iterator end()   const  { return this->__end_ ; }
	const_iterator begin() const  { return this->__begin_ ; }

	reverse_iterator rbegin() { return reverse_iterator( this->__end_ ); }
	reverse_iterator rend()   { return reverse_iterator( this->__begin_ ); }

	const_reverse_iterator rbegin() const { return reverse_iterator( this->__end_ ); }
	const_reverse_iterator rend()   const { return reverse_iterator( this->__begin_ ); }

/*
** ASSIGN
** Replaces the contents of the container.
** 1 Replaces the contents with count copies of value value
** 2 Replaces the contents with copies of those in the range [first, last).
**   The behavior is undefined if either argument is an iterator into *this.
*/

	void assign( size_type __n , const_reference __u )
	{
		clear();
		if ( __n == 0 )
			return ;
		if ( __n <= capacity() )
			__construct_at_end( __n , __u );
		else
		{
			__vdeallocate();
			__vallocate( __recommend( __n ) );
			for(; __n > 0 ; ++__end_, --__n )
				__vconstruct( __u );
		}
	}

	template < typename _InputIterator >
	void assign(
					_InputIterator __first,
					_InputIterator __last,
					typename ft::enable_if
					<
						!ft::is_integral<_InputIterator>::value, _InputIterator
					>::type * = NULL
				)
	{
			clear();
			difference_type __ns = std::distance( __first , __last );
			const size_t __n = static_cast<size_type>( __ns );
			if ( __n )
			{
				if ( __n > capacity() )
				{
					__vdeallocate();
					__vallocate( __recommend( __n ) );
				}
				__construct_at_end( __first, __last );
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
*/

	bool empty() const
	{
		return this->__size_ == 0;
	}

	size_type size () const
	{
		return this->__size_;
	}

	size_type max_size() const
	{
		return this->__alloc().max_size();
	}

	size_type capacity() const
	{
		return static_cast< size_type > ( __end_cap() - this->__begin_ );
	}

	void reserve ( size_type __n )
	{
		if ( __n > this->capacity() )
		{
			vector __v( this->__alloc() );
			__v.__vallocate( __n );
			__v.__construct_at_end( __begin_ , __end_ );
			swap( __v );
		}
	}

/*
** MODIFIERS
** clear: Erases all elements from the container. After this call, size() returns zero
** insert : 
**  1 inserts value before pos
**  3 inserts count copies of the value before pos
**  4 inserts elements from range [first, last) before pos
** erase Erases the specified elements from the container.
**  1 Removes the element at pos.
**  2 Removes the elements in the range [first, last).
** push_back : Appends the given element value to the end of the container.
** pop_back Removes the last element of the container.
** resize changes the number of elements stored
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
	
	iterator insert( iterator __positions , const value_type& __x  )
	{
		pointer __p = this->__begin_ + ( __positions - begin() );
		
		if ( this->__end_ < this->__end_cap() )
		{
			if ( __p == this->__end_ )
			{
				__vconstruct( __x );
				++this->__end_;
			}
			else
			{
				__move( __p, this->__end_++ - 1, __p + 1 );
				*__p = __x;
				++this->__size_;
			}
		}
		else
		{
			vector __v( this->__alloc() );
			__v.reserve( __recommend( size() + 1 ) );
			__v.__construct_at_end( this->__begin_ , __p );
			__v.push_back( __x );
			__v.__construct_at_end( __p , this->__end_ );
			swap( __v );
		}
		return __p;
	}

	iterator insert( iterator __positions, size_type __n, const  value_type& __x )
	{
		pointer __p = this->__begin_ + ( __positions - begin() );

		if ( __n > 0 )
		{
			if ( __n <= static_cast<size_type>( this->__end_cap() - this->__end_ ) )
			{
				if ( __p == this->__end_ )
					__construct_at_end( __n, __x );
				else
				{
					__move( __p, this->__end_++ - 1, __p + __n );
					for ( size_type i = 0; i < __n; i++, ++__p )
						*__p = __x;
					this->__size_ += __n;
				}
			}
			else
			{
				vector __v( this->__alloc() );
				__v.reserve( __recommend ( size() + __n ) );
				__v.__construct_at_end( this->__begin_, __p );
				__v.__construct_at_end( __n, __x );
				__v.__construct_at_end( __p, this->__end_ );
				swap( __v );
			}
		}
		return __positions;
	}

	template< class _InputIterator >
	iterator insert(
						iterator __positions,
						_InputIterator __first,
						_InputIterator __last,
						typename ft::enable_if
						<
							!ft::is_integral<_InputIterator>::value, _InputIterator
						>::type * = NULL
					)
	{
		pointer __p = this->__begin_ + ( __positions - begin() );
		difference_type __n = std::distance( __first , __last );
		if ( __n > 0 )
		{
			if ( __n <= this->__end_cap() - this->__end_  )
			{
				if ( __p == this->__end_ )
					__construct_at_end( __first, __last );
				else
				{
					__move( __p, this->__end_++ - 1 ,__p + __n );
					for (; __first != __last ; ++__p, ++__first )
						*__p = *__first;
					this->__size_ += __n;
				}
			}
			else
			{
				vector __v( this->__alloc() );
				__v.reserve( __recommend( size() + __n ) );
				__v.__construct_at_end( this->__begin_, __p );
				__v.__construct_at_end( __first, __last );
				__v.__construct_at_end( __p , this->__end_);
				swap( __v );
			}
		}
		return __positions;
	}

	iterator erase( iterator __positions )
	{
		if ( __positions == end() )
			pop_back();
		pointer __p = this->__begin_ + ( __positions  - begin() ) + 1; 
		for (; __p != this->__end_ ; ++__p )
			 *(__p - 1) = *(__p);
		__alloc().destroy( this->__end_ - 1 );
		this->__end_--;
		this->__size_--;
		return __positions;
	}

	iterator erase ( iterator __first, iterator __last )
	{
		if ( __first != __last )
		{
			for (; __first != __last ; --__last )
				this->erase( __last - 1 );
		}
		return( iterator( __first ) );
	}

	void push_back( const value_type& __x )
	{
		if ( this->size() == this->capacity() )
			reserve( __recommend( this->__size_ + 1 ) );
		__vconstruct( __x );
		 this->__end_++;
	}

	void pop_back()
	{
		__alloc().destroy( &back() );
		this->__end_--;
		this->__size_--;
	}

	void resize( size_type __sz )
	{
		resize( __sz, T() );
/* 		size_type __cs = size();
		if ( __cs < __sz )
		{
			if ( __sz > capacity() )
				reserve( __sz );
			for ( size_type __diff = ( __sz - __cs) ; __diff > 0 ; --__diff, ++__end_ )
				__vconstruct( T() );
		}
		for(; __cs > __sz ; )
			erase( begin() + (--__cs) ); */
	}

	void resize( size_type __sz, const_reference __x )
	{
		size_type __cs = size();
		if ( __cs < __sz )
		{
			 if ( __sz > capacity() )
				reserve( __sz );
			for ( size_type __diff = ( __sz - __cs) ; __diff > 0 ; --__diff, ++__end_ )
				__vconstruct( __x );
		}
		for(; __cs > __sz ; )
			erase( begin() + (--__cs) );
		
	}

	void swap( vector& __x )
	{
		__swap( this->__begin_, __x.__begin_ );
		__swap( this->__end_, __x.__end_ );
		__swap( this->__end_cap_, __x.__end_cap_ );
		__swap( this->__size_ , __x.__size_ );
	}
};

/*
** Non-member functions
**
*/
	template< typename T, class Allocator>
	bool operator==( const ft::vector<T, Allocator> & __x,  const ft::vector<T, Allocator> & __y )
	{
		return __x.size() == __y.size() && ft::equal( __x.begin(), __x.end(), __y.begin() );
	}

	template< typename T, class Allocator >
	bool operator!=( const ft::vector<T, Allocator> & __x,  const ft::vector<T, Allocator> & __y )
	{
		return !( __x == __y );
	}

	template <typename T, class Allocator>
	bool operator<( const ft::vector<T, Allocator> & __x,  const ft::vector<T, Allocator> & __y )
	{
		return ft::lexicographical_compare( __x.begin(), __x.end(), __y.begin(), __y.end() );
	}
	template <typename T, class Allocator>
	bool operator>( const ft::vector<T, Allocator> & __x,  const ft::vector<T, Allocator> & __y )
	{
		return  __y < __x;
	}

	template <typename T, class Allocator>
	bool operator>=( const ft::vector<T, Allocator> & __x,  const ft::vector<T, Allocator> & __y )
	{
		return !(__x < __y);
	}

	template <typename T, class Allocator>
	bool operator<=( const ft::vector<T, Allocator> & __x,  const ft::vector<T, Allocator> & __y )
	{
		return !(__y < __x);
	}

	template <typename T, class Allocator>
	void swap ( const ft::vector<T, Allocator> & __x,  const ft::vector<T, Allocator> & __y )
	{
		__x.swap( __y );
	}
}

#endif
