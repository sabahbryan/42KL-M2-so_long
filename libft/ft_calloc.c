/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:13:55 by bryaloo           #+#    #+#             */
/*   Updated: 2024/04/05 19:10:53 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	str;
	void	*ptr;

	if (num == 0 || size == 0)
	{
		num = 1;
		size = 1;
	}
	if (num > 2147483647 / size)
		return (NULL);
	str = num * size;
	ptr = malloc(str);
	if (ptr == NULL)
		return (NULL);
	else
		ft_bzero(ptr, str);
	return (ptr);
}
