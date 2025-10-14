/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:25:00 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/09 17:06:19 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i = 0;

	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
		ft_putchar(s[i++]);
	return (i);
}

int	ft_putnbr(int n)
{
	int	count = 0;

	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr(n / 10);
	count += ft_putchar(n % 10 + '0');
	return (count);
}

int	ft_puthex(unsigned int n)
{
	char	*base = "0123456789abcdef";
	int		count = 0;

	if (n >= 16)
		count += ft_puthex(n / 16);
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		count = 0;

	va_start(args, fmt);
	while (*fmt)
	{
		if (*fmt == '%' && *(fmt + 1))
		{
			fmt++;
			if (*fmt == 's')
				count += ft_putstr(va_arg(args, char *));
			else if (*fmt == 'd')
				count += ft_putnbr(va_arg(args, int));
			else if (*fmt == 'x')
				count += ft_puthex(va_arg(args, unsigned int));
			else
				count += ft_putchar(*fmt);
		}
		else
			count += ft_putchar(*fmt);
		fmt++;
	}
	va_end(args);
	return (count);
}
