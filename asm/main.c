/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:58:05 by prastoin          #+#    #+#             */
/*   Updated: 2019/03/13 14:59:38 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, const char *argv[])
{
	char	str[sizeof(uintmax_t) * 2 + 2];

	ft_itoa_base(atoi(argv[1]), str, 16, "0123456789abcdef");
	printf("%s\n", str);
	return 0;
}
