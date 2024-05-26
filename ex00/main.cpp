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

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <regex.h>

int	parse_data(std::string data, bool comma_pipe)
{
	regex_t regex;
	std::string regex_comma = "(((19|20)\\d{2})[-.]((0[13578]|1[02])[-.](0[1-9]|[12][0-9]|3[01])|(0[469]|11)[-.](0[1-9]|[12][0-9]|30)|02[-.](0[1-9]|1[0-9]|2[0-8]))|((19|20)([02468][048]|[13579][26])|2000)[-.]02[-.]29),[+-]?[0-9]+\\.?[0-9]*$";
	// std::string regex_comma = "(((19|20)\\d{2})[-.]((0[13578]|1[02])[-.](0[1-9]|[12][0-9]|3[01])|(0[469]|11)[-.](0[1-9]|[12][0-9]|30)|02[-.](0[1-9]|1[0-9]|2[0-8]))|((19|20)([02468][048]|[13579][26])|2000)[-.]02[-.]29),[+-]?[0-9]+\\.?[0-9]*$";
	std::string	regex_pipe = "(((19|20)\\d{2})[-.]((0[13578]|1[02])[-.](0[1-9]|[12][0-9]|3[01])|(0[469]|11)[-.](0[1-9]|[12][0-9]|30)|02[-.](0[1-9]|1[0-9]|2[0-8]))|((19|20)([02468][048]|[13579][26])|2000)[-.]02[-.]29) \\| [+-]?[0-9]+\\.?[0-9]*$";
	std::string	regex_string = comma_pipe ? regex_comma : regex_pipe;

	if (regcomp(&regex, regex_string.c_str(), REG_EXTENDED) != 0)
	{
		std::cout << "Error: Invalid regex" << std::endl;
		exit(0);
	}
	int status = regexec(&regex, data.c_str(), 0, NULL, 0);
	std::cout << (status) << std::endl;

	regfree(&regex);
	return (status == 0);
}

std::string	read_input(char *file_name, bool comma_pipe)
{
	std::ifstream file(file_name);
	std::string fileContent;

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (!parse_data(line, comma_pipe))
			{
				std::cout << "Error: Parsing: " << line << std::endl;
				exit(0);
			}
			fileContent += line + "\n";
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
		exit(0);
	}
	return fileContent;
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
		return (0);
	}
	read_input(argv[1], true);
}