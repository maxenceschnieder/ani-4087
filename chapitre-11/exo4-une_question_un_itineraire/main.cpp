
#include <iostream>
#include <string>

static void retirerCR(std::string& s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

static long long lireEntier(const std::string& s) {
    try {
        return std::stoll(s);
    } catch (...) {
        return 0;
    }
}

// Rejoue le scan du manifeste et affiche le resultat pour la machine i.
static void traiter(long long i, const std::string& manifeste, long long l, const std::string& texte) {
    std::cout << i << " MANIFESTE " << manifeste << "\n";
    if (l < 0) {
        std::cout << i << " ECHEC ILLISIBLE\n";
        return;
    }

    const std::string cle = "\"library_path\"";
    std::size_t posCle = texte.find(cle);
    if (posCle == std::string::npos) {
        std::cout << i << " ECHEC CLE\n";
        return;
    }
    std::size_t posDeuxPoints = texte.find(':', posCle + cle.size());
    if (posDeuxPoints == std::string::npos) {
        std::cout << i << " ECHEC DEUX_POINTS\n";
        return;
    }
    std::size_t g1 = texte.find('"', posDeuxPoints);
    std::size_t g2 = (g1 == std::string::npos) ? std::string::npos : texte.find('"', g1 + 1);
    if (g1 == std::string::npos || g2 == std::string::npos) {
        std::cout << i << " ECHEC GUILLEMET\n";
        return;
    }

    std::string brut = texte.substr(g1 + 1, g2 - g1 - 1);
    std::string valeur;
    for (std::size_t k = 0; k < brut.size(); ++k) {
        if (brut[k] == '\\' && k + 1 < brut.size() && brut[k + 1] == '\\') {
            continue;
        }
        valeur += brut[k];
    }
    if (valeur.empty()) {
        std::cout << i << " ECHEC VIDE\n";
        return;
    }

    std::cout << i << " VALEUR " << valeur << "\n";
    bool absolu = (valeur.size() >= 2 && valeur[1] == ':') || valeur[0] == '\\' || valeur[0] == '/';
    std::string charge;
    if (absolu) {
        std::cout << i << " ABSOLU\n";
        charge = valeur;
    } else {
        std::cout << i << " RELATIF\n";
        std::size_t sep = manifeste.find_last_of("\\/");
        std::string dossier = (sep == std::string::npos) ? std::string() : manifeste.substr(0, sep + 1);
        charge = dossier + valeur;
    }
    std::cout << i << " CHARGE " << charge << "\n";
}

int main() {
    std::string ligne;
    long long k = 0;
    if (std::getline(std::cin, ligne)) {
        retirerCR(ligne);
        k = lireEntier(ligne);
    }

    for (long long i = 1; i <= k; ++i) {
        std::string registre;
        std::getline(std::cin, registre);
        retirerCR(registre);

        std::string ligneL;
        std::getline(std::cin, ligneL);
        retirerCR(ligneL);
        long long l = lireEntier(ligneL);

        std::string texte;
        for (long long j = 0; j < l; ++j) {
            std::string m;
            std::getline(std::cin, m);
            retirerCR(m);
            texte += m;
            texte += '\n';
        }

        if (registre == "-") {
            std::cout << i << " REGISTRE AUCUN\n";
            continue;
        }
        traiter(i, registre, l, texte);
    }
    return 0;
}
