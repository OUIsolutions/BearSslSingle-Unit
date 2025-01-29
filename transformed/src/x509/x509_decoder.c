/* Automatically generated code; do not modify directly. */

#include <stddef.h>
#include <stdint.h>

typedef struct {
	uint32_t *dp;
	uint32_t *rp;
	const unsigned char *ip;
} t0_context;

static uint32_t
t0_parse7E_unsigned(const unsigned char **p)
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
t0_parse7E_signed(const unsigned char **p)
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

/* static const unsigned char t0_datablock[]; */


void br_x509_decoder_init_main(void *t0ctx);

void br_x509_decoder_run(void *t0ctx);











#define CTX   ((br_x509_decoder_context *)(void *)((unsigned char *)t0ctx - offsetof(br_x509_decoder_context, cpu)))
#define CONTEXT_NAME   br_x509_decoder_context

/* see bearssl_x509.h */
void
br_x509_decoder_init(br_x509_decoder_context *ctx,
	void (*append_dn)(void *ctx, const void *buf, size_t len),
	void *append_dn_ctx)
{
	memset(ctx, 0, sizeof *ctx);
	/* obsolete
	ctx->err = 0;
	ctx->hbuf = NULL;
	ctx->hlen = 0;
	*/
	ctx->append_dn = append_dn;
	ctx->append_dn_ctx = append_dn_ctx;
	ctx->cpu.dp = &ctx->dp_stack[0];
	ctx->cpu.rp = &ctx->rp_stack[0];
	br_x509_decoder_init_main(&ctx->cpu);
	br_x509_decoder_run(&ctx->cpu);
}

/* see bearssl_x509.h */
void
br_x509_decoder_push(br_x509_decoder_context *ctx,
	const void *data, size_t len)
{
	ctx->hbuf = data;
	ctx->hlen = len;
	br_x509_decoder_run(&ctx->cpu);
}



static const unsigned char t0_datablock[] = {
	0x00, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x09,
	0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05, 0x09, 0x2A, 0x86,
	0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x0E, 0x09, 0x2A, 0x86, 0x48, 0x86,
	0xF7, 0x0D, 0x01, 0x01, 0x0B, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D,
	0x01, 0x01, 0x0C, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01,
	0x0D, 0x07, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01, 0x08, 0x2A, 0x86,
	0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x05, 0x2B, 0x81, 0x04, 0x00, 0x22,
	0x05, 0x2B, 0x81, 0x04, 0x00, 0x23, 0x07, 0x2A, 0x86, 0x48, 0xCE, 0x3D,
	0x04, 0x01, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x01, 0x08,
	0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x08, 0x2A, 0x86, 0x48,
	0xCE, 0x3D, 0x04, 0x03, 0x03, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04,
	0x03, 0x04, 0x00, 0x1F, 0x03, 0xFC, 0x07, 0x7F, 0x0B, 0x5E, 0x0F, 0x1F,
	0x12, 0xFE, 0x16, 0xBF, 0x1A, 0x9F, 0x1E, 0x7E, 0x22, 0x3F, 0x26, 0x1E,
	0x29, 0xDF, 0x00, 0x1F, 0x03, 0xFD, 0x07, 0x9F, 0x0B, 0x7E, 0x0F, 0x3F,
	0x13, 0x1E, 0x16, 0xDF, 0x1A, 0xBF, 0x1E, 0x9E, 0x22, 0x5F, 0x26, 0x3E,
	0x29, 0xFF, 0x03, 0x55, 0x1D, 0x13
};

