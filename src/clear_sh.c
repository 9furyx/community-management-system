#include <stdlib.h>


// clear shell content
void clear_sh() {
    system("clear || cls");  // compatible with both POSIX and WIN32
}