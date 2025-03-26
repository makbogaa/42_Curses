/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:53:36 by makboga           #+#    #+#             */
/*   Updated: 2025/03/16 20:18:07 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_parts(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		if (*s)
			s++;
	}
	return (count);
}

static void	ft_free(char **result, size_t ridx)
{
	while (ridx > 0)
	{
		ridx--;
		free(result[ridx]);
	}
	free(result);
}

static char	*ft_print_parts(char const *s, char *str, size_t i, size_t plen)
{
	size_t	idx;

	idx = 0;
	while (0 < plen)
	{
		str[idx] = s[i - plen];
		idx++;
		plen--;
	}
	str[idx] = '\0';
	return (str);
}

static char	**ft_split_parts(char const *s, char c, char **result, size_t part)
{
	size_t	i;
	size_t	ridx;
	size_t	plen;

	i = 0;
	ridx = 0;
	while (s[i] && ridx < part)
	{
		while (s[i] && s[i] == c)
			i++;
		plen = 0;
		while (s[i + plen] && s[i + plen] != c)
			plen++;
		result[ridx] = (char *)malloc(sizeof(char) * (plen + 1));
		if (!result[ridx])
		{
			ft_free(result, ridx);
			return (NULL);
		}
		ft_print_parts(s, result[ridx], i + plen, plen);
		ridx++;
		i += plen;
	}
	result[ridx] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	size_t	part;
	char	**result;

	if (!s)
		return (NULL);
	part = ft_count_parts(s, c);
	result = (char **)malloc((part + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!ft_split_parts(s, c, result, part))
		return (NULL);
	return (result);
}
