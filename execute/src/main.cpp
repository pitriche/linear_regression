/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:29:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/04/13 21:18:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstdlib>

inline float	estimate(float km, float a, float b)
{
	return (km * a + b);
}

int		main(int ac, char **av)
{
	std::ifstream	ifs;
	float			km;
	float			a;
	float			b;

	if (ac < 2)
	{
		std::cout << "Enter car mileage (in km)" << std::endl;
		return (0);
	}
	km = static_cast<float>(std::atof(av[1]));
	ifs.open("theta");
	if (!ifs.is_open())
	{
		std::cout << "Cannot find theta" << std::endl;
		return (0);
	}
	a = 0.0f;
	b = 0.0f;
	ifs >> a >> b;
	ifs.close();
	std::cout << "Estimated price: " << km * a + b << " euro" << std::endl;
	return (0);
}
