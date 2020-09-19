#pragma output nostreams
#pragma output nofileio

#include <stdio.h>
#include <stdlib.h>

#define PREPARE_NMI \
/*  asm("push af");*/ \
/*  asm("push hl");*/ \
    asm("push bc"); \
    asm("push de"); \
    asm("push ix"); \
    asm("push iy"); \
    asm("ex af, af"); \
    asm("exx"); \
    asm("push af"); \
    asm("push hl"); \
    asm("push bc"); \
    asm("push de");

#define UNPREPARE_NMI \
    asm("pop de"); \
    asm("pop bc"); \
    asm("pop hl"); \
    asm("pop af"); \
    asm("exx"); \
    asm("ex af, af"); \
    asm("pop iy"); \
    asm("pop ix"); \
    asm("pop de"); \
    asm("pop bc"); \
    asm("pop hl"); \
    asm("pop af"); \
    asm("retn");

void cls() __naked
{
    #asm
    call 0x0d6b // cls
    ret
    #endasm
}

void nmi() __naked
{
    PREPARE_NMI
    cls();
    static int nmi_count = 0;
    printk("NMI happened! Count=%d", ++nmi_count);
    UNPREPARE_NMI
}

int main()
{
    cls();
    printk("Press NMI button to perform test\n");
    wpoke(0x5CB0, nmi);
    while(1);

    return 0;
}