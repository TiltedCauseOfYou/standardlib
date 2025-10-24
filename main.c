#include "vector.h"

int main(int argc, char const *argv[])
{
    vec32* vec = newVec();

    for(int i = 1; i < 51; i++) {
        append(vec, i);
        printVec(vec);
    }

    for(int i = 0; i < 50; i++) {
        printf("%d", pop(vec));
        printVec(vec);
    }

    freeVec(vec);

    return 0;
}
