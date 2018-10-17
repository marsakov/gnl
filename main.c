/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 20:10:51 by msakovyc          #+#    #+#             */
/*   Updated: 2018/04/14 20:10:52 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
	int fd;
	int i;
	int a;
	char *str;

	i = 0;
	str = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((a = get_next_line(fd, &str)) > 0)
		{
			printf("`````````````````````````````STR %d`````````````````````````````\n", i);
			printf("%d : %s\n", a, str);
			printf("````````````````````````````````````````````````````````````````\n");
			i++;
		}
		a = get_next_line(fd, &str);
		printf("%d %s\n", a, str);
	}
	return (0);
}
