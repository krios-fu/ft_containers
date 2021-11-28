/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainIterator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:10:43 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/28 05:40:00 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./containers/vector.hpp"

#include <string>
// #include "./utils.hpp"
 
/* // quite often implementation details are hidden in a dedicated namespace
namespace implementation_details {
template<class BDIter>
void alg(BDIter, BDIter, std::bidirectional_iterator_tag)
{
	std::cout << "alg() called for bidirectional iterator\n";
}
 
template<class RAIter>
void alg(RAIter, RAIter, std::random_access_iterator_tag)
{
	std::cout << "alg() called for random-access iterator\n";
}
} // namespace implementation_details
 
template<class Iter>
void alg(Iter first, Iter last)
{
	implementation_details::alg(first, last,
		typename std::iterator_traits<Iter>::iterator_category());
} */
 
#include <cstddef>
#include <iostream>
#include <span>
#include <vector>
 
void pointer_func(const int* p, std::size_t size)
{
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
}
 

 
int main()
{
    ft::vector<int> container;

	container.push_back(42);
	container.push_back(21);
	container.push_back(12);
	container.push_back(42);



 
    // Prefer container.data() over &container[0]
    pointer_func(container.data(), container.size());

	std::cout << container.at(3) << std::endl;
	
	container.pop_back();
	container.pop_back();
	container.pop_back();
	container.pop_back();




	std::cout << container.size() << std::endl;

	
 
    // std::span (C++20) is a safer alternative to separated pointer/size.
    // span_func({container.data(), container.size()});
}
