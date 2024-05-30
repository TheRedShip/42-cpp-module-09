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
#include <stack>

int	calcul_input(std::string rpn_string)
{
	std::stack<double>	stack;

	for (std::string::iterator it = rpn_string.begin(); it != rpn_string.end(); ++it)
	{
		if (*it == ' ')
			continue ;
		if (isdigit(*it))
			stack.push(*it - '0');

		else if (stack.size() >= 2 && std::string("+-*/").find(*it) != std::string::npos)
		{
			double	b = stack.top();
			stack.pop();
			double	a = stack.top();
			stack.pop();

			switch (*it)
			{
				case '+':
					stack.push(a + b);
					break;
				case '-':
					stack.push(a - b);
					break ;
				case '*':
					stack.push(a * b);
					break ;
				case '/':
					if (b == 0)
						return (-1);
					stack.push(a / b);
			}
		}
		else
			return (0);
	}

	if (stack.size() != 1)
		return (0);

	std::cout << stack.top() << std::endl;
	return (1);
}

int main(int argc, char *argv[])
{
	int	error;

	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <RPN calcul>" << std::endl;
		return (0);
	}

	error = calcul_input(argv[1]);
	if (error == -1)
		std::cout << "Error: Division by zero." << std::endl;
	else if (error == 0)
		std::cout << "Error: Invalid input." << std::endl;
}