static const unsigned char t0_codeblock[] = {
	0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x01, 0x00, 0x11, 0x00, 0x00, 0x01,
	0x01, 0x09, 0x00, 0x00, 0x01, 0x01, 0x0A, 0x00, 0x00, 0x1A, 0x1A, 0x00,
	0x00, 0x01, T0_INT1(BR_ERR_X509_BAD_BOOLEAN), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_BAD_TAG_CLASS), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_BAD_TAG_VALUE), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_BAD_TIME), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_EXTRA_ELEMENT), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_INDEFINITE_LENGTH), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_INNER_TRUNC), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_LIMIT_EXCEEDED), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_NOT_CONSTRUCTED), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_NOT_PRIMITIVE), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_OVERFLOW), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_PARTIAL_BYTE), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_UNEXPECTED), 0x00, 0x00, 0x01,
	T0_INT1(BR_ERR_X509_UNSUPPORTED), 0x00, 0x00, 0x01,
	T0_INT1(BR_KEYTYPE_EC), 0x00, 0x00, 0x01, T0_INT1(BR_KEYTYPE_RSA),
	0x00, 0x00, 0x01, T0_INT2(offsetof(CONTEXT_NAME, copy_dn)), 0x00, 0x00,
	0x01, T0_INT2(offsetof(CONTEXT_NAME, decoded)), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(CONTEXT_NAME, isCA)), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(br_x509_decoder_context, pkey_data)), 0x01,
	T0_INT2(BR_X509_BUFSIZE_KEY), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(CONTEXT_NAME, notafter_days)), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(CONTEXT_NAME, notafter_seconds)), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(CONTEXT_NAME, notbefore_days)), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(CONTEXT_NAME, notbefore_seconds)), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(CONTEXT_NAME, pad)), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(CONTEXT_NAME, signer_hash_id)), 0x00, 0x00, 0x01,
	T0_INT2(offsetof(CONTEXT_NAME, signer_key_type)), 0x00, 0x00, 0x01,
	0x80, 0x45, 0x00, 0x00, 0x01, 0x80, 0x4E, 0x00, 0x00, 0x01, 0x80, 0x54,
	0x00, 0x00, 0x01, 0x81, 0x36, 0x00, 0x02, 0x03, 0x00, 0x03, 0x01, 0x1B,
	0x02, 0x01, 0x13, 0x26, 0x02, 0x00, 0x0F, 0x15, 0x00, 0x00, 0x05, 0x02,
	0x34, 0x1D, 0x00, 0x00, 0x06, 0x02, 0x35, 0x1D, 0x00, 0x00, 0x01, 0x10,
	0x4F, 0x00, 0x00, 0x11, 0x05, 0x02, 0x38, 0x1D, 0x4C, 0x00, 0x00, 0x11,
	0x05, 0x02, 0x38, 0x1D, 0x4D, 0x00, 0x00, 0x06, 0x02, 0x30, 0x1D, 0x00,
	0x00, 0x1B, 0x19, 0x01, 0x08, 0x0E, 0x26, 0x29, 0x19, 0x09, 0x00, 0x00,
	0x01, 0x30, 0x0A, 0x1B, 0x01, 0x00, 0x01, 0x09, 0x4B, 0x05, 0x02, 0x2F,
	0x1D, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x01, 0x80, 0x5A, 0x00, 0x00,
	0x01, 0x80, 0x62, 0x00, 0x00, 0x01, 0x80, 0x6B, 0x00, 0x00, 0x01, 0x80,
	0x74, 0x00, 0x00, 0x01, 0x80, 0x7D, 0x00, 0x00, 0x01, 0x3D, 0x00, 0x00,
	0x20, 0x11, 0x06, 0x04, 0x2B, 0x6B, 0x7A, 0x71, 0x00, 0x04, 0x01, 0x00,
	0x3D, 0x25, 0x01, 0x00, 0x3C, 0x25, 0x01, 0x87, 0xFF, 0xFF, 0x7F, 0x6D,
	0x6D, 0x70, 0x1B, 0x01, 0x20, 0x11, 0x06, 0x11, 0x1A, 0x4C, 0x6B, 0x70,
	0x01, 0x02, 0x50, 0x6E, 0x01, 0x02, 0x12, 0x06, 0x02, 0x39, 0x1D, 0x51,
	0x70, 0x01, 0x02, 0x50, 0x6C, 0x6D, 0x7A, 0x6D, 0x7A, 0x6D, 0x65, 0x43,
	0x24, 0x42, 0x24, 0x65, 0x41, 0x24, 0x40, 0x24, 0x51, 0x01, 0x01, 0x3C,
	0x25, 0x6D, 0x7A, 0x01, 0x00, 0x3C, 0x25, 0x6D, 0x6D, 0x60, 0x05, 0x02,
	0x39, 0x1D, 0x74, 0x1C, 0x06, 0x1C, 0x7A, 0x61, 0x6D, 0x3F, 0x68, 0x03,
	0x00, 0x3F, 0x26, 0x02, 0x00, 0x09, 0x26, 0x02, 0x00, 0x0A, 0x68, 0x03,
	0x01, 0x51, 0x51, 0x02, 0x00, 0x02, 0x01, 0x18, 0x04, 0x1E, 0x5A, 0x1C,
	0x06, 0x18, 0x64, 0x03, 0x02, 0x51, 0x61, 0x1B, 0x03, 0x03, 0x1B, 0x3F,
	0x23, 0x0D, 0x06, 0x02, 0x33, 0x1D, 0x62, 0x02, 0x02, 0x02, 0x03, 0x17,
	0x04, 0x02, 0x39, 0x1D, 0x51, 0x01, 0x00, 0x3E, 0x25, 0x71, 0x01, 0x21,
	0x5B, 0x01, 0x22, 0x5B, 0x1B, 0x01, 0x23, 0x11, 0x06, 0x28, 0x1A, 0x4C,
	0x6B, 0x6D, 0x1B, 0x06, 0x1D, 0x6D, 0x60, 0x1A, 0x70, 0x1B, 0x01, 0x01,
	0x11, 0x06, 0x03, 0x63, 0x1A, 0x70, 0x01, 0x04, 0x50, 0x6B, 0x4A, 0x1C,
	0x06, 0x03, 0x5F, 0x04, 0x01, 0x7B, 0x51, 0x51, 0x04, 0x60, 0x51, 0x51,
	0x04, 0x08, 0x01, 0x7F, 0x11, 0x05, 0x02, 0x38, 0x1D, 0x1A, 0x51, 0x6D,
	0x60, 0x06, 0x80, 0x63, 0x75, 0x1C, 0x06, 0x06, 0x01, 0x02, 0x3B, 0x04,
	0x80, 0x57, 0x76, 0x1C, 0x06, 0x06, 0x01, 0x03, 0x3B, 0x04, 0x80, 0x4D,
	0x77, 0x1C, 0x06, 0x06, 0x01, 0x04, 0x3B, 0x04, 0x80, 0x43, 0x78, 0x1C,
	0x06, 0x05, 0x01, 0x05, 0x3B, 0x04, 0x3A, 0x79, 0x1C, 0x06, 0x05, 0x01,
	0x06, 0x3B, 0x04, 0x31, 0x55, 0x1C, 0x06, 0x05, 0x01, 0x02, 0x3A, 0x04,
	0x28, 0x56, 0x1C, 0x06, 0x05, 0x01, 0x03, 0x3A, 0x04, 0x1F, 0x57, 0x1C,
	0x06, 0x05, 0x01, 0x04, 0x3A, 0x04, 0x16, 0x58, 0x1C, 0x06, 0x05, 0x01,
	0x05, 0x3A, 0x04, 0x0D, 0x59, 0x1C, 0x06, 0x05, 0x01, 0x06, 0x3A, 0x04,
	0x04, 0x01, 0x00, 0x01, 0x00, 0x04, 0x04, 0x01, 0x00, 0x01, 0x00, 0x46,
	0x25, 0x45, 0x25, 0x7A, 0x61, 0x7A, 0x51, 0x1A, 0x01, 0x01, 0x3D, 0x25,
	0x73, 0x30, 0x1D, 0x00, 0x00, 0x01, 0x81, 0x06, 0x00, 0x01, 0x54, 0x0D,
	0x06, 0x02, 0x32, 0x1D, 0x1B, 0x03, 0x00, 0x0A, 0x02, 0x00, 0x00, 0x00,
	0x6D, 0x71, 0x1B, 0x01, 0x01, 0x11, 0x06, 0x08, 0x63, 0x01, 0x01, 0x15,
	0x3E, 0x25, 0x04, 0x01, 0x2B, 0x7A, 0x00, 0x00, 0x70, 0x01, 0x06, 0x50,
	0x6F, 0x00, 0x00, 0x70, 0x01, 0x03, 0x50, 0x6B, 0x72, 0x06, 0x02, 0x37,
	0x1D, 0x00, 0x00, 0x26, 0x1B, 0x06, 0x07, 0x21, 0x1B, 0x06, 0x01, 0x16,
	0x04, 0x76, 0x2B, 0x00, 0x00, 0x01, 0x01, 0x50, 0x6A, 0x01, 0x01, 0x10,
	0x06, 0x02, 0x2C, 0x1D, 0x72, 0x27, 0x00, 0x00, 0x60, 0x05, 0x02, 0x39,
	0x1D, 0x47, 0x1C, 0x06, 0x04, 0x01, 0x17, 0x04, 0x12, 0x48, 0x1C, 0x06,
	0x04, 0x01, 0x18, 0x04, 0x0A, 0x49, 0x1C, 0x06, 0x04, 0x01, 0x19, 0x04,
	0x02, 0x39, 0x1D, 0x00, 0x04, 0x70, 0x1B, 0x01, 0x17, 0x01, 0x18, 0x4B,
	0x05, 0x02, 0x2F, 0x1D, 0x01, 0x18, 0x11, 0x03, 0x00, 0x4D, 0x6B, 0x66,
	0x02, 0x00, 0x06, 0x0C, 0x01, 0x80, 0x64, 0x08, 0x03, 0x01, 0x66, 0x02,
	0x01, 0x09, 0x04, 0x0E, 0x1B, 0x01, 0x32, 0x0D, 0x06, 0x04, 0x01, 0x80,
	0x64, 0x09, 0x01, 0x8E, 0x6C, 0x09, 0x03, 0x01, 0x02, 0x01, 0x01, 0x82,
	0x6D, 0x08, 0x02, 0x01, 0x01, 0x03, 0x09, 0x01, 0x04, 0x0C, 0x09, 0x02,
	0x01, 0x01, 0x80, 0x63, 0x09, 0x01, 0x80, 0x64, 0x0C, 0x0A, 0x02, 0x01,
	0x01, 0x83, 0x0F, 0x09, 0x01, 0x83, 0x10, 0x0C, 0x09, 0x03, 0x03, 0x01,
	0x01, 0x01, 0x0C, 0x67, 0x2A, 0x01, 0x01, 0x0E, 0x02, 0x01, 0x01, 0x04,
	0x07, 0x28, 0x02, 0x01, 0x01, 0x80, 0x64, 0x07, 0x27, 0x02, 0x01, 0x01,
	0x83, 0x10, 0x07, 0x28, 0x1F, 0x15, 0x06, 0x03, 0x01, 0x18, 0x09, 0x5D,
	0x09, 0x52, 0x1B, 0x01, 0x05, 0x14, 0x02, 0x03, 0x09, 0x03, 0x03, 0x01,
	0x1F, 0x15, 0x01, 0x01, 0x26, 0x67, 0x02, 0x03, 0x09, 0x2A, 0x03, 0x03,
	0x01, 0x00, 0x01, 0x17, 0x67, 0x01, 0x9C, 0x10, 0x08, 0x03, 0x02, 0x01,
	0x00, 0x01, 0x3B, 0x67, 0x01, 0x3C, 0x08, 0x02, 0x02, 0x09, 0x03, 0x02,
	0x01, 0x00, 0x01, 0x3C, 0x67, 0x02, 0x02, 0x09, 0x03, 0x02, 0x72, 0x1B,
	0x01, 0x2E, 0x11, 0x06, 0x0D, 0x1A, 0x72, 0x1B, 0x01, 0x30, 0x01, 0x39,
	0x4B, 0x06, 0x03, 0x1A, 0x04, 0x74, 0x01, 0x80, 0x5A, 0x10, 0x06, 0x02,
	0x2F, 0x1D, 0x51, 0x02, 0x03, 0x02, 0x02, 0x00, 0x01, 0x72, 0x53, 0x01,
	0x0A, 0x08, 0x03, 0x00, 0x72, 0x53, 0x02, 0x00, 0x09, 0x00, 0x02, 0x03,
	0x00, 0x03, 0x01, 0x66, 0x1B, 0x02, 0x01, 0x02, 0x00, 0x4B, 0x05, 0x02,
	0x2F, 0x1D, 0x00, 0x00, 0x23, 0x70, 0x01, 0x02, 0x50, 0x0B, 0x69, 0x00,
	0x03, 0x1B, 0x03, 0x00, 0x03, 0x01, 0x03, 0x02, 0x6B, 0x72, 0x1B, 0x01,
	0x81, 0x00, 0x13, 0x06, 0x02, 0x36, 0x1D, 0x1B, 0x01, 0x00, 0x11, 0x06,
	0x0B, 0x1A, 0x1B, 0x05, 0x04, 0x1A, 0x01, 0x00, 0x00, 0x72, 0x04, 0x6F,
	0x02, 0x01, 0x1B, 0x05, 0x02, 0x33, 0x1D, 0x2A, 0x03, 0x01, 0x02, 0x02,
	0x25, 0x02, 0x02, 0x29, 0x03, 0x02, 0x1B, 0x06, 0x03, 0x72, 0x04, 0x68,
	0x1A, 0x02, 0x00, 0x02, 0x01, 0x0A, 0x00, 0x01, 0x72, 0x1B, 0x01, 0x81,
	0x00, 0x0D, 0x06, 0x01, 0x00, 0x01, 0x81, 0x00, 0x0A, 0x1B, 0x05, 0x02,
	0x31, 0x1D, 0x03, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0x12, 0x06,
	0x19, 0x02, 0x00, 0x2A, 0x03, 0x00, 0x1B, 0x01, 0x83, 0xFF, 0xFF, 0x7F,
	0x12, 0x06, 0x02, 0x32, 0x1D, 0x01, 0x08, 0x0E, 0x26, 0x72, 0x23, 0x09,
	0x04, 0x60, 0x00, 0x00, 0x6A, 0x5E, 0x00, 0x00, 0x6B, 0x7A, 0x00, 0x00,
	0x70, 0x4E, 0x6B, 0x00, 0x01, 0x6B, 0x1B, 0x05, 0x02, 0x36, 0x1D, 0x72,
	0x1B, 0x01, 0x81, 0x00, 0x13, 0x06, 0x02, 0x36, 0x1D, 0x03, 0x00, 0x1B,
	0x06, 0x16, 0x72, 0x02, 0x00, 0x1B, 0x01, 0x87, 0xFF, 0xFF, 0x7F, 0x13,
	0x06, 0x02, 0x36, 0x1D, 0x01, 0x08, 0x0E, 0x09, 0x03, 0x00, 0x04, 0x67,
	0x1A, 0x02, 0x00, 0x00, 0x00, 0x6B, 0x1B, 0x01, 0x81, 0x7F, 0x12, 0x06,
	0x08, 0x7A, 0x01, 0x00, 0x44, 0x25, 0x01, 0x00, 0x00, 0x1B, 0x44, 0x25,
	0x44, 0x29, 0x62, 0x01, 0x7F, 0x00, 0x01, 0x72, 0x03, 0x00, 0x02, 0x00,
	0x01, 0x05, 0x14, 0x01, 0x01, 0x15, 0x1E, 0x02, 0x00, 0x01, 0x06, 0x14,
	0x1B, 0x01, 0x01, 0x15, 0x06, 0x02, 0x2D, 0x1D, 0x01, 0x04, 0x0E, 0x02,
	0x00, 0x01, 0x1F, 0x15, 0x1B, 0x01, 0x1F, 0x11, 0x06, 0x02, 0x2E, 0x1D,
	0x09, 0x00, 0x00, 0x1B, 0x05, 0x05, 0x01, 0x00, 0x01, 0x7F, 0x00, 0x70,
	0x00, 0x00, 0x1B, 0x05, 0x02, 0x32, 0x1D, 0x2A, 0x73, 0x00, 0x00, 0x22,
	0x1B, 0x01, 0x00, 0x13, 0x06, 0x01, 0x00, 0x1A, 0x16, 0x04, 0x74, 0x00,
	0x01, 0x01, 0x00, 0x00, 0x01, 0x0B, 0x00, 0x00, 0x01, 0x15, 0x00, 0x00,
	0x01, 0x1F, 0x00, 0x00, 0x01, 0x29, 0x00, 0x00, 0x01, 0x33, 0x00, 0x00,
	0x7B, 0x1A, 0x00, 0x00, 0x1B, 0x06, 0x07, 0x7C, 0x1B, 0x06, 0x01, 0x16,
	0x04, 0x76, 0x00, 0x00, 0x01, 0x00, 0x20, 0x21, 0x0B, 0x2B, 0x00
};

