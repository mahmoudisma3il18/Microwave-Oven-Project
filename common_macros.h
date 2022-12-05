#ifndef   __COMMON_MACROS_H__
#define   __COMMON_MACROS_H__

#define SET_BIT(REG,BIT)        (REG |=(1<<BIT))
#define CLEAR_BIT(REG,BIT)      (REG &=(~(1<<BIT)))
#define TOGGLE_BIT(REG,BIT)     (REG ^=(1<<BIT))

#define BIT_IS_SET(REG,BIT)     (REG & (1<<BIT))
#define BIT_IS_CLEAR(REG,BIT)   (!(REG & (1<<BIT)))

#endif
