#include <assert.h>
#include <stdio.h>

int	skip_number(const char **iter);

int main(void)
{
	const char *iter;

	iter = "123.456";
	assert(skip_number(&iter) == 0 && *iter == '\0');

	iter = "123.";
	assert(skip_number(&iter) != 0 && *iter == '.');

	iter = "123";
	assert(skip_number(&iter) == 0 && *iter == '\0');

	iter = ".456";
	assert(skip_number(&iter) != 0 && *iter == '.');

	iter = "-.456";
	assert(skip_number(&iter) != 0 && *iter == '-');

	iter = "-456";
	assert(skip_number(&iter) == 0 && *iter == '\0');

	iter = "+0456";
	assert(skip_number(&iter) == 0 && *iter == '\0');

	printf("skip_number: \033[92mOK\033[0m\n");
	return 0;
}
