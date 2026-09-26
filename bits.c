/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    //return ~((~(x&~y))&(~(~x&y)));
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if((!x)&&(!y))
        return 1;
    if(!x)
        return 0;
    if(!y)
        return 0;
    if((x>>31)^(y>>31))
        return 0;
    return 1;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r1,r2,r3,r4,r5;
    r1=((v>>16)>0)<<4;
    v=v>>r1;
    r2=((v>>8)>0)<<3;
    v=v>>r2;
    r3=((v>>4)>0)<<2;
    v=v>>r3;
    r4=((v>>2)>0)<<1;
    v=v>>r4;
    r5=((v>>1)>0);
    //v=v>>r5;
    return r1|r2|r3|r4|r5;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n3=n<<3,m3=m<<3;
    int d1=255<<n3,d2=255<<m3;
    int d3=~(d1|d2);
    int s1=d1&x,s2=d2&x;
    s1=(s1>>n3&255)<<m3;
    s2=(s2>>m3&255)<<n3;
    x=x&d3;
    x=x|s1;
    x=x|s2;
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned int ans=0;
    for(int i=0;i-32;i++)
    {
        unsigned int a;
        a=((v>>i)&1);
        ans=(ans<<1|a);
    }
    return ans;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int r=(x>>31)&1;
    r=r<<(n^31);
    x=x&0x7FFFFFFF;
    x=x>>n;
    x=x|r;
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int a=x;
    int r1,r2,r3,r4,r5;
    r1=(!(~(x>>16)))<<4;
    x=x<<r1;
    r2=(!(~(x>>24)))<<3;
    x=x<<r2;
    r3=(!(~(x>>28)))<<2;
    x=x<<r3;
    r4=(!(~(x>>30)))<<1;
    x=x<<r4;
    r5=(!(~(x>>31)));
    return (r1|r2|r3|r4|r5)+(!(~a));
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ux=x;
    unsigned sign=ux & 0x80000000;
    unsigned a;
    unsigned frac;
    unsigned low;
    int exp=158;
    if (sign)
        a = ~ux + 1;
    else
        a = ux;
    if (!a)
        return 0;
    while (!(a & 0x80000000)) 
    {
        a = a << 1;
        exp = exp - 1;
    }
    frac = (a >> 8) & 0x7FFFFF;
    low = a & 0xFF;
    if (low > 0x80)
        frac = frac + 1;
    if (low == 0x80)
        if (frac & 1)
            frac = frac + 1;
    if (frac & 0x800000)
    {
        exp = exp + 1;
        frac = 0;
    }
    return sign | (exp << 23) | frac;

}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned a = (uf >> 23) & 255;

    if (a == 255)
        return uf;
    if (!a)
        return (uf & 0x80000000) | ((uf & 0x7FFFFF) << 1);
    if (a == 254)
        return (uf & 0x80000000) | 0x7F800000;
    return uf + (1 << 23);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned a = uf2 >> 31;
    unsigned b = (uf2 >> 20) & 2047;
    unsigned c = 0x80000000 | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);
    int d;

    if (b < 1023)
        return 0;
    if (b >= 1054)
        return 0x80000000u;

    d = c >> (1054 - b);
    if (a)
        return -d;
    return d;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149)
        return 0;
    if (x < -126)
        return 1 << (x + 149);
    if (x > 127)
        return 0x7F800000;
    return (x + 127) << 23;
}
