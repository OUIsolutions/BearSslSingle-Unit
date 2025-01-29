/* Automatically generated code; do not modify directly. */

#include <stddef.h>
#include <stdint.h>

typedef struct {
	uint32_t *dp;
	uint32_t *rp;
	const unsigned char *ip;
} t0_context;

static uint32_t
(BEAR_SINGLE_UNITY_FILE)t0_parse7E_unsigned(const unsigned char **p)
{
	uint32_t x;

	x = 0;
	for (;;) {
		unsigned y;

		y = *(*p) ++;
		x = (x << 7) | (uint32_t)(y & 0x7F);
		if (y < 0x80) {
			return x;
		}
	}
}

static int32_t
(BEAR_SINGLE_UNITY_FILE)t0_parse7E_signed(const unsigned char **p)
{
	int neg;
	uint32_t x;

	neg = ((**p) >> 6) & 1;
	x = (uint32_t)-neg;
	for (;;) {
		unsigned y;

		y = *(*p) ++;
		x = (x << 7) | (uint32_t)(y & 0x7F);
		if (y < 0x80) {
			if (neg) {
				return -(int32_t)~x - 1;
			} else {
				return (int32_t)x;
			}
		}
	}
}

#define T0_VBYTE(x, n)   (unsigned char)((((uint32_t)(x) >> (n)) & 0x7F) | 0x80)
#define T0_FBYTE(x, n)   (unsigned char)(((uint32_t)(x) >> (n)) & 0x7F)
#define T0_SBYTE(x)      (unsigned char)((((uint32_t)(x) >> 28) + 0xF8) ^ 0xF8)
#define T0_INT1(x)       T0_FBYTE(x, 0)
#define T0_INT2(x)       T0_VBYTE(x, 7), T0_FBYTE(x, 0)
#define T0_INT3(x)       T0_VBYTE(x, 14), T0_VBYTE(x, 7), T0_FBYTE(x, 0)
#define T0_INT4(x)       T0_VBYTE(x, 21), T0_VBYTE(x, 14), T0_VBYTE(x, 7), T0_FBYTE(x, 0)
#define T0_INT5(x)       T0_SBYTE(x), T0_VBYTE(x, 21), T0_VBYTE(x, 14), T0_VBYTE(x, 7), T0_FBYTE(x, 0)

/* static const unsigned char (BEAR_SINGLE_UNITY_FILE)t0_datablock[]; */


void br_pem_decoder_init_main(void *t0ctx);

void br_pem_decoder_run(void *t0ctx);





#define (BEAR_SINGLE_UNITY_FILE)CTX   ((br_pem_decoder_context *)(void *)((unsigned char *)t0ctx - offsetof(br_pem_decoder_context, cpu)))

/* see bearssl_pem.h */
void
br_pem_decoder_init(br_pem_decoder_context *ctx)
{
	memset(ctx, 0, sizeof *ctx);
	ctx->cpu.dp = &ctx->dp_stack[0];
	ctx->cpu.rp = &ctx->rp_stack[0];
	br_pem_decoder_init_main(&ctx->cpu);
	br_pem_decoder_run(&ctx->cpu);
}

/* see bearssl_pem.h */
size_t
br_pem_decoder_push(br_pem_decoder_context *ctx,
	const void *data, size_t len)
{
	if (ctx->event) {
		return 0;
	}
	ctx->hbuf = data;
	ctx->hlen = len;
	br_pem_decoder_run(&ctx->cpu);
	return len - ctx->hlen;
}

/* see bearssl_pem.h */
int
br_pem_decoder_event(br_pem_decoder_context *ctx)
{
	int event;

	event = ctx->event;
	ctx->event = 0;
	return event;
}



static const unsigned char (BEAR_SINGLE_UNITY_FILE)t0_datablock[] = {
	0x00, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x42, 0x45, 0x47, 0x49, 0x4E, 0x20,
	0x00, 0x2D, 0x2D, 0x2D, 0x2D, 0x45, 0x4E, 0x44, 0x20, 0x00
};

