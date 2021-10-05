/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:52:14 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/05 15:27:19 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./template/utils.hpp"
#include <utility>

int main ()
{
	ft::pair<int , std::string> hola;
	ft::pair<int , std::string> mundo;

	

	hola.first  = 12;
	hola.second = "hola";

	mundo = hola;

	std::cout << mundo.first << " " << mundo.second << std::endl;
	std::cout << (mundo < hola) << std::endl;
	std::cout << (mundo  >  hola) << std::endl;
	std::cout << (mundo <= hola ) <<std::endl;
	std::cout << (mundo >= hola ) <<std::endl;
	std::cout << (mundo == hola ) <<std::endl;
	std::cout << (mundo != hola ) <<std::endl;

}