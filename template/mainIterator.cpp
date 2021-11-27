/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainIterator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:10:43 by krios-fu          #+#    #+#             */
/*   Updated: 2021/11/27 05:00:13 by krios-fu         ###   ########.fr       */
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

	ft::vector<std::string> cadena;

	cadena.push_back("HOLA MUNDO");
	cadena.push_back("HOLA");
	cadena.push_back("MUNDO");
	cadena.push_back("HOLAMUNDO");
	cadena.push_back("HOLA----MUNDO");
	cadena.push_back("HOLA*MUNDO");
	cadena.push_back("HOLA******MUNDO");
	cadena.push_back("HOLA_____MUNDO");
	

{
	ft::vector<std::string> a;
	
	ft::vector<int> b;

	int array [] = { 42, 3, 12, 21 , 24 };

	ft::vector<std::string>::iterator first = cadena.begin();
	ft::vector<std::string>::iterator last = cadena.end();

	ft::vector<int>::iterator it_array(&(array[0]));

	 std::cout << "*** " << std::endl;


		a.assign(first, last);
		b.assign(it_array, it_array + 5);

	  {
		  	ft::vector<int>::iterator first = b.begin();
			ft::vector<int>::iterator last = b.end();
			for ( ; first != last; ++first )
			{
				std::cout << *first << std::endl;
			}
	  }

	{
			ft::vector<std::string>::iterator first = a.begin();
			ft::vector<std::string>::iterator last = a.end();
			ft::vector<std::string> ft(first, last);
			ft::vector<std::string>::iterator first2 = ft.begin();
			ft::vector<std::string>::iterator last2= ft.end();
			
			for ( ; first2 != last2; ++first2 )
			{
				std::cout << *first2 << std::endl;
			}
	}

}

{
	// std::vector<std::string> a;

	// std::vector<std::string>::iterator first = cadena.begin();
	// std::vector<std::string>::iterator last = cadena.end();

	// a.assign(first, last);
	
}


}