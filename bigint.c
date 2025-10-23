#include "vector.h"
#include "bigint.h"

struct big_int {
    char sign;
    vec32* arr;
};

void add(big_int* b, int i) {
    char sign = ((b->sign) ^ (i < 0)) & 1;
    i -= sign;
    uint32_t num = i ^ sign;
    
    if(!sign) {
        uint32_t bi = get(b->arr, 0);
        uint32_t spaceLeft = UINT32_MAX - bi;
        if(spaceLeft < num) {
            num -= spaceLeft;

            int j = 1;
            uint8_t carry = 1;
            do {
                if(b->arr->i <= j) {
                    append(b->arr, 1);
                    break;
                }

                bi = get(b->arr, j);
                if(bi == UINT32_MAX) {
                    set(b->arr, j++, 0);
                    continue;
                }
                set(b->arr, j, bi + 1);
                break;
            } while(1);
        }

        set(b->arr, 0, num);
    } else {
        
    }
}
void addBig(big_int* b1, big_int* b2) {

}

big_int* newBigInt(int i) {
    big_int* b = malloc(sizeof(big_int));
    if(!b) {
        perror("An error occured when allocating memory for a new Big Int.");
        return 0;
    }

    b->arr = newVecA(1);
    if(!b->arr) {
        perror("An error occured when allocating memory for a new Big Int.");
        free(b);
        return 0;
    }

    if(i < 0) {
        b->sign = 1;
        i = -i;
    } else b-> sign = 0;

    b->arr[0] = i;

    return b;
}

