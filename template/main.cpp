/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:52:14 by krios-fu          #+#    #+#             */
/*   Updated: 2022/01/19 19:51:46 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./utility/utils.hpp"
#include "./containers/map.hpp"
#include "tree.hpp"
// #include <utility>
// #include <algorithm>
//  #include <vector>
// #include <random>



int main ()
{
	// if (typeid(ft::iterator_traits<ft::vector<int>::iterator>::iterator_category)==typeid(ft::random_access_iterator_tag))
    //     std::cout << "int* is a random-access iterator";
}
















/* 
template < typename T>
void print (T a )
{
	std::cout << a  << std::endl;
}



int main ()
{
	std::string a("hola");

	int b (9);

	char c('c');


	print(a);
	print(b);
	print(c);

	
} */







/* 
template <typename T >
typename ft::enable_if
< 
	!ft::is_integral<T>::value,
	std::string
	
>::type
		ft_suma( T a, T b)
		{
			return a + b ;
		}

int main ( )
{
	std::string a = "hola";
	std::cout << ft_suma(a, a) << std::endl;
}
 */

/* 
template <unsigned  int  N>
struct  factorial
{
	enum
	{
		data = N * factorial<N -1 >::data
	};
};

template <>
struct  factorial<0>
{
	enum
	{
		data = 1
	};
};

int main ()
{
	std::cout << factorial<5>::data;
}  */


/* template<typename T, typename U>
struct ft 
{
	enum
	{
		value = ft<T + U >::value
	};
	
}; */
/* 
template<typename U = int>
struct ft <int, U> 
{
	enum
	{
		value = ft<U>::value
	};
	
};

template<>
struct ft<bool, bool > 
{
	enum
	{
		value = ft<bool, bool>::value
	};
	
};





// bool mypredicate (int i, int j) {
//   return (i==j);
// }

// bool comp (char s1, char s2)
// {
// 	return std::tolower(s1) < std::tolower(s2);
// } */

// int main ()
// {

// 	ft::pair<int , std::string> hola;
// 	ft::pair<int , std::string> mundo;

// 	hola.first  = 12;
// 	hola.second = "hola";

// 	mundo = hola;

// 	std::cout << mundo.first << " " << mundo.second << std::endl;
// 	std::cout << (mundo < hola) << std::endl;
// 	std::cout << (mundo > hola) << std::endl;
// 	std::cout << (mundo <= hola ) <<std::endl;
// 	std::cout << (mundo >= hola ) <<std::endl;
// 	std::cout << (mundo == hola ) <<std::endl;
// 	std::cout << (mundo != hola ) <<std::endl;

// 	ft::pair <int,int> foo;
// 	ft::pair <int,int> bar;

// 	foo = ft::make_pair (10,20);
// 	bar = ft::make_pair <double, char>(10.5,'A'); // ok: implicit conversion from pair<double,char>

// 	std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
// 	std::cout << "bar: " << static_cast<double>(bar.first) << ", " << static_cast<char>(bar.second) << '\n';

// 	int array[]  = { 1 , 2 , 3 ,4 ,5 };
// 	int array2[]  = { 1 , 2 , 3 ,4 ,6 };

// 	std::vector<int> vec (array, array + 5);

// 	if (ft::equal(vec.begin(), vec.end(), array2))
// 		std::cout << "is equal sequences" << std::endl;
// 	else
// 		std::cout << "is sequences differ" << std::endl;

// 	// function mypredycate v.2
	
// 	if (ft::equal(vec.begin(), vec.end(), array, mypredicate))
// 		std::cout << "is equal sequences" << std::endl;
// 	else
// 		std::cout << "is sequences differ" << std::endl;
	
// 	char one[] = "42 for ever";
// 	char two[] = "4fv";

// 	// using lexicographical_compare for checking 
// 	// is "one" is less than "two"
// 	if( ft::lexicographical_compare(one, one+13, two, two+3) )
// 		std::cout << "one is lexicographically less than gfg";
// 	else
// 		std::cout << "oneis not lexicographically less than gfg";
// 	if( ft::lexicographical_compare(one, one+13, two, two+3, comp))
// 	{
// 		std::cout << "one is lexicographically less  ";
// 		std::cout << "than two( case-insensitive )";
// 	}
// 	else
// 	{
// 		std::cout << "one is not lexicographically less ";
// 		std::cout<< "twoGfg( case-insensitive )";
// 	}


// 	return 0;
// }