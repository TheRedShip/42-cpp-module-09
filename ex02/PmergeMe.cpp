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

void merge(std::deque<std::pair<int, int> > &pairs, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::deque<std::pair<int, int> > leftPairs(n1);
	std::deque<std::pair<int, int> > rightPairs(n2);

	for (int i = 0; i < n1; ++i)
		leftPairs[i] = pairs[left + i];
	for (int i = 0; i < n2; ++i)
		rightPairs[i] = pairs[mid + 1 + i];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (leftPairs[i].first <= rightPairs[j].first) {
			pairs[k] = leftPairs[i];
			++i;
		} else {
			pairs[k] = rightPairs[j];
			++j;
		}
		++k;
	}

	while (i < n1) {
		pairs[k] = leftPairs[i];
		++i;
		++k;
	}

	while (j < n2) {
		pairs[k] = rightPairs[j];
		++j;
		++k;
	}
}

void mergeSort(std::deque<std::pair<int, int> > &pairs, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		mergeSort(pairs, left, mid);
		mergeSort(pairs, mid + 1, right);

		merge(pairs, left, mid, right);
	}
}

template <typename L>
std::vector<int>::iterator	find_position(L final, int element_to_insert, int left, int right)
{
	if (left >= right)
		return final->begin() + left;

	int mid = left + (right - left) / 2;

	if (element_to_insert == (*final)[mid])
		return final->begin() + mid;
	if (element_to_insert < (*final)[mid])
		return find_position(final, element_to_insert, left, mid);

	return find_position(final, element_to_insert, mid + 1, right);
}

template <typename L>
void	add_pairs(std::deque<std::pair<int, int> > pairs, L final)
{
	for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
		final->push_back((*it).first);
	
	for (size_t i = 0; i < pairs.size(); i++)
	{
		int element_to_insert = pairs[i].second;
		std::vector<int>::iterator position = find_position(final, element_to_insert, 0, final->size() - 1);
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
	mergeSort(*pairs, 0, pairs->size() - 1);
}


std::vector<int>	sort_vector(std::vector<int> n_vector)
{
	int									straggler = -1;
	std::vector<int> 					final;
	std::deque<std::pair<int, int> >	pairs;

	size_t i;
	for (i = 0; i < n_vector.size(); i+=2)
		if (i + 1 < n_vector.size())
			pairs.push_back(std::make_pair(n_vector[i], n_vector[i + 1]));

	if (i > n_vector.size())
		straggler = n_vector[n_vector.size() - 1];

	sort_pairs(&pairs);
	add_pairs(pairs, &final);

	if (straggler != -1)
	{
		std::vector<int>::iterator position = find_position(&final, straggler, 0, final.size());
		final.insert(position, straggler);
	}

	for (std::vector<int>::iterator it = final.begin(); it != final.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	return final;
}