/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:45:15 by bryaloo           #+#    #+#             */
/*   Updated: 2024/04/05 19:26:03 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	a;
	size_t	b;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		a = 0;
		b = ft_strlen(s1);
		while (s1[a] && ft_strchr(set, s1[a]))
			a++;
		while (s1[b - 1] && ft_strchr(set, s1[b - 1]) && b > a)
			b--;
		str = (char *)malloc(sizeof(char) * (b - a + 1));
		if (str)
			ft_strlcpy(str, &s1[a], b - a + 1);
	}
	return (str);
}