static const unsigned char (BEAR_SINGLE_UNITY_FILE)t0_codeblock[] = {
	0x00, 0x01, 0x00, 0x09, 0x00, 0x00, 0x01, 0x01, 0x07, 0x00, 0x00, 0x01,
	0x01, 0x08, 0x00, 0x00, 0x13, 0x13, 0x00, 0x00, 0x01,
	T0_INT2(offsetof(br_pem_decoder_context, event)), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(br_pem_decoder_context, name)), 0x00, 0x00, 0x05,
	0x14, 0x2C, 0x14, 0x01, 0x0A, 0x0D, 0x06, 0x03, 0x13, 0x04, 0x76, 0x01,
	0x2D, 0x0C, 0x06, 0x05, 0x2E, 0x01, 0x03, 0x2D, 0x00, 0x01, 0x0D, 0x27,
	0x05, 0x04, 0x01, 0x03, 0x2D, 0x00, 0x15, 0x2E, 0x01, 0x02, 0x2D, 0x00,
	0x01, 0x01, 0x7F, 0x03, 0x00, 0x25, 0x01, 0x00, 0x18, 0x0D, 0x06, 0x03,
	0x13, 0x04, 0x3C, 0x01, 0x7F, 0x18, 0x0D, 0x06, 0x13, 0x13, 0x02, 0x00,
	0x05, 0x06, 0x2E, 0x01, 0x03, 0x2D, 0x04, 0x03, 0x01, 0x7F, 0x23, 0x01,
	0x00, 0x00, 0x04, 0x23, 0x01, 0x01, 0x18, 0x0D, 0x06, 0x09, 0x13, 0x01,
	0x00, 0x23, 0x01, 0x00, 0x00, 0x04, 0x14, 0x01, 0x02, 0x18, 0x0D, 0x06,
	0x06, 0x13, 0x01, 0x7F, 0x00, 0x04, 0x08, 0x13, 0x01, 0x03, 0x2D, 0x01,
	0x00, 0x00, 0x13, 0x01, 0x00, 0x03, 0x00, 0x04, 0xFF, 0x33, 0x01, 0x2C,
	0x14, 0x01, 0x2D, 0x0D, 0x06, 0x04, 0x13, 0x01, 0x7F, 0x00, 0x14, 0x31,
	0x06, 0x02, 0x13, 0x29, 0x14, 0x01, 0x0A, 0x0D, 0x06, 0x04, 0x13, 0x01,
	0x02, 0x00, 0x16, 0x14, 0x1D, 0x06, 0x05, 0x13, 0x2E, 0x01, 0x03, 0x00,
	0x03, 0x00, 0x29, 0x14, 0x01, 0x0A, 0x0D, 0x06, 0x04, 0x13, 0x01, 0x03,
	0x00, 0x16, 0x14, 0x1D, 0x06, 0x05, 0x13, 0x2E, 0x01, 0x03, 0x00, 0x02,
	0x00, 0x01, 0x06, 0x0A, 0x07, 0x03, 0x00, 0x29, 0x14, 0x01, 0x0A, 0x0D,
	0x06, 0x04, 0x13, 0x01, 0x03, 0x00, 0x14, 0x01, 0x3D, 0x0D, 0x06, 0x2E,
	0x13, 0x29, 0x14, 0x01, 0x0A, 0x0D, 0x06, 0x04, 0x13, 0x01, 0x03, 0x00,
	0x2F, 0x05, 0x04, 0x13, 0x01, 0x03, 0x00, 0x01, 0x3D, 0x0C, 0x06, 0x03,
	0x01, 0x03, 0x00, 0x02, 0x00, 0x01, 0x0F, 0x10, 0x06, 0x03, 0x01, 0x03,
	0x00, 0x02, 0x00, 0x01, 0x04, 0x0F, 0x1C, 0x01, 0x01, 0x00, 0x16, 0x14,
	0x1D, 0x06, 0x05, 0x13, 0x2E, 0x01, 0x03, 0x00, 0x02, 0x00, 0x01, 0x06,
	0x0A, 0x07, 0x03, 0x00, 0x29, 0x14, 0x01, 0x0A, 0x0D, 0x06, 0x04, 0x13,
	0x01, 0x03, 0x00, 0x14, 0x01, 0x3D, 0x0D, 0x06, 0x20, 0x13, 0x2F, 0x05,
	0x03, 0x01, 0x03, 0x00, 0x02, 0x00, 0x01, 0x03, 0x10, 0x06, 0x03, 0x01,
	0x03, 0x00, 0x02, 0x00, 0x01, 0x0A, 0x0F, 0x1C, 0x02, 0x00, 0x01, 0x02,
	0x0F, 0x1C, 0x01, 0x01, 0x00, 0x16, 0x14, 0x1D, 0x06, 0x05, 0x13, 0x2E,
	0x01, 0x03, 0x00, 0x02, 0x00, 0x01, 0x06, 0x0A, 0x07, 0x03, 0x00, 0x02,
	0x00, 0x01, 0x10, 0x0F, 0x1C, 0x02, 0x00, 0x01, 0x08, 0x0F, 0x1C, 0x02,
	0x00, 0x1C, 0x01, 0x00, 0x00, 0x00, 0x28, 0x01, 0x01, 0x2D, 0x24, 0x06,
	0x02, 0x04, 0x7B, 0x04, 0x75, 0x00, 0x14, 0x12, 0x2A, 0x14, 0x05, 0x04,
	0x20, 0x01, 0x7F, 0x00, 0x2C, 0x2A, 0x14, 0x01, 0x0A, 0x0D, 0x06, 0x05,
	0x13, 0x20, 0x01, 0x00, 0x00, 0x0D, 0x05, 0x05, 0x13, 0x2E, 0x01, 0x00,
	0x00, 0x1E, 0x04, 0x5E, 0x00, 0x01, 0x01, 0x27, 0x06, 0x0B, 0x22, 0x01,
	0x80, 0x7F, 0x2B, 0x14, 0x06, 0x02, 0x30, 0x00, 0x13, 0x04, 0x6E, 0x00,
	0x2C, 0x14, 0x31, 0x05, 0x01, 0x00, 0x13, 0x04, 0x77, 0x00, 0x14, 0x14,
	0x01, 0x80, 0x61, 0x0E, 0x1B, 0x01, 0x80, 0x7A, 0x0B, 0x10, 0x06, 0x03,
	0x01, 0x20, 0x08, 0x00, 0x01, 0x14, 0x03, 0x00, 0x1B, 0x18, 0x05, 0x05,
	0x20, 0x2E, 0x01, 0x00, 0x00, 0x2C, 0x14, 0x01, 0x0A, 0x0D, 0x06, 0x06,
	0x20, 0x02, 0x00, 0x1B, 0x08, 0x00, 0x14, 0x01, 0x0D, 0x0D, 0x06, 0x03,
	0x13, 0x04, 0x03, 0x2A, 0x18, 0x1A, 0x1E, 0x1B, 0x1F, 0x1B, 0x04, 0x59,
	0x00, 0x19, 0x14, 0x1D, 0x05, 0x01, 0x00, 0x13, 0x11, 0x04, 0x76, 0x00,
	0x21, 0x1A, 0x11, 0x00, 0x00, 0x2C, 0x01, 0x0A, 0x0C, 0x06, 0x02, 0x04,
	0x78, 0x00, 0x01, 0x01, 0x7F, 0x03, 0x00, 0x2C, 0x14, 0x01, 0x0A, 0x0C,
	0x06, 0x09, 0x31, 0x05, 0x04, 0x01, 0x00, 0x03, 0x00, 0x04, 0x70, 0x13,
	0x02, 0x00, 0x00, 0x00, 0x14, 0x06, 0x14, 0x1F, 0x14, 0x22, 0x07, 0x17,
	0x01, 0x2D, 0x0C, 0x06, 0x08, 0x22, 0x07, 0x1E, 0x01, 0x00, 0x1B, 0x1A,
	0x00, 0x04, 0x69, 0x22, 0x1A, 0x00, 0x00, 0x14, 0x01, 0x0A, 0x0C, 0x1B,
	0x01, 0x20, 0x0B, 0x10, 0x00
};

