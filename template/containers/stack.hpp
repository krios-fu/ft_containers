/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:22:35 by krios-fu          #+#    #+#             */
/*   Updated: 2021/12/20 16:40:52 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <stack>
#include "./vector.hpp"


namespace ft
{

template <typename _Tp, class _Container = ft::vector<_Tp> >
class stack
{
	public:

	typedef _Container									container_type;
	typedef typename container_type::value_type			value_type;
	typedef typename container_type::reference 			reference;
	typedef typename container_type::const_reference	const_reference;
	typedef typename container_type::size_type			size_type;
	
	protected:
		container_type c;
	
	public:
	

	stack ( stack const & __q  ) : c ( __q.c ) {}
	
	stack ( container_type const & __c = container_type() ) : c ( __c ) {}

	virtual ~stack() {}
	
	stack& operator=( const stack& __q )
	{
		c = __q.c;
		return *this;
	}

	bool empty() const { return c.empty(); }
	
	size_type size() const { return c.size(); }

	reference top() { return c.back(); }
	
	const_reference top() const { return c.back(); }
	
	void push( const value_type& __v ) { c.push_back( __v ); }

	void pop() { c.pop_back(); }
	

	template < typename _T1, class _C1 >
	friend bool operator==( const stack< _T1, _C1 >& __x, const stack< _T1, _C1 >& __y);
	
	template < typename _T1, class _C1 >
	friend bool operator<( const stack< _T1, _C1 >& __x, const stack< _T1, _C1 >& __y);
};

	template < typename _T1, class _C1 >
	bool operator==( const stack< _T1, _C1 >& __x, const stack< _T1, _C1 >& __y)
	{
		return __x.c == __y.c;
	}
	
	template < typename _T1, class _C1 >
	bool operator<( const stack< _T1, _C1 >& __x, const stack< _T1, _C1 >& __y)
	{
		return __x.c < __y.c;
	}

	template < typename _T1, class _C1 >
	bool operator!=( const stack< _T1, _C1 >& __x, const stack< _T1, _C1 >& __y)
	{
		return !(__x == __y);
	}
	
	template < typename _T1, class _C1 >
	bool operator>( const stack< _T1, _C1 >& __x, const stack< _T1, _C1 >& __y)
	{
		return __y < __x;
	}

	template < typename _T1, class _C1 >
	bool operator>=( const stack< _T1, _C1 >& __x, const stack< _T1, _C1 >& __y)
	{
		return !(__x < __y);
	}

	template < typename _T1, class _C1 >
	bool operator<=( const stack< _T1, _C1 >& __x, const stack< _T1, _C1 >& __y)
	{
		return !(__y < __x);
	}
}

#endif 
