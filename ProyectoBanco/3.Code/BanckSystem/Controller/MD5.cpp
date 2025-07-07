#include "MD5.h"
#include <cstring>
#include <sstream>
#include <iomanip>

static constexpr unsigned int S11 = 7;
static constexpr unsigned int S12 = 12;
static constexpr unsigned int S13 = 17;
static constexpr unsigned int S14 = 22;
static constexpr unsigned int S21 = 5;
static constexpr unsigned int S22 = 9;
static constexpr unsigned int S23 = 14;
static constexpr unsigned int S24 = 20;
static constexpr unsigned int S31 = 4;
static constexpr unsigned int S32 = 11;
static constexpr unsigned int S33 = 16;
static constexpr unsigned int S34 = 23;
static constexpr unsigned int S41 = 6;
static constexpr unsigned int S42 = 10;
static constexpr unsigned int S43 = 15;
static constexpr unsigned int S44 = 21;

inline unsigned int F(unsigned int x, unsigned int y, unsigned int z) {
    return (x & y) | (~x & z);
}

inline unsigned int G(unsigned int x, unsigned int y, unsigned int z) {
    return (x & z) | (y & ~z);
}

inline unsigned int H(unsigned int x, unsigned int y, unsigned int z) {
    return x ^ y ^ z;
}

inline unsigned int I(unsigned int x, unsigned int y, unsigned int z) {
    return y ^ (x | ~z);
}

inline unsigned int rotate_left(unsigned int x, unsigned int n) {
    return (x << n) | (x >> (32 - n));
}

inline void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d,
               unsigned int x, unsigned int s, unsigned int ac) {
    a += F(b, c, d) + x + ac;
    a = rotate_left(a, s);
    a += b;
}

inline void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d,
               unsigned int x, unsigned int s, unsigned int ac) {
    a += G(b, c, d) + x + ac;
    a = rotate_left(a, s);
    a += b;
}

inline void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d,
               unsigned int x, unsigned int s, unsigned int ac) {
    a += H(b, c, d) + x + ac;
    a = rotate_left(a, s);
    a += b;
}

inline void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d,
               unsigned int x, unsigned int s, unsigned int ac) {
    a += I(b, c, d) + x + ac;
    a = rotate_left(a, s);
    a += b;
}

MD5::MD5() : finalized(false) {
    count[0] = count[1] = 0;

    // Load magic initialization constants.
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
}

void MD5::update(const unsigned char* input, size_t length) {
    size_t index = (count[0] >> 3) & 0x3F;
    if ((count[0] += static_cast<unsigned int>(length << 3)) < (length << 3)) {
        count[1]++;
    }
    count[1] += static_cast<unsigned int>(length >> 29);

    size_t firstpart = 64 - index;
    size_t i = 0;

    if (length >= firstpart) {
        memcpy(&buffer[index], input, firstpart);
        transform(buffer);

        for (i = firstpart; i + 63 < length; i += 64)
            transform(&input[i]);

        index = 0;
    }

    memcpy(&buffer[index], &input[i], length - i);
}

void MD5::update(const std::string& str) {
    update(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());
}

