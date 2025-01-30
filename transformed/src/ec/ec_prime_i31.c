/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */



/*
 * Parameters for supported curves (field modulus, and 'b' equation
 * parameter; both values use the 'i31' format, and 'b' is in Montgomery
 * representation).
 */

static const uint32_t BEAR_SINGLE_UNITY_FILEP256_P[] = {
	0x00000108,
	0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x00000007,
	0x00000000, 0x00000000, 0x00000040, 0x7FFFFF80,
	0x000000FF
};

static const uint32_t BEAR_SINGLE_UNITY_FILEP256_R2[] = {
	0x00000108,
	0x00014000, 0x00018000, 0x00000000, 0x7FF40000,
	0x7FEFFFFF, 0x7FF7FFFF, 0x7FAFFFFF, 0x005FFFFF,
	0x00000000
};

static const uint32_t BEAR_SINGLE_UNITY_FILEP256_B[] = {
	0x00000108,
	0x6FEE1803, 0x6229C4BD, 0x21B139BE, 0x327150AA,
	0x3567802E, 0x3F7212ED, 0x012E4355, 0x782DD38D,
	0x0000000E
};

static const uint32_t BEAR_SINGLE_UNITY_FILEP384_P[] = {
	0x0000018C,
	0x7FFFFFFF, 0x00000001, 0x00000000, 0x7FFFFFF8,
	0x7FFFFFEF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,
	0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,
	0x00000FFF
};

static const uint32_t BEAR_SINGLE_UNITY_FILEP384_R2[] = {
	0x0000018C,
	0x00000000, 0x00000080, 0x7FFFFE00, 0x000001FF,
	0x00000800, 0x00000000, 0x7FFFE000, 0x00001FFF,
	0x00008000, 0x00008000, 0x00000000, 0x00000000,
	0x00000000
};

static const uint32_t BEAR_SINGLE_UNITY_FILEP384_B[] = {
	0x0000018C,
	0x6E666840, 0x070D0392, 0x5D810231, 0x7651D50C,
	0x17E218D6, 0x1B192002, 0x44EFE441, 0x3A524E2B,
	0x2719BA5F, 0x41F02209, 0x36C5643E, 0x5813EFFE,
	0x000008A5
};

static const uint32_t BEAR_SINGLE_UNITY_FILEP521_P[] = {
	0x00000219,
	0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,
	0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,
	0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,
	0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,
	0x01FFFFFF
};

static const uint32_t BEAR_SINGLE_UNITY_FILEP521_R2[] = {
	0x00000219,
	0x00001000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000
};

static const uint32_t BEAR_SINGLE_UNITY_FILEP521_B[] = {
	0x00000219,
	0x540FC00A, 0x228FEA35, 0x2C34F1EF, 0x67BF107A,
	0x46FC1CD5, 0x1605E9DD, 0x6937B165, 0x272A3D8F,
	0x42785586, 0x44C8C778, 0x15F3B8B4, 0x64B73366,
	0x03BA8B69, 0x0D05B42A, 0x21F929A2, 0x2C31C393,
	0x00654FAE
};

typedef struct {
	const uint32_t *p;
	const uint32_t *b;
	const uint32_t *R2;
	uint32_t p0i;
	size_t point_len;
} BEAR_SINGLE_UNITY_FILEcurve_params;

static inline const BEAR_SINGLE_UNITY_FILEcurve_params *
BEAR_SINGLE_UNITY_FILEid_to_curve(int curve)
{
	static const BEAR_SINGLE_UNITY_FILEcurve_params pp[] = {
		{ BEAR_SINGLE_UNITY_FILEP256_P, BEAR_SINGLE_UNITY_FILEP256_B, BEAR_SINGLE_UNITY_FILEP256_R2, 0x00000001,  65 },
		{ BEAR_SINGLE_UNITY_FILEP384_P, BEAR_SINGLE_UNITY_FILEP384_B, BEAR_SINGLE_UNITY_FILEP384_R2, 0x00000001,  97 },
		{ BEAR_SINGLE_UNITY_FILEP521_P, BEAR_SINGLE_UNITY_FILEP521_B, BEAR_SINGLE_UNITY_FILEP521_R2, 0x00000001, 133 }
	};

	return &pp[curve - BR_EC_secp256r1];
}

#define I31_LEN   ((BR_MAX_EC_SIZE + 61) / 31)

