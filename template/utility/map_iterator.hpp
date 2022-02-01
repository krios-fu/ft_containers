/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:15:45 by krios-fu          #+#    #+#             */
/*   Updated: 2022/02/01 21:00:17 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_ITERATOR_HPP
#define __MAP_ITERATOR_HPP

# include "../utility/node.hpp"




namespace ft
{
	template < typename _Node, typename  _Vt >
	class mapIterator
	{
		public:
				typedef _Vt												value_type;
				typedef ptrdiff_t 										difference_type;
				typedef typename std::bidirectional_iterator_tag		iterator_category;
				typedef _Node											node_pointer;
				typedef value_type*										pointer;
				typedef value_type&										reference;

				protected:

				node_pointer __node_;
				node_pointer __end_node_;


		private:
		
		bool __is_left_child( node_pointer __x )
		{
			return __x == __x->parent->left;
		}

		node_pointer __child_min ( node_pointer __x ) const 
		{
			while ( __x->left != __end_node_ )
				__x = __x->left;
			return __x;
		}

		node_pointer __child_max ( node_pointer __x ) const 
		{
			while ( __x->right != __end_node_)
				__x = __x->right;
			return __x;
		}

		public:

		~mapIterator(){}


		explicit mapIterator( node_pointer __node , node_pointer __end_node )
			: __node_( __node ),
			  __end_node_ ( __end_node  )
		{
		}

		template< typename _NodePtr, typename _ValueT >
		mapIterator ( const mapIterator<_NodePtr, _ValueT> & __x )
		{
			__node_ = __x.__node_;
			__end_node_ = __x.__end_node_;
		}

		template< typename _NodePtr, typename _ValueT >
		mapIterator& operator=( const mapIterator<_NodePtr, _ValueT > & __x )
		{
			__node_ = __x.getNode();
			__end_node_ = __x.getEndNode();
			return *this;
		}

		const node_pointer getNode() const 
		{
			return __node_;
		}

		const node_pointer getEndNode() const
		{
			return __end_node_;
		}


		reference operator*() const { return __node_->content; }

		pointer operator->() const { return &__node_->content; }

		mapIterator& operator++()
		{
			if ( __node_->right != __end_node_ )
			{
				__node_ = __child_min( __node_->right );
				return *this;
			}
			else
			{
				while ( !__is_left_child( __node_ ) )
					__node_ = __node_->parent;
				__node_ = __node_->parent;
				return *this;
				
			}
		}

		mapIterator operator++(int)
		{
			mapIterator tmp( *this );
			operator++();
			return tmp;
		}

		mapIterator& operator--()
		{
			if ( __node_->left != __end_node_ )
			{
				__node_ =  __child_max( __node_->left );
				return *this;
			}
			else
			{
				while ( __is_left_child( __node_ ) )
					__node_ = __node_->parent;
				__node_ = __node_->parent;
				return *this;
			}
		}

		mapIterator operator--(int)
		{
			mapIterator tmp( *this );
			operator--();
			return tmp;
		}
		
		
	};

	template < typename _N1, typename _V1, typename _N2, typename _V2 >
	bool operator== ( const ft::mapIterator<_N1, _V1> __x, const ft::mapIterator<_N2, _V2> __y )
	{
		return __x.getNode() == __y.getNode() ;
	}

	template < typename _N1, typename _V1,  typename _N2, typename _V2>
	bool operator< ( const ft::mapIterator<_N1, _V1> __x, const ft::mapIterator<_N2, _V2> __y )
	{
		return __x.getNode() < __y.getNode();
	}

	template < typename _N1, typename _V1, typename _N2, typename _V2 >
	bool operator!= ( const ft::mapIterator<_N1, _V1> __x, const ft::mapIterator<_N2, _V2> __y )
	{
		return !( __x == __y);
	}

	template < typename _N1, typename _V1,  typename _N2, typename _V2>
	bool operator> ( const ft::mapIterator<_N1, _V1> __x, const ft::mapIterator<_N2, _V2> __y )
	{
		return __y < __x ;
	}

	template < typename _N1, typename _V1,  typename _N2, typename _V2>
	bool operator>= ( const ft::mapIterator<_N1, _V1> __x, const ft::mapIterator<_N2, _V2> __y )
	{
		return !(__x < __y ) ;
	}
	
	template < typename _N1, typename _V1,  typename _N2, typename _V2>
	bool operator<= ( const ft::mapIterator<_N1, _V1> __x, const ft::mapIterator<_N2, _V2> __y )
	{
		return !(__y < __x ) ;
	}

	template < typename _N1, typename _V1,  typename _N2, typename _V2>
	ptrdiff_t operator- ( const ft::mapIterator<_N1, _V1> __x, const ft::mapIterator<_N2, _V2> __y )
	{
		return __x.getNode() - __y.getNode() ;
	}

	template < typename _N, typename _V>
	ptrdiff_t operator+ ( typename ft::mapIterator<_N, _V>::difference_type __N, const ft::mapIterator<_N, _V> __x )
	{
		return (ft::mapIterator<_N,_V>)(__x.getNode() + __N);
	}
	
}
#endif