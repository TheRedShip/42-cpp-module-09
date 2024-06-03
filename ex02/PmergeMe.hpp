/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 01:08:37 by marvin            #+#    #+#             */
/*   Updated: 2024/06/03 01:08:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <algorithm>
# include <list>
# include <deque>

template <typename T>
int		parse_numbers(int argc, char **argv, T *numbers)
{

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
			return (0);
		numbers->push_back(std::strtod(argv[i], NULL));
	}
	return (1);
}

void	sort_list(std::list<double> *n_list);

#endif