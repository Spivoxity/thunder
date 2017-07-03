#include "vm.h"
#include <stdlib.h>
#include <stdio.h>

typedef int (*funcp)(int);

funcp compile(void) {
     code_addr entry;
     vmreg xV0 = vreg[0], xV1 = vreg[1];
     vmlabel lab1 = vm_newlab(), lab2 = vm_newlab();

     entry = vm_begin("fact", 1);
     vm_gen(GETARG, xV0, 0);
     vm_gen(MOV, xV1, 1);

     vm_label(lab1);
     vm_gen(BEQ, xV0, 0, lab2);
     vm_gen(MUL, xV1, xV1, xV0);
     vm_gen(SUB, xV0, xV0, 1);
     vm_gen(JUMP, lab1);

     vm_label(lab2);
     vm_gen(MOV, ret, xV1);
     vm_gen(RET);

     vm_end();

     return (funcp) entry;
}

funcp compile2(void) {
     code_addr entry;
     vmlabel lab1 = vm_newlab(), lab2 = vm_newlab();
     vmreg xV0 = vreg[0], xV1 = vreg[1];

     entry = vm_begin("fact", 1);
     vm_gen(GETARG, xV0, 0);

     vm_gen(BNEQ, xV0, 0, lab1);
     vm_gen(MOV, ret, 1);
     vm_gen(JUMP, lab2);
     
     vm_label(lab1);
     vm_gen(SUB, xV1, xV0, 1);
     vm_gen(PREP, 1);
     vm_gen(ARG, xV1);
     vm_gen(CALL, (int) entry);
     vm_gen(MUL, ret, xV0, ret);

     vm_label(lab2);
     vm_gen(RET);

     vm_end();

     return (funcp) entry;
}

int main(int argc, char *argv[]) {
     funcp fp, fp2;
     int n;

     vm_debug = 2;
     fp = compile(); fp2 = compile2();
     n = (argc > 1 ? atoi(argv[1]) : 10);
     printf("The factorial of %d is %d\n", n, (*fp)(n));
     printf("The factorial of %d is %d\n", n, (*fp2)(n));
     return 0;
}

void *vm_alloc(int size) {
     void *mem = NULL;
     if (posix_memalign(&mem, 4096, size) < 0) {
          fprintf(stderr, "Allocation failed\n");
          exit(2);
     }
     return mem;
}
