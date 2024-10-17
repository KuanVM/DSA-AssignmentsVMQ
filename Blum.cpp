#include <iostream>
#include <vector>
#include <set>
#include <cmath>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

std::vector<int> generateBlumNumbers(int N) {
    std::vector<int> primes;
    for (int i = 3; i < N; i++) {
        if (isPrime(i) && i % 4 == 3) {
            primes.push_back(i);
        }
    }

    std::set<int> blumNumbers;
    for (size_t i = 0; i < primes.size(); ++i) {
        for (size_t j = i + 1; j < primes.size(); ++j) {
            int blumNumber = primes[i] * primes[j];
            if (blumNumber < N) {
                blumNumbers.insert(blumNumber);
            }
        }
    }
    return std::vector<int>(blumNumbers.begin(), blumNumbers.end());
}

std::vector<std::pair<int, int>> findBlumPairs(const std::vector<int>& blumNumbers) {
    std::set<int> blumSet(blumNumbers.begin(), blumNumbers.end());
    std::vector<std::pair<int, int>> blumPairs;
    for (size_t i = 0; i < blumNumbers.size(); ++i) {
        for (size_t j = i; j < blumNumbers.size(); ++j) {
            if (blumSet.count(blumNumbers[i] + blumNumbers[j])) {
                blumPairs.emplace_back(blumNumbers[i], blumNumbers[j]);
            }
        }
    }
    return blumPairs;
}

bool checkBlumExistence(const std::vector<int>& blumNumbers, int M) {
    return std::find(blumNumbers.begin(), blumNumbers.end(), M) != blumNumbers.end();
}

int main() {
    int N = 100;
    std::vector<int> blumNumbers = generateBlumNumbers(N);

    std::cout << "Blum numbers: ";
    for (int num : blumNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<std::pair<int, int>> blumPairs = findBlumPairs(blumNumbers);
    std::cout << "Blum pairs with Blum sums: ";
    for (const auto& pair : blumPairs) {
        std::cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    std::cout << std::endl;

    int M = 21;
    bool exists = checkBlumExistence(blumNumbers, M);
    std::cout << "Blum number " << M << " exists: " << (exists ? "Yes" : "No") << std::endl;

    return 0;
}