test=skip_number
gcc src/load_file/skip/"$test".c \
    tests/"$test"_test.c \
    lib/libft/lib/libft.a \
    -o "$test"_test -g -Wall -Wextra \
    && ./"$test"_test \
    && rm "$test"_test

test=skip_rgb
gcc src/load_file/skip/"$test".c \
    tests/"$test"_test.c \
    lib/libft/lib/libft.a \
    -o "$test"_test -g -Wall -Wextra \
    && ./"$test"_test \
    && rm "$test"_test

