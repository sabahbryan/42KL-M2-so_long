/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:13:28 by bryaloo           #+#    #+#             */
/*   Updated: 2024/04/05 19:25:40 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	s;

	if (!haystack && !len)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len--)
	{
		s = 0;
		while (*(haystack + s) == *(needle + s) && *(needle + s) && s <= len)
		{
			if (!*(needle + s + 1))
				return ((char *)haystack);
			s++;
		}
		haystack++;
	}
	return (NULL);
}
