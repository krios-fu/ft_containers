#ifndef __FT_ITERATOR_HPP
# define __FT_ITERATOR_HPP


#include "./nullptr.hpp"
namespace ft
{
		/* 
		**    Star iterators_traits
		**
		** is the type trait class that provides uniform interface
		** to the properties of LegacyIterator types.
		**
		*/
	
		/*  LegacyIterator
		**
		** The LegacyIterator requirements describe types that can be used to identify and traverse the elements of a container.
		** Empty class types used to indicate iterator categories
		*/

	struct input_iterator_tag {}; // LegacyInputIterator .
	struct output_iterator_tag {}; // LegacyOutputIterator 
	struct forward_iterator_tag			: public input_iterator_tag {};  // LegacyForwardIterator
	struct bidirectional_iterator_tag	: public forward_iterator_tag {};  //  LegacyBidirectionalIterator
	struct random_access_iterator_tag	: public bidirectional_iterator_tag {}; // LegacyRandomAccessIterator

		/*  Check iterator_tag*/

	template <bool is_valid, typename T>
		struct check_iterator_tag
		{
			typedef T type;
			const static bool value = is_valid;
		};
	

	template< typename T >
		struct is_input_it_tag : public check_iterator_tag <false , T> {};
		
	template<>
		struct is_input_it_tag<ft::input_iterator_tag> : public check_iterator_tag<true, ft::input_iterator_tag> {};
		
	template<>
		struct is_input_it_tag<ft::output_iterator_tag> : public check_iterator_tag<true, ft::output_iterator_tag> {};

	template<>
		struct is_input_it_tag<ft::forward_iterator_tag> : public check_iterator_tag<true, ft::forward_iterator_tag> {};
		
	template<>
		struct is_input_it_tag<ft::bidirectional_iterator_tag> : public check_iterator_tag<true, ft::bidirectional_iterator_tag> {};
		
	template<>
		struct is_input_it_tag<ft::random_access_iterator_tag> : public check_iterator_tag<true, ft::random_access_iterator_tag> {};


	template< typename T >
		struct __is_forward_iterator: public check_iterator_tag <false , T> {};
	template<>
		struct __is_forward_iterator <ft::forward_iterator_tag> : public check_iterator_tag<true, ft::forward_iterator_tag> {};

	template< class _Iter >
		struct iterator_traits
		{
			typedef typename _Iter::difference_type		difference_type;
			typedef typename _Iter::value_type			value_type;
			typedef typename _Iter::pointer				pointer;
			typedef typename _Iter::reference			reference;
			typedef typename _Iter::iterator_category	iterator_category;
		};

	template< class _Iter>
		struct iterator_traits < _Iter * >
		{
			typedef ptrdiff_t						difference_type;
			typedef _Iter							value_type;
			typedef _Iter*							pointer;
			typedef _Iter&							reference;
			typedef std::random_access_iterator_tag	iterator_category;
		};

	template< class _Iter>
		struct iterator_traits < const _Iter * >
		{
			typedef ptrdiff_t						difference_type;
			typedef _Iter							value_type;
			typedef _Iter const *					pointer;
			typedef _Iter const &					reference;
			typedef std::random_access_iterator_tag	iterator_category;
		};

		/*  END ITERATOR_TRAITS */
/* 
	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
		struct iterator
		{
			typedef T								value_type;
			typedef Distance						difference_type;
			typedef Pointer							pointer;
			typedef Reference						refrences;
			typedef Category						iterator_category;
		}; */

/* 	template <class _InputIter>
		typename ft::iterator_traits< _InputIter >::difference_type
			distance( _InputIter __first, _InputIter __last )
			{
				typename ft::iterator_traits<_InputIter>::difference_type __r( __last - __first );
				return __r;
			} */
	

	/* START REVERSE_ITERATOR */

template < class _Iter >
class reverse_iterator
	{

			protected:
				_Iter  current;
			public:
				typedef _Iter																iterator_type;
				typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;
				typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
				typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
				typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
				typedef typename ft::iterator_traits<iterator_type>::reference				reference;

				/* Default constructor  */
				reverse_iterator() : current(ft::nullptr_t) {}
				explicit reverse_iterator(_Iter __x) : current(__x) {}

				/* Copy constructor */
				template < class _Up >
				reverse_iterator( const reverse_iterator<_Up>& __other )
					: current( __other.base() ) {}

				// ~reverse_iterator();

			/* 	template < class _Up >
					reverse_iterator& operator=( const reverse_iterator<_Up>& __other)
					{
						
						current = __other.base();
						return *this;
					} */
				_Iter base() const{ return current; }