/*
 * Type for a point in Jacobian coordinates:
 * -- three values, x, y and z, in Montgomery representation
 * -- affine coordinates are X = x / z^2 and Y = y / z^3
 * -- for the point at infinity, z = 0
 */
typedef struct {
	uint32_t c[3][I31_LEN];
} BEAR_SINGLE_UNITY_FILEjacobian;

/*
 * We use a custom interpreter that uses a dozen registers, and
 * only six operations:
 *    MSET(d, a)       copy a into d
 *    MADD(d, a)       d = d+a (modular)
 *    MSUB(d, a)       d = d-a (modular)
 *    BEAR_SINGLE_UNITY_FILEMMUL(d, a, b)    d = a*b (Montgomery multiplication)
 *    MINV(d, a, b)    invert d modulo p; a and b are used as scratch registers
 *    MTZ(d)           clear return value if d = 0
 * Destination of BEAR_SINGLE_UNITY_FILEMMUL (d) must be distinct from operands (a and b).
 * There is no such constraint for MSUB and MADD.
 *
 * Registers include the operand coordinates, and temporaries.
 */
#define MSET(d, a)      (0x0000 + ((d) << 8) + ((a) << 4))
#define MADD(d, a)      (0x1000 + ((d) << 8) + ((a) << 4))
#define MSUB(d, a)      (0x2000 + ((d) << 8) + ((a) << 4))
#define BEAR_SINGLE_UNITY_FILEMMUL(d, a, b)   (0x3000 + ((d) << 8) + ((a) << 4) + (b))
#define MINV(d, a, b)   (0x4000 + ((d) << 8) + ((a) << 4) + (b))
#define MTZ(d)          (0x5000 + ((d) << 8))
#define ENDCODE         0

/*
 * Registers for the input operands.
 */
#define BEAR_SINGLE_UNITY_FILEP1x    0
#define BEAR_SINGLE_UNITY_FILEP1y    1
#define BEAR_SINGLE_UNITY_FILEP1z    2
#define BEAR_SINGLE_UNITY_FILEP2x    3
#define BEAR_SINGLE_UNITY_FILEP2y    4
#define BEAR_SINGLE_UNITY_FILEP2z    5

/*
 * Alternate names for the first input operand.
 */
#define BEAR_SINGLE_UNITY_FILEPx     0
#define BEAR_SINGLE_UNITY_FILEPy     1
#define BEAR_SINGLE_UNITY_FILEPz     2

/*
 * Temporaries.
 */
#define BEAR_SINGLE_UNITY_FILEt1     6
#define BEAR_SINGLE_UNITY_FILEt2     7
#define BEAR_SINGLE_UNITY_FILEt3     8
#define BEAR_SINGLE_UNITY_FILEt4     9
#define BEAR_SINGLE_UNITY_FILEt5    10
#define BEAR_SINGLE_UNITY_FILEt6    11
#define BEAR_SINGLE_UNITY_FILEt7    12

/*
 * Extra scratch registers available when there is no second operand (e.g.
 * for "double" and "affine").
 */
#define BEAR_SINGLE_UNITY_FILEt8     3
#define BEAR_SINGLE_UNITY_FILEt9     4
#define BEAR_SINGLE_UNITY_FILEt10    5

/*
 * Doubling formulas are:
 *
 *   s = 4*x*y^2
 *   m = 3*(x + z^2)*(x - z^2)
 *   x' = m^2 - 2*s
 *   y' = m*(s - x') - 8*y^4
 *   z' = 2*y*z
 *
 * If y = 0 (P has order 2) then this yields infinity (z' = 0), as it
 * should. This case should not happen anyway, because our curves have
 * prime order, and thus do not contain any point of order 2.
 *
 * If P is infinity (z = 0), then again the formulas yield infinity,
 * which is correct. Thus, this code works for all points.
 *
 * Cost: 8 multiplications
 */