static const uint16_t (BEAR_SINGLE_UNITY_FILE)t0_caddr[] = {
	0,
	5,
	10,
	15,
	19,
	24,
	29,
	67,
	149,
	384,
	396,
	431,
	450,
	460,
	479,
	523,
	534,
	539,
	549,
	574,
	601
};

#define (BEAR_SINGLE_UNITY_FILE)T0_INTERPRETED   29

#define (BEAR_SINGLE_UNITY_FILE)T0_ENTER(ip, rp, slot)   do { \
		const unsigned char *t0_newip; \
		uint32_t t0_lnum; \
		t0_newip = &(BEAR_SINGLE_UNITY_FILE)t0_codeblock[(BEAR_SINGLE_UNITY_FILE)t0_caddr[(slot) - (BEAR_SINGLE_UNITY_FILE)T0_INTERPRETED]]; \
		t0_lnum = (BEAR_SINGLE_UNITY_FILE)t0_parse7E_unsigned(&t0_newip); \
		(rp) += t0_lnum; \
		*((rp) ++) = (uint32_t)((ip) - &(BEAR_SINGLE_UNITY_FILE)t0_codeblock[0]) + (t0_lnum << 16); \
		(ip) = t0_newip; \
	} while (0)

#define (BEAR_SINGLE_UNITY_FILE)T0_DEFENTRY(name, slot) \
void \
name(void *ctx) \
{ \
	t0_context *t0ctx = ctx; \
	t0ctx->ip = &(BEAR_SINGLE_UNITY_FILE)t0_codeblock[0]; \
	(BEAR_SINGLE_UNITY_FILE)T0_ENTER(t0ctx->ip, t0ctx->rp, slot); \
}

