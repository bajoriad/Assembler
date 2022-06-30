        lw      0       1       six      load reg1 with 6 (symbolic address)
        lw      1       2       negate   load reg2 with -1 (nueric address)
start   add     1       1       4
        nor     4       5       6        nor function check 
loop    jalr    4       3                checking 
        beq     5       2       date
        beq     2       4       size 
        sw      5       3       full
        noop
        halt 
size    .fill   7 
date    .fill   8
full    .fill   45
negate  .fill   -3
six     .fill    6