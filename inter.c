
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	ft_char_check(char ch, char *str)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(str);
	while ((i < l) && (ch != str[i]))
		i++;
	if (ch != str[i])
		return (ch);
	else
		return ('\0');
}

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	char	res[100000];

	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	j = 0;
	res[0] = '\0';
	while (argv[1][i] != '\0')
	{
		while ((j < ft_strlen(argv[2])) && (argv[1][i] != argv[2][j]))
			j++;
		if (argv[1][i] == argv[2][j])
		{
			res[ft_strlen(res)] = ft_char_check(argv[1][i], res);
			res[ft_strlen(res)] = '\0';
		}
		j = 0;
		i++;
	}
	write(1, &res, ft_strlen(res));
	write(1, "\n", 1);
	return (0);
}
