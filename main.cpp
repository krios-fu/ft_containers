/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:52:14 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/01 14:28:13 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include <iostream>


void ft_lambda ( int a)
{
  std::cout << a << std::endl;
}

int main() {
 
  ft_lambda([](int a, int b) { return a + b; });
}

