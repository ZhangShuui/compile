    .data 
  n:    
    .word   20

    .global array
    .bss
    .align 2
    .size array, 80
  array:
    .space 80

@常量区    
    .section .rodata
    .align 2
  str0: 
    .ascii "%d \0"

    .global main 
    .global fibprint   

    .text  
                                                                                                               
  main:  
  push    {lr}
  bl fibprint
  
  pop     {pc}

  fibprint:
  push    {lr}
  @r0存储项数,r1存array的地址
  @r4 计数器
  ldr r11,_bridge+8
  mov r4,#0
  @r5 中间变量计算结果
  mov r5,#1
  @中间变量计算结果放入对应的地址中
  
  str r5,[r11,r4,LSL #2]
  add r4,r4,#1
  str r5,[r11,r4,LSL #2]
  mov r4,#0

  
  LOOP:
  mov r9,#1

  cmp r4,#0
  beq L1

  cmp r4,#1
  beq L1

  sub r5,r4,#1
  sub r6,r4,#2
  ldr r7,[r11,r5,LSL #2]
  ldr r8,[r11,r6,LSL #2]

@   ldr r0,_bridge+4
@   mov r1,r7
@   bl printf

@   ldr r0,_bridge+4
@   mov r1,r8
@   bl printf

  add r9,r7,r8
  str r9,[r11,r4,LSL #2]

  @打印

  L1:
  ldr r0,_bridge+4
  mov r1,r9
  bl printf

  add r4,r4,#1
  ldr r10,_bridge
  ldr r10,[r10]
  cmp r4,r10
  beq END
  b LOOP
  END:

  pop     {pc}
  
  _bridge:
    .word   n
    .word   str0
    .word   array



  