(BEAR_SINGLE_UNITY_FILE)T0_DEFENTRY(br_pem_decoder_init_main, 38)

#define T0_NEXT(t0ipp)   (*(*(t0ipp)) ++)

void
br_pem_decoder_run(void *t0ctx)
{
	uint32_t *dp, *rp;
	const unsigned char *ip;

#define T0_LOCAL(x)    (*(rp - 2 - (x)))
#define T0_POP()       (*-- dp)
#define T0_POPi()      (*(int32_t *)(-- dp))
#define T0_PEEK(x)     (*(dp - 1 - (x)))
#define T0_PEEKi(x)    (*(int32_t *)(dp - 1 - (x)))
#define T0_PUSH(v)     do { *dp = (v); dp ++; } while (0)
#define T0_PUSHi(v)    do { *(int32_t *)dp = (v); dp ++; } while (0)
#define T0_RPOP()      (*-- rp)
#define T0_RPOPi()     (*(int32_t *)(-- rp))
#define T0_RPUSH(v)    do { *rp = (v); rp ++; } while (0)
#define T0_RPUSHi(v)   do { *(int32_t *)rp = (v); rp ++; } while (0)
#define T0_ROLL(x)     do { \
	size_t t0len = (size_t)(x); \
	uint32_t t0tmp = *(dp - 1 - t0len); \
	memmove(dp - t0len - 1, dp - t0len, t0len * sizeof *dp); \
	*(dp - 1) = t0tmp; \
} while (0)
#define T0_SWAP()      do { \
	uint32_t t0tmp = *(dp - 2); \
	*(dp - 2) = *(dp - 1); \
	*(dp - 1) = t0tmp; \
} while (0)
#define T0_ROT()       do { \
	uint32_t t0tmp = *(dp - 3); \
	*(dp - 3) = *(dp - 2); \
	*(dp - 2) = *(dp - 1); \
	*(dp - 1) = t0tmp; \
} while (0)
#define T0_NROT()       do { \
	uint32_t t0tmp = *(dp - 1); \
	*(dp - 1) = *(dp - 2); \
	*(dp - 2) = *(dp - 3); \
	*(dp - 3) = t0tmp; \
} while (0)
#define T0_PICK(x)      do { \
	uint32_t t0depth = (x); \
	T0_PUSH(T0_PEEK(t0depth)); \
} while (0)
#define T0_CO()         do { \
	goto t0_exit; \
} while (0)
#define T0_RET()        goto t0_next

	dp = ((t0_context *)t0ctx)->dp;
	rp = ((t0_context *)t0ctx)->rp;
	ip = ((t0_context *)t0ctx)->ip;
	goto t0_next;
	for (;;) {
		uint32_t t0x;

	t0_next:
		t0x = T0_NEXT(&ip);
		if (t0x < (BEAR_SINGLE_UNITY_FILE)T0_INTERPRETED) {
			switch (t0x) {
				int32_t t0off;

			case 0: /* ret */
				t0x = T0_RPOP();
				rp -= (t0x >> 16);
				t0x &= 0xFFFF;
				if (t0x == 0) {
					ip = NULL;
					goto t0_exit;
				}
				ip = &(BEAR_SINGLE_UNITY_FILE)t0_codeblock[t0x];
				break;
			case 1: /* literal constant */
				T0_PUSHi((BEAR_SINGLE_UNITY_FILE)t0_parse7E_signed(&ip));
				break;
			case 2: /* read local */
				T0_PUSH(T0_LOCAL((BEAR_SINGLE_UNITY_FILE)t0_parse7E_unsigned(&ip)));
				break;
			case 3: /* write local */
				T0_LOCAL((BEAR_SINGLE_UNITY_FILE)t0_parse7E_unsigned(&ip)) = T0_POP();
				break;
			case 4: /* jump */
				t0off = (BEAR_SINGLE_UNITY_FILE)t0_parse7E_signed(&ip);
				ip += t0off;
				break;
			case 5: /* jump if */
				t0off = (BEAR_SINGLE_UNITY_FILE)t0_parse7E_signed(&ip);
				if (T0_POP()) {
					ip += t0off;
				}
				break;
			case 6: /* jump if not */
				t0off = (BEAR_SINGLE_UNITY_FILE)t0_parse7E_signed(&ip);
				if (!T0_POP()) {
					ip += t0off;
				}
				break;
			case 7: {
				/* + */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(a + b);

				}
				break;
			case 8: {
				/* - */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(a - b);

				}
				break;
			case 9: {
				/* < */

	int32_t b = T0_POPi();
	int32_t a = T0_POPi();
	T0_PUSH(-(uint32_t)(a < b));

				}
				break;
			case 10: {
				/* << */

	int c = (int)T0_POPi();
	uint32_t x = T0_POP();
	T0_PUSH(x << c);

				}
				break;
			case 11: {
				/* <= */

	int32_t b = T0_POPi();
	int32_t a = T0_POPi();
	T0_PUSH(-(uint32_t)(a <= b));

				}
				break;
			case 12: {
				/* <> */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(-(uint32_t)(a != b));

				}
				break;
			case 13: {
				/* = */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(-(uint32_t)(a == b));

				}
				break;
			case 14: {
				/* >= */

	int32_t b = T0_POPi();
	int32_t a = T0_POPi();
	T0_PUSH(-(uint32_t)(a >= b));

				}
				break;
			case 15: {
				/* >> */

	int c = (int)T0_POPi();
	int32_t x = T0_POPi();
	T0_PUSHi(x >> c);

				}
				break;
			case 16: {
				/* and */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(a & b);

				}
				break;
			case 17: {
				/* co */
 T0_CO(); 
				}
				break;
			case 18: {
				/* data-get8 */

	size_t addr = T0_POP();
	T0_PUSH((BEAR_SINGLE_UNITY_FILE)t0_datablock[addr]);

				}
				break;
			case 19: {
				/* drop */
 (void)T0_POP(); 
				}
				break;
			case 20: {
				/* dup */
 T0_PUSH(T0_PEEK(0)); 
				}
				break;
			case 21: {
				/* flush-buf */

	if ((BEAR_SINGLE_UNITY_FILE)CTX->ptr > 0) {
		if ((BEAR_SINGLE_UNITY_FILE)CTX->dest) {
			(BEAR_SINGLE_UNITY_FILE)CTX->dest((BEAR_SINGLE_UNITY_FILE)CTX->dest_ctx, (BEAR_SINGLE_UNITY_FILE)CTX->buf, (BEAR_SINGLE_UNITY_FILE)CTX->ptr);
		}
		(BEAR_SINGLE_UNITY_FILE)CTX->ptr = 0;
	}

				}
				break;
			case 22: {
				/* from-base64 */

	uint32_t c = T0_POP();
	uint32_t p, q, r, z;
	p = c - 0x41;
	q = c - 0x61;
	r = c - 0x30;

	z = ((p + 2) & -LT(p, 26))
		| ((q + 28) & -LT(q, 26))
		| ((r + 54) & -LT(r, 10))
		| (64 & -EQ(c, 0x2B))
		| (65 & -EQ(c, 0x2F))
		| EQ(c, 0x3D);
	T0_PUSHi((int32_t)z - 2);

				}
				break;
			case 23: {
				/* get8 */

	size_t addr = T0_POP();
	T0_PUSH(*((unsigned char *)(BEAR_SINGLE_UNITY_FILE)CTX + addr));

				}
				break;
			case 24: {
				/* over */
 T0_PUSH(T0_PEEK(1)); 
				}
				break;
			case 25: {
				/* read8-native */

	if ((BEAR_SINGLE_UNITY_FILE)CTX->hlen > 0) {
		T0_PUSH(*(BEAR_SINGLE_UNITY_FILE)CTX->hbuf ++);
		(BEAR_SINGLE_UNITY_FILE)CTX->hlen --;
	} else {
		T0_PUSHi(-1);
	}

				}
				break;
			case 26: {
				/* set8 */

	size_t addr = T0_POP();
	unsigned x = T0_POP();
	*((unsigned char *)(BEAR_SINGLE_UNITY_FILE)CTX + addr) = x;

				}
				break;
			case 27: {
				/* swap */
 T0_SWAP(); 
				}
				break;
			case 28: {
				/* write8 */

	unsigned char x = (unsigned char)T0_POP();
	(BEAR_SINGLE_UNITY_FILE)CTX->buf[(BEAR_SINGLE_UNITY_FILE)CTX->ptr ++] = x;
	if ((BEAR_SINGLE_UNITY_FILE)CTX->ptr == sizeof (BEAR_SINGLE_UNITY_FILE)CTX->buf) {
		if ((BEAR_SINGLE_UNITY_FILE)CTX->dest) {
			(BEAR_SINGLE_UNITY_FILE)CTX->dest((BEAR_SINGLE_UNITY_FILE)CTX->dest_ctx, (BEAR_SINGLE_UNITY_FILE)CTX->buf, sizeof (BEAR_SINGLE_UNITY_FILE)CTX->buf);
		}
		(BEAR_SINGLE_UNITY_FILE)CTX->ptr = 0;
	}

				}
				break;
			}

		} else {
			(BEAR_SINGLE_UNITY_FILE)T0_ENTER(ip, rp, t0x);
		}
	}
t0_exit:
	((t0_context *)t0ctx)->dp = dp;
	((t0_context *)t0ctx)->rp = rp;
	((t0_context *)t0ctx)->ip = ip;
}
