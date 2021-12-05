/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainIterator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:10:43 by krios-fu          #+#    #+#             */
/*   Updated: 2021/12/05 17:20:54 by krios-fu         ###   ########.fr       */
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
#include <typeinfo>
 
/* void pointer_func(const int* p, std::size_t size)
{
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
} */
 


int main()
{
		int array [] = { 100, 101, 102, 103 , 104};
	{
		ft::vector<int> lol;

		lol.insert( lol.begin(), array, array + 5 );




		lol.erase(lol.begin() + 2 );



		ft::vector<int>::iterator first = lol.begin();
		ft::vector<int>::iterator last = lol.end();

		for (; first != last ; ++first )
			std::cout << *first << " ";
		std::cout << "\n";

		std::cout << "SIZE: "<< lol.size() << " CAP: " << lol.capacity() << std::endl;
		
	}

	

}


