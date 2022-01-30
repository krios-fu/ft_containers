/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:19:01 by krios-fu          #+#    #+#             */
/*   Updated: 2022/01/30 21:48:08 by krios-fu         ###   ########.fr       */
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
			while ( __x->right != __end_node() )
				__x = __x->right;
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

		pointer __tconstructNode( const value_type & __x )
		{
			pointer tmpNode = __node_alloc().allocate( 1 );
			__node_alloc().construct( tmpNode, __x );
			tmpNode->parent = __end_node();
			tmpNode->right = __end_node();
			tmpNode->left = __end_node();
			tmpNode->black = false;

			return tmpNode;
		}

		pointer __tconstructNode( const value_type & __x, pointer __parent )
		{
			pointer tmpNode = __node_alloc().allocate( 1 );
			__node_alloc().construct( tmpNode, __x );
			tmpNode->parent = __parent;
			tmpNode->right = __end_node();
			tmpNode->left = __end_node();
			tmpNode->black = false;
			__size_++;
			return tmpNode;
		}
		void __tdestroyNode( pointer __node )
		{
			__node_alloc().destroy( __node );
			__node_alloc().deallocate( __node, 1 );
		}
		
		template< typename _NodePtr >
		_NodePtr __next ( _NodePtr __x )
		{
			if ( __x->right != __end_node() )
				return __child_min( __x->right );
			while ( !__is_left_child( __x ) )
				__x = __x->parent;
			return __x->parent;
		}

		template< typename _NodePtr >
		_NodePtr __back ( _NodePtr __x )
		{
			if ( __x->left != __end_node() )
				return __child_max( __x->left );
			while ( __is_left_child( __x ) )
				__x = __x->parent;
			return __x->parent;
		}

		public:

			void print(const std::string& prefix = "", const ft::Node<_Tp>* node = NULL, bool isLeft = false) {
				if (node == NULL)
					node = __root_;
				if (node != __end_node()) {
					 std::cout << BLACK << prefix << WHITE ;
					 std::cout << BLACK << (isLeft ? "├──" : "└──" ) << WHITE;
					if (!node->black)
						std::cout << RED ""<< node->content.first << WHITE <<std::endl;
					else {
						if (node == __end_node() )
							std::cout << "nil"  << std::endl;
						else
							std::cout << node->content.first  << WHITE << std::endl;
					}
					print(prefix + (isLeft ? "│   " : "    "), node->right, true);
					print(prefix + (isLeft ? "│   " : "    "), node->left, false);
				}
			}


		template< typename _NodePtr >
			void __rightRotate ( _NodePtr __x )
			{
				_NodePtr __y = __x->left;
				__x->left = __y->right;
				if ( __x->right != __end_node() )
					__y->right->parent = __x;
				__y->parent = __x->parent;
				if ( __x->parent == __end_node()  )
					__root_ = __y; 
				if ( __is_left_child( __x ) )
					__x->parent->left = __y;
				else 
					__x->parent->right= __y;
				__y->right = __x;
				__x->parent = __y;
			}

			template< typename _NodePtr >
			void __leftRotate ( _NodePtr __x )
			{
				_NodePtr __y = __x->right;
				__x->right = __y->left;
				if ( __x->left != __end_node() )
					__y->left->parent = __x;
				__y->parent = __x->parent;
			if ( __x->parent == __end_node()  )
					__root_ = __y; 
				if ( __is_left_child( __x ) )
					__x->parent->left = __y;
				else 
					__x->parent->right= __y;
				__y->left = __x;
				__x->parent = __y;
			}


			template < typename _NodePtr >
			_NodePtr  __caseRed ( _NodePtr __node, _NodePtr __uncle , _NodePtr __root )
			{
				__node = __node->parent;
				__node->black = true;
				__node = __node->parent;
				__node->black = __node == __root;
				__uncle->black = true;
				return __node;
			}

			template < typename _NodePtr >
			_NodePtr __caseBlack( _NodePtr __node, bool __isLeft )
			{
				if ( __isLeft )
				{
					if ( !__is_left_child( __node ) )
					{
						__node = __node->parent;
						__leftRotate( __node );
					}

						__node = __node->parent;
						__node->black = true;
						__node = __node->parent;
						__node->black = false;
						__rightRotate( __node );
				}
				else 
				{
					if ( __is_left_child( __node ) )
					{
						__node = __node->parent;
						__rightRotate( __node );
						
					}
				
					__node = __node->parent;
					__node->black = true;
					__node = __node->parent;
					__node->black = false;
					__leftRotate( __node );
				}
				return __node;
			}

		
		template < typename _NodePtr >
		void __balanceTree( _NodePtr __root, _NodePtr __node )
		{
			__node->black = __node == __root;
			while ( __node != __root && !__node->parent->black )
			{
				if ( __is_left_child( __node->parent ) )
				{
					_NodePtr __uncle = __node->parent->parent->right;
					if ( __uncle != __end_node() && !__uncle->black )
						__node = __caseRed( __node, __uncle, __root );
					else
					{
						__node = __caseBlack( __node, true );
						break ;
					}
				}
				else
				{
					_NodePtr __uncle = __node->parent->parent->left;
					if ( __uncle != __end_node() && !__uncle->black )
						__node = __caseRed( __node, __uncle, __root);
					else
					{
						__node = __caseBlack( __node, false );
						break ;
					}
					
				}

			}
		}
	
		template < typename _NodePtr >
		void __removeTree( _NodePtr __dNode )
		{
			_NodePtr __hole = ( __dNode->left == __end_node() || __dNode->right == __end_node() ) ? 
								__dNode : __back( __dNode );
			
			_NodePtr __childHole  = __hole->left != __end_node() ? __hole->left : __hole->right;
			
			_NodePtr __uncle = __end_node();


			if ( __childHole != __end_node()  ) 
				__childHole->parent = __hole->parent;

			if ( __is_left_child( __hole ) )
			{
				__hole->parent->left = __childHole;
				if ( __hole != __root_ )
					__uncle = __hole->parent->right;
				else
					__root_ = __childHole;
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
				if ( __root_ == __dNode )
					__root_ = __hole;
			}

			__tdestroyNode( __dNode );
			if ( __colorRemove && __root_ != __end_node() )
			{
				if ( __childHole != __end_node() )
					__childHole->black = true;
				else 
					__balanceRemove(__uncle, __childHole );
			}
			
		}

		template < typename _NodePtr >
		void __balanceRemove( _NodePtr __uncle, _NodePtr __childHole )
		{
			while ( 42 )
			{
				if ( !__is_left_child( __uncle ) )
				{
					if ( !__uncle->black )
					{
						__uncle->black = true;
						__uncle->parent->black = false;
						__leftRotate( __uncle->parent );
						
						if ( __root_ == __uncle->left )
							__root_ = __uncle;
						__uncle = __uncle->left->right;
					}
					
					if ( __uncle->left->black  && __uncle->right->black )
					{
						__uncle->black = false;
						__childHole = __uncle->parent;

						if ( __childHole == __root_ || !__childHole->black )
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
							__rightRotate( __uncle );
							__uncle =  __uncle->parent;
						}

						__uncle->black = __uncle->parent->black;
						__uncle->parent->black = true;
						__uncle->right->black = true;
						__leftRotate( __uncle->parent );
						break;
					}
				}
				else
				{
					if ( !__uncle->black )
					{
						__uncle->black = true;
						__uncle->parent->black = false;
						__rightRotate( __uncle->parent );
						
						if ( __root_ == __uncle->right )
							__root_ = __uncle;
						__uncle = __uncle->right->left;
					}
					if ( __uncle->left->black && __uncle->right->black )
					{
						__uncle->black = false;
						__childHole = __uncle->parent;

						if ( !__childHole->black ||  __childHole == __root_   )
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
							__leftRotate( __uncle );
							__uncle =  __uncle->parent;
						}

						__uncle->black = __uncle->parent->black;
						__uncle->parent->black = true;
						__uncle->left->black = true;
						__rightRotate( __uncle->parent );
						break;
					}
					
				}
			}
		
		}

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
			__root_ = __end_node();
		}

		ft::pair< pointer, bool> insert ( value_type & __x )
		{
			if ( __root_ == __end_node() )
			{
				__root_ = __tconstructNode( __x );
				__end_node()->left = __root_;
				__end_node()->right = __root_;
				__root_->black = true;
				return ft::make_pair<pointer, bool>( __root_, true );
			}
			else
			{
				ft::pair< pointer, bool > __checkLeaf = __treeLeaf( __root_, __x );

				if ( __checkLeaf.second )
				{
					if ( __compare_( __checkLeaf.first->content, __x ) )
					{
						__checkLeaf.first->right = __tconstructNode( __x, __checkLeaf.first);
						__checkLeaf.first = __checkLeaf.first->right;
						
					}
					else if ( __compare_( __x,__checkLeaf.first->content ) )
					{
						__checkLeaf.first->left= __tconstructNode( __x, __checkLeaf.first);
						__checkLeaf.first = __checkLeaf.first->left;
						
					}
					 __balanceTree( __root_, __checkLeaf.first );
				}
				
			__root_->parent = __end_node();
			__end_node()->left = __root_;
			__end_node()->right = __root_;

				return __checkLeaf;
			}
		}

	};
}
#endif 