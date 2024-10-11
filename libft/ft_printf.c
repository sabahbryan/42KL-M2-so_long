/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:23:16 by bryaloo           #+#    #+#             */
/*   Updated: 2024/07/22 21:24:04 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conversion(va_list args, const char type)
{
	int	len;

	len = 0;
	if (type == 'c')
		len += print_char(va_arg(args, int));
	else if (type == 's')
		len += print_str(va_arg(args, char *));
	else if (type == 'p')
		len += print_ptr(va_arg(args, unsigned long long));
	else if (type == 'd' || type == 'i')
		len += print_nbr(va_arg(args, int));
	else if (type == 'u' )
		len += print_unsigned(va_arg(args, unsigned int));
	else if (type == 'x' || type == 'X')
		len += print_hex(va_arg(args, unsigned int), type);
	else if (type == '%')
		len += print_percent();
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_conversion(args, str[i + 1]);
			i++;
		}
		else
			len += print_char(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