static const uint16_t BEAR_SINGLE_UNITY_FILEcode_double[] = {
	/*
	 * Compute z^2 (in t1).
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEPz, BEAR_SINGLE_UNITY_FILEPz),

	/*
	 * Compute x-z^2 (in t2) and then x+z^2 (in t1).
	 */
	MSET(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEPx),
	MSUB(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEt1),
	MADD(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEPx),

	/*
	 * Compute m = 3*(x+z^2)*(x-z^2) (in t1).
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt3, BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEt2),
	MSET(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEt3),
	MADD(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEt3),
	MADD(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEt3),

	/*
	 * Compute s = 4*x*y^2 (in t2) and 2*y^2 (in t3).
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(	BEAR_SINGLE_UNITY_FILEt3, 	BEAR_SINGLE_UNITY_FILEPy, 	BEAR_SINGLE_UNITY_FILEPy),
	MADD(	BEAR_SINGLE_UNITY_FILEt3, 	BEAR_SINGLE_UNITY_FILEt3),
	BEAR_SINGLE_UNITY_FILEMMUL(	BEAR_SINGLE_UNITY_FILEt2, 	BEAR_SINGLE_UNITY_FILEPx, 	BEAR_SINGLE_UNITY_FILEt3),
	MADD(	BEAR_SINGLE_UNITY_FILEt2, 	BEAR_SINGLE_UNITY_FILEt2),

	/*
	 * Compute x' = m^2 - 2*s.
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(	BEAR_SINGLE_UNITY_FILEPx, 	BEAR_SINGLE_UNITY_FILEt1, 	BEAR_SINGLE_UNITY_FILEt1),
	MSUB(	BEAR_SINGLE_UNITY_FILEPx, 	BEAR_SINGLE_UNITY_FILEt2),
	MSUB(	BEAR_SINGLE_UNITY_FILEPx, 	BEAR_SINGLE_UNITY_FILEt2),

	/*
	 * Compute z' = 2*y*z.
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(	BEAR_SINGLE_UNITY_FILEt4, 	BEAR_SINGLE_UNITY_FILEPy, 	BEAR_SINGLE_UNITY_FILEPz),
	MSET(	BEAR_SINGLE_UNITY_FILEPz, 	BEAR_SINGLE_UNITY_FILEt4),
	MADD(	BEAR_SINGLE_UNITY_FILEPz, 	BEAR_SINGLE_UNITY_FILEt4),

	/*
	 * Compute y' = m*(s - x') - 8*y^4. Note that we already have
	 * 2*y^2 in t3.
	 */
	MSUB(	BEAR_SINGLE_UNITY_FILEt2, 	BEAR_SINGLE_UNITY_FILEPx),
	BEAR_SINGLE_UNITY_FILEMMUL(	BEAR_SINGLE_UNITY_FILEPy, 	BEAR_SINGLE_UNITY_FILEt1, 	BEAR_SINGLE_UNITY_FILEt2),
	BEAR_SINGLE_UNITY_FILEMMUL(	BEAR_SINGLE_UNITY_FILEt4, 	BEAR_SINGLE_UNITY_FILEt3, 	BEAR_SINGLE_UNITY_FILEt3),
	MSUB(	BEAR_SINGLE_UNITY_FILEPy, 	BEAR_SINGLE_UNITY_FILEt4),
	MSUB(	BEAR_SINGLE_UNITY_FILEPy, 	BEAR_SINGLE_UNITY_FILEt4),

	ENDCODE
};

/*
 * Addtions formulas are:
 *
 *   u1 = x1 * z2^2
 *   u2 = x2 * z1^2
 *   s1 = y1 * z2^3
 *   s2 = y2 * z1^3
 *   h = u2 - u1
 *   r = s2 - s1
 *   x3 = r^2 - h^3 - 2 * u1 * h^2
 *   y3 = r * (u1 * h^2 - x3) - s1 * h^3
 *   z3 = h * z1 * z2
 *
 * If both P1 and P2 are infinity, then z1 == 0 and z2 == 0, implying that
 * z3 == 0, so the result is correct.
 * If either of P1 or P2 is infinity, but not both, then z3 == 0, which is
 * not correct.
 * h == 0 only if u1 == u2; this happens in two cases:
 * -- if s1 == s2 then P1 and/or P2 is infinity, or P1 == P2
 * -- if s1 != s2 then P1 + P2 == infinity (but neither P1 or P2 is infinity)
 *
 * Thus, the following situations are not handled correctly:
 * -- P1 = 0 and P2 != 0
 * -- P1 != 0 and P2 = 0
 * -- P1 = P2
 * All other cases are properly computed. However, even in "incorrect"
 * situations, the three coordinates still are properly formed field
 * elements.
 *
 * The returned flag is cleared if r == 0. This happens in the following
 * cases:
 * -- Both points are on the same horizontal line (same Y coordinate).
 * -- Both points are infinity.
 * -- One point is infinity and the other is on line Y = 0.
 * The third case cannot happen with our curves (there is no valid point
 * on line Y = 0 since that would be a point of order 2). If the two
 * source points are non-infinity, then remains only the case where the
 * two points are on the same horizontal line.
 *
 * This allows us to detect the "P1 == P2" case, assuming that P1 != 0 and
 * P2 != 0:
 * -- If the returned value is not the point at infinity, then it was properly
 * computed.
 * -- Otherwise, if the returned flag is 1, then P1+P2 = 0, and the result
 * is indeed the point at infinity.
 * -- Otherwise (result is infinity, flag is 0), then P1 = P2 and we should
 * use the 'double' code.
 *
 * Cost: 16 multiplications
 */
