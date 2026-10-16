#ifndef ROLE_H
#define ROLE_H

#include <string>
#include "core/Exceptions.h"
using namespace std;

// Enum for user roles in the banking system
enum class Role { Admin, Customer };

// Convert Role enum to string for display or storage
inline string roleToString(Role role) {
    return role == Role::Admin ? "Admin" : "Customer";
}

// Convert string to Role enum, throwing an exception for invalid input
inline Role roleFromString(const string& text) {
    if (text == "Admin") return Role::Admin;
    if (text == "Customer") return Role::Customer;
    throw FileIOException("Unknown role in data file: " + text);
}

#endif // ROLE_H