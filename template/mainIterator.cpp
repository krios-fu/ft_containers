/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainIterator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:10:43 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/11 21:34:14 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include "./Ft_iterator.hpp"
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
 
int main()
{
    std::vector<int> v;

    v.push_back(42);
    v.push_back(12);
    v.push_back(21);
    v.push_back(23);

    std::vector<int>::iterator __first = v.begin();
    std::vector<int>::iterator __last = v.end();

   std::cout << ft::distance(__first, __last) << std::endl;
   std::cout << std::distance(__first, __last) << std::endl;

    

 
//    std::istreambuf_iterator<char> i1(std::cin), i2;
//    alg(i1, i2); // compile error: no matching function for call
}