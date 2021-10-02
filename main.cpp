/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:52:14 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/02 22:06:48 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./template/utils.hpp"

template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
	is_odd (T i)
{
		return bool(i%2);
}
	
int main()
{
	std::cout << std::boolalpha;
	std::cout << "is_integral:" <<  std::endl;
	std::cout << "char: " <<        ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << 				ft::is_integral<int>::value << std::endl;
	std::cout << "float: " <<				ft::is_integral<float>::value << std::endl;
}