static const uint16_t t0_caddr[] = {
	0,
	5,
	10,
	15,
	20,
	24,
	28,
	32,
	36,
	40,
	44,
	48,
	52,
	56,
	60,
	64,
	68,
	72,
	76,
	80,
	84,
	88,
	93,
	98,
	103,
	111,
	116,
	121,
	126,
	131,
	136,
	141,
	146,
	151,
	156,
	161,
	166,
	181,
	187,
	193,
	198,
	206,
	214,
	220,
	231,
	246,
	250,
	255,
	260,
	265,
	270,
	275,
	279,
	289,
	620,
	625,
	639,
	659,
	666,
	678,
	692,
	707,
	740,
	960,
	974,
	991,
	1000,
	1067,
	1123,
	1127,
	1131,
	1136,
	1184,
	1210,
	1254,
	1265,
	1274,
	1287,
	1291,
	1295,
	1299,
	1303,
	1307,
	1311,
	1315,
	1327
};

#define X509_DECODER_T0_INTERPRETED   39

#define X509_DECODER_T0_ENTER(ip, rp, slot)   do { \
		const unsigned char *t0_newip; \
		uint32_t t0_lnum; \
		t0_newip = &t0_codeblock[t0_caddr[(slot) - X509_DECODER_T0_INTERPRETED]]; \
		t0_lnum = t0_parse7E_unsigned(&t0_newip); \
		(rp) += t0_lnum; \
		*((rp) ++) = (uint32_t)((ip) - &t0_codeblock[0]) + (t0_lnum << 16); \
		(ip) = t0_newip; \
	} while (0)

