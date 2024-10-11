/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:20:49 by bryaloo           #+#    #+#             */
/*   Updated: 2024/02/23 19:21:08 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	char_s1;
	unsigned char	char_s2;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1)
	{
		char_s1 = (unsigned char)s1[i];
		char_s2 = (unsigned char)s2[i];
		if (char_s1 != char_s2)
			return (char_s1 - char_s2);
		if (char_s1 == '\0')
			break ;
		i++;
	}
	if ((unsigned char)s1[i] == (unsigned char)s2[i])
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
	ORIGINAL:
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n - 1)
		i++;
	if (s1[i] == s2[i])
		return (0);
	else
		return (s1[i] - s2[i]);
*/