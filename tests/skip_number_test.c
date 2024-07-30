#include <assert.h>
#include <stdio.h>

void	skip_number(const char **iter);

int main(void)
{
	const char *iter;

	iter = "123.456";
	skip_number(&iter);
	assert(*iter == '\0');

	iter = "123.";
	skip_number(&iter);
	assert(*iter == '.');

	iter = "123";
	skip_number(&iter);
	assert(*iter == '\0');

	iter = ".456";
	skip_number(&iter);
	assert(*iter == '.');

	iter = "-.456";
	skip_number(&iter);
	assert(*iter == '-');

	iter = "-456";
	skip_number(&iter);
	assert(*iter == '\0');

	iter = "+0456";
	skip_number(&iter);
	assert(*iter == '\0');

	printf("skip_number: \033[92mOK\033[0m\n");
	return 0;
}
