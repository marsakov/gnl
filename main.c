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
	int bytes;

	i = 0;
	str = (char *)malloc(sizeof(char) * 651);
	//str = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
<<<<<<< HEAD
		while ((a = get_next_line(fd, &str)) > 0)
=======
		//get_next_line(fd, &str);
		while (i < 11 && get_next_line(fd, &str) == 1)
>>>>>>> 3e70d45b5d30f9553ecc4bd8fa7b0e4116fa88a2
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

// int				main(void)
// {
// 	char		*line;
// 	int			fd;
// 	int			ret;
// 	int			count_lines;
// 	char		*filename;
// 	int			errors;

// 	filename = "gnl1_1.txt";
// 	fd = open(filename, O_RDONLY);
// 	if (fd > 2)
// 	{
// 		count_lines = 0;
// 		errors = 0;
// 		line = (char *)malloc(sizeof(char) * 100);
// 		while ((ret = get_next_line(fd, &line)) > 0)
// 		{
// 			printf("vse ok\n");
// 			if (count_lines == 0 && strcmp(line, "1234567") != 0)
// 				errors++;
// 			count_lines++;
// 			if (count_lines > 50)
// 				break;
// 		}
// 		close(fd);
// 		if (count_lines != 1)
// 			printf("-> must have returned '1' once instead of %d time(s)\n", count_lines);
// 		if (errors > 0)
// 			printf("-> must have read \"1234567\" instead of \"%s\"\n", line);
// 		if (count_lines == 1 && errors == 0)
// 			printf("OK\n");
// 	}
// 	else
// 		printf("An error occured while opening file %s\n", filename);
// 	return (0);
// }
