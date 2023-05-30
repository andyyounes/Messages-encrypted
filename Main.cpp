#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1)
        return false;
    
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0)
            return false;
    }
    
    return true;
}

// Function to calculate (base^exponent) % modulus
int powerMod(int base, int exponent, int modulus) {
    int result = 1;
    
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        
        base = (base * base) % modulus;
        exponent /= 2;
    }
    
    return result;
}

// Function to generate a random prime number within a given range
int generatePrime(int min, int max) {
    int num;
    
    do {
        num = rand() % (max - min + 1) + min;
    } while (!isPrime(num));
    
    return num;
}

// Function to generate a Diffie-Hellman key
int generateKey(int prime, int primitiveRoot, int privateKey) {
    return powerMod(primitiveRoot, privateKey, prime);
}

// Function to encrypt a message using Vigenere cipher
string encryptMessage(const string& message, const string& key) {
    string encryptedMessage = message;
    
    for (size_t i = 0; i < message.length(); ++i) {
        if (isupper(message[i])) {
            encryptedMessage[i] = (message[i] + key[i % key.length()] - 2 * 'A') % 26 + 'A';
        } else if (islower(message[i])) {
            encryptedMessage[i] = (message[i] + key[i % key.length()] - 2 * 'a') % 26 + 'a';
        }
    }
    
    return encryptedMessage;
}

// Function to decrypt a message using Vigenere cipher
string decryptMessage(const string& encryptedMessage, const string& key) {
    string decryptedMessage = encryptedMessage;
    
    for (size_t i = 0; i < encryptedMessage.length(); ++i) {
        if (isupper(encryptedMessage[i])) {
            decryptedMessage[i] = (encryptedMessage[i] - key[i % key.length()] + 26) % 26 + 'A';
        } else if (islower(encryptedMessage[i])) {
            decryptedMessage[i] = (encryptedMessage[i] - key[i % key.length()] + 26) % 26 + 'a';
        }
    }
    
    return decryptedMessage;
}

int main() {
    // Generate prime number and primitive root
    int prime = generatePrime(100, 1000);
    int primitiveRoot = generatePrime(2, prime - 2);
    
    // Server's private key
    int serverPrivateKey = generatePrime(2, prime - 2);
    
    // Calculate server's public key
    int serverPublicKey = generateKey(prime, primitiveRoot, serverPrivateKey);
    
    // Client's private key
    int clientPrivateKey = generatePrime(2, prime - 2);
    
    // Calculate client's public key
    int clientPublicKey = generateKey(prime, primitiveRoot, clientPrivateKey);
    
    // Shared key calculation
    int serverSharedKey = generateKey(prime, clientPublicKey, serverPrivateKey);
    int clientSharedKey = generateKey(prime, serverPublicKey, clientPrivateKey);
    
    // Print the shared key (should be the same on both server and client sides)
    cout << "Shared Key: " << serverSharedKey << endl;
    
    // User input
    string message;
    
    cout << "Enter message: ";
    getline(cin, message);
    
    // Encryption and decryption
    string encryptionKey = "KEY";  // Replace with your own key or generate it dynamically
    
    string encryptedMessage = encryptMessage(message, encryptionKey);
    string decryptedMessage = decryptMessage(encryptedMessage, encryptionKey);
    
    cout << "Original Message: " << message << endl;
    cout << "Encrypted Message: " << encryptedMessage << endl;
    cout << "Decrypted Message: " << decryptedMessage << endl;
    
    return 0;
}
