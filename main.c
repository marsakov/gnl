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
	//str = (char *)malloc(sizeof(char) * 651);
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

// int				main(void)
// {
// 	char 	*line;
// 	int		out;
// 	int		p[2];
// 	char 	*str;
// 	int		gnl_ret;

// 	str = (char *)malloc(1000 * 1000);
// 	*str = '\0';
// 	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
// 	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
// 	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
// 	out = dup(1);
// 	pipe(p);
// 	dup2(p[1], 1);
// 	printf("%s\n", str);
// 	write(1, str, strlen(str));
// 	close(p[1]);
// 	dup2(out, 1);
// 	gnl_ret = get_next_line(p[0], &line);
// 	printf("%d : %s\n", gnl_ret, line);
// }


//	printf("%d : %s\n", gnl_ret, line);