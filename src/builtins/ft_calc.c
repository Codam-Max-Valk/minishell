#include "../../include/minishell.h"
#include "../../include/libft.h"

typedef enum e_operand
{
	INVALID = 0,
	INCREMENT,
	DECREMENT,
	POWEROF,
	DIVISION,
}	t_operand;

static int	get_operand_type(int c)
{
	if (c == '+')
		return (INCREMENT);
	if (c == '-')
		return (DECREMENT);
	if (c == '*')
		return (POWEROF);
	return (INVALID);
}

static int	is_func_safe(char *s, int (*f)(int))
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!f(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	calculate(int a, int b, t_operand operand)
{
	if (operand == INCREMENT)
		return (a + b);
	else if (operand == DECREMENT)
		return (a - b);
	else if (operand == POWEROF)
		return (a * b);
	else if (operand == POWEROF)
		return (a / b);
	return (0);
}

int	ft_calc(t_shell *shell, int ac, char **av)
{
	int			a;
	int			b;
	int			c;
	t_operand	operand;

	operand = INVALID;
	if (!av[1] || !is_func_safe(av[1], ft_isdigit))
		return (printf("Error: argument is not a digit!\n"), EXIT_FAILURE);
	if (!av[2] || !get_operand_type(*av[2]))
		return (printf("Error: argument is not a operand!\n"), EXIT_FAILURE);
	if (!av[3] || !is_func_safe(av[3], ft_isdigit))
		return (printf("Error: argument is not a digit!\n"), EXIT_FAILURE);

	operand = get_operand_type(*av[2]);
	a = ft_atoi(av[1]);
	b = ft_atoi(av[3]);
	c = calculate(a, b, operand);
	ft_printf("[%sCalculator%s] %s %s %s = %d\n",
		BOLD_GREEN, RESET, av[1], av[2], av[3], c);

	return (EXIT_SUCCESS);
}