static const uint16_t BEAR_SINGLE_UNITY_FILEcode_add[] = {
	/*
	 * Compute u1 = x1*z2^2 (in t1) and s1 = y1*z2^3 (in t3).
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt3, BEAR_SINGLE_UNITY_FILEP2z, BEAR_SINGLE_UNITY_FILEP2z),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEt3),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt4, BEAR_SINGLE_UNITY_FILEP2z, BEAR_SINGLE_UNITY_FILEt3),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt3, BEAR_SINGLE_UNITY_FILEP1y, BEAR_SINGLE_UNITY_FILEt4),

	/*
	 * Compute u2 = x2*z1^2 (in t2) and s2 = y2*z1^3 (in t4).
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt4, BEAR_SINGLE_UNITY_FILEP1z, BEAR_SINGLE_UNITY_FILEP1z),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEP2x, BEAR_SINGLE_UNITY_FILEt4),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt5, BEAR_SINGLE_UNITY_FILEP1z, BEAR_SINGLE_UNITY_FILEt4),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt4, BEAR_SINGLE_UNITY_FILEP2y, BEAR_SINGLE_UNITY_FILEt5),

	/*
	 * Compute h = u2 - u1 (in t2) and r = s2 - s1 (in t4).
	 */
	MSUB(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEt1),
	MSUB(BEAR_SINGLE_UNITY_FILEt4, BEAR_SINGLE_UNITY_FILEt3),

	/*
	 * Report cases where r = 0 through the returned flag.
	 */
	MTZ(BEAR_SINGLE_UNITY_FILEt4),

	/*
	 * Compute u1*h^2 (in t6) and h^3 (in t5).
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt7, BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEt2),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt6, BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEt7),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt5, BEAR_SINGLE_UNITY_FILEt7, BEAR_SINGLE_UNITY_FILEt2),

	/*
	 * Compute x3 = r^2 - h^3 - 2*u1*h^2.
	 * t1 and t7 can be used as scratch registers.
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEt4, BEAR_SINGLE_UNITY_FILEt4),
	MSUB(BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEt5),
	MSUB(BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEt6),
	MSUB(BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEt6),

	/*
	 * Compute y3 = r*(u1*h^2 - x3) - s1*h^3.
	 */
	MSUB(BEAR_SINGLE_UNITY_FILEt6, BEAR_SINGLE_UNITY_FILEP1x),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEP1y, BEAR_SINGLE_UNITY_FILEt4, BEAR_SINGLE_UNITY_FILEt6),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEt5, BEAR_SINGLE_UNITY_FILEt3),
	MSUB(BEAR_SINGLE_UNITY_FILEP1y, BEAR_SINGLE_UNITY_FILEt1),

	/*
	 * Compute z3 = h*z1*z2.
	 */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEP1z, BEAR_SINGLE_UNITY_FILEP2z),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEP1z, BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEt2),

	ENDCODE
};

/*
 * Check that the point is on the curve. This code snippet assumes the
 * following conventions:
 * -- Coordinates x and y have been freshly decoded in P1 (but not
 * converted to Montgomery coordinates yet).
 * -- P2x, P2y and P2z are set to, respectively, R^2, b*R and 1.
 */
static const uint16_t BEAR_SINGLE_UNITY_FILEcode_check[] = {

	/* Convert x and y to Montgomery representation. */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEP2x),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEP1y, BEAR_SINGLE_UNITY_FILEP2x),
	MSET(BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEt1),
	MSET(BEAR_SINGLE_UNITY_FILEP1y, BEAR_SINGLE_UNITY_FILEt2),

	/* Compute x^3 in t1. */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEP1x),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEt2),

	/* Subtract 3*x from t1. */
	MSUB(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEP1x),
	MSUB(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEP1x),
	MSUB(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEP1x),

	/* Add b. */
	MADD(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEP2y),

	/* Compute y^2 in t2. */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEP1y, BEAR_SINGLE_UNITY_FILEP1y),

	/* Compare y^2 with x^3 - 3*x + b; they must match. */
	MSUB(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEt2),
	MTZ(BEAR_SINGLE_UNITY_FILEt1),

	/* Set z to 1 (in Montgomery representation). */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEP1z, BEAR_SINGLE_UNITY_FILEP2x, BEAR_SINGLE_UNITY_FILEP2z),

	ENDCODE
};

