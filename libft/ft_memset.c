/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:23:23 by bryaloo           #+#    #+#             */
/*   Updated: 2024/04/05 19:21:59 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)str;
	while (n > 0)
	{
		*(tmp++) = (unsigned char)c;
		n--;
	}
	return (str);
}
/*
int main(void)
    char buffer[10];
    ft_memset(buffer, 'A', sizeof(buffer));
*/
