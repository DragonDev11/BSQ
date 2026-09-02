/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhmichi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 12:20:18 by mhmichi           #+#    #+#             */
/*   Updated: 2026/09/02 13:30:20 by mhmichi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_string.h"
#include <unistd.h>

int	get_start_index(char *str, int *sign)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
	{
		i++;
	}
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	if (*(str + i) >= '0' && *(str + i) <= '9')
		return (i);
	return (-1);
}

int	get_num_length(char *str, int start)
{
	int	l;

	l = 0;
	while (*(str + start))
	{
		if (*(str + start) >= '0' && *(str + start) <= '9')
			l++;
		else if (l > 0)
			return (l);
		start++;
	}
	return (l);
}

int	ft_atoi(char *str)
{
	int	nb;
	int	i;
	int	start;
	int	len;
	int	sign;

	nb = 0;
	i = 0;
	sign = 1;
	start = get_start_index(str, &sign);
	len = get_num_length(str, start);
	if (start == -1)
		return (0);
	while (i < len)
	{
		nb = nb * 10 + (str[start + i] - 48);
		i++;
	}
	return (nb * sign);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		if (nb == -2147483648)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		nb *= -1;
		ft_putchar('-');
	}
	if (nb >= 0 && nb <= 9)
	{
		ft_putchar(nb + 48);
		return ;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	return ;
}
