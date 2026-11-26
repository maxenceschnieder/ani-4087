#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

static void retirerCR(std::string& s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

static bool estMot(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

// Lit une ligne "X n nom1 ... nomn" et rend les noms.
static std::vector<std::string> lireNoms(const std::string& ligne) {
    std::istringstream flux(ligne);
    std::string etiquette;
    long long n = 0;
    std::vector<std::string> noms;
    flux >> etiquette >> n;
    for (long long i = 0; i < n; ++i) {
        std::string nom;
        if (!(flux >> nom)) {
            break;
        }
        noms.push_back(nom);
    }
    return noms;
}

// Vrai si 'nom' apparait entier dans 'texte'.
static bool contientNom(const std::string& texte, const std::string& nom) {
    if (nom.empty()) {
        return false;
    }
    std::size_t pos = texte.find(nom);
    while (pos != std::string::npos) {
        bool avantOk = (pos == 0) || !estMot(texte[pos - 1]);
        std::size_t fin = pos + nom.size();
        bool apresOk = (fin >= texte.size()) || !estMot(texte[fin]);
        if (avantOk && apresOk) {
            return true;
        }
        pos = texte.find(nom, pos + 1);
    }
    return false;
}

static bool contientUnNom(const std::string& texte, const std::vector<std::string>& noms) {
    for (const std::string& nom : noms) {
        if (contientNom(texte, nom)) {
            return true;
        }
    }
    return false;
}

static bool estCommentaire(const std::string& texte) {
    std::size_t i = 0;
    while (i < texte.size() && (texte[i] == ' ' || texte[i] == '\t')) {
        ++i;
    }
    return i + 1 < texte.size() && texte[i] == '/' && texte[i + 1] == '/';
}

int main() {
    std::string ligneC, ligneD, ligneN;
    std::getline(std::cin, ligneC);
    std::getline(std::cin, ligneD);
    std::getline(std::cin, ligneN);
    retirerCR(ligneC);
    retirerCR(ligneD);
    retirerCR(ligneN);

    std::vector<std::string> nomsC = lireNoms(ligneC);
    std::vector<std::string> nomsD = lireNoms(ligneD);
    long long n = 0;
    try {
        n = std::stoll(ligneN);
    } catch (...) {
        n = 0;
    }

    long long decisions = 0;
    long long fuites = 0;
    long long definis = 0;

    for (long long l = 1; l <= n; ++l) {
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            break;
        }
        retirerCR(ligne);

        std::size_t espace = ligne.find(' ');
        std::string zone = (espace == std::string::npos) ? ligne : ligne.substr(0, espace);
        std::string texte = (espace == std::string::npos) ? std::string() : ligne.substr(espace + 1);

        if (estCommentaire(texte)) {
            continue;
        }

        if (contientUnNom(texte, nomsC)) {
            if (zone == "INIT") {
                ++decisions;
            } else if (zone == "BOUCLE" || zone == "SCENE") {
                ++fuites;
                std::cout << "FUITE " << l << " " << zone << "\n";
            }
        }
        if (zone != "FABRIQUE" && contientUnNom(texte, nomsD)) {
            ++definis;
            std::cout << "DEFINI " << l << " " << zone << "\n";
        }
    }

    std::cout << "DECISIONS " << decisions << "\n";
    std::cout << "FUITES " << fuites << "\n";
    std::cout << "DEFINIS " << definis << "\n";
    if (fuites == 0 && definis == 0) {
        std::cout << "ABSTRACTION TENUE\n";
    } else {
        std::cout << "ABSTRACTION FUIT\n";
    }
    return 0;
}
