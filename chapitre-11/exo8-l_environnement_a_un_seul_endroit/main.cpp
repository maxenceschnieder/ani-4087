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

// Lit un nombre a partir de 'pos' : espaces, signe facultatif, chiffres.
// Rend vrai si au moins un chiffre a ete lu. 'pos' avance apres le nombre.
static bool lireNombre(const std::string& s, std::size_t& pos, long long& valeur) {
    while (pos < s.size() && s[pos] == ' ') {
        ++pos;
    }
    bool negatif = false;
    if (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
        negatif = (s[pos] == '-');
        ++pos;
    }
    bool chiffre = false;
    long long v = 0;
    while (pos < s.size() && std::isdigit(static_cast<unsigned char>(s[pos]))) {
        chiffre = true;
        v = v * 10 + (s[pos] - '0');
        ++pos;
    }
    valeur = negatif ? -v : v;
    return chiffre;
}

static std::string interrupteur(const std::string& valeur) {
    if (valeur[0] == '0' || valeur == "false") {
        return "NON";
    }
    return "OUI";
}

int main() {
    std::string ligne1, loader, ligne3;
    std::getline(std::cin, ligne1);
    std::getline(std::cin, loader);
    std::getline(std::cin, ligne3);
    retirerCR(ligne1);
    retirerCR(loader);
    retirerCR(ligne3);

    std::string backend, demi, profondeur, liste;
    long long hz = 0;
    long long latence = 0;
    {
        std::istringstream flux(ligne1);
        flux >> backend >> hz >> demi >> profondeur >> liste >> latence;
    }

    bool poseFixe = false;
    long long pose[5] = {0, 0, 0, 0, 0};
    {
        std::istringstream flux(ligne3);
        std::string mot;
        flux >> mot;
        if (mot == "FIXE") {
            poseFixe = true;
            for (long long& p : pose) {
                flux >> p;
            }
        }
    }

    std::string ligneM;
    long long m = 0;
    if (std::getline(std::cin, ligneM)) {
        retirerCR(ligneM);
        try {
            m = std::stoll(ligneM);
        } catch (...) {
            m = 0;
        }
    }

    long long appliquees = 0;
    long long ignorees = 0;
    for (long long i = 0; i < m; ++i) {
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            break;
        }
        retirerCR(ligne);
        std::size_t egal = ligne.find('=');
        std::string nom = (egal == std::string::npos) ? ligne : ligne.substr(0, egal);
        std::string valeur = (egal == std::string::npos) ? std::string() : ligne.substr(egal + 1);

        bool appliquee = false;
        if (!valeur.empty()) {
            if (nom == "NK_XR_BACKEND") {
                if (valeur == "openxr") {
                    backend = "OPENXR";
                    appliquee = true;
                }
            } else if (nom == "NK_XR_HZ" || nom == "NK_XR_SIM_LATENCY_MS") {
                std::size_t pos = 0;
                long long v = 0;
                lireNombre(valeur, pos, v);
                if (nom == "NK_XR_HZ") {
                    hz = v;
                } else {
                    latence = v;
                }
                appliquee = true;
            } else if (nom == "NK_XR_HALF_RATE") {
                demi = interrupteur(valeur);
                appliquee = true;
            } else if (nom == "NK_XR_DEPTH_LAYER") {
                profondeur = interrupteur(valeur);
                appliquee = true;
            } else if (nom == "NK_XR_LIST_EXT") {
                liste = interrupteur(valeur);
                appliquee = true;
            } else if (nom == "NK_XR_OPENXR_LOADER") {
                loader = valeur;
                appliquee = true;
            } else if (nom == "NK_XR_SIM_POSE") {
                std::vector<long long> nombres;
                std::size_t pos = 0;
                while (pos < valeur.size() && nombres.size() < 5) {
                    long long v = 0;
                    if (!lireNombre(valeur, pos, v)) {
                        break;
                    }
                    nombres.push_back(v);
                    while (pos < valeur.size() && (valeur[pos] == ',' || valeur[pos] == ' ')) {
                        ++pos;
                    }
                }
                if (nombres.size() == 5) {
                    poseFixe = true;
                    for (std::size_t k = 0; k < 5; ++k) {
                        pose[k] = nombres[k];
                    }
                    appliquee = true;
                }
            }
        }

        if (appliquee) {
            ++appliquees;
        } else {
            ++ignorees;
        }
    }

    std::cout << "BACKEND " << backend << "\n";
    std::cout << "HZ " << hz << "\n";
    std::cout << "DEMI " << demi << "\n";
    std::cout << "PROFONDEUR " << profondeur << "\n";
    std::cout << "LISTE " << liste << "\n";
    std::cout << "LOADER " << loader << "\n";
    std::cout << "LATENCE " << latence << "\n";
    if (poseFixe) {
        std::cout << "POSE FIXE";
        for (long long p : pose) {
            std::cout << " " << p;
        }
        std::cout << "\n";
    } else {
        std::cout << "POSE LIBRE\n";
    }
    std::cout << "APPLIQUEES " << appliquees << "\n";
    std::cout << "IGNOREES " << ignorees << "\n";
    return 0;
}