/*
 * Conversion back to affine coordinates. This code snippet assumes that
 * the z coordinate of P2 is set to 1 (not in Montgomery representation).
 */
static const uint16_t BEAR_SINGLE_UNITY_FILEcode_affine[] = {

	/* Save z*R in t1. */
	MSET(BEAR_SINGLE_UNITY_FILEt1, BEAR_SINGLE_UNITY_FILEP1z),

	/* Compute z^3 in t2. */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEP1z, BEAR_SINGLE_UNITY_FILEP1z),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt3, BEAR_SINGLE_UNITY_FILEP1z, BEAR_SINGLE_UNITY_FILEt2),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEt3, BEAR_SINGLE_UNITY_FILEP2z),

	/* Invert to (1/z^3) in t2. */
	MINV(BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEt3, BEAR_SINGLE_UNITY_FILEt4),

	/* Compute y. */
	MSET(BEAR_SINGLE_UNITY_FILEt3, BEAR_SINGLE_UNITY_FILEP1y),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEP1y, BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEt3),

	/* Compute (1/z^2) in t3. */
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEt3, BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEt1),

	/* Compute x. */
	MSET(	BEAR_SINGLE_UNITY_FILEt2, 	BEAR_SINGLE_UNITY_FILEP1x),
	BEAR_SINGLE_UNITY_FILEMMUL(BEAR_SINGLE_UNITY_FILEP1x, BEAR_SINGLE_UNITY_FILEt2, BEAR_SINGLE_UNITY_FILEt3),

	ENDCODE
};

static uint32_t
BEAR_SINGLE_UNITY_FILErun_code(BEAR_SINGLE_UNITY_FILEjacobian *P1, const BEAR_SINGLE_UNITY_FILEjacobian *P2,
	const BEAR_SINGLE_UNITY_FILEcurve_params *cc, const uint16_t *code)
{
	uint32_t r;
	uint32_t t[13][I31_LEN];
	size_t u;

	r = 1;

	/*
	 * Copy the two operands in the dedicated registers.
	 */
	memcpy(t[BEAR_SINGLE_UNITY_FILEP1x], P1->c, 3 * I31_LEN * sizeof(uint32_t));
	memcpy(t[BEAR_SINGLE_UNITY_FILEP2x], P2->c, 3 * I31_LEN * sizeof(uint32_t));

	/*
	 * Run formulas.
	 */
	for (u = 0;; u ++) {
		unsigned op, d, a, b;

		op = code[u];
		if (op == 0) {
			break;
		}
		d = (op >> 8) & 0x0F;
		a = (op >> 4) & 0x0F;
		b = op & 0x0F;
		op >>= 12;
		switch (op) {
			uint32_t ctl;
			size_t plen;
			unsigned char tp[(BR_MAX_EC_SIZE + 7) >> 3];

		case 0:
			memcpy(t[d], t[a], I31_LEN * sizeof(uint32_t));
			break;
		case 1:
			ctl = br_i31_add(t[d], t[a], 1);
			ctl |= NOT(br_i31_sub(t[d], cc->p, 0));
			br_i31_sub(t[d], cc->p, ctl);
			break;
		case 2:
			br_i31_add(t[d], cc->p, br_i31_sub(t[d], t[a], 1));
			break;
		case 3:
			br_i31_montymul(t[d], t[a], t[b], cc->p, cc->p0i);
			break;
		case 4:
			plen = (cc->p[0] - (cc->p[0] >> 5) + 7) >> 3;
			br_i31_encode(tp, plen, cc->p);
			tp[plen - 1] -= 2;
			br_i31_modpow(t[d], tp, plen,
				cc->p, cc->p0i, t[a], t[b]);
			break;
		default:
			r &= ~br_i31_iszero(t[d]);
			break;
		}
	}

	/*
	 * Copy back result.
	 */
	memcpy(P1->c, t[BEAR_SINGLE_UNITY_FILEP1x], 3 * I31_LEN * sizeof(uint32_t));
	return r;
}

