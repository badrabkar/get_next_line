/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babkar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 04:20:10 by babkar            #+#    #+#             */
/*   Updated: 2021/12/14 04:29:03 by babkar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*readline_bonus(int fd, char *readline)
{
	char	*buff;
	int		line;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	line = 1;
	while (!ft_strchr_bonus(readline, '\n') && line > 0)
	{
		line = read(fd, buff, BUFFER_SIZE);
		if (line == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[line] = '\0';
		readline = ft_strjoin_bonus(readline, buff);
	}
	free (buff);
	return (readline);
}

char	*get_line_bonus(char *read)
{
	char	*line;
	int		i;

	i = 0;
	if (read[0] == '\0')
		return (NULL);
	while (read[i] && read[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (read[i] && read[i] != '\n')
	{
		line[i] = read[i];
		i++;
	}
	if (read[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*resetread_bonus(char *read)
{
	char	*resetread;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (read[i] && read[i] != '\n')
		i++;
	if (read[i] == '\0')
	{
		free(read);
		return (NULL);
	}
	i++;
	resetread = (char *)malloc((ft_strlen_bonus(read) - i + 1) * sizeof(char));
	if (resetread == NULL)
		return (NULL);
	while (read[i])
		resetread[j++] = read[i++];
	if (read[i] == '\n')
		resetread[j] = '\n';
	resetread[j] = '\0';
	free (read);
	return (resetread);
}

char	*get_next_line(int fd)
{
	static char	*read[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read[fd] = readline_bonus(fd, read[fd]);
	if (!read[fd])
		return (NULL);
	line = get_line_bonus(read[fd]);
	read[fd] = resetread_bonus(read[fd]);
	return (line);
}
