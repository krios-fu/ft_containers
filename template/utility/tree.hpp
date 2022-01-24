/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:19:01 by krios-fu          #+#    #+#             */
/*   Updated: 2022/01/24 22:13:26 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_HPP
# define __TREE_HPP

#include "./utils.hpp"
#include <memory>
#include <map>


namespace ft 
{
	template<class T>
		struct Node
		{
			T					content;
			bool				isBlack;
			Node*				parent;
			Node*				rigth;
			Node*				left;

 			Node( T const &  __val = T() )
			: content(__val),
			  isblack( false ),
			  parent(nullptr),
			  rigth(nullptr),
			  left(nullptr){}

			Node( Node const &other )
			: content( other.__content ),
			  isBlack( false ),
			  parent(nullptr),
			  rigth(nullptr),
			  left(nullptr){}

			bool isBlack()
			{
				return isBlack;
			}

			bool isLeft()
			{
				return this == this->parent->left; 
			}

			Node const & next()
			{
				
			}

		
		};

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

		pointer										root;
		pointer										nill;
		node_allocator								n_allocator;
		size_type									size;
		
		ft::pair< pointer, node_allocator >		__end_alloc_;


		const node_allocator& __node_alloc() const { return __end_alloc_.second; }
		node_allocator& __node_alloc() { return __end_alloc_.second;  }

		pointer & __end_node() { return __end_alloc_.first; }
		const_pointer & __end_node() const { return __end_alloc_.first; }

		public:

		explicit tree ( node_type const & __x = node_type(), const allocator_type & __node_alloc_ = allocator_type() )
		: root( nullptr ),
		 nill ( nullptr ), 
		 size( 0 ),
		 __end_alloc_( ft::make_pair ( nullptr , __node_alloc_ ))
		 {
			root = __node_alloc().allocate( 1 );
			__node_alloc().construct( root, __x );
		 }

		int print()
		{
			return root->__content.first;
		}
	};
}
#endif 