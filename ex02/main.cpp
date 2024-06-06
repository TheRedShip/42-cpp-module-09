/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:26:30 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 14:26:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
void	show_sort(T container)
{
	clock_t start = clock();
	T sorted = sort_container(container);
	clock_t end = clock();

	for (typename T::iterator it = sorted.begin(); it != sorted.end(); ++it)
	{
		if (it - sorted.begin() > 10)
		{
			std::cout << "[...] ";
			break ;
		}
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "Process took : " << (end - start) / (double)CLOCKS_PER_SEC * 100 << "us" << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << "Usage: " << argv[0] << " <Numbers>" << std::endl;
		return (0);
	}

	std::vector<int> n_vector;
	std::deque<int> n_deque;
	if (!parse_numbers(argc, argv, &n_vector) || !parse_numbers(argc, argv, &n_deque))
	{
		std::cout << "Error: Invalid input" << std::endl;
		return (0);
	}

	std::cout << "Vector: ";
	show_sort(n_vector);

	std::cout << std::endl;

	std::cout << "Deque: ";
	show_sort(n_deque);

	return (0);
}