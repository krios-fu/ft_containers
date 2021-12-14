/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainIterator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:10:43 by krios-fu          #+#    #+#             */
/*   Updated: 2021/12/14 21:55:26 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./containers/vector.hpp"
#include "./containers/map.hpp"

#include <iostream>
#include <vector>
#include <string>
/* #include <deque>
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = ft;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif */

/* #include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))
 */
/* template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};
 */
int main() {

/* 
	std::map<int, int> j { { 12, 42 } , {21, 42 } };

	j[12] = 42; */
	// ft::map< int , int> k(12, 42);

	// std::cout << k.getNode().second << std::endl;

	// k[12] = 42;
	

/* 
	int array [] = { 1, 2, 3, 4, 5};
	std::vector<int> k;

	k.assign(array, array + 5 );

	std::vector<int>::iterator start = k.begin();
	std::vector<int>::iterator end = k.end();

	ft::vector<int> l ;

	l.assign(start,  end);

	ft::vector<int>::iterator start2 = l.begin();
	ft::vector<int>::iterator end2 = l.end();

	for (; start2 != end2 ; ++start2)
	{
		std::cout << *start2 << std::endl;
	} */
	

	// if (typeid(ft::iterator_traits<ft::vector<int>::iterator>::iterator_category)==typeid(ft::random_access_iterator_tag))
        // std::cout << "int* is a random-access iterator";


/* 	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	// ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	// ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	// ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
		std::cout << e.what() << std::endl;
	} */
	
/* 	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl; */
	return (0);
}

