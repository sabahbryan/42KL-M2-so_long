/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:38:19 by bryaloo           #+#    #+#             */
/*   Updated: 2024/03/20 15:38:21 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	i = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

/*
	ORIGINAL
	size_t	count;
	size_t	len;

	count = 0;
	len = 0;
	if (size == 0)
		return (len);
	while (src[len] != '\0' && len < size - 1)
	{
		dest[count] = src[len];
		count++;
		len++;
	}
	dest[count] = '\0';
	while (src[len] != '\0')
		len++;
	return (count);
*/