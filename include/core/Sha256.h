#ifndef SHA256_H
#define SHA256_H

#include <string>
using namespace std;

// Small dependency-free SHA-256 (FIPS 180-4). Used only through PinHasher.
class Sha256 {
public:
    static string hashHex(const string& input);
};

#endif // SHA256_H