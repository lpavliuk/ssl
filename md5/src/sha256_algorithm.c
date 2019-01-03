/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 21:00:42 by opavliuk          #+#    #+#             */
/*   Updated: 2019/01/03 20:55:54 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void	swipe_size(unsigned long int *size)
{
	unsigned long int	reversed;
	unsigned char		*n1;
	unsigned char		*n2;

	n1 = (unsigned char *)&size;
	n2 = (unsigned char *)&reversed;
	n2[0] = n1[7];
	n2[1] = n1[6];
	n2[2] = n1[5];
	n2[3] = n1[4];
	n2[4] = n1[3];
	n2[5] = n1[2];
	n2[6] = n1[1];
	n2[7] = n1[0];
	*size = reversed;
}

static inline void	twice_last_line(t_md5 *md5)
{
	ft_memcpy(&md5->input_md5int[0], &md5->input_md5chr[0], 64);
	formula_md5(md5);
	ft_bzero(&md5->input_md5int[0], 64);
	ft_bzero(&md5->input_md5chr[0], 64);
	swipe_size(&md5->size);
	ft_memcpy(&md5->input_md5chr[0] + 56, (char *)&md5->size, 8);
	ft_memcpy(&md5->input_md5int[0], &md5->input_md5chr[0], 64);
	formula_sha256(md5);
}

static inline void	last_line(t_md5 *md5)
{
	swipe_size(&md5->size);
	ft_memcpy(&md5->input_md5chr[0] + 56, (char *)&md5->size, 8);
	ft_memcpy(&md5->input_md5int[0], &md5->input_md5chr[0], 64);
	formula_sha256(md5);
}

static inline void	end(t_md5 *md5, int i, int n)
{
	md5->size += i * 8;
	md5->input_md5chr[n] = 128;
	if (i < 56)
		last_line(md5);
	else
		twice_last_line(md5);
	ft_bzero(&md5->input_md5chr[0], 64);
	ft_bzero(&md5->input_md5int[0], 64);
	md5->size = 0;
	output_hash_md5();
}

void				take_fd_sha256(t_md5 *md5)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 0;
	while ((i = read(md5->fd, &md5->input_md5chr[n], 64 - n)) > 63 || i > 0)
	{
		md5->size += i * 8;
		n += i;
		if (n < 64)
			continue ;
		ft_memcpy(&md5->input_md5int[0], &md5->input_md5chr[0], 64);
		formula_sha256(md5);
		ft_bzero(&md5->input_md5chr[0], 64);
		ft_bzero(&md5->input_md5int[0], 64);
		n = 0;
	}
	end(md5, i, n + i);
}

void				take_str_sha256(t_md5 *md5)
{
	unsigned int	i;
	unsigned int	n;

	i = 1;
	n = 0;
	while (i > 0)
	{
		ft_strncpy((char *)&md5->input_md5chr[0], &md5->str[n], 64);
		i = ft_strlen((char *)&md5->input_md5chr[0]);
		n += i;
		if (i < 64)
			break ;
		md5->size += i * 8;
		ft_memcpy(&md5->input_md5int[0], &md5->input_md5chr[0], 64);
		formula_sha256(md5);
		ft_bzero(&md5->input_md5chr[0], 64);
		ft_bzero(&md5->input_md5int[0], 64);
	}	
	end(md5, i, n);
}
