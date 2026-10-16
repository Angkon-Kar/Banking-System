#include "core/PinHasher.h"
#include "core/Sha256.h"
#include <iomanip>
#include <random>
#include <sstream>
using namespace std;

namespace {
const int ROUNDS = 2000;
}

// Generate a random 32-character hexadecimal salt for PIN hashing
string PinHasher::generateSalt() {
    random_device source;
    ostringstream out;
    for (int i = 0; i < 4; ++i) out << hex << setw(8) << setfill('0') << source();
    return out.str();
}

// Hash the PIN with the given salt using multiple rounds of SHA-256
string PinHasher::hash(const string& salt, const string& pin) {
    string digest = Sha256::hashHex(salt + pin);
    for (int i = 0; i < ROUNDS; ++i) digest = Sha256::hashHex(digest + salt + pin);
    return digest;
}

// Verify that the provided PIN matches the expected hash when combined with the salt
bool PinHasher::verify(const string& salt, const string& pin, const string& expectedHash) {
    string actual = hash(salt, pin);
    if (actual.size() != expectedHash.size()) return false;
    unsigned char difference = 0; // constant-time compare
    for (size_t i = 0; i < actual.size(); ++i) {
        difference |= static_cast<unsigned char>(actual[i] ^ expectedHash[i]);
    }
    return difference == 0;
}