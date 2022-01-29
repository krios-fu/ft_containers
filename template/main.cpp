/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:52:14 by krios-fu          #+#    #+#             */
/*   Updated: 2022/01/29 23:30:07 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./utility/utils.hpp"
#include "./containers/map.hpp"
#include "./utility/tree.hpp"
// #include <utility>
// #include <algorithm>
//  #include <vector>
// #include <random>



int main ()
{

	 ft::pair<int, int> lol(1,12);
	 ft::pair<int, int> lol2(2,42);
	 ft::pair<int, int> lol3(3,1);
	 ft::pair<int, int> lol4(4,1);
	 ft::pair<int, int> lol5(5,1);
	 ft::pair<int, int> lol6(6,1);
	 ft::pair<int, int> lol7(7,1);
	 ft::pair<int, int> lol8(8,1);
	  ft::pair<int, int> lol9(9,1);
	 ft::pair<int, int> lol10(10,1);
	 ft::pair<int, int> loll(11,12);
	 ft::pair<int, int> lol12(12,12);
	 ft::pair<int, int> lol13(1,12);
	 ft::pair<int, int> lol14(13,12);
	 ft::pair<int, int> lol15(42,12);
	 ft::pair<int, int> lol16(0,12);
	 ft::pair<int, int> lol17(111,12);
	 ft::pair<int, int> lol18(110,12);
	 ft::pair<int, int> lol19(1993,12);
	 ft::pair<int, int> lol20(1994,12);





	 
	 




	
	// ft::pair<ft::Node<ft::pair<int, int> > *, bool> aux;
	ft::tree< ft::pair<int, int> , std::less<ft::pair<int, int> > > tree_lol;


	tree_lol.insert(lol);
	tree_lol.print(); 

	tree_lol.insert(lol2);
	tree_lol.print(); 

	tree_lol.insert(lol3);
	tree_lol.print(); 
	
	tree_lol.insert(lol4);
	tree_lol.print(); 

	tree_lol.insert(lol5);
	tree_lol.print(); 

	tree_lol.insert(lol6);
	tree_lol.print(); 

	tree_lol.insert(lol7);
	tree_lol.print(); 

	tree_lol.insert(lol8);
	tree_lol.print(); 

	tree_lol.insert(lol9);
	tree_lol.print(); 

	tree_lol.insert(lol10);
	tree_lol.print(); 

	tree_lol.insert(loll);

	tree_lol.print();
	tree_lol.insert(lol12);
	tree_lol.print();

	// tree_lol.print(); 
	tree_lol.insert(lol13);
	tree_lol.print(); 

	tree_lol.insert(lol14);
	tree_lol.print();
	tree_lol.insert(lol15);
	tree_lol.print();
		tree_lol.insert(lol16);
	tree_lol.print();
		tree_lol.insert(lol17);
	tree_lol.print();
		tree_lol.insert(lol18);
	tree_lol.print();
			tree_lol.insert(lol19);
	tree_lol.print();
				tree_lol.insert(lol20);
	tree_lol.print();


	// std::cout <<.first->content.first << std::endl;





	// aux2 = tree_lol.insert( lol );

	
	// std::cout << aux2.first->content.first << " bool: " << aux2.second << std::endl;

	// std::cout << aux.first->content.first << " bool: " << aux.second << std::endl;

	// std::cout << aux.first->content.first << " bool: " << aux.second << std::endl;


	// std::cout << aux.first->content.first << " bool: " << aux2->second << std::endl;

	//  std::cout << " ---> " << (tree_lol.__back(aux.first))->content.first << std::endl;





	
	
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


/* template <unsigned  int  N>
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
}; */

 /* template <typename T>
typename ft::enable_if
						<
							ft::is_integral<T>::value, int
						>::type

printNum ( T n )
{
	
	return n;
}

 template <typename T>
typename ft::enable_if
						<
							!ft::is_integral<T>::value, std::string
						>::type

printNum ( T n )
{
	
	return n;
}


int main ()
{
	std::cout << printNum<std::string>("hola") << std::endl;
	std::cout << printNum<int>(42) << std::endl;

}   */


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