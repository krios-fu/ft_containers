/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:19:01 by krios-fu          #+#    #+#             */
/*   Updated: 2022/01/27 18:18:23 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_HPP
# define __TREE_HPP

# include "./utils.hpp"
# include <memory>
# include "../utility/node.hpp"
# include <map>
#include <iostream>



namespace ft 
{
	
	template < class _Tp, class _Compare, class _Allocator = std::allocator<_Tp> >
	class tree
	{
		public:

		typedef _Tp															value_type;
		typedef _Compare													value_compare;
		typedef _Allocator													allocator_type;
		typedef ft::Node<_Tp>												node_type;
		typedef typename _Allocator::template rebind<node_type>::other		node_allocator;
		typedef typename node_allocator::pointer							pointer;
		typedef typename node_allocator::const_pointer						const_pointer;
		//typedef typename allocator_type::reference			reference;
		//typedef typename allocator_type::const_reference		const_eference;
		//typedef typename allocator_type::pointer				pointer;
		//typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type							size_type;
		typedef typename allocator_type::difference_type					differences_type;


	private:

		pointer										__root_;
		pointer										__nil_;
		size_type									__size_;
		value_compare								__compare_;
		
		ft::pair< pointer, node_allocator >		__end_alloc_;


		const node_allocator& __node_alloc() const { return __end_alloc_.second; }
		node_allocator& __node_alloc() { return __end_alloc_.second;  }

		pointer & __end_node() { return __end_alloc_.first; }
		const_pointer & __end_node() const { return __end_alloc_.first; }

<<<<<<< HEAD
	}; */
=======
		template < typename _NodePtr >
		bool __is_left_child( _NodePtr __x )
		{
			return __x == __x->parent->left;
		}

		template< typename _NodePtr >
		_NodePtr __child_min ( _NodePtr __x) 
		{
			while ( __x->left != __end_node() )
				__x = __x->left;
			return __x;
		}

		template < typename  _NodePtr >
		_NodePtr __child_max ( _NodePtr __x)
		{
			while ( __x->rigth != __end_node() )
				__x = __x->rigth;
			return __x;
		}



		template < typename _NodePtr>
		ft::pair< _NodePtr, bool >
			__treeLeaf ( _NodePtr __x, value_type const & __value )
		{
			while ( true )
			{
				if ( __compare_( __x->content, __value ) )
				{
					if ( __x->rigth == __end_node() )
						break; 
					__x = __x->rigth;
				}
				else if ( __compare_( __value, __x->content ) )
				{
					if ( __x->left == __end_node() )
						break ;
					__x = __x->left;
				}
				else
					return ft::make_pair( __x, false );
			}
			return ft::make_pair( __x, true );
		}

		pointer __vconstructNode( const value_type & __x )
		{
			pointer tmpNode = __node_alloc().allocate( 1 );
			__node_alloc().construct( tmpNode, __x );
			tmpNode->parent = __end_node();
			tmpNode->rigth = __end_node();
			tmpNode->left = __end_node();
			tmpNode->black = false;
			return tmpNode;
		}

		pointer __vconstructNode( const value_type & __x, pointer __parent )
		{
			pointer tmpNode = __node_alloc().allocate( 1 );
			__node_alloc().construct( tmpNode, __x );
			tmpNode->parent = __parent;
			tmpNode->rigth = __end_node();
			tmpNode->left = __end_node();
			tmpNode->black = false;
	

			return tmpNode;
		}

		public:

		template< typename _NodePtr >
		_NodePtr __next ( _NodePtr __x )
		{
			if ( __x->rigth != __end_node() )
				return __child_min( __x->rigth );
			while ( !__is_left_child( __x ) )
			{
				std::cout << "****** "<< __x->rigth->content.first << std::endl;
				__x = __x->parent;
			}
			return __x->parent;
		}

		explicit tree ( const allocator_type & __node_alloc_ = allocator_type() )
		: __compare_( value_compare() ),
		  __end_alloc_( ft::make_pair ( ft::nullptr_t , __node_alloc_ ) )
		{
			__size_ = 0;
			__nil_ = __vconstructNode( value_type() );
			__end_node() = __nil_;
			__end_node()->black = true;
			__root_ = __end_node();
		}

		ft::pair< pointer, bool> insert ( value_type & __x )
		{
			if ( __root_ == __end_node() )
			{
				__root_ = __vconstructNode( __x );
				__root_->black = true;
				return make_pair<pointer, bool>( __root_, true );
			}
			else
			{
				ft::pair< pointer, bool > __checkLeaf = __treeLeaf( __root_, __x );

				if ( __checkLeaf.second )
				{
					if ( __compare_( __checkLeaf.first->content, __x ) )
					{
						__checkLeaf.first->rigth = __vconstructNode( __x, __checkLeaf.first );
						__checkLeaf.first = __checkLeaf.first->rigth;
						
					}
					else if ( __compare_( __x, __checkLeaf.first->content ) )
					{
						__checkLeaf.first->left= __vconstructNode( __x, __checkLeaf.first );
						__checkLeaf.first = __checkLeaf.first->left;
						
					}
					__size_++;
				}
				return __checkLeaf;
			}
		}

	};
>>>>>>> 1931d6f6782bf835575a15e186565e8c50e20993
}
#endif 