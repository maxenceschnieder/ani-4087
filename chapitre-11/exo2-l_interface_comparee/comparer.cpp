#include <iostream>
#include <string>
#include <vector>
#include <set>

// Lit une liste : son nombre de noms, puis les noms (doublons retires).
static std::vector<std::string> lireListe() {
    std::vector<std::string> liste;
    std::set<std::string> vus;
    long long n = 0;
    if (!(std::cin >> n)) {
        return liste;
    }
    for (long long i = 0; i < n; ++i) {
        std::string nom;
        if (!(std::cin >> nom)) {
            break;
        }
        if (vus.insert(nom).second) {
            liste.push_back(nom);
        }
    }
    return liste;
}

int main() {
    std::vector<std::string> a = lireListe();
    std::vector<std::string> b = lireListe();
    std::set<std::string> ensA(a.begin(), a.end());
    std::set<std::string> ensB(b.begin(), b.end());

    std::vector<std::string> seulA;
    std::vector<std::string> seulB;
    long long deux = 0;
    for (const std::string& nom : a) {
        if (ensB.count(nom)) {
            ++deux;
        } else {
            seulA.push_back(nom);
        }
    }
    for (const std::string& nom : b) {
        if (!ensA.count(nom)) {
            seulB.push_back(nom);
        }
    }

    long long differentes = static_cast<long long>(seulA.size() + seulB.size());
    long long reunis = deux + differentes;

    std::cout << "DEUX " << deux << "\n";
    for (const std::string& nom : seulA) {
        std::cout << "SEUL_A " << nom << "\n";
    }
    for (const std::string& nom : seulB) {
        std::cout << "SEUL_B " << nom << "\n";
    }
    std::cout << "DIFFERENTES " << differentes << " SUR " << reunis << "\n";
    return 0;
}
