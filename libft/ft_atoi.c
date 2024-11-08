/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:25:25 by abzaiz            #+#    #+#             */
/*   Updated: 2024/10/11 11:18:02 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	result = 0;
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str++ - '0');
	}
	return (result * sign);
}

static long	int	ft_at(const char *str, long int i, long int num, long int num2)
{
	long int	nega;

	nega = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' \
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			nega *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num2 = (num * 10) + (int)(str[i] - 48);
		if ((num > num2) && nega == 1)
			return (-1);
		if ((num > num2) && nega == -1)
			return (0);
		num = num2;
		i++;
	}
	num *= nega;
	return (num);
}

int	ft_atoi2(const char *str)
{
	long int	i;
	long int	num;
	long int	num2;

	i = 0;
	num2 = 0;
	num = 0;
	return ((int)ft_at(str, i, num, num2));
}