#define X509_DECODER_T0_DEFENTRY(name, slot) \
void \
name(void *ctx) \
{ \
	t0_context *t0ctx = ctx; \
	t0ctx->ip = &t0_codeblock[0]; \
	X509_DECODER_T0_ENTER(t0ctx->ip, t0ctx->rp, slot); \
}

X509_DECODER_T0_DEFENTRY(br_x509_decoder_init_main, 92)

#define T0_NEXT(t0ipp)   (*(*(t0ipp)) ++)

void
br_x509_decoder_run(void *t0ctx)
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
		if (t0x < X509_DECODER_T0_INTERPRETED) {
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
				ip = &t0_codeblock[t0x];
				break;
			case 1: /* literal constant */
				T0_PUSHi(t0_parse7E_signed(&ip));
				break;
			case 2: /* read local */
				T0_PUSH(T0_LOCAL(t0_parse7E_unsigned(&ip)));
				break;
			case 3: /* write local */
				T0_LOCAL(t0_parse7E_unsigned(&ip)) = T0_POP();
				break;
			case 4: /* jump */
				t0off = t0_parse7E_signed(&ip);
				ip += t0off;
				break;
			case 5: /* jump if */
				t0off = t0_parse7E_signed(&ip);
				if (T0_POP()) {
					ip += t0off;
				}
				break;
			case 6: /* jump if not */
				t0off = t0_parse7E_signed(&ip);
				if (!T0_POP()) {
					ip += t0off;
				}
				break;
			case 7: {
				/* %25 */

	int32_t b = T0_POPi();
	int32_t a = T0_POPi();
	T0_PUSHi(a % b);

				}
				break;
			case 8: {
				/* * */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(a * b);

				}
				break;
			case 9: {
				/* + */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(a + b);

				}
				break;
			case 10: {
				/* - */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(a - b);

				}
				break;
			case 11: {
				/* -rot */
 T0_NROT(); 
				}
				break;
			case 12: {
				/* / */

	int32_t b = T0_POPi();
	int32_t a = T0_POPi();
	T0_PUSHi(a / b);

				}
				break;
			case 13: {
				/* < */

	int32_t b = T0_POPi();
	int32_t a = T0_POPi();
	T0_PUSH(-(uint32_t)(a < b));

				}
				break;
			case 14: {
				/* << */

	int c = (int)T0_POPi();
	uint32_t x = T0_POP();
	T0_PUSH(x << c);

				}
				break;
			case 15: {
				/* <= */

	int32_t b = T0_POPi();
	int32_t a = T0_POPi();
	T0_PUSH(-(uint32_t)(a <= b));

				}
				break;
			case 16: {
				/* <> */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(-(uint32_t)(a != b));

				}
				break;
			case 17: {
				/* = */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(-(uint32_t)(a == b));

				}
				break;
			case 18: {
				/* > */

	int32_t b = T0_POPi();
	int32_t a = T0_POPi();
	T0_PUSH(-(uint32_t)(a > b));

				}
				break;
			case 19: {
				/* >= */

	int32_t b = T0_POPi();
	int32_t a = T0_POPi();
	T0_PUSH(-(uint32_t)(a >= b));

				}
				break;
			case 20: {
				/* >> */

	int c = (int)T0_POPi();
	int32_t x = T0_POPi();
	T0_PUSHi(x >> c);

				}
				break;
			case 21: {
				/* and */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(a & b);

				}
				break;
			case 22: {
				/* co */
 T0_CO(); 
				}
				break;
			case 23: {
				/* copy-ec-pkey */

	size_t qlen = T0_POP();
	uint32_t curve = T0_POP();
	CTX->pkey.key_type = BR_KEYTYPE_EC;
	CTX->pkey.key.ec.curve = curve;
	CTX->pkey.key.ec.q = CTX->pkey_data;
	CTX->pkey.key.ec.qlen = qlen;

				}
				break;
			case 24: {
				/* copy-rsa-pkey */

	size_t elen = T0_POP();
	size_t nlen = T0_POP();
	CTX->pkey.key_type = BR_KEYTYPE_RSA;
	CTX->pkey.key.rsa.n = CTX->pkey_data;
	CTX->pkey.key.rsa.nlen = nlen;
	CTX->pkey.key.rsa.e = CTX->pkey_data + nlen;
	CTX->pkey.key.rsa.elen = elen;

				}
				break;
			case 25: {
				/* data-get8 */

	size_t addr = T0_POP();
	T0_PUSH(t0_datablock[addr]);

				}
				break;
			case 26: {
				/* drop */
 (void)T0_POP(); 
				}
				break;
			case 27: {
				/* dup */
 T0_PUSH(T0_PEEK(0)); 
				}
				break;
			case 28: {
				/* eqOID */

	const unsigned char *a2 = &t0_datablock[T0_POP()];
	const unsigned char *a1 = &CTX->pad[0];
	size_t len = a1[0];
	int x;
	if (len == a2[0]) {
		x = -(memcmp(a1 + 1, a2 + 1, len) == 0);
	} else {
		x = 0;
	}
	T0_PUSH((uint32_t)x);

				}
				break;
			case 29: {
				/* fail */

	CTX->err = T0_POPi();
	T0_CO();

				}
				break;
			case 30: {
				/* neg */

	uint32_t a = T0_POP();
	T0_PUSH(-a);

				}
				break;
			case 31: {
				/* or */

	uint32_t b = T0_POP();
	uint32_t a = T0_POP();
	T0_PUSH(a | b);

				}
				break;
			case 32: {
				/* over */
 T0_PUSH(T0_PEEK(1)); 
				}
				break;
			case 33: {
				/* read-blob-inner */

	uint32_t len = T0_POP();
	uint32_t addr = T0_POP();
	size_t clen = CTX->hlen;
	if (clen > len) {
		clen = (size_t)len;
	}
	if (addr != 0) {
		memcpy((unsigned char *)CTX + addr, CTX->hbuf, clen);
	}
	if (CTX->copy_dn && CTX->append_dn) {
		CTX->append_dn(CTX->append_dn_ctx, CTX->hbuf, clen);
	}
	CTX->hbuf += clen;
	CTX->hlen -= clen;
	T0_PUSH(addr + clen);
	T0_PUSH(len - clen);

				}
				break;
			case 34: {
				/* read8-low */

	if (CTX->hlen == 0) {
		T0_PUSHi(-1);
	} else {
		unsigned char x = *CTX->hbuf ++;
		if (CTX->copy_dn && CTX->append_dn) {
			CTX->append_dn(CTX->append_dn_ctx, &x, 1);
		}
		CTX->hlen --;
		T0_PUSH(x);
	}

				}
				break;
			case 35: {
				/* rot */
 T0_ROT(); 
				}
				break;
			case 36: {
				/* set32 */

	uint32_t addr = T0_POP();
	*(uint32_t *)(void *)((unsigned char *)CTX + addr) = T0_POP();

				}
				break;
			case 37: {
				/* set8 */

	uint32_t addr = T0_POP();
	*((unsigned char *)CTX + addr) = (unsigned char)T0_POP();

				}
				break;
			case 38: {
				/* swap */
 T0_SWAP(); 
				}
				break;
			}

		} else {
			X509_DECODER_T0_ENTER(ip, rp, t0x);
		}
	}
t0_exit:
	((t0_context *)t0ctx)->dp = dp;
	((t0_context *)t0ctx)->rp = rp;
	((t0_context *)t0ctx)->ip = ip;
}
