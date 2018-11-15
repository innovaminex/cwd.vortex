#ifndef SPH_RADIOGATUN_H__
#define SPH_RADIOGATUN_H__

#include <stddef.h>
#include "sph_types.h"

/**
 * Output size (in bits) for RadioGatun[32].
 */
#define SPH_SIZE_radiogatun32   256

/**
 * This structure is a context for RadioGatun[32] computations: it
 * contains intermediate values and some data from the last entered
 * block. Once a RadioGatun[32] computation has been performed, the
 * context can be reused for another computation.
 *
 * The contents of this structure are private. A running RadioGatun[32]
 * computation can be cloned by copying the context (e.g. with a
 * simple <code>memcpy()</code>).
 */
typedef struct {
#ifndef DOXYGEN_IGNORE
	unsigned char data[156];   /* first field, for alignment */
	unsigned data_ptr;
	sph_u32 a[19], b[39];
#endif
} sph_radiogatun32_context;

/**
 * Initialize a RadioGatun[32] context. This process performs no
 * memory allocation.
 *
 * @param cc   the RadioGatun[32] context (pointer to a
 *             <code>sph_radiogatun32_context</code>)
 */
void sph_radiogatun32_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the RadioGatun[32] context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_radiogatun32(void *cc, const void *data, size_t len);

/**
 * Terminate the current RadioGatun[32] computation and output the
 * result into the provided buffer. The destination buffer must be wide
 * enough to accomodate the result (32 bytes). The context is
 * automatically reinitialized.
 *
 * @param cc    the RadioGatun[32] context
 * @param dst   the destination buffer
 */
void sph_radiogatun32_close(void *cc, void *dst);

#if SPH_64

/**
 * Output size (in bits) for RadioGatun[64].
 */
#define SPH_SIZE_radiogatun64   256

/**
 * This structure is a context for RadioGatun[64] computations: it
 * contains intermediate values and some data from the last entered
 * block. Once a RadioGatun[64] computation has been performed, the
 * context can be reused for another computation.
 *
 * The contents of this structure are private. A running RadioGatun[64]
 * computation can be cloned by copying the context (e.g. with a
 * simple <code>memcpy()</code>).
 */
typedef struct {
#ifndef DOXYGEN_IGNORE
	unsigned char data[312];   /* first field, for alignment */
	unsigned data_ptr;
	sph_u64 a[19], b[39];
#endif
} sph_radiogatun64_context;

/**
 * Initialize a RadioGatun[64] context. This process performs no
 * memory allocation.
 *
 * @param cc   the RadioGatun[64] context (pointer to a
 *             <code>sph_radiogatun64_context</code>)
 */
void sph_radiogatun64_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the RadioGatun[64] context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_radiogatun64(void *cc, const void *data, size_t len);

/**
 * Terminate the current RadioGatun[64] computation and output the
 * result into the provided buffer. The destination buffer must be wide
 * enough to accomodate the result (32 bytes). The context is
 * automatically reinitialized.
 *
 * @param cc    the RadioGatun[64] context
 * @param dst   the destination buffer
 */
void sph_radiogatun64_close(void *cc, void *dst);

#endif

#endif
