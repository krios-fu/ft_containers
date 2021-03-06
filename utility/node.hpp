/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:15:12 by krios-fu          #+#    #+#             */
/*   Updated: 2022/02/04 19:15:13 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

# include "./utils.hpp"

namespace ft
{

template<typename T>
struct Node
{
	public : 
	typedef T			value_type;
	value_type			content;
	bool				black;
	Node*				parent;
	Node*				right;
	Node*				left;

	Node( T const &  __val , Node *__nill )
	: content(__val),
	  black( false ),
	  parent( __nill ),
	  right( __nill ),
	  left( __nill ){}

	Node( Node const &other )
	: content( other.content ),
	  black( other.black ),
	  parent( other.parent ),
	  right( other.right),
	  left( other.left ){}

	~Node(){}

	bool isBlack()
	{
			return black;
	}

	void setParent( Node* __p )
	{
		parent = __p;
	}
};

} // namespace ft

#endif