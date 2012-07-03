/* mem.h: memory operations definitions.
 * Convers mem.S and mem.c */

/* mem.S */
extern void raise_privilege(void);
extern void user_mode(void);
extern void user_mode_branch(void (*fptr)(void));
extern void enable_psp(uint32_t *);
extern void disable_psp();

/* mem.c */
#define NULL                    (void *) 0x00000000
#define STKSIZE                 64                      /* This is in words */

void memset32(uint32_t *p, int32_t value, uint32_t size) __attribute__((section(".kernel")));

struct memlist {
    struct memlist *next;
};
