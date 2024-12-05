#ifndef ARCH_I386_IO_H
#define ARCH_I386_IO_H

#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1 %0" : "=a" (ret) : "Nd" (port) : "memory");
    return ret;
}

static inline uint16_t inw(uint16_t port) {
    uint16_t ret;
    asm volatile("inw %1 %0" : "=a" (ret) : "Nd" (port) : "memory");
    return ret;
}

static inline uint32_t inl(uint16_t port) {
    uint32_t ret;
    asm volatile("inl %1 %0" : "=a" (ret) : "Nd" (port) : "memory");
    return ret;
}

static inline void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %b0 %w1" : : "a" (value), "Nd" (port) : "memory");
}

static inline void outw(uint16_t port, uint16_t value) {
    asm volatile("outw %w0 %w1" : : "a" (value), "Nd" (port) : "memory");
}

static inline void outl(uint16_t port, uint32_t value) {
    asm volatile("outl %l0 %w1" : : "a" (value), "Nd" (port) : "memory");
}

static inline void io_wait(void) {
    outb(0x80, 0);
}

#endif