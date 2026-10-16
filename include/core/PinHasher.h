#ifndef PINHASHER_H
#define PINHASHER_H

#include <string>
using namespace std;

// Salted, iterated SHA-256 for PINs. Good enough to show the right idea in a
// learning project; a production system would use bcrypt / scrypt / Argon2.
class PinHasher {
public:
    static string generateSalt();
    static string hash(const string& salt, const string& pin);
    static bool verify(const string& salt, const string& pin, const string& expectedHash);
};

#endif // PINHASHER_H