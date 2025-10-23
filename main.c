#include "vector.h"

int main(int argc, char const *argv[])
{
    vec32* vec = newVec();

    for(int i = 1; i < 101; i++) {
        append(vec, i);
        printVec(vec);
    }

    freeVec(vec);

    return 0;
}
