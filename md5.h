#include "stdint.h"
#include "string.h"

#define MD5_BLOCK_LENGTH    64
#define MD5_DIGEST_LENGTH   16
#define bufpos(ctx) ((ctx)->nbytes & (MD5_BLOCK_LENGTH - 1))

#define F(X,Y,Z) ((X & Y) | ((~X) & Z))
#define G(X,Y,Z) ((X & Z) | (Y & (~Z)))
#define H(X,Y,Z) (X ^ Y ^ Z)
#define I(X,Y,Z) (Y ^ (X | (~Z)))

#define OP(fn, a, b, c, d, k, s, T_i) \
    a = b + md5_rol(a + fn(b, c, d) + X[k] + T_i, s)

//md5 structure
struct md5_ctx {
    uint64_t nbytes;
    uint32_t a, b, c, d;
    uint32_t buf[16];
};

//function declaration
void md5_reset(struct md5_ctx *ctx);
void md5_update(struct md5_ctx *ctx, const void *data, unsigned int len);
void md5_final(uint8_t *dst, struct md5_ctx *ctx);
static void md5_mix(struct md5_ctx *ctx, const uint32_t *X);


//static function
static inline uint32_t md5_rol(uint32_t v, int s) { return (v << s) | (v >> (32 - s)); }

static inline void put_word(uint8_t *dst, uint32_t val)
{
    memcpy(dst, &val, 4);
}

static void hash2hex(const uint8_t *hash, char *dst)
{
    int i;
    static const char hextbl [] = "0123456789abcdef";
    for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
        *dst++ = hextbl[hash[i] >> 4];
        *dst++ = hextbl[hash[i] & 15];
    }
    *dst = 0;
}

