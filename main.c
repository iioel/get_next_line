#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	char	*line;
	int		fd;

	fd = 0;
	line = get_next_line(fd);
	while (line)
	{
		printf("Texted line: %s", line);
		line = get_next_line(fd);
	}
}
