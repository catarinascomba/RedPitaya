/**
 * $Id: $
 *
 * @brief Red Pitaya library common module interface
 *
 * @Author Red Pitaya
 *
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "redpitaya/rp.h"

#define ECHECK(x) { \
        int retval = (x); \
        if (retval != RP_OK) { \
            fprintf(stderr, "Runtime error: %s returned \"%s\" at %s:%d\n", #x, rp_GetError(retval), __FILE__, __LINE__); \
            return retval; \
        } \
}

#define CHANNEL_ACTION(CHANNEL, CHANNEL_1_ACTION, CHANNEL_2_ACTION) \
if ((CHANNEL) == RP_CH_1) { \
    CHANNEL_1_ACTION; \
} \
else if ((CHANNEL) == RP_CH_2) { \
    CHANNEL_2_ACTION; \
} \
else { \
    return RP_EPN; \
}

// unmasked IO read/write (p - pointer, v - value)
#define ioread32(p) (*(volatile uint32_t *)(p))
#define iowrite32(v,p) (*(volatile uint32_t *)(p) = (v))

#define SET_BITS(x,b) ((x) |= (b))
#define UNSET_BITS(x,b) ((x) &= ~(b))
#define SET_VALUE(x,b) ((x) = (b))
#define ARE_BITS_SET(x,b) (((x) & (b)) == (b))

#define VALIDATE_BITS(b,m) { \
        if (((b) & ~(m)) != 0) return RP_EOOR; \
}

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define FLOAT_EPS 0.00001f

#define FULL_SCALE_NORM     20.0    // V

int cmn_Init();
int cmn_Release();

int cmn_Map(size_t size, size_t offset, void** mapped);
int cmn_Unmap(size_t size, void** mapped);

int cmn_SetBits(volatile uint32_t* field, uint32_t bits, uint32_t mask);
int cmn_UnsetBits(volatile uint32_t* field, uint32_t bits, uint32_t mask);
int cmn_SetValue(volatile uint32_t* field, uint32_t value, uint32_t mask);
int cmn_SetShiftedValue(volatile uint32_t* field, uint32_t value, uint32_t mask, uint32_t bitsToSet);
int cmn_GetValue(volatile uint32_t* field, uint32_t* value, uint32_t mask);
int cmn_GetShiftedValue(volatile uint32_t* field, uint32_t* value, uint32_t mask, uint32_t bitsToSetShift);
int cmn_AreBitsSet(volatile uint32_t field, uint32_t bits, uint32_t mask, bool* result);

int intcmp(const void *a, const void *b);
int int16cmp(const void *aa, const void *bb);
int floatCmp(const void *a, const void *b);

float cmn_CnvCntToV(uint32_t field_len, uint32_t cnts, float adc_max_v);
uint32_t cmn_CnvVToCnt(uint32_t field_len, float voltage, float adc_max_v, bool calibFS_LO);

#endif /* COMMON_H_ */
