#ifndef SPH_TIGER_H__
#define SPH_TIGER_H__

#include <stddef.h>
#include "sph_types.h"

#if SPH_64

/**
 * Output size (in bits) for Tiger.
 */
#define SPH_SIZE_tiger   192

/**
 * Output size (in bits) for Tiger2.
 */
#define SPH_SIZE_tiger2   192

/**
 * This structure is a context for Tiger computations: it contains the
 * intermediate values and some data from the last entered block. Once
 * a Tiger computation has been performed, the context can be reused for
 * another computation.
 *
 * The contents of this structure are private. A running Tiger computation
 * can be cloned by copying the context (e.g. with a simple
 * <code>memcpy()</code>).
 */
typedef struct {
#ifndef DOXYGEN_IGNORE
	unsigned char buf[64];    /* first field, for alignment */
	sph_u64 val[3];
	sph_u64 count;
#endif
} sph_tiger_context;

/**
 * Initialize a Tiger context. This process performs no memory allocation.
 *
 * @param cc   the Tiger context (pointer to
 *             a <code>sph_tiger_context</code>)
 */
void sph_tiger_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the Tiger context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_tiger(void *cc, const void *data, size_t len);

/**
 * Terminate the current Tiger computation and output the result into the
 * provided buffer. The destination buffer must be wide enough to
 * accomodate the result (24 bytes). The context is automatically
 * reinitialized.
 *
 * @param cc    the Tiger context
 * @param dst   the destination buffer
 */
void sph_tiger_close(void *cc, void *dst);

/**
 * Apply the Tiger compression function on the provided data. The
 * <code>msg</code> parameter contains the 8 64-bit input blocks,
 * as numerical values (hence after the little-endian decoding). The
 * <code>val</code> parameter contains the 3 64-bit input blocks for
 * the compression function; the output is written in place in this
 * array.
 *
 * @param msg   the message block (8 values)
 * @param val   the function 192-bit input and output
 */
void sph_tiger_comp(const sph_u64 msg[8], sph_u64 val[3]);

/**
 * This structure is a context for Tiger2 computations. It is identical
 * to the Tiger context, and they may be freely exchanged, since the
 * difference between Tiger and Tiger2 resides solely in the padding, which
 * is computed only in the last computation step.
 */
typedef sph_tiger_context sph_tiger2_context;

#ifdef DOXYGEN_IGNORE
/**
 * Initialize a Tiger2 context. This function is identical to
 * <code>sph_tiger_init()</code>.
 *
 * @param cc   the Tiger2 context (pointer to
 *             a <code>sph_tiger2_context</code>)
 */
void sph_tiger2_init(void *cc);
#endif

#ifndef DOXYGEN_IGNORE
#define sph_tiger2_init   sph_tiger_init
#endif

#ifdef DOXYGEN_IGNORE
/**
 * Process some data bytes. This function is identical to
 * <code>sph_tiger()</code>.
 *
 * @param cc     the Tiger2 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_tiger2(void *cc, const void *data, size_t len);
#endif

#ifndef DOXYGEN_IGNORE
#define sph_tiger2   sph_tiger
#endif

/**
 * Terminate the current Tiger2 computation and output the result into the
 * provided buffer. The destination buffer must be wide enough to
 * accomodate the result (24 bytes). The context is automatically
 * reinitialized. Note that this function is NOT identical to
 * <code>sph_tiger2_close()</code>: this is the exact and unique point
 * where Tiger and Tiger2 differ.
 *
 * @param cc    the Tiger context
 * @param dst   the destination buffer
 */
void sph_tiger2_close(void *cc, void *dst);

#ifdef DOXYGEN_IGNORE
/**
 * Apply the Tiger2 compression function, which is identical to the Tiger
 * compression function.
 *
 * @param msg   the message block (8 values)
 * @param val   the function 192-bit input and output
 */
void sph_tiger2_comp(const sph_u64 msg[8], sph_u64 val[3]);
#endif

#ifndef DOXYGEN_IGNORE
#define sph_tiger2_comp   sph_tiger_comp
#endif

#endif

#endif
