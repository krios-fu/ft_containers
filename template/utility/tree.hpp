/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:19:01 by krios-fu          #+#    #+#             */
/*   Updated: 2022/01/31 01:26:35 by krios-fu         ###   ########.fr       */
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

		pointer & __root() { return __root_; };
		const_pointer & __root() const { return __root_; };



		bool __is_left_child( pointer __x )
		{
			return __x == __x->parent->left;
		}

		pointer __child_min ( pointer __x)
		{
			while ( __x->left != __end_node() )
				__x = __x->left;
			return __x;
		}

		pointer __child_max ( pointer __x)
		{
			while ( __x->right != __end_node() )
				__x = __x->right;
			return __x;
		}

		ft::pair< pointer, bool >
			__treeLeaf ( pointer __x, value_type const & __value )
		{
			while ( true )
			{
				if ( __compare_( __x->content, __value ) )
				{
					if ( __x->right == __end_node() )
						break; 
					__x = __x->right;
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

		pointer __tconstruct_node( const value_type & __x )
		{
			pointer tmpNode = __node_alloc().allocate( 1 );
			__node_alloc().construct( tmpNode, __x );
			tmpNode->parent = __end_node();
			tmpNode->right = __end_node();
			tmpNode->left = __end_node();
			tmpNode->black = false;
			size()++;
			return tmpNode;
		}

		pointer __tconstruct_node( const value_type & __x, pointer __parent )
		{
			pointer tmpNode = __node_alloc().allocate( 1 );
			__node_alloc().construct( tmpNode, __x );
			tmpNode->parent = __parent;
			tmpNode->right = __end_node();
			tmpNode->left = __end_node();
			tmpNode->black = false;
			size()++;
			return tmpNode;
		}
		void __tdestroy_alloc_node( pointer __node )
		{
			__node_alloc().destroy( __node );
			__node_alloc().deallocate( __node, 1 );
			size()--;
		}
		
		pointer __next ( pointer __x )
		{
			if ( __x->right != __end_node() )
				return __child_min( __x->right );
			while ( !__is_left_child( __x ) )
				__x = __x->parent;
			return __x->parent;
		}

		pointer __back ( pointer __x )
		{
			if ( __x->left != __end_node() )
				return __child_max( __x->left );
			while ( __is_left_child( __x ) )
				__x = __x->parent;
			return __x->parent;
		}

		void __right_rotate ( pointer __node )
		{
			pointer __tmp = __node->left;
			__node->left = __tmp->right;

			if ( __node->right != __end_node() )
				__tmp->right->parent = __node;
			__tmp->parent = __node->parent;

			if ( __node->parent == __end_node() )
				__root() = __tmp;

			if ( __is_left_child( __node ) )
				__node->parent->left = __tmp;
			else
				__node->parent->right= __tmp;
			__tmp->right = __node;
			__node->parent = __tmp;
		}

		void __left_rotate ( pointer __node )
		{
			pointer __tmp = __node->right;
			__node->right = __tmp->left;

			if ( __node->left != __end_node() )
				__tmp->left->parent = __node;
			__tmp->parent = __node->parent;

			if ( __node->parent == __end_node() )
				__root() = __tmp;

			if ( __is_left_child( __node ) )
				__node->parent->left = __tmp;
			else
				__node->parent->right= __tmp;
			__tmp->left = __node;
			__node->parent = __tmp;
		}


		pointer __case_red ( pointer __node, pointer __uncle , pointer __root )
		{
			__node = __node->parent;
			__node->black = true;
			__node = __node->parent;
			__node->black = __node == __root;
			__uncle->black = true;
			return __node;
		}


		pointer __case_black( pointer __node, bool __isLeft )
		{
			if ( __isLeft )
			{
				if ( !__is_left_child( __node ) )
				{
					__node = __node->parent;
					__left_rotate ( __node );
				}

					__node = __node->parent;
					__node->black = true;
					__node = __node->parent;
					__node->black = false;
					__right_rotate( __node );
			}
			else
			{
				if ( __is_left_child( __node ) )
				{
					__node = __node->parent;
					__right_rotate( __node );
					
				}

				__node = __node->parent;
				__node->black = true;
				__node = __node->parent;
				__node->black = false;
				__left_rotate ( __node );
			}
			return __node;
		}

		void __balance_tree_after_insert( pointer __root, pointer __node )
		{
			__node->black = __node == __root;
			while ( __node != __root && !__node->parent->black )
			{
				if ( __is_left_child( __node->parent ) )
				{
					pointer __uncle = __node->parent->parent->right;
					if ( __uncle != __end_node() && !__uncle->black )
						__node = __case_red( __node, __uncle, __root );
					else
					{
						__node = __case_black( __node, true );
						break ;
					}
				}
				else
				{
					pointer __uncle = __node->parent->parent->left;
					if ( __uncle != __end_node() && !__uncle->black )
						__node = __case_red( __node, __uncle, __root);
					else
					{
						__node = __case_black( __node, false );
						break ;
					}
					
				}

			}
		}

		void __balance_tree_after_remove( pointer __uncle, pointer __childHole )
		{
			while ( 42 )
			{
				if ( !__is_left_child( __uncle ) )
				{
					if ( !__uncle->black )
					{
						__uncle->black = true;
						__uncle->parent->black = false;
						__left_rotate ( __uncle->parent );
						
						if ( __root() == __uncle->left )
							__root() = __uncle;
						__uncle = __uncle->left->right;
					}
					
					if ( __uncle->left->black && __uncle->right->black )
					{
						__uncle->black = false;
						__childHole = __uncle->parent;

						if ( __childHole == __root() || !__childHole->black )
						{
							__childHole->black = true;
							break;
						}
						__uncle = __is_left_child( __childHole ) ?
							__childHole->parent->right :
							__childHole->parent->left;
					}
					else
					{
						if ( __uncle->right == __end_node() || __uncle->right->black )
						{
							__uncle->left->black = true;
							__uncle->black = false;
							__right_rotate( __uncle );
							__uncle = __uncle->parent;
						}
						__uncle->black = __uncle->parent->black;
						__uncle->parent->black = true;
						__uncle->right->black = true;
						__left_rotate ( __uncle->parent );
						break;
					}
				}
				else
				{
					if ( !__uncle->black )
					{
						__uncle->black = true;
						__uncle->parent->black = false;
						__right_rotate( __uncle->parent );
						
						if ( __root() == __uncle->right )
							__root() = __uncle;
						__uncle = __uncle->right->left;
					}
					if ( __uncle->left->black && __uncle->right->black )
					{
						__uncle->black = false;
						__childHole = __uncle->parent;

						if ( !__childHole->black ||  __childHole == __root()   )
						{
							__childHole->black = true;
							break;
						}
						__uncle = __is_left_child( __childHole ) ?
									__childHole->parent->right :
									__childHole->parent->left;
					}
					else
					{
						if ( __uncle->left == __end_node() || __uncle->left->black )
						{
							__uncle->right->black = true;
							__uncle->black = false;
							__left_rotate( __uncle );
							__uncle =  __uncle->parent;
						}
						__uncle->black = __uncle->parent->black;
						__uncle->parent->black = true;
						__uncle->left->black = true;
						__right_rotate( __uncle->parent );
						break;
					}
				}
			}
		}
		public:


		explicit tree ( const allocator_type & __node_alloc_ = allocator_type() )
		: __compare_( value_compare() ),
		  __end_alloc_( ft::make_pair ( ft::nullptr_t , __node_alloc_ ) )
		{
			__size_ = 0;
			__nil_ = __node_alloc().allocate( 1 );
			__node_alloc().construct( __nil_, value_type() );
			__nil_->black = true;
			__nil_->parent = __nil_;
			__nil_->right = __nil_;
			__nil_->left = __nil_;
			__end_node() = __nil_;
			__root() = __end_node();
		}

			void print(const std::string& prefix = "", const ft::Node<_Tp>* node = NULL, bool isLeft = false) {
				if (node == NULL)
					node = __root_;
				if (node != __end_node()) {
					 std::cout << BLACK << prefix << WHITE ;
					 std::cout << BLACK << (isLeft ? "├──" : "└──" ) << WHITE;
					if (!node->black)
						std::cout << RED ""<< node->content.first << WHITE <<std::endl;
					else {
						if ( node == __end_node() )
							std::cout << "nil"  << std::endl;
						else
							std::cout << node->content.first  << WHITE << std::endl;
					}
					print(prefix + (isLeft ? "│   " : "    "), node->right, true);
					print(prefix + (isLeft ? "│   " : "    "), node->left, false);
				}
			}

		void remove( pointer __dNode )
		{
			pointer __hole = (  __dNode->left == __end_node() ||
								__dNode->right == __end_node() ) ?
								__dNode :
								__back( __dNode );

			pointer __childHole  = __hole->left != __end_node() ? __hole->left : __hole->right;

			pointer __uncle = __end_node();

			if ( __childHole != __end_node() )
				__childHole->parent = __hole->parent;

			if ( __is_left_child( __hole ) )
			{
				__hole->parent->left = __childHole;
				if ( __hole != __root() )
					__uncle = __hole->parent->right;
				else
					__root() = __childHole;
			}
			else
			{
				__hole->parent->right = __childHole;
				__uncle = __hole->parent->left;
			}

			bool __colorRemove = __hole->black;

			if ( __hole != __dNode )
			{
				__hole->parent = __dNode->parent;
				if ( __is_left_child( __dNode ) )
					__hole->parent->left = __hole;
				else
					__hole->parent->right = __hole;
				__hole->left = __dNode->left;
				__hole->left->parent = __hole;
				__hole->right = __dNode->right;
				if ( __hole->right != __end_node() )
					__hole->right->parent = __hole;
				__hole->black = __dNode->black;
				if ( __root() == __dNode )
					__root() = __hole;
			}

			__tdestroy_alloc_node( __dNode );
			if ( __colorRemove && __root() != __end_node() )
			{
				if ( __childHole != __end_node() )
					__childHole->black = true;
				else
					__balance_tree_after_remove( __uncle, __childHole );
			}
		}

		ft::pair< pointer, bool> insert ( value_type & __x )
		{
			if ( __root() == __end_node() )
			{
				__root() = __tconstruct_node( __x );
				__end_node()->left = __root();
				__end_node()->right = __root();
				__root()->black = true;
				return ft::make_pair<pointer, bool>( __root(), true );
			}
			else
			{
				ft::pair< pointer, bool > __checkLeaf = __treeLeaf( __root(), __x );

				if ( __checkLeaf.second )
				{
					if ( __compare_( __checkLeaf.first->content, __x ) )
					{
						__checkLeaf.first->right = __tconstruct_node( __x, __checkLeaf.first);
						__checkLeaf.first = __checkLeaf.first->right;
						
					}
					else if ( __compare_( __x,__checkLeaf.first->content ) )
					{
						__checkLeaf.first->left= __tconstruct_node( __x, __checkLeaf.first);
						__checkLeaf.first = __checkLeaf.first->left;
						
					}
					__balance_tree_after_insert( __root(), __checkLeaf.first );
				}
				
				__root()->parent = __end_node();
				__end_node()->left = __root();
				__end_node()->right = __root();
				return __checkLeaf;
			}
		}
		
		size_type& size() { return __size_; }
		size_type& size() const { return __size_; }
	};
}

#endif