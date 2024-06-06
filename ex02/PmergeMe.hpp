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
# include <vector>
# include <deque>

template <typename T>
int		parse_numbers(int argc, char **argv, T *numbers)
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
			return (0);
		numbers->push_back(atoi(argv[i]));
	}
	return (1);
}


void merge(std::deque<std::pair<int, int> > &pairs, int left, int mid, int right)
{
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

void mergeSort(std::deque<std::pair<int, int> > &pairs, int left, int right)
{
	if (left < right) {
		int mid = left + (right - left) / 2;

		mergeSort(pairs, left, mid);
		mergeSort(pairs, mid + 1, right);

		merge(pairs, left, mid, right);
	}
}

template <typename Container>
typename Container::iterator find_position(Container &final, int element_to_insert, int left, int right)
{
	if (left >= right)
		return final.begin() + left;

	int mid = left + (right - left) / 2;

	if (element_to_insert == final[mid])
		return final.begin() + mid;
	if (element_to_insert < final[mid])
		return find_position(final, element_to_insert, left, mid);

	return find_position(final, element_to_insert, mid + 1, right);
}

template <typename Container>
void add_pairs(std::deque<std::pair<int, int> > &pairs, Container &final)
{
	for (typename std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
		final.push_back(it->first);

	for (typename std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
		int element_to_insert = it->second;
		typename Container::iterator position = find_position(final, element_to_insert, 0, final.size());
		final.insert(position, element_to_insert);
	}
}

void sort_pairs(std::deque<std::pair<int, int> > &pairs)
{
	for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
		if (it->first < it->second)
			std::swap(it->first, it->second);
	}
	mergeSort(pairs, 0, pairs.size() - 1);
}

template <typename Container>
Container sort_container(Container n_container)
{
	int straggler = -1;
	Container final;
	std::deque<std::pair<int, int> > pairs;

	size_t i;
	for (i = 0; i < n_container.size(); i += 2) {
		if (i + 1 < n_container.size())
			pairs.push_back(std::make_pair(n_container[i], n_container[i + 1]));
	}

	if (i > n_container.size())
		straggler = n_container[n_container.size() - 1];

	sort_pairs(pairs);
	add_pairs(pairs, final);

	if (straggler != -1) {
		typename Container::iterator position = find_position(final, straggler, 0, final.size());
		final.insert(position, straggler);
	}

	return final;
}

#endif