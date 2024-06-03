/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 01:08:09 by marvin            #+#    #+#             */
/*   Updated: 2024/06/03 01:08:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	add_pairs(std::deque<std::pair<int, int> > pairs, std::vector<int> *final)
{
	for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
		final->push_back((*it).first);
	
	for (size_t i = 0; i < pairs.size(); i++)
	{
		int element_to_insert = pairs[i].second;
		std::vector<int>::iterator position = std::lower_bound(final->begin(), final->end(), element_to_insert);
		final->insert(position, element_to_insert);
	}
}

void	sort_pairs(std::deque<std::pair<int, int> > *pairs)
{
	for (size_t i = 0; i < pairs->size(); i++)
	{
		if ((*pairs)[i].first < (*pairs)[i].second)
			std::swap((*pairs)[i].first, (*pairs)[i].second);
	}
	std::sort(pairs->begin(), pairs->end());
}

std::vector<int>	sort_vector(std::vector<int> n_vector)
{
	std::vector<int> final;
	std::deque<std::pair<int, int> > pairs;

	for (size_t i = 0; i < n_vector.size(); i+=2)
		pairs.push_back(std::make_pair(n_vector[i], n_vector[i + 1]));

	sort_pairs(&pairs);
	add_pairs(pairs, &final);

	for (std::vector<int>::iterator it = final.begin(); it != final.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	return final;
}