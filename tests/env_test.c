#include <stdio.h>

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	int i = 1;

	while (env[i] && i == 1)
	{
		printf("%s\n", env[i]);
		i++;
	}
}