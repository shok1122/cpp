#include <stdio.h>

#define LOGOUT(fmt, ...) fprintf(stderr, "%s:%d " fmt "\n", __FILE__, __LINE__, ## __VA_ARGS__)
