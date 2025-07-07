#ifndef MD5_H
#define MD5_H

#include <string>

class MD5 {
public:
    MD5();
    void update(const unsigned char* input, size_t length);
    void update(const std::string& str);
    std::string final();
    static std::string md5(const std::string& str);

private:
    void transform(const unsigned char block[64]);
    void encode(unsigned char* output, const unsigned int* input, size_t len);
    void decode(unsigned int* output, const unsigned char* input, size_t len);

    unsigned int state[4];
    unsigned int count[2];
    unsigned char buffer[64];
    unsigned char digest[16];
    bool finalized;
};

#endif
