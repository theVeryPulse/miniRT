#include <assert.h>
#include <stdio.h>

int	skip_rgb(const char **iter);

int main(void)
{
	const char *iter;

	iter = "255,255,255";
	assert(skip_rgb(&iter) == 0);

	iter = "255,255.255";
	assert(skip_rgb(&iter) != 0);

	iter = "255,255   ";
	assert(skip_rgb(&iter) != 0);

	iter = "255,255,255  ";
	assert(skip_rgb(&iter) == 0);

	iter = "255,-1,255";
	assert(skip_rgb(&iter) != 0);

	iter = "255,254.1,255";
	assert(skip_rgb(&iter) != 0);

	printf("skip_rgb: \033[92mOK\033[0m\n");
	return 0;
}
