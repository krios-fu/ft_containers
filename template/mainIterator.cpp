/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainIterator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:10:43 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/26 05:24:46 by krios-fu         ###   ########.fr       */
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
 
int main()
{


    //  ft::vector<int> b(10);


    //  std::string ft (12, '4');

    //     int f[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 , 11 , 24 };
    //      ft::vector<int> c (&f[0], &f[12]);

{
        ft::vector<int> a(42);

        a.assign(12, 42);

        ft::vector<int>::iterator start2 = a.begin();
        ft::vector<int>::iterator end2 = a.end();

        for (; start2 != end2 ; start2++ )
        {
            std::cout << " --> " << *start2 << std::endl;
        }
        std::cout << "MAX SIZE :" << a.max_size() << std::endl ;
        std::cout << "SIZE :" << a.size() << std::endl ;
        std::cout << "CAPACITY :" << a.capacity() << std::endl ;

        ft::vector<char> cadena (42);
        const std::string extra(6, 'b');
        //  cadena.assign(extra.begin(), extra.end());
        cadena.reserve(100);
        
        std::cout << "MAX SIZE :" << a.max_size() << std::endl ;
        std::cout << "SIZE :" << a.size() << std::endl ;
        std::cout << "CAPACITY :" << a.capacity() << std::endl ;
}
         std::vector<int> a(42);

        a.assign(12, 42);

        std::vector<int>::iterator start2 = a.begin();
        std::vector<int>::iterator end2 = a.end();

        for (; start2 != end2 ; start2++ )
        {
            std::cout << " ** " << *start2 << std::endl;
        }
        std::cout << "MAX SIZE :" << a.max_size() << std::endl ;
        std::cout << "SIZE :" << a.size() << std::endl ;

        std::cout << "CAPACITY :" << a.capacity() << std::endl ;


        
 




    // ft::is_integral<int>::type a = 12;

    // std::cout << a << std::endl;
    // std::vector<int> v;

    // v.push_back(42);
    // v.push_back(12);
    // v.push_back(21);
    // v.push_back(23);

    // std::vector<int>::iterator __first = v.begin();
    // std::vector<int>::iterator __last = v.end();

//    std::cout << ft::distance(__first, __last) << std::endl;
//    std::cout << std::distance(__first, __last) << std::endl;


 
//    std::istreambuf_iterator<char> i1(std::cin), i2;
//    alg(i1, i2); // compile error: no matching function for call
}