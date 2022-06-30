        lw      0       1       6     load reg1 with 6 (symbolic address)
        lw      1       2      -3     load reg2 with -1 (nueric address)
start   ad      1       1       4
        beq     4       5      size    nor function check 
loop    jalr    4       3              checking 
        beq     5       2      35000
        beq     2       4      -35000 
        noop
        halt 
size    .fill   7   