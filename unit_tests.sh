gcc src/load_file/skip/skip_number.c \
    tests/skip_number_test.c \
    lib/libft/lib/libft.a \
    -o skip_number_test \
    -g -D SKIP_NUMBER_UNIT_TEST=1 \
    && ./skip_number_test \
    && rm skip_number_test

