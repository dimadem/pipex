/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmdemirk <dmdemirk@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:51:24 by dmdemirk          #+#    #+#             */
/*   Updated: 2023/12/18 18:02:05 by dmdemirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void ft_u_itoa(unsigned int input_number, int *counter)
{
    int i;

    i = 0;
    if(input_number > 9)
    {
        ft_u_itoa(input_number / 10, counter);
        ft_putchar(input_number % 10 + '0', counter);
        i++;
    }
    else
        ft_putchar(input_number + '0', counter);
}

void	ft_putunsigned(unsigned int input_number, int *counter)
{
    if (input_number == 0)
        ft_putchar('0', counter);
    else
    {
        ft_u_itoa(input_number, counter);
    }
}
