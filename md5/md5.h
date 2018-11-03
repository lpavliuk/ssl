/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 17:00:42 by opavliuk          #+#    #+#             */
/*   Updated: 2018/10/22 17:00:43 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft/include_lib/libft.h"
# include <fcntl.h>

# define CMD_MD5 0x01
# define CMD_SHA256 0x02

# define FLAG_P 0x01
# define FLAG_S 0x02
# define FLAG_R 0x04
# define FLAG_Q 0x08

# define A g_hash_md5[0]
# define B g_hash_md5[1]
# define C g_hash_md5[2]
# define D g_hash_md5[3]
# define TMD5 g_table_md5

unsigned int				g_hash_md5[4];

static const unsigned int	g_table_md5[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

typedef struct				s_md5
{
	unsigned int		input_md5int[16];
	unsigned long int	size;
	char				*str;
	char				flags_rqps;
	char				flag_data;
	char				flag_usage;
	char				*line;
	char				command;
}							t_md5;

void						loop_ssl(t_md5 *md5);
void						usage(char *str);
void						take_fd_md5(t_md5 *md5, int fd);
void						use_formula(t_md5 *md5, int fd, char string);
void						formula_md5(t_md5 *md5);
void						parsing_argv(t_md5 *md5, char **argv, int *i);
void						check_command(t_md5 *md5, char *argv);
void						check_flags(t_md5 *md5, char **argv, int *i);
void						update_hashes(void);
void						free_md5(t_md5 *md5);

#endif
