#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
using namespace std;

// Base exception for the whole banking system
class BankException : public exception {
protected:
    string message;
public:
    explicit BankException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Specific exceptions for various error scenarios
class InsufficientFundException : public BankException {
public:
    explicit InsufficientFundException(const string& msg = "Insufficient balance for this operation.")
        : BankException(msg) {}
};

// Exception for invalid amount (e.g., negative or zero)
class InvalidAmountException : public BankException {
public:
    explicit InvalidAmountException(const string& msg = "Amount must be greater than zero.")
        : BankException(msg) {}
};

// Exception for invalid interest rate (e.g., negative)
class AccountNotFoundException : public BankException {
public:
    explicit AccountNotFoundException(const string& msg = "Account not found.")
        : BankException(msg) {}
};

// Exception for invalid interest rate (e.g., negative)
class LoanNotFoundException : public BankException {
public:
    explicit LoanNotFoundException(const string& msg = "Loan not found.")
        : BankException(msg) {}
};

// Exception for invalid interest rate (e.g., negative)
class InvestmentNotFoundException : public BankException {
public:
    explicit InvestmentNotFoundException(const string& msg = "Investment not found.")
        : BankException(msg) {}
};

// Exception for invalid interest rate (e.g., negative)
class UserNotFoundException : public BankException {
public:
    explicit UserNotFoundException(const string& msg = "User not found.")
        : BankException(msg) {}
};

// Exception for duplicate user or account
class DuplicateUserException : public BankException {
public:
    explicit DuplicateUserException(const string& msg = "Username already exists.")
        : BankException(msg) {}
};

// Exception for duplicate account
class DuplicateAccountException : public BankException {
public:
    explicit DuplicateAccountException(const string& msg = "Record number already exists.")
        : BankException(msg) {}
};

// Exception for authentication failures (e.g., wrong username or PIN)
class AuthenticationException : public BankException {
public:
    explicit AuthenticationException(const string& msg = "Invalid username or PIN.")
        : BankException(msg) {}
};

// Exception for account lockout after too many failed attempts
class AccountLockedException : public BankException {
public:
    explicit AccountLockedException(
        const string& msg = "This user is locked after too many failed attempts. Ask an admin to unlock it.")
        : BankException(msg) {}
};

// Exception for unauthorized access attempts (e.g., trying to access another user's account)
class AccessDeniedException : public BankException {
public:
    explicit AccessDeniedException(const string& msg = "You are not allowed to perform this action.")
        : BankException(msg) {}
};

// Exception for invalid input (e.g., non-numeric input when a number is expected)
class ValidationException : public BankException {
public:
    explicit ValidationException(const string& msg = "Invalid input.")
        : BankException(msg) {}
};

// Exception for file I/O errors (e.g., unable to read/write data files)
class FileIOException : public BankException {
public:
    explicit FileIOException(const string& msg = "Could not access data file.")
        : BankException(msg) {}
};

// Deliberately NOT a BankException: menus catch BankException and keep looping,
// but a closed stdin (Ctrl+D / piped input ended) must unwind to main().
class InputClosedException : public exception {
public:
    const char* what() const noexcept override { return "Input stream closed."; }
};

#endif // EXCEPTIONS_H