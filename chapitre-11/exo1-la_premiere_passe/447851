#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// Retire un eventuel retour chariot en fin de ligne.
static void retirerCR(std::string& s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

static bool estMot(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

static bool estSigneNom(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

// Vrai si la ligne commence par // une fois otes espaces et tabulations.
static bool estCommentaire(const std::string& ligne) {
    std::size_t i = 0;
    while (i < ligne.size() && (ligne[i] == ' ' || ligne[i] == '\t')) {
        ++i;
    }
    return i + 1 < ligne.size() && ligne[i] == '/' && ligne[i + 1] == '/';
}

// Ajoute a 'vars' les variables NK_...= annoncees dans la ligne.
static void chercherVariables(const std::string& ligne, std::vector<std::string>& vars) {
    std::size_t pos = ligne.find("NK_");
    while (pos != std::string::npos) {
        bool debutOk = (pos == 0) || !estMot(ligne[pos - 1]);
        if (debutOk) {
            std::size_t fin = pos + 3;
            while (fin < ligne.size() && estSigneNom(ligne[fin])) {
                ++fin;
            }
            if (fin > pos + 3 && fin < ligne.size() && ligne[fin] == '=') {
                std::string nom = ligne.substr(pos, fin - pos);
                bool dejaVu = false;
                for (const std::string& v : vars) {
                    if (v == nom) {
                        dejaVu = true;
                        break;
                    }
                }
                if (!dejaVu) {
                    vars.push_back(nom);
                }
            }
        }
        pos = ligne.find("NK_", pos + 1);
    }
}

int main() {
    std::string premiere;
    long long n = 0;
    if (std::getline(std::cin, premiere)) {
        retirerCR(premiere);
        try {
            n = std::stoll(premiere);
        } catch (...) {
            n = 0;
        }
    }
    if (n <= 0) {
        std::cout << "ENTETE 0\nIGNOREES 0\nVARIABLE AUCUNE\nPART 0\n";
        return 0;
    }

    long long entete = 0;
    bool dansEntete = true;
    std::vector<std::string> vars;
    for (long long i = 0; i < n; ++i) {
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            ligne.clear();
        }
        retirerCR(ligne);
        if (!dansEntete) {
            continue;
        }
        if (estCommentaire(ligne)) {
            ++entete;
            chercherVariables(ligne, vars);
        } else {
            dansEntete = false;
        }
    }

    std::cout << "ENTETE " << entete << "\n";
    std::cout << "IGNOREES " << (n - entete) << "\n";
    if (vars.empty()) {
        std::cout << "VARIABLE AUCUNE\n";
    } else {
        for (const std::string& v : vars) {
            std::cout << "VARIABLE " << v << "\n";
        }
    }
    std::cout << "PART " << (100 * entete / n) << "\n";
    return 0;
}
