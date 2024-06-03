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

	std::vector<int> vec_sort = sort_vector(n_vector);

	// for (std::list<double>::iterator it = n_list.begin(); it != n_list.end(); ++it)
	// {
	// 	std::cout << *it << std::endl;
	// }

	// for (std::deque<double>::iterator it = n_deque.begin(); it != n_deque.end(); ++it)
	// {
	// 	std::cout << *it << std::endl;
	// }
}