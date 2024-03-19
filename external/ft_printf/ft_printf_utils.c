/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:50:59 by dmdemirk          #+#    #+#             */
/*   Updated: 2023/12/18 18:18:09 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_putchar(int c, int *counter)
{
	(*counter) += write(1, &c, 1);
}

void	ft_putstring(const char *string, int *counter)
{
	int	i;

	i = 0;
	if(!string)
		string = "(null)";
	while(string[i])
			(*counter) += write(1 , &string[i++], 1);
}

void	ft_putnbr(int number, int *counter)
{
	char	*temp_number;

	temp_number = ft_itoa(number);
	ft_putstring(temp_number, counter);
	free(temp_number);
}
