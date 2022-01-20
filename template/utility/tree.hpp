/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:19:01 by krios-fu          #+#    #+#             */
/*   Updated: 2022/01/20 17:35:12 by krios-fu         ###   ########.fr       */
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
			T					__content;
			Node*				__parent;
			Node*				__rigth;
			Node*				__left;

		Node( const_reference __val = T() ):
			__content(__val), parent(nullptr), left(nullptr), right(nullptr) {}
		Node(Node const &other):
			__content(other.__content), parent(nullptr), left(nullptr), right(nullptr) {}
		};

	template < class _Tp, class _Compare, class _Allocator>
	class tree
	{
		public:

		typedef _Tp															value_type;
		typedef _Compare													value_compare;
		typedef _Allocator													allocator_type;
		typedef ft::Node<T>													node_type;
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
		
		ft::pair< pointer, node_allocator >		__end_cap_;



		const node_allocator& __node_alloc() const { return __end_cap_.second; }
		node_allocator& __node_alloc() { return __end_cap_.second;  }

		pointer & __end_node() { return __end_cap.first; }
		const_pointer & __end_node() const { return __end_cap.first; }

		public:

		explicit tree ( const )

	};
}
#endif 