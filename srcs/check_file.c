#include "minirt.h"

int vec_range(t_vec* vec, double min, double max)
{
    if (vec->x < min || vec->x > max || vec->y < min || \
    vec->y > max || vec->z < min || vec->z > max)
        return (1);
    return (0);
}

int double_range(double* d, double min, double max)
{
    if (*d < min || *d > max)
        return (1);
    return (0);
}

void extension_check(char* filename)
{
    char *temp;

    temp = ft_strnstr(filename, ".rt", ft_strlen(filename));
    if (temp == NULL || ft_strlen(temp) > 3)
        exit_err("Invalid filename extension.");
}