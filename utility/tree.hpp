/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:19:01 by krios-fu          #+#    #+#             */
/*   Updated: 2022/02/04 17:44:47 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TREE_HPP
# define __TREE_HPP

# include "./utils.hpp"
# include <memory>
# include "../utility/node.hpp"
#include "../utility/tree_iterator.hpp"


namespace ft 
{

template< class _Tp,
		  class _Compare,
		  class _Allocator
		>
class tree
{

public:

	typedef _Tp  														value_type;
	typedef _Compare													value_compare;
	typedef _Allocator  												allocator_type;
	typedef ft::Node<_Tp>   											node_type;

	typedef typename _Allocator::template rebind<node_type>::other		node_allocator;
	typedef typename node_allocator::pointer							pointer;
	typedef typename node_allocator::const_pointer						const_pointer;
	typedef typename node_allocator::reference							reference;
	typedef typename node_allocator::const_reference					const_reference;

	typedef typename ft::tree_iterator<pointer, value_type>				iterator;
	typedef typename ft::tree_iterator<const_pointer, const value_type>	const_iterator;
	typedef typename ft::reverse_iterator<iterator>  					reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	typedef typename allocator_type::size_type							size_type;
	typedef typename allocator_type::difference_type					differences_type;

private:

	pointer 								__root_;
	pointer 								__nil_;
	size_type								__size_;
	value_compare							__compare_;
	ft::pair< pointer, node_allocator > 	__end_alloc_;

	tree( const tree& __other ) ;

	tree& operator= (const tree& __other ) ;

	const node_allocator& __node_alloc() const { return __end_alloc_.second; }
	node_allocator& __node_alloc() { return __end_alloc_.second;  }

	pointer __end_node() { return __end_alloc_.first; }

	size_type& __size() { return __size_; }
	const size_type& __size() const { return __size_; }

	void __reWriteNill() const 
	{
		__nil_->parent = __nil_;
		__nil_->right = __root_;
		__nil_->left = __root_;
		__root_->parent = __nil_;
		__nil_->black = true;
	}
		// const_pointer &__end_node() const { return static_cast<const_pointer>(__end_alloc_.first); }

		// pointer & __root_ { return __root_; };
		// const_pointer & __root_ const { return __root_; };

	bool __is_left_child( pointer __x )
	{
		return __x == __x->parent->left;
	}

	pointer __child_min ( pointer __x)
	{
		while ( __x->left != __nil_ )
			__x = __x->left;
		return __x;
	}

	const_pointer __child_min ( const_pointer __x) const 
	{
		while ( __x->left != __nil_ )
			__x = __x->left;
		return __x;
	}

	pointer __child_max ( pointer __x)
	{
		while ( __x->right != __nil_ )
			__x = __x->right;
		return __x;
	}

	pointer __successor( pointer __x )
	{
		if ( __x->right != __nil_ )
			return __child_min( __x->right );
		while ( !__is_left_child( __x ) )
			__x = __x->parent;
		return __x->parent;
	}

	pointer __predecessor ( pointer __x )
	{
		if ( __x->left != __nil_ )
			return __child_max( __x->left );
		while ( __is_left_child( __x ) )
			__x = __x->parent;
		return __x->parent;
	}

	pointer __find ( value_type const & __x ) 
	{
		pointer __tmp = __root_;

		while ( __tmp != __nil_ )
		{
			if ( __compare_( __tmp->content, __x ) )
				__tmp = __tmp->right;
			else if ( __compare_( __x, __tmp->content ) )
				__tmp = __tmp->left;
			 else
			 	return __tmp;
		}
		return __tmp;
	}

	const_pointer __find ( value_type const & __x ) const
	{
		pointer __tmp = __root_;

		while ( __tmp != __nil_ )
		{
			if ( __compare_( __tmp->content, __x ) )
				__tmp = __tmp->right;
			else if ( __compare_( __x, __tmp->content ) )
				__tmp = __tmp->left;
			else
				return __tmp;
		}
		return __nil_ ;
	}

	template < typename __Sw >
	void __swap( __Sw &a, __Sw  &b)
	{
		__Sw  c;
		c = a;
		a = b;
		b = c;
	}

	ft::pair< pointer, bool >
		__treeLeaf ( pointer __x, value_type const & __value )
		{
			while ( true )
			{
				if ( __compare_( __x->content, __value ) )
				{
					if ( __x->right == __nil_ )
						break; 
					__x = __x->right;
				}
				else if ( __compare_( __value, __x->content ) )
				{
					if ( __x->left == __nil_ )
						break ;
					__x = __x->left;
				}
				else
					return ft::make_pair(__x, false );
			}
			return ft::make_pair( __x, true );
		}

	pointer __tconstruct_node( const value_type & __x )
	{
		pointer tmpNode = __node_alloc().allocate( 1 );
		__node_alloc().construct( tmpNode, node_type(__x , __nil_ ) );
		__size()++;
		return tmpNode;
	}

	pointer __tconstruct_node( const value_type & __x, pointer __parent )
	{
		pointer tmpNode = __node_alloc().allocate( 1 );
		__node_alloc().construct( tmpNode, node_type( __x , __nil_ ) );
		tmpNode->parent = __parent;
		__size()++;
		return tmpNode;
	}
	
	void __tdestroy_alloc_node( pointer __node )
	{
		__node_alloc().destroy( __node );
		__node_alloc().deallocate( __node, 1 );
	}

	void __tdestroy_alloc_tree( pointer __node )
	{
		if ( __node != __nil_ )
		{
			__tdestroy_alloc_tree( __node->left );
			__tdestroy_alloc_tree( __node->right );

			__tdestroy_alloc_node( __node );
		}
	}
		
	void __right_rotate ( pointer __node )
	{
		if ( __node == __nil_ || __node->left== __nil_ )
			return ;

		pointer __tmp = __node->left;
		__node->left = __tmp->right;

		if ( __node->right != __nil_ )
			__tmp->right->parent = __node;
		__tmp->parent = __node->parent;

		if ( __node->parent == __nil_ )
		{
			__root_ = __tmp;
			__reWriteNill();
		}

		if ( __is_left_child( __node ) )
			__node->parent->left = __tmp;
		else
			__node->parent->right= __tmp;

		__node->parent = __tmp;
		__tmp->right = __node;
	}

	void __left_rotate ( pointer __node )
	{
		if ( __node == __nil_ || __node->right == __nil_ )
			return ;
		pointer __tmp = __node->right;
		__node->right = __tmp->left;

		if ( __node->left != __nil_ )
			__tmp->left->parent = __node;
		__tmp->parent = __node->parent;

		if ( __node->parent == __nil_ )
		{
			__root_ = __tmp;
			__reWriteNill();
		}

		if ( __is_left_child( __node ) )
			__node->parent->left = __tmp;
		else
			__node->parent->right= __tmp;

		__node->parent = __tmp;
		__tmp->left = __node;
	}

	ft::pair< iterator, bool> __insert ( value_type const & __x )
	{
		if ( __root_ == __nil_ )
		{
			__root_ = __tconstruct_node( __x );
			__reWriteNill();
			__root_->black = true;
			return ft::make_pair( iterator( __root_, __nil_ ), true );
		}
		else
		{
			ft::pair< pointer, bool > __checkLeaf = __treeLeaf( __root_, __x );

			if ( __checkLeaf.second )
			{
				if ( __compare_( __checkLeaf.first->content, __x ) )
				{
					__checkLeaf.first->right = __tconstruct_node( __x, __checkLeaf.first );
					__checkLeaf.first = __checkLeaf.first->right;
					
				}
				else if ( __compare_( __x,__checkLeaf.first->content ) )
				{
					__checkLeaf.first->left= __tconstruct_node( __x, __checkLeaf.first );
					__checkLeaf.first = __checkLeaf.first->left;
					
				}
				__balance_tree_after_insert( __root_, __checkLeaf.first );
				__reWriteNill();
				return ft::make_pair( iterator(__checkLeaf.first, __nil_ ), true );
			}
			__reWriteNill();
			return ft::make_pair( iterator( __checkLeaf.first, __nil_ ), false );
		}
	}

	void __balance_tree_after_insert( pointer __root, pointer __node )
	{
		__node->black = __node == __root;
		while ( __node != __root && !__node->parent->black )
		{
			if ( __is_left_child( __node->parent ) )
			{
				pointer __uncle = __node->parent->parent->right;
				if ( __uncle != __nil_ && !__uncle->black )
					__node = __case_red_insert( __node, __uncle, __root );
				else
				{
					__node = __case_black_insert( __node, true );
					break ;
				}
			}
			else
			{
				pointer __uncle = __node->parent->parent->left;
				if ( __uncle != __nil_ && !__uncle->black )
					__node = __case_red_insert( __node, __uncle, __root);
				else
				{
					__node = __case_black_insert( __node, false );
					break ;
				}
				
			}

		}
	}

	pointer __case_red_insert( pointer __node, pointer __uncle , pointer __root )
	{
		__node = __node->parent;
		__node->black = true;
		__node = __node->parent;
		__node->black = __node == __root;
		__uncle->black = true;
		return __node;
	}

	pointer __case_black_insert( pointer __node, bool __isLeft )
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

	void __remove( pointer __dNode  )
	{

		pointer __hole = (  __dNode->left == __nil_ ||
							__dNode->right == __nil_ ) ?
							__dNode :
							__predecessor ( __dNode );

		pointer __childHole  = __hole->left != __nil_ ? __hole->left : __hole->right;
		pointer __uncle = __nil_;

		if ( __childHole != __nil_ )
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
			if ( __hole->right != __nil_ )
				__hole->right->parent = __hole;
			__hole->black = __dNode->black;
			if ( __root_ == __dNode )
					__root_ = __hole;
		}
			__tdestroy_alloc_node( __dNode );
			__reWriteNill();
			__size()--;
		if ( __colorRemove && __root_ != __nil_ )
			__balance_tree_after_remove( __uncle, __childHole );
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

					if ( __root_ == __uncle->left )
						__root_ = __uncle;
					__uncle = __uncle->left->right;
				}
				
				if ( (__uncle->left == __nil_ || __uncle->left->black ) &&
					(__uncle->right == __nil_ && __uncle->right->black ) )
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
					if ( __uncle->right == __nil_ || __uncle->right->black )
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
					
					if ( __root_ == __uncle->right )
						__root_ = __uncle;
					__uncle = __uncle->right->left;
				}
				if ( (__uncle->left == __nil_ ||  __uncle->left->black )&& 
					(__uncle->right == __nil_ && __uncle->right->black ) )
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
					if ( __uncle->left == __nil_ || __uncle->left->black )
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

	explicit tree ( const value_compare & __comp = value_compare(),
					const allocator_type & __node_alloc_ = allocator_type() )
	: __compare_( __comp  ),
	  __end_alloc_( ft::make_pair ( ft::nullptr_t , __node_alloc_ ) )
	{
		__size_ = 0;
		__nil_ = __node_alloc().allocate( 1 );
		__node_alloc().construct( __nil_, node_type( value_type(), __nil_ ) );
		__nil_->black = true;
		__nil_->parent = __nil_;
		__nil_->right = __nil_;
		__nil_->left = __nil_;
		__end_alloc_.first = __nil_;
		__root_ = __nil_;
	}

	~tree()
	{
		__tdestroy_alloc_tree( __root_ );
		__tdestroy_alloc_node( __nil_ );
	}


	iterator		begin() {  return iterator( __child_min( __root_ ), __nil_ ); }
	const_iterator	begin() const {return const_iterator( __child_min( __root_ ), __nil_); }

	iterator		end() {  return iterator(__nil_, __nil_); }
	const_iterator	end() const { return const_iterator( __nil_ , __nil_); }

	reverse_iterator		rbegin() { return reverse_iterator( end() ); }
	reverse_iterator		rend() { return reverse_iterator( begin() ); }

	const_reverse_iterator	rbegin() const { return const_reverse_iterator( end() ); }
	const_reverse_iterator	rend() const { return const_reverse_iterator( begin() ); }

	ft::pair< iterator, bool> insert ( value_type const & __x ) { return __insert ( __x ); }

	void remove ( const value_type & __x ) { __remove( __find( __x ) ); }

	size_type size() const { return __size_ ; }

	iterator find ( value_type const & __x ) { return iterator ( __find( __x ), __nil_ ); }

	const_iterator find ( value_type const & __x ) const { return const_iterator ( __find( __x ), __nil_ ); }

	value_compare value_comp() const  { return __compare_; }

	size_type max_size() const { return __node_alloc().max_size(); }
	
	bool empty() const { return ( __size() ) ? false : true; }

	allocator_type get_allocator() const { return __node_alloc(); }

	void clear()
	{
		__tdestroy_alloc_tree( __root_ );
		__size() = 0;
		__root_ = __nil_;
	}

	void	swap( tree& __other_)
	{
			__swap(__root_, __other_.__root_);
			__swap(__size_, __other_.__size_);
			__swap(__nil_, __other_.__nil_);
			__swap(__end_alloc_, __other_.__end_alloc_);
			__swap(__compare_, __other_.__compare_);
	}

	void print(const std::string& prefix = "", const ft::Node<_Tp>* node = NULL, bool isLeft = false)
	{
		if (node == NULL)
			node = __root_;
		if (node != __nil_ ) {
			 std::cout << BLACK << prefix << WHITE ;
			 std::cout << BLACK << (isLeft ? "├──" : "└──" ) << WHITE;
			if (!node->black)
				std::cout << RED ""<< node->content.first << WHITE <<std::endl;
			else {
				if ( node == __nil_ )
					std::cout << "nil"  << std::endl;
				else
					std::cout << node->content.first  << WHITE << std::endl;
			}
			print(prefix + (isLeft ? "│   " : "    "), node->right, true);
			print(prefix + (isLeft ? "│   " : "    "), node->left, false);
		}
	}

};
}

#endif