void MD5::transform(const unsigned char block[64]) {
    unsigned int a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    decode(x, block, 64);

    // Round 1
    FF(a, b, c, d, x[ 0], S11, 0xd76aa478);
    FF(d, a, b, c, x[ 1], S12, 0xe8c7b756);
    FF(c, d, a, b, x[ 2], S13, 0x242070db);
    FF(b, c, d, a, x[ 3], S14, 0xc1bdceee);
    FF(a, b, c, d, x[ 4], S11, 0xf57c0faf);
    FF(d, a, b, c, x[ 5], S12, 0x4787c62a);
    FF(c, d, a, b, x[ 6], S13, 0xa8304613);
    FF(b, c, d, a, x[ 7], S14, 0xfd469501);
    FF(a, b, c, d, x[ 8], S11, 0x698098d8);
    FF(d, a, b, c, x[ 9], S12, 0x8b44f7af);
    FF(c, d, a, b, x[10], S13, 0xffff5bb1);
    FF(b, c, d, a, x[11], S14, 0x895cd7be);
    FF(a, b, c, d, x[12], S11, 0x6b901122);
    FF(d, a, b, c, x[13], S12, 0xfd987193);
    FF(c, d, a, b, x[14], S13, 0xa679438e);
    FF(b, c, d, a, x[15], S14, 0x49b40821);

    // Round 2
    GG(a, b, c, d, x[ 1], S21, 0xf61e2562);
    GG(d, a, b, c, x[ 6], S22, 0xc040b340);
    GG(c, d, a, b, x[11], S23, 0x265e5a51);
    GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa);
    GG(a, b, c, d, x[ 5], S21, 0xd62f105d);
    GG(d, a, b, c, x[10], S22,  0x2441453);
    GG(c, d, a, b, x[15], S23, 0xd8a1e681);
    GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8);
    GG(a, b, c, d, x[ 9], S21, 0x21e1cde6);
    GG(d, a, b, c, x[14], S22, 0xc33707d6);
    GG(c, d, a, b, x[ 3], S23, 0xf4d50d87);
    GG(b, c, d, a, x[ 8], S24, 0x455a14ed);
    GG(a, b, c, d, x[13], S21, 0xa9e3e905);
    GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8);
    GG(c, d, a, b, x[ 7], S23, 0x676f02d9);
    GG(b, c, d, a, x[12], S24, 0x8d2a4c8a);

    // Round 3
    HH(a, b, c, d, x[ 5], S31, 0xfffa3942);
    HH(d, a, b, c, x[ 8], S32, 0x8771f681);
    HH(c, d, a, b, x[11], S33, 0x6d9d6122);
    HH(b, c, d, a, x[14], S34, 0xfde5380c);
    HH(a, b, c, d, x[ 1], S31, 0xa4beea44);
    HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9);
    HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60);
    HH(b, c, d, a, x[10], S34, 0xbebfbc70);
    HH(a, b, c, d, x[13], S31, 0x289b7ec6);
    HH(d, a, b, c, x[ 0], S32, 0xeaa127fa);
    HH(c, d, a, b, x[ 3], S33, 0xd4ef3085);
    HH(b, c, d, a, x[ 6], S34,  0x4881d05);
    HH(a, b, c, d, x[ 9], S31, 0xd9d4d039);
    HH(d, a, b, c, x[12], S32, 0xe6db99e5);
    HH(c, d, a, b, x[15], S33, 0x1fa27cf8);
    HH(b, c, d, a, x[ 2], S34, 0xc4ac5665);

    // Round 4
    II(a, b, c, d, x[ 0], S41, 0xf4292244);
    II(d, a, b, c, x[ 7], S42, 0x432aff97);
    II(c, d, a, b, x[14], S43, 0xab9423a7);
    II(b, c, d, a, x[ 5], S44, 0xfc93a039);
    II(a, b, c, d, x[12], S41, 0x655b59c3);
    II(d, a, b, c, x[ 3], S42, 0x8f0ccc92);
    II(c, d, a, b, x[10], S43, 0xffeff47d);
    II(b, c, d, a, x[ 1], S44, 0x85845dd1);
    II(a, b, c, d, x[ 8], S41, 0x6fa87e4f);
    II(d, a, b, c, x[15], S42, 0xfe2ce6e0);
    II(c, d, a, b, x[ 6], S43, 0xa3014314);
    II(b, c, d, a, x[13], S44, 0x4e0811a1);
    II(a, b, c, d, x[ 4], S41, 0xf7537e82);
    II(d, a, b, c, x[11], S42, 0xbd3af235);
    II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb);
    II(b, c, d, a, x[ 9], S44, 0xeb86d391);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

void MD5::encode(unsigned char* output, const unsigned int* input, size_t len) {
    for (size_t i = 0, j = 0; j < len; i++, j += 4) {
        output[j] = static_cast<unsigned char>(input[i] & 0xff);
        output[j + 1] = static_cast<unsigned char>((input[i] >> 8) & 0xff);
        output[j + 2] = static_cast<unsigned char>((input[i] >> 16) & 0xff);
        output[j + 3] = static_cast<unsigned char>((input[i] >> 24) & 0xff);
    }
}

void MD5::decode(unsigned int* output, const unsigned char* input, size_t len) {
    for (size_t i = 0, j = 0; j < len; i++, j += 4) {
        output[i] = static_cast<unsigned int>(input[j]) |
                    (static_cast<unsigned int>(input[j + 1]) << 8) |
                    (static_cast<unsigned int>(input[j + 2]) << 16) |
                    (static_cast<unsigned int>(input[j + 3]) << 24);
    }
}

std::string MD5::final() {
    if (finalized)
        return "";

    unsigned char bits[8];
    encode(bits, count, 8);

    size_t index = (count[0] >> 3) & 0x3F;
    size_t padLen = (index < 56) ? (56 - index) : (120 - index);
    static unsigned char PADDING[64] = { 0x80 };

    update(PADDING, padLen);
    update(bits, 8);

    encode(digest, state, 16);

    finalized = true;

    std::ostringstream oss;
    for (int i = 0; i < 16; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    return oss.str();
}

std::string MD5::md5(const std::string& str) {
    MD5 md5;
    md5.update(str);
    return md5.final();
}