static void
BEAR_SINGLE_UNITY_FILEset_one(uint32_t *x, const uint32_t *p)
{
	size_t plen;

	plen = (p[0] + 63) >> 5;
	memset(x, 0, plen * sizeof *x);
	x[0] = p[0];
	x[1] = 0x00000001;
}

static void
BEAR_SINGLE_UNITY_FILEpoint_zero(BEAR_SINGLE_UNITY_FILEjacobian *P, const BEAR_SINGLE_UNITY_FILEcurve_params *cc)
{
	memset(P, 0, sizeof *P);
	P->c[0][0] = P->c[1][0] = P->c[2][0] = cc->p[0];
}

static inline void
BEAR_SINGLE_UNITY_FILEpoint_double(BEAR_SINGLE_UNITY_FILEjacobian *P, const BEAR_SINGLE_UNITY_FILEcurve_params *cc)
{
	BEAR_SINGLE_UNITY_FILErun_code(P, P, cc, BEAR_SINGLE_UNITY_FILEcode_double);
}

static inline uint32_t
BEAR_SINGLE_UNITY_FILEpoint_add(BEAR_SINGLE_UNITY_FILEjacobian *P1, const BEAR_SINGLE_UNITY_FILEjacobian *P2, const BEAR_SINGLE_UNITY_FILEcurve_params *cc)
{
	return BEAR_SINGLE_UNITY_FILErun_code(P1, P2, cc, BEAR_SINGLE_UNITY_FILEcode_add);
}

static void
BEAR_SINGLE_UNITY_FILEpoint_mul(BEAR_SINGLE_UNITY_FILEjacobian *P, const unsigned char *x, size_t xlen,
	const BEAR_SINGLE_UNITY_FILEcurve_params *cc)
{
	/*
	 * We do a simple double-and-add ladder with a 2-bit window
	 * to make only one add every two doublings. We thus first
	 * precompute 2P and 3P in some local buffers.
	 *
	 * We always perform two doublings and one addition; the
	 * addition is with P, 2P and 3P and is done in a temporary
	 * array.
	 *
	 * The addition code cannot handle cases where one of the
	 * operands is infinity, which is the case at the start of the
	 * ladder. We therefore need to maintain a flag that controls
	 * this situation.
	 */
	uint32_t qz;
	BEAR_SINGLE_UNITY_FILEjacobian P2, P3, Q, T, U;

	memcpy(&P2, P, sizeof P2);
	BEAR_SINGLE_UNITY_FILEpoint_double(&P2, cc);
	memcpy(&P3, P, sizeof P3);
	BEAR_SINGLE_UNITY_FILEpoint_add(&P3, &P2, cc);

	BEAR_SINGLE_UNITY_FILEpoint_zero(&Q, cc);
	qz = 1;
	while (xlen -- > 0) {
		int k;

		for (k = 6; k >= 0; k -= 2) {
			uint32_t bits;
			uint32_t bnz;

			BEAR_SINGLE_UNITY_FILEpoint_double(&Q, cc);
			BEAR_SINGLE_UNITY_FILEpoint_double(&Q, cc);
			memcpy(&T, P, sizeof T);
			memcpy(&U, &Q, sizeof U);
			bits = (*x >> k) & (uint32_t)3;
			bnz = NEQ(bits, 0);
			CCOPY(EQ(bits, 2), &T, &P2, sizeof T);
			CCOPY(EQ(bits, 3), &T, &P3, sizeof T);
			BEAR_SINGLE_UNITY_FILEpoint_add(&U, &T, cc);
			CCOPY(bnz & qz, &Q, &T, sizeof Q);
			CCOPY(bnz & ~qz, &Q, &U, sizeof Q);
			qz &= ~bnz;
		}
		x ++;
	}
	memcpy(P, &Q, sizeof Q);
}

/*
 * Decode point into Jacobian coordinates. This function does not support
 * the point at infinity. If the point is invalid then this returns 0, but
 * the coordinates are still set to properly formed field elements.
 */
