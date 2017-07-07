#include "vm.h"
#include <stdlib.h>
#include <stdio.h>

typedef int (*funcp)(int);

funcp compile(void) {
     code_addr entry;
     vmreg r0 = ireg[0], r1 = ireg[1];
     vmlabel lab1 = vm_newlab(), lab2 = vm_newlab();

     entry = vm_begin("fact", 1);
     vm_gen(GETARG, r0, 0);
     vm_gen(MOV, r1, 1);

     vm_label(lab1);
     vm_gen(BEQ, r0, 0, lab2);
     vm_gen(MUL, r1, r1, r0);
     vm_gen(SUB, r0, r0, 1);
     vm_gen(JUMP, lab1);

     vm_label(lab2);
     vm_gen(MOV, ret, r1);
     vm_gen(RET);

     vm_end();

     return (funcp) entry;
}

funcp compile2(void) {
     code_addr entry;
     vmlabel lab1 = vm_newlab(), lab2 = vm_newlab();
     vmreg r0 = ireg[0], r1 = ireg[1];

     entry = vm_begin("fact", 1);
     vm_gen(GETARG, r0, 0);

     vm_gen(BNE, r0, 0, lab1);
     vm_gen(MOV, ret, 1);
     vm_gen(JUMP, lab2);
     
     vm_label(lab1);
     vm_gen(SUB, r1, r0, 1);
     vm_gen(PREP, 1);
     vm_gen(ARG, r1);
     vm_gen(CALL, (int) entry);
     vm_gen(MUL, ret, r0, ret);

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