				reference			operator*() const { _Iter __tmp = current; return *--__tmp ;}
				pointer				operator->() const { return &(operator*()) ;}

				reverse_iterator&	operator++()		{ --current; return *this ; }
				reverse_iterator&	operator--()		{ ++current; return *this; }
				reverse_iterator	operator++( int )	{ reverse_iterator __tmp( *this ); --current; return __tmp;}
				reverse_iterator	operator--( int )	{ reverse_iterator __tmp( *this ); ++current; return __tmp;}

				reverse_iterator	operator+ ( difference_type __N ) const { return reverse_iterator( current - __N );}
				reverse_iterator&	operator+=( difference_type __N )		{ current -= __N; return *this ; }
				reverse_iterator	operator- ( difference_type __N ) const { return reverse_iterator( current + __N );}
				reverse_iterator&	operator-=( difference_type __N )		{ current += __N; return *this ;}
				reference			operator[]( difference_type __N ) const { return *(*this + __N) ;}
		};


		template< class _Iter1>
		bool operator== ( const ft::reverse_iterator<_Iter1>& __x, const ft::reverse_iterator<_Iter1>& __y )
		{ 
			return __x.base() == __y.base(); 
		}

		template< class _Iter1, class _Iter2>
		bool operator== ( const ft::reverse_iterator<_Iter1>& __x, const ft::reverse_iterator<_Iter2>& __y )
		{ 
			return __x.base() == __y.base(); 
		}

		template< class _Iter1>
		bool operator!=( const ft::reverse_iterator<_Iter1>& __x, const ft::reverse_iterator<_Iter1>& __y )
		{ 
			return !( __x.base() == __y.base()) ; 
		}

		template < class _Iter1, class _Iter2>
		bool operator!= ( const ft::reverse_iterator<_Iter1>& __x, const ft::reverse_iterator<_Iter2>&  __y )
		{
			return  !(__x.base() == __y.base());
		}

		template < class _Iter1, class _Iter2 >
		bool operator< ( const ft::reverse_iterator<_Iter1>& __x, const ft::reverse_iterator <_Iter2>& __y )
		{
			return __x.base() > __y.base();
		}

		template < class _Iter1 >
		bool operator< ( const ft::reverse_iterator<_Iter1>& __x, const ft::reverse_iterator <_Iter1>& __y )
		{
			return __x.base() > __y.base();
		}

		template < class _Iter1, class _Iter2 >
		bool operator> ( const reverse_iterator<_Iter1>& __x , const reverse_iterator <_Iter2>& __y )
		{
			return __x.base() < __y.base();
		}

		template < class _Iter1 >
		bool operator> ( const reverse_iterator<_Iter1>& __x , const reverse_iterator <_Iter1>& __y )
		{
			return __x.base() < __y.base();
		}

		template < class _Iter1, class _Iter2 >
		bool operator>= ( const reverse_iterator<_Iter1>& __x , const reverse_iterator <_Iter2>& __y )
		{
			return __x.base() <= __y.base();
		}

		template < class _Iter1 >
		bool operator>= ( const reverse_iterator<_Iter1>& __x , const reverse_iterator <_Iter1>& __y )
		{
			return __x.base() <= __y.base();
		}

		template < class _Iter1, class _Iter2 >
		bool operator<= ( const reverse_iterator<_Iter1>& __x , const reverse_iterator <_Iter2>& __y )
		{
			return __x.base() >= __y.base();
		}

		template < class _Iter1 >
		bool operator<= ( const reverse_iterator<_Iter1>& __x , const reverse_iterator <_Iter1>& __y )
		{
			return __x.base() >= __y.base();
		}


		template< class _Iter1, class _Iter2>
		typename ft::reverse_iterator<_Iter1>::difference_type
			operator-( const ft::reverse_iterator<_Iter1>& __x , const ft::reverse_iterator<_Iter2>& __y )
			{
				return __y.base() - __x.base() ;
			}
	
		template< class _Iter1>
		typename ft::reverse_iterator<_Iter1>::difference_type
			operator-( const ft::reverse_iterator<_Iter1>& __x , const ft::reverse_iterator<_Iter1>& __y )
			{
				return __x.base() - __y.base() ;
			}

		template< class _Iter>
		ft::reverse_iterator<_Iter>
			operator+( typename ft::reverse_iterator<_Iter>::difference_type __N , const ft::reverse_iterator<_Iter>& __x )
			{
				return  ft::reverse_iterator<_Iter> ( __x.base() - __N ) ;
			}

		/* Ramdom_assccess_iterator start */

