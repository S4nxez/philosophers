/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:16:25 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/13 19:31:50 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	ret;
	int	sign;

	ret = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("Atoi og: %d\n", atoi("--12"));
	printf("Atoi og: %d\n", atoi("-+12"));
	printf("Atoi og: %d\n", atoi("++12"));
	printf("Atoi og: %d\n", atoi(" -12323s2"));
	printf("Atoi og: %d\n", atoi("    123"));
	printf("Atoi og: %d\n", atoi("asdas"));
	printf("\n\n");
	printf("Atoi ft: %d\n", ft_atoi("--12"));
	printf("Atoi ft: %d\n", ft_atoi("-+12"));
	printf("Atoi ft: %d\n", ft_atoi("++12"));
	printf("Atoi ft: %d\n", ft_atoi(" -12323s2"));
	printf("Atoi ft: %d\n", ft_atoi("    123"));
	printf("Atoi ft: %d\n", ft_atoi("asdas"));
}
