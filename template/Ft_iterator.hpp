#ifndef __FT_ITERATOR_HPP
# define __FT_ITERATOR_HPP

#include <vector>
namespace ft
{
		/* 
		**      Star iterators_traits
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
	struct forward_iterator_tag : public input_iterator_tag {};  // LegacyForwardIterator
	struct bidirectional_iterator_tag : public forward_iterator_tag {};  //  LegacyBidirectionalIterator
	struct random_access_iterator_tag : public bidirectional_iterator_tag {}; // LegacyRandomAccessIterator

		/*  Check iterator_tag*/

	template <bool is_valid, typename T>
		struct check_iterator_tag
		{
			typedef T type;
			const static bool value = is_valid;
		};
	

	template< typename T>
		struct is_input_it_tag : public check_iterator_tag <false , T> {};
		
	template <>
		struct is_input_it_tag<ft::input_iterator_tag> : public check_iterator_tag<true, ft::input_iterator_tag> {};
		
	template <>
		struct is_input_it_tag<ft::output_iterator_tag> : public check_iterator_tag<true, ft::output_iterator_tag> {};

	template <>
		struct is_input_it_tag<ft::forward_iterator_tag> : public check_iterator_tag<true, ft::forward_iterator_tag> {};
		
	template <>
		struct is_input_it_tag<ft::bidirectional_iterator_tag> : public check_iterator_tag<true, ft::bidirectional_iterator_tag> {};
		
	template <>
		struct is_input_it_tag<ft::random_access_iterator_tag> : public check_iterator_tag<true, ft::random_access_iterator_tag> {};

	template< class _Iter>
		struct iterator_traits
		{
			typedef typename _Iter::difference_type		difference_type;
			typedef typename _Iter::value_type			value_type;
			typedef typename _Iter::pointer				pointer;
			typedef typename _Iter::reference			reference;
			typedef typename _Iter::iterator_category	iterator_category;
		};

	template< class _Iter>
		struct iterator_traits < _Iter *>
		{
			typedef ptrdiff_t						difference_type;
			typedef _Iter							value_type;
			typedef _Iter*							pointer;
			typedef _Iter&							reference;
			typedef ft::random_access_iterator_tag	iterator_category;
		};

	template< class _Iter>
		struct iterator_traits < const _Iter *>
		{
			typedef ptrdiff_t						difference_type;
			typedef _Iter							value_type;
			typedef _Iter*							pointer;
			typedef _Iter&							reference;
			typedef ft::random_access_iterator_tag	iterator_category;
		};

		/*  END ITERATOR_TRAITS */

	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
		struct iterator
		{
			typedef T								value_type;
			typedef Distance						difference_type;
			typedef Pointer							pointer;
			typedef Reference						refrences;
			typedef Category						iterator_category;
		};

	template <class _InputIter>
		typename ft::iterator_traits< _InputIter >::difference_type
			distance( _InputIter __first, _InputIter __last )
			{
				typename ft::iterator_traits<_InputIter>::difference_type __r(0);
				for( ; __first != __last; ++__first)
					++__r;
				return __r;
			}
	

	/* START REVERSE_ITERATOR */

	template < class _Iter >
		class reverse_iterator
			: public ft::iterator < typename ft::iterator_traits<_Iter>::iterator_category,
									typename ft::iterator_traits<_Iter>::value_type,
									typename ft::iterator_traits<_Iter>::difference_type,
									typename ft::iterator_traits<_Iter>::pointer,
									typename ft::iterator_traits<_Iter>::reference>
		{
			private:
				_Iter __t;
			protected:
				_Iter  current;
			public:
				typedef _Iter												iterator_type;
				typedef typename iterator_traits<_Iter>::difference_Type	difference_type;
				typedef typename iterator_traits<_Iter>::reference			refrence;
				typedef typename iterator_traits<_Iter>::pointer			pointer;

				/* Default constructor  */
				reverse_iterator() : __t() , current() {}
				explicit reverse_iterator(_Iter __x) : __t(__x), current(__x) {}

				/* Copy constructor */
				template < class _Up >
				reverse_iterator( const reverse_iterator<_Up>& __other )
					: __t( __other.base() ) , current( __other.base() ) {}

				virtual ~reverse_iterator();

				template < class _Up >
					reverse_iterator& operator=( const reverse_iterator<_Up>& __other)
					{
						__t = current = __other.base();
						return *this;
					}
				_Iter base const()
				{
					return current;
				}
		};
}
#endif