	template < class _Iter>
		class random_access_iterator
		{
			public: 
				typedef _Iter																iterator_type;
				typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;
				typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
				typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
				typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
				typedef typename ft::iterator_traits<iterator_type>::reference				reference;

			protected:
				iterator_type __i;
	
				
			public:

			random_access_iterator() : __i( ft::nullptr_t ){}
	
			template <class _Up>
				random_access_iterator( const random_access_iterator<_Up>&__u )
					: __i( __u.base() ) {}

			random_access_iterator( const iterator_type & __it ) : __i( __it ) {}

	virtual ~random_access_iterator(){}

			random_access_iterator & operator=( const random_access_iterator& __u )
			{
				if (this == &__u)
					return *this;
				this->__i = __u.base();
				return *this;
			}

			iterator_type base() const { return __i; }

			reference	operator*()		const { return *__i ;}
			pointer		operator->()	const { return &( this->operator*() );}

			random_access_iterator& operator++() { ++__i; return *this; }
			random_access_iterator& operator--() { --__i; return *this; }

			random_access_iterator operator++ ( int ) { random_access_iterator __tmp( *this ); ++(*this); return __tmp;}
			random_access_iterator operator-- ( int ) { random_access_iterator __tmp( *this ); --(*this); return __tmp;}

			random_access_iterator operator+ ( difference_type __N ) const { return  __i  + __N; }
			random_access_iterator operator- ( difference_type __N ) const { return *this + (-__N) ;}

			random_access_iterator& operator+= ( difference_type __N ) { __i += __N; return *this; }
			random_access_iterator& operator-= ( difference_type __N ) { *this += -__N; return *this; }

			reference 	operator[] ( difference_type __N ) const { return __i[__N]; }
	};

	template<class _Iter1, class _Iter2>
		bool operator== ( const ft::random_access_iterator<_Iter1>& __x , const ft::random_access_iterator<_Iter2>& __y ) { return __x.base() == __y.base(); }
	
	template<class _Iter1, class _Iter2>
		bool operator< ( const ft::random_access_iterator<_Iter1>& __x, const ft::random_access_iterator<_Iter2>& __y ) { return __x.base() < __y.base(); }

	template<class _Iter1, class _Iter2>
		bool operator!= ( const ft::random_access_iterator<_Iter1>& __x, ft::random_access_iterator<_Iter2>& __y ) { return !( __x == __y ) ; }

	template<class _Iter1, class _Iter2>
		bool operator> ( const ft::random_access_iterator<_Iter1>& __x, const ft::random_access_iterator<_Iter2>& __y ) { return __y < __x; }

	template<class _Iter1, class _Iter2>
		bool operator>= ( const ft::random_access_iterator<_Iter1>& __x, const ft::random_access_iterator<_Iter2>& __y ) { return !(__x < __y); }

	template<class _Iter1, class _Iter2>
		bool operator<= ( const ft::random_access_iterator<_Iter1>& __x, const ft::random_access_iterator<_Iter2>& __y ) { return !(__y < __x); }

	template <class _Iter1>
		bool operator!= ( const ft::random_access_iterator<_Iter1>& __x, const ft::random_access_iterator<_Iter1> __y ) { return !( __x == __y ); }

	template<class _Iter1>
		bool operator> ( const ft::random_access_iterator<_Iter1>& __x, const ft::random_access_iterator<_Iter1>& __y ) { return __y < __x; }

	template<class _Iter1>
		bool operator>= ( const ft::random_access_iterator<_Iter1>& __x, const ft::random_access_iterator<_Iter1>& __y ) { return !(__x < __y); }
	
	template<class _Iter1>
		bool operator<= ( const ft::random_access_iterator<_Iter1>& __x, const ft::random_access_iterator<_Iter1>& __y ) { return !(__y < __x); }
	

	template <class _Iter1, class _Iter2>
		typename ft::random_access_iterator<_Iter1>::difference_type
		operator- ( const ft::random_access_iterator<_Iter1>& __x , const ft::random_access_iterator<_Iter2>&__y ) { return __x.base() - __y.base(); }

	template <class _Iter>
		ft::random_access_iterator<_Iter>
		operator+ ( typename  ft::random_access_iterator<_Iter>::difference_type __N, 
					ft::random_access_iterator<_Iter> __x )
		{ 
			__x += __N;
			return __x;
		}



/* Iterator map */
/* 
	template < class _TreeIterator >
	class map_iterator
	{
		private:
		typedef typename _TreeIterator::_NodeType					_NodeType;
		typedef typename _TreeIterator::__pointer_traits			__pointer_traits;

		_TreeIterator __i;
		public: 

		typedef std::bidirectional_iterator_Tag						iterator_category;
		typedef typename 



	}; */

}
#endif
