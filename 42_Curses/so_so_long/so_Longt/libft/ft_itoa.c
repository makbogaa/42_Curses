/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:36:30 by makboga           #+#    #+#             */
/*   Updated: 2024/10/31 21:06:14 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n, int sign)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	if (sign < 0)
		len++;
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	long	nb;
	char	*s;

	nb = n;
	sign = 1;
	if (nb < 0)
		sign = -1;
	nb = nb * sign;
	len = ft_len(nb, sign);
	s = (char *)malloc(sizeof(char) * len + 1);
	if (!s)
		return (0);
	s[len] = '\0';
	while (--len >= 0)
	{
		s[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (sign == -1)
		s[0] = '-';
	return (s);
}
