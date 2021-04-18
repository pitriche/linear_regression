/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:29:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/04/13 21:08:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

#define LEARNING_CYCLES	6000
#define LEARNING_RATE	1e-2f
#define SEC_A_DAMPING	1e-3f

// floats to avoid constant cast for calculus
struct Tup
{
	Tup(int km_, int price_) : km(static_cast<float>(km_)),
	price(static_cast<float>(price_)) { }

	float	km;
	float	price;
};

std::ostream	&operator<<(std::ostream &lhs, const Tup &rhs)
{
	lhs << "km:" << rhs.km << " price:" << rhs.price;
	return (lhs);
}

inline float	estimate(float km, float a, float b)
{
	return (km * a + b);
}

float			mse(std::vector<Tup> data, float a, float b)
{
	float	mse;
	float	tmp;

	mse = 0;
	for (unsigned tup_id = 0; tup_id < data.size(); ++tup_id)
	{
		tmp = estimate(data[tup_id].km, a, b) - data[tup_id].price;
		mse += tmp * tmp;
	}
	return (mse / static_cast<float>(data.size()));
}

void	add_file(float a, float b)
{
	std::ofstream	ofs;

	ofs.open("theta", std::fstream::out);
	if (!ofs.is_open())
	{
		std::cout << "I hate your guts" << std::endl;
		exit(0);
	}
	ofs << a << '\n' << b;
	ofs.close();
}

void	train(std::vector<Tup> data, float a_damping)
{
	float	a; // theta1
	float	b; // theta0
	float	delta_a;
	float	delta_b;
	float	diff;
	

	a = 0.0f;
	b = 0.0f;
	for (unsigned epoch = 0; epoch < LEARNING_CYCLES; ++epoch)
	{
		delta_a = 0.0f;
		delta_b = 0.0f;
		for (unsigned tup_id = 0; tup_id < data.size(); ++tup_id)
		{
			diff = estimate(data[tup_id].km, a, b) - data[tup_id].price;
			delta_a += diff * data[tup_id].km;
			delta_b += diff;
		}
		delta_a /= static_cast<float>(data.size());
		delta_b /= static_cast<float>(data.size());
		a -= delta_a * LEARNING_RATE * a_damping * SEC_A_DAMPING;
		b -= delta_b * LEARNING_RATE;
		if (epoch % (LEARNING_CYCLES / 10) == 0)
			std::cout << "Epoch:" << epoch << "\tdelta a:" << delta_a <<
			"\t delta b:" << delta_b << "\t  mean squared error:" << mse(data,
				a, b) << std::endl;
	}
	add_file(a, b);
}

int		main(void)
{
	std::string			str;
	std::string			tmp;
	std::ifstream		ifs;
	std::vector<Tup>	data;
	float				a_damping;

	ifs.open("data.csv");
	if (!ifs.is_open())
	{
		std::cout << "Cannot find data.csv" << std::endl;
		return (0);
	}
	std::getline(ifs, str);
	str.clear();
	std::getline(ifs, str);
	a_damping = 0.0f;
	while (!str.empty())
	{
		tmp = str.substr(0, str.find(','));
		str.erase(0, str.find(',') + 1);
		data.push_back(Tup(std::atoi(tmp.c_str()), std::atoi(str.c_str())));
		a_damping += data.back().km;
		str.clear();
		std::getline(ifs, str);
	}
	a_damping = 1.0f / (std::abs(a_damping) / static_cast<float>(data.size()));
	ifs.close();
	train(data, a_damping);
	return (0);
}
