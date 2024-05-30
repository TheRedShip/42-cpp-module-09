/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:33:11 by marvin            #+#    #+#             */
/*   Updated: 2024/05/27 00:33:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <regex.h>
#include <map>

int	verify_input(std::string data)
{
	regex_t regex;
	std::string	regex_string = "(((18|19|20)[0-9]{2}[-.](0[13578]|1[02])[-.](0[1-9]|[12][0-9]|3[01]))|((18|19|20)[0-9]{2}[-.](0[469]|11)[-.](0[1-9]|[12][0-9]|30))|((18|19|20)[0-9]{2}[-.](02)[-.](0[1-9]|1[0-9]|2[0-8]))|(((18|19|20)(04|08|[2468][048]|[13579][26])|2000)[-.](02)[-.]29)) \\| [+-]?[0-9]+\\.?[0-9]*$";
	
	if (regcomp(&regex, regex_string.c_str(), REG_EXTENDED) != 0)
	{
		std::cout << "Error: Invalid regex" << std::endl;
		regfree(&regex);
		exit(0);
	}
	int status = regexec(&regex, data.c_str(), 0, NULL, 0);

	regfree(&regex);
	return (status == 0);
}

double	search_nearest(std::string date, std::map<std::string, double> data)
{
	std::map<std::string, double>::iterator itlow = data.lower_bound(date);
	if (data.find(date) != data.end())
		return data[date];
	if (itlow != data.begin())
		*(itlow--);
	return itlow->second;
}

void	show_convert(std::string line, std::map<std::string, double> data)
{
	std::string	date_in;
	double		value_in;
	size_t		separator;

	separator = line.find(" | ");
	date_in = line.substr(0, separator);
	value_in = std::strtod(line.substr(separator + 3).c_str(), NULL);

	if (value_in < 0)
		std::cout << "Error: not a positive number : " << line <<  std::endl;
	else if (value_in > 1000)
		std::cout << "Error: too large a number : " << line <<  std::endl;
	else
	{
		std::cout << date_in << " => " << value_in << " = " << value_in * search_nearest(date_in, data) << std::endl;
	}
}

void	read_input(char *file_name, std::map<std::string, double> data)
{
	std::string		line;
	std::ifstream	file(file_name);

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (line.substr(0, 4) == "date")
				continue ;
			if (line[line.size() - 1] == '\r')
				line = line.substr(0, line.size() - 1);
			if (!verify_input(line))
			{
				std::cout << "Error: bad input => " << line << std::endl;
				continue ;
			}
			show_convert(line, data);
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
		return ;
	}
}

std::map<std::string, double>	read_data()
{
	std::ifstream file("data.csv");
	std::map<std::string, double> data;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			size_t pos = line.find(",");
			std::string date = line.substr(0, pos);

			if (date == "date")
				continue ;
			
			data[date] = std::strtod(line.substr(pos + 1).c_str(), NULL);
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
		exit(0);
	}

	return data;
}