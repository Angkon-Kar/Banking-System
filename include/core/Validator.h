#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
using namespace std;

// Central input validation. Every require*() returns the cleaned value or
// throws ValidationException, so services never trust raw user input.
class Validator {
public:
    static string trim(const string& text);
    static string toLower(const string& text);

    static string requireName(const string& value, const string& fieldName);
    static string requireUsername(const string& value);
    static string requirePin(const string& value);      // 4-8 digits
    static string requirePhone(const string& value);    // optional +, 7-15 digits
    static string requireEmail(const string& value);
    static string requireCardType(const string& value); // "Visa" or "Master"
};

#endif // VALIDATOR_H