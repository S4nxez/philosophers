/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:10:23 by dansanc3          #+#    #+#             */
/*   Updated: 2025/08/27 22:32:04 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @return true if string is made only of numbers
 * @param arg the string to be checked
 */
bool	is_number(char *arg)
{
	int	i;

	if (arg == NULL || arg[0] == '\0')
		return (false);
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] > '9' || arg[i] < '0')
			return (false);
		i++;
	}
	return (true);
}

/*
int main()
{
	printf("is_number(\"asdad\"): %s\n", is_number("asdad") ? "true" : "false");
	printf("is_number(\"12\"): %s\n", is_number("12") ? "true" : "false");
	printf("is_number(\"123a\"): %s\n", is_number("123a") ? "true" : "false");
	printf("is_number(\"a1234\"): %s\n", is_number("a1234") ? "true" : "false");
	is_number("a1234");
	return 0;
}
*/
