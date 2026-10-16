#include "core/Validator.h"
#include "core/Exceptions.h"
#include <cctype>
using namespace std;

// Central input validation. Every require*() returns the cleaned value or
// throws ValidationException, so services never trust raw user input.
string Validator::trim(const string& text) {
    size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

// Convert all letters to lowercase for case-insensitive comparisons
string Validator::toLower(const string& text) {
    string result = text;
    for (char& c : result) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return result;
}

// Validate a name (first, last, etc.) with basic rules: non-empty, max length, allowed characters
string Validator::requireName(const string& value, const string& fieldName) {
    string v = trim(value);
    if (v.empty()) throw ValidationException(fieldName + " cannot be empty.");
    if (v.size() > 40) throw ValidationException(fieldName + " is too long (max 40 characters).");
    for (char c : v) {
        unsigned char u = static_cast<unsigned char>(c);
        bool ok = isalpha(u) || u >= 128 || c == ' ' || c == '.' || c == '-' || c == '\'';
        if (!ok) throw ValidationException(fieldName + " contains invalid characters.");
    }
    return v;
}

// Validate a username: 3-20 characters, letters, digits, underscores, and dots only
string Validator::requireUsername(const string& value) {
    string v = trim(value);
    if (v.size() < 3 || v.size() > 20)
        throw ValidationException("Username must be 3-20 characters long.");
    for (char c : v) {
        bool ok = isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '.';
        if (!ok) throw ValidationException("Username may only contain letters, digits, '_' and '.'.");
    }
    return v;
}

// Validate a PIN: 4-8 digits only
string Validator::requirePin(const string& value) {
    if (value.size() < 4 || value.size() > 8)
        throw ValidationException("PIN must be 4-8 digits.");
    for (char c : value) {
        if (!isdigit(static_cast<unsigned char>(c))) throw ValidationException("PIN must contain digits only.");
    }
    return value;
}

// Validate a phone number: optional leading '+', followed by 7-15 digits
string Validator::requirePhone(const string& value) {
    string v = trim(value);
    size_t start = (!v.empty() && v[0] == '+') ? 1 : 0;
    size_t digits = v.size() - start;
    if (digits < 7 || digits > 15) throw ValidationException("Phone must have 7-15 digits (optional leading +).");
    for (size_t i = start; i < v.size(); ++i) {
        if (!isdigit(static_cast<unsigned char>(v[i]))) throw ValidationException("Phone must contain digits only.");
    }
    return v;
}

// Validate an email address with basic rules: non-empty, max length, one '@', valid domain
string Validator::requireEmail(const string& value) {
    string v = trim(value);
    if (v.empty() || v.size() > 60) throw ValidationException("Email must be 1-60 characters.");
    if (v.find(' ') != string::npos) throw ValidationException("Email cannot contain spaces.");
    size_t at = v.find('@');
    if (at == string::npos || at == 0 || v.find('@', at + 1) != string::npos)
        throw ValidationException("Email must contain exactly one '@' with text before it.");
    size_t dot = v.find('.', at + 1);
    if (dot == string::npos || dot == at + 1 || dot + 1 >= v.size())
        throw ValidationException("Email domain looks invalid (example: name@mail.com).");
    return v;
}

// Validate a card type: must be "Visa" or "Master" (case-insensitive)
string Validator::requireCardType(const string& value) {
    string v = toLower(trim(value));
    if (v == "visa") return "Visa";
    if (v == "master" || v == "mastercard") return "Master";
    throw ValidationException("Card type must be Visa or Master.");
}