static uint32_t
BEAR_SINGLE_UNITY_FILEpoint_decode(BEAR_SINGLE_UNITY_FILEjacobian *P, const void *src, size_t len, const BEAR_SINGLE_UNITY_FILEcurve_params *cc)
{
	/*
	 * Points must use uncompressed format:
	 * -- first byte is 0x04;
	 * -- coordinates X and Y use unsigned big-endian, with the same
	 *    length as the field modulus.
	 *
	 * We don't support hybrid format (uncompressed, but first byte
	 * has value 0x06 or 0x07, depending on the least significant bit
	 * of Y) because it is rather useless, and explicitly forbidden
	 * by PKIX (RFC 5480, section 2.2).
	 *
	 * We don't support compressed format either, because it is not
	 * much used in practice (there are or were patent-related
	 * concerns about point compression, which explains the lack of
	 * generalised support). Also, point compression support would
	 * need a bit more code.
	 */
	const unsigned char *buf;
	size_t plen, zlen;
	uint32_t r;
	BEAR_SINGLE_UNITY_FILEjacobian Q;

	buf = (const unsigned char*)src;
	BEAR_SINGLE_UNITY_FILEpoint_zero(P, cc);
	plen = (cc->p[0] - (cc->p[0] >> 5) + 7) >> 3;
	if (len != 1 + (plen << 1)) {
		return 0;
	}
	r = br_i31_decode_mod(P->c[0], buf + 1, plen, cc->p);
	r &= br_i31_decode_mod(P->c[1], buf + 1 + plen, plen, cc->p);

	/*
	 * Check first byte.
	 */
	r &= EQ(buf[0], 0x04);
	/* obsolete
	r &= EQ(buf[0], 0x04) | (EQ(buf[0] & 0xFE, 0x06)
		& ~(uint32_t)(buf[0] ^ buf[plen << 1]));
	*/

	/*
	 * Convert coordinates and check that the point is valid.
	 */
	zlen = ((cc->p[0] + 63) >> 5) * sizeof(uint32_t);
	memcpy(Q.c[0], cc->R2, zlen);
	memcpy(Q.c[1], cc->b, zlen);
	BEAR_SINGLE_UNITY_FILEset_one(Q.c[2], cc->p);
	r &= ~BEAR_SINGLE_UNITY_FILErun_code(P, &Q, cc, BEAR_SINGLE_UNITY_FILEcode_check);
	return r;
}

/*
 * Encode a point. This method assumes that the point is correct and is
 * not the point at infinity. Encoded size is always 1+2*plen, where
 * plen is the field modulus length, in bytes.
 */
static void
BEAR_SINGLE_UNITY_FILEpoint_encode(void *dst, const BEAR_SINGLE_UNITY_FILEjacobian *P, const BEAR_SINGLE_UNITY_FILEcurve_params *cc)
{
	unsigned char *buf;
	uint32_t xbl;
	size_t plen;
	BEAR_SINGLE_UNITY_FILEjacobian Q, T;

	buf = (unsigned char*)dst;
	xbl = cc->p[0];
	xbl -= (xbl >> 5);
	plen = (xbl + 7) >> 3;
	buf[0] = 0x04;
	memcpy(&Q, P, sizeof *P);
	BEAR_SINGLE_UNITY_FILEset_one(T.c[2], cc->p);
	BEAR_SINGLE_UNITY_FILErun_code(&Q, &T, cc, BEAR_SINGLE_UNITY_FILEcode_affine);
	br_i31_encode(buf + 1, plen, Q.c[0]);
	br_i31_encode(buf + 1 + plen, plen, Q.c[1]);
}

static const br_ec_curve_def *
BEAR_SINGLE_UNITY_FILEid_to_curve_def(int curve)
{
	switch (curve) {
	case BR_EC_secp256r1:
		return &br_secp256r1;
	case BR_EC_secp384r1:
		return &br_secp384r1;
	case BR_EC_secp521r1:
		return &br_secp521r1;
	}
	return NULL;
}

static const unsigned char *
BEAR_SINGLE_UNITY_FILEapi_generator(int curve, size_t *len)
{
	const br_ec_curve_def *cd;

	cd = BEAR_SINGLE_UNITY_FILEid_to_curve_def(curve);
	*len = cd->generator_len;
	return cd->generator;
}

static const unsigned char *
BEAR_SINGLE_UNITY_FILEapi_order(int curve, size_t *len)
{
	const br_ec_curve_def *cd;

	cd = BEAR_SINGLE_UNITY_FILEid_to_curve_def(curve);
	*len = cd->order_len;
	return cd->order;
}

static size_t
BEAR_SINGLE_UNITY_FILEapi_xoff(int curve, size_t *len)
{
	BEAR_SINGLE_UNITY_FILEapi_generator(curve, len);
	*len >>= 1;
	return 1;
}

