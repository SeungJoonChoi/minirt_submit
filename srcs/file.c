#include "minirt.h"

static void extension_check(char* filename)
{
    char *temp;

    temp = ft_strnstr(filename, ".rt", ft_strlen(filename));
    if (temp == NULL || ft_strlen(temp) > 3)
        exit_err("Invalid filename extension.");
}

int open_file(char *filename)
{
    int fd;

    extension_check(filename);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        exit_err("Can not open file.");
    return (fd);
}