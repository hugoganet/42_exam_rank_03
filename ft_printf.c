#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

static int	ft_strlen(const char *string)
{
	const char *start;

	start = string;
	while(*string)
		string++;
	return(string - start);
}

static void ft_putstr(const char *string, int *length)
{
	int	string_lenght;

	if (!(*string))
		string = "(null)";
	string_lenght = ft_strlen(string);
	*length += write(1, string, string_lenght);
}

static void	ft_putnbr(int number, int *length)
{
	if(number == -2147483648)
	{
		*length += write(1, "-2147483648", 11);
		return ;
	}
	if (number < 0)
	{
		*length += write(1, "-", 1);
		number = -number;
	}
	if (number >= 10)
		ft_putnbr(number / 10, length);
	*length += write(1, &"0123456789"[number % 10], 1);
}

static void ft_putnbr_hex(unsigned int number, int *length)
{
	if (number >= 16)
		ft_putnbr_hex(number / 16, length);
	*length += write(1, &"0123456789abcdef"[number % 16], 1);
}

static void handle_format(const char *format, va_list *arguments, int *length)
{
	if (*format == '%')
		*length += write(1, "%", 1);
	else if (*format == 's')
		ft_putstr(va_arg(*arguments, char *), length);
	else if (*format == 'd')
		ft_putnbr(va_arg(*arguments, int), length);
	else if (*format == 'x')
		ft_putnbr_hex(va_arg(*arguments, unsigned int), length);
	// TODO handle else case
}

int	ft_printf(const char *format, ...)
{
	int		length;
	va_list arguments;

	length = 0;
	va_start(arguments, format);
	while(*format)
	{
		if((*format == '%') && *(format + 1))
		{
			format++;
			handle_format(format, &arguments, &length);
		}
		else
			length += write(1, format, 1);
		format++;
	}
	va_end(arguments);
	return (length);
}

int main(void)
{
	int retval_ft_printf;
	int retval_printf;
	int number;
	char *string;

	string = "Hello motherfucker !";
	number = 42;
	retval_ft_printf = ft_printf("ft_printf : \n string = %s (%%)\n dec = %d\n hex = %x\n", string, number, number);
	printf("retval = %d\n\n", retval_ft_printf);
	retval_printf = printf("printf    : \n string = %s (%%)\n dec = %d\n hex = %x\n", string, number, number);
	printf("retval = %d\n\n", retval_printf);
	return (0);
}