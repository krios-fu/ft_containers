#ifndef __TREE_HPP
# define __TREE_HPP

#include "./utils.hpp"
#include <memory>


namespace ft 
{

	template < class _Tp, class _Compare, class _Allocator>
	class tree
	{
		public:

		typedef _Tp												value_type;
		typedef _Compare										value_compare;
		typedef _Allocator										allocator_type;

		// typedef typename allocator_type::reference				reference;
		// typedef typename allocator_type::const_reference		const_eference;
		// typedef typename allocator_type::pointer				pointer;
		// typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::difference_type		differences_type;

		typedef struct Node
		{
			value_type			__content;
			Node*				__parent;
			Node*				__rigth;
			Node*				__left;

		Node(const_reference __val=value_type()):
			__content(__val), parent(nullptr), left(nullptr), right(nullptr) {}
		Node(Node const &other):
			__content(other.__content), parent(nullptr), left(nullptr), right(nullptr) {}
		};
	private:

		typedef Node*								n_pointer;
		n_pointer									__begin_node_;
		n_pointer									__end_node_;
		ft::pair< pointer, allocator_type > 		__end_cap_;

		public:


		const allocator_type& __alloc() const { return __end_cap_.second; }
		allocator_type& __alloc() { return __end_cap_.second;  }

		n_pointer & __end_cap() { return __end_cap.first; }
		const n_pointer & __end_cap() const { return __end_cap.first; }











	};

	
}
#endif 