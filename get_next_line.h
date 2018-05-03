/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:16:15 by msakovyc          #+#    #+#             */
/*   Updated: 2018/04/12 16:16:19 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/includes/libft.h"
# include <fcntl.h>

# define BUFF_SIZE 3

typedef struct			s_gnl
{
	int					fd;
	int					i;
	char				content[BUFF_SIZE + 1];
	struct s_gnl		*next;
}						t_gnl;

int						get_next_line(const int fd, char **line);

#endif
