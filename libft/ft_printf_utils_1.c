/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:25:54 by bryaloo           #+#    #+#             */
/*   Updated: 2024/07/22 21:29:13 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//print_char
int	print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

//print_hex
int	hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	put_hex(unsigned int num, const char type)
{
	if (num >= 16)
	{
		put_hex(num / 16, type);
		put_hex(num % 16, type);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (type == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (type == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	print_hex(unsigned int num, const char type)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		put_hex(num, type);
	return (hex_len(num));
}

//print_nbr
int	print_nbr(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = print_str(num);
	free(num);
	return (len);
}
