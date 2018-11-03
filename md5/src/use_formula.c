/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_formula.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:42:51 by opavliuk          #+#    #+#             */
/*   Updated: 2018/11/01 20:42:52 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void	use_formula(t_md5 *md5, int fd, char string)
{
	md5->flag_data = 1;
	if (md5->command == CMD_MD5)
	{
		(!string) ? take_fd_md5(md5, fd) : take_str_md5(md5);
		output_hash_md5();
	}
	else if (md5->command == CMD_SHA256)
		;
}
