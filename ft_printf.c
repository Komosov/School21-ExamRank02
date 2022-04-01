#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

//Remove fom
#include <stdio.h>
//Remove to

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_is_digit(char ch)
{
	return ((ch >= '0') && (ch <= '9'));
}

int	digits_count(int number)
{
	int	i;

	if (number < 0)
		number = -number;
	i = 0;
	while (number >= 10)
	{
		number = number / 10;
		i++;
	}
	return (i+1);
}

int	digits_count_x(int number)
{
	int	i;

	if (number < 0)
		number = -number;
	i = 0;
	while (number >= 16)
	{
		number = number / 16;
		i++;
	}
	return (i+1);
}

void	write_number(char *str, unsigned long l, unsigned long base, int *ret)
{
	if (l < base)
	{
		write (1, &str[l], 1);
		*ret += 1;
	}
	else
	{
		write_number(str, l / base, base, ret);
		write_number(str, l % base, base, ret);
	}
}

void	write_number_x(char *str, unsigned int l, unsigned int base, int *ret)
{
	if (l < base)
	{
		write (1, &str[l], 1);
		*ret += 1;
	}
	else
	{
		write_number(str, l / base, base, ret);
		write_number(str, l % base, base, ret);
	}
}

int ft_printf(const char *fmt, ... )
{
	va_list			ap;
	int				ret;
	int				i;
	int				num;
	unsigned int	u_num;
	long			spaces;
	long			precision;
	char			*str;

	ret = 0;
	va_start(ap, fmt);
	while (*fmt != '\0')
	{
		while ((*fmt != '\0') && (*fmt != '%'))
		{
			write (1, fmt, 1);
			ret += 1;
			fmt++;
		}
		if (*fmt == '%')
		{
			fmt++;
			spaces = -1;
			if (ft_is_digit(*fmt))
			{
				spaces = *fmt - '0';
				fmt++;
				while (ft_is_digit(*fmt))
				{
					spaces = spaces * 10 + (*fmt - '0');
					fmt++;
				}
			}
			precision = -1;
			if (*fmt == '.')
			{
				fmt++;
				precision = *fmt - '0';
				fmt++;
				while (ft_is_digit(*fmt))
				{
					precision = precision * 10 + (*fmt - '0');
					fmt++;
				}
			}
			if (*fmt == 's')
			{
				str = va_arg(ap, char *);
				if ((precision < ft_strlen(str)) && (precision != -1))
				{
					spaces = spaces - precision;
					i = 0;
					while (i < spaces)
					{
						write(1, " ", 1);
						ret += 1;
						i++;
					}
					i = 0;
					while (i < precision)
					{
						write(1, &str[i], 1);
						ret += 1;
						i++;
					}
				}
				else
				{
					spaces = spaces - ft_strlen(str);
					i = 0;
					while (i < spaces)
					{
						write(1, " ", 1);
						ret += 1;
						i++;
					}
					write(1, str, ft_strlen(str));
					ret += ft_strlen(str);
				}
				i = 0;
				fmt++;
			}
			else if (*fmt == 'd')
			{
				num = va_arg(ap, int);
				if (precision != -1)
				{
					if (precision < digits_count(num))
						precision = 0;
					else
						precision = precision - digits_count(num);
				}
				else
					precision = 0;
				if (spaces != -1)
				{
					if (spaces < (digits_count(num) + precision + (num < 0)))
						spaces = 0;
					else
						spaces = spaces - (digits_count(num) + precision + (num < 0));
				}
				while (spaces > 0)
				{
					write (1, " ", 1);
					ret += 1;
					spaces--;
				}
				if (num < 0)
				{
					write (1, "-", 1);
					ret += 1;
					num = -num;
				}
				while (precision > 0)
				{
					write (1, "0", 1);
					ret += 1;
					precision--;
				}
				write_number("0123456789", num, 10, &ret);
				fmt++;
			}
			else if (*fmt == 'x')
			{
				num = va_arg(ap, int);
				u_num = (unsigned int)num;
				if (precision != -1)
				{
					if (precision < digits_count_x(u_num))
						precision = 0;
					else
						precision = precision - digits_count_x(u_num);
				}
				else
					precision = 0;
				if (spaces != -1)
				{
					if (spaces < (digits_count_x(u_num) + precision))
						spaces = 0;
					else
						spaces = spaces - (digits_count_x(u_num) + precision);
				}
				while (spaces > 0)
				{
					write (1, " ", 1);
					ret += 1;
					spaces--;
				}
				while (precision > 0)
				{
					write (1, "0", 1);
					ret += 1;
					precision--;
				}
				write_number("0123456789abcdef", u_num, 16, &ret);
				fmt++;
			}
			else if (*fmt != '\0')
			{
				write(1, fmt, 1);
				if (*fmt != '\n')
					ret += 1;
				fmt++;
			}
		}
	}
	va_end(ap);
	return (ret);
}

int	main(void)
{
	int	a;
	int	b;

	// a = ft_printf("Magic %s is %5d", "number", 42);
	// ft_printf("\n%d\n", a);
	// b = printf("Magic %s is %5d", "number", 42);
	// printf("\n%d\n", b);

	a = ft_printf("Hexadecimal for %d is %x", -123, -123);
	write(1, "\n", 1);
	ft_printf("%d\n", a);
	   b = printf("Hexadecimal for %d is %x", -123, -123);
	printf("\n");
	printf("%d\n", b);
	return (0);
}
