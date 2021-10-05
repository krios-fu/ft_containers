/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:52:14 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/06 00:12:50 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./utils.hpp"
#include <utility>
#include <algorithm>
#include <vector>
#include <random>

bool mypredicate (int i, int j) {
  return (i==j);
}

bool comp (char s1, char s2)
{
    return std::tolower(s1) < std::tolower(s2);
}

int main ()
{
	ft::pair<int , std::string> hola;
	ft::pair<int , std::string> mundo;

	hola.first  = 12;
	hola.second = "hola";

	mundo = hola;

	std::cout << mundo.first << " " << mundo.second << std::endl;
	std::cout << (mundo < hola) << std::endl;
	std::cout << (mundo > hola) << std::endl;
	std::cout << (mundo <= hola ) <<std::endl;
	std::cout << (mundo >= hola ) <<std::endl;
	std::cout << (mundo == hola ) <<std::endl;
	std::cout << (mundo != hola ) <<std::endl;

	ft::pair <int,int> foo;
	ft::pair <int,int> bar;

	foo = ft::make_pair (10,20);
	bar = ft::make_pair <double, char>(10.5,'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
	std::cout << "bar: " << static_cast<double>(bar.first) << ", " << static_cast<char>(bar.second) << '\n';

	int array[]  = { 1 , 2 , 3 ,4 ,5 };
	int array2[]  = { 1 , 2 , 3 ,4 ,6 };

	std::vector<int> vec (array, array + 5);

	if (ft::equal(vec.begin(), vec.end(), array2))
		std::cout << "is equal sequences" << std::endl;
	else
		std::cout << "is differ sequences" << std::endl;

	if (ft::equal(vec.begin(), vec.end(), array, mypredicate))
		std::cout << "is equal sequences" << std::endl;
	else
		std::cout << "is differ sequences" << std::endl;
	
	char one[] = "geeksforgeeks";
    char two[] = "gfg";
      
    // using lexicographical_compare for checking 
    // is "one" is less than "two"
    if( ft::lexicographical_compare(one, one+13, two, two+3) )
    {
        std::cout << "geeksforgeeks is lexicographically less than gfg";
          
    }
    else
    {
        std::cout << "geeksforgeeks is not lexicographically less than gfg";
          
    }
	
	 if( ft::lexicographical_compare(one, one+13, two, two+3, comp))
    {
        std::cout << "geeksforgeeks is lexicographically less  ";
        std::cout << "than Gfg( case-insensitive )";
          
    }
    else
    {
        std::cout << "geeksforgeeks is not lexicographically less ";
        std::cout<< "than Gfg( case-insensitive )";
          
    }
 
    
	return 0;
}