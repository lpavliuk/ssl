/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_ssl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:40:02 by opavliuk          #+#    #+#             */
/*   Updated: 2018/11/01 20:40:03 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
// =============| DELETE IT!!! |================ //

void	check_binary(unsigned char *tmp)
{
	int i = -1;
	while (++i < 64)
		ft_printf("%d - %x\n", i, tmp[i]);
	ft_printf("\n");
}

// ============================================= //

static inline void	input_ssl(t_md5 *md5)
{
	char 	**str;
	int		i;

	ft_printf("==> %s\n", md5->line);
	write(1, "\e[0m", 4);
	str = ft_strsplit(md5->line, ' ');
	i = 0;
	if (str && str[0])
		check_command(md5, str[0]);
	if (md5->command && str && str[1])
		parsing_argv(md5, &str[0], &i);
	else if (md5->command)
		use_formula(md5, 0, 0);
	else
		while (str[++i])
			;
	ft_printf("free!\n");

	if (str && str[0])
		while (i > -1)
			free(str[i--]);
	(str) ? free(str) : 0;
	(md5->line) ? free(md5->line) : 0;
	ft_bzero(md5, sizeof(t_md5));
}

void				loop_ssl(t_md5 *md5)
{
	ft_printf("{yellow}OpenSSL>{green} ");
	while (get_next_line(0, &md5->line))
	{
		input_ssl(md5);

		update_hashes();
		system("leaks a.out");
		ft_printf("{yellow}OpenSSL>{green} ");
	}
}
