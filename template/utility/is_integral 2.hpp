/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:59:40 by krios-fu          #+#    #+#             */
/*   Updated: 2021/10/12 21:05:47 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __IS_INTEGRAL_HPP
#define __IS_INTEGRAL_HPP

# include <cstddef>
namespace ft
{
		/* Is integral start  */

	template < bool is_integral, typename T >
	struct is_integral_check
	{
		typedef T type;
		static const bool value = is_integral;
	};

	template < typename >
		struct is_integral_type : public is_integral_check< false, bool> {};

	template <> struct is_integral_type < bool >					: public is_integral_check < true, bool>						{};
	template <> struct is_integral_type < char >					: public is_integral_check < true, char>						{};
	template <> struct is_integral_type < char16_t >				: public is_integral_check < true, char16_t >					{};
	template <> struct is_integral_type < char32_t >				: public is_integral_check < true, char32_t >					{};
	template <> struct is_integral_type < wchar_t >					: public is_integral_check < true, wchar_t >					{};
	template <> struct is_integral_type < signed char >				: public is_integral_check < true, signed char >				{};
	template <> struct is_integral_type < short int >				: public is_integral_check < true, short int >					{};
	template <> struct is_integral_type < int >						: public is_integral_check < true, int >						{};
	template <> struct is_integral_type < long int >				: public is_integral_check < true, long int >					{};
	template <> struct is_integral_type < long long int >			: public is_integral_check < true, long long int >				{};
	template <> struct is_integral_type < unsigned char >			: public is_integral_check < true, unsigned char >				{};
	template <> struct is_integral_type < unsigned short int >		: public is_integral_check < true, unsigned short int >			{};
	template <> struct is_integral_type < unsigned int >			: public is_integral_check < true, unsigned int >				{};
	template <> struct is_integral_type < unsigned long int >		: public is_integral_check < true, unsigned long int >			{};
	template <> struct is_integral_type < unsigned long long int >	: public is_integral_check < true, unsigned long  long int >	{};

	template <typename T>
		struct is_integral : public is_integral_type<T> {};
	/* Is integral end  */
}

#endif 