static uint32_t
BEAR_SINGLE_UNITY_FILEapi_mul(unsigned char *G, size_t Glen,
	const unsigned char *x, size_t xlen, int curve)
{
	uint32_t r;
	const BEAR_SINGLE_UNITY_FILEcurve_params *cc;
	BEAR_SINGLE_UNITY_FILEjacobian P;

	cc = BEAR_SINGLE_UNITY_FILEid_to_curve(curve);
	if (Glen != cc->point_len) {
		return 0;
	}
	r = BEAR_SINGLE_UNITY_FILEpoint_decode(&P, G, Glen, cc);
	BEAR_SINGLE_UNITY_FILEpoint_mul(&P, x, xlen, cc);
	BEAR_SINGLE_UNITY_FILEpoint_encode(G, &P, cc);
	return r;
}

static size_t
BEAR_SINGLE_UNITY_FILEapi_mulgen(unsigned char *R,
	const unsigned char *x, size_t xlen, int curve)
{
	const unsigned char *G;
	size_t Glen;

	G = BEAR_SINGLE_UNITY_FILEapi_generator(curve, &Glen);
	memcpy(R, G, Glen);
	BEAR_SINGLE_UNITY_FILEapi_mul(R, Glen, x, xlen, curve);
	return Glen;
}

static uint32_t
BEAR_SINGLE_UNITY_FILEapi_muladd(unsigned char *A, const unsigned char *B, size_t len,
	const unsigned char *x, size_t xlen,
	const unsigned char *y, size_t ylen, int curve)
{
	uint32_t r, t, z;
	const BEAR_SINGLE_UNITY_FILEcurve_params *cc;
	BEAR_SINGLE_UNITY_FILEjacobian P, Q;

	/*
	 * TODO: see about merging the two ladders. Right now, we do
	 * two independent point multiplications, which is a bit
	 * wasteful of CPU resources (but yields short code).
	 */

	cc = BEAR_SINGLE_UNITY_FILEid_to_curve(curve);
	if (len != cc->point_len) {
		return 0;
	}
	r = BEAR_SINGLE_UNITY_FILEpoint_decode(&P, A, len, cc);
	if (B == NULL) {
		size_t Glen;

		B = BEAR_SINGLE_UNITY_FILEapi_generator(curve, &Glen);
	}
	r &= BEAR_SINGLE_UNITY_FILEpoint_decode(&Q, B, len, cc);
	BEAR_SINGLE_UNITY_FILEpoint_mul(&P, x, xlen, cc);
	BEAR_SINGLE_UNITY_FILEpoint_mul(&Q, y, ylen, cc);

	/*
	 * We want to compute P+Q. Since the base points A and B are distinct
	 * from infinity, and the multipliers are non-zero and lower than the
	 * curve order, then we know that P and Q are non-infinity. This
	 * leaves two special situations to test for:
	 * -- If P = Q then we must use BEAR_SINGLE_UNITY_FILEpoint_double().
	 * -- If P+Q = 0 then we must report an error.
	 */
	t = BEAR_SINGLE_UNITY_FILEpoint_add(&P, &Q, cc);
	BEAR_SINGLE_UNITY_FILEpoint_double(&Q, cc);
	z = br_i31_iszero(P.c[2]);

	/*
	 * If z is 1 then either P+Q = 0 (t = 1) or P = Q (t = 0). So we
	 * have the following:
	 *
	 *   z = 0, t = 0   return P (normal addition)
	 *   z = 0, t = 1   return P (normal addition)
	 *   z = 1, t = 0   return Q (a 'double' case)
	 *   z = 1, t = 1   report an error (P+Q = 0)
	 */
	CCOPY(z & ~t, &P, &Q, sizeof Q);
	BEAR_SINGLE_UNITY_FILEpoint_encode(A, &P, cc);
	r &= ~(z & t);

	return r;
}

/* see bearssl_ec.h */
const br_ec_impl br_ec_prime_i31 = {
	(uint32_t)0x03800000,
	&BEAR_SINGLE_UNITY_FILEapi_generator,
	&BEAR_SINGLE_UNITY_FILEapi_order,
	&BEAR_SINGLE_UNITY_FILEapi_xoff,
	&BEAR_SINGLE_UNITY_FILEapi_mul,
	&BEAR_SINGLE_UNITY_FILEapi_mulgen,
	&BEAR_SINGLE_UNITY_FILEapi_muladd
};
