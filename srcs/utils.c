#include "minirt.h"

static double set_point(const char *str, double output)
{
    int point;
    int i;

    point = 0;
    i = 0;
    while (str[i] != '.' && str[i] != '\0')
        ++i;
    if (str[i] == '.')
        ++i;
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        ++i;
        ++point;
    }
    while (point > 0)
    {
        output *= 0.1;
        --point;
    }
    return (output);
}

double atod(const char *str)
{
    int			i;
	double minus;
	double output;

	i = 0;
	output = 0.0;
	minus = 1.0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = -1;
		++i;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		output = output * 10.0 + (double)(str[i] - '0');
        if (str[i + 1] == '.')
            ++i;
		++i;
	}
    output = set_point(str, output);
	return (output * minus);
}

void free_strs(char **strs)
{
    int i;

    i = 0;
    while (strs[i])
    {
        free(strs[i]);
        ++i;
    }
    free(strs);
}