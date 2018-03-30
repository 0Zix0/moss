#include <assert.h>

void assert_failed(char* file, int line, char* expr)
{
    cls();
    printf("Assetion failed [%s] at %s, line %d\n", expr, file, line);
    system_catch_fire();
}
