#include <iostream>
#include <string>

int main() {
    long long k = 0;
    if (!(std::cin >> k) || k <= 0) {
        std::cout << "AUCUNE MACHINE\n";
        return 0;
    }

    for (long long i = 1; i <= k; ++i) {
        std::string d, v, l, r, b, g;
        std::cin >> d >> v >> l >> r >> b >> g;

        long long chargees = 0;
        long long liberees = 0;
        bool casqueLie = false;

        if (d == "SIMULATEUR") {
            std::cout << i << " BACKEND SIMULATEUR DEMANDE\n";
        } else {
            bool tenue = false;        // une bibliotheque est chargee en ce moment
            std::string sorte;         // BON ou SANS pour la bibliotheque tenue
            std::string source;        // chemin qui a donne la bibliotheque
            bool entree = false;

            // Regle 2 : la variable d'environnement.
            if (v == "ABSENT") {
                std::cout << i << " VARIABLE IGNOREE\n";
            } else if (v == "BON" || v == "SANS") {
                std::cout << i << " VARIABLE CHARGEE\n";
                ++chargees;
                tenue = true;
                sorte = v;
                source = "VARIABLE";
            }

            // Regle 3 : le loader standard, seulement si rien n'est charge.
            if (!tenue) {
                if (l == "BON" || l == "SANS") {
                    std::cout << i << " LOADER CHARGE\n";
                    ++chargees;
                    tenue = true;
                    sorte = l;
                    source = "LOADER";
                } else {
                    std::cout << i << " LOADER ABSENT\n";
                }
            }

            // Regle 4 : point d'entree ou liberation.
            if (tenue) {
                if (sorte == "BON") {
                    entree = true;
                } else {
                    ++liberees;
                    tenue = false;
                    std::cout << i << " SANS_ENTREE\n";
                }
            }

            // Regle 5 : la decouverte directe.
            if (!entree) {
                std::cout << i << " DIRECT " << r << "\n";
                if (r == "NEGO_KO" || r == "BON") {
                    ++chargees;
                    tenue = true;
                    if (r == "BON") {
                        entree = true;
                        source = "DIRECT";
                    }
                }
            }

            // Regle 6 : le backend, puis la liaison graphique.
            if (!entree) {
                std::cout << i << " BACKEND INDISPONIBLE\n";
                if (tenue) {
                    ++liberees;
                    tenue = false;
                }
            } else {
                std::cout << i << " BACKEND OPENXR " << source << "\n";
                if (b == "NON") {
                    ++liberees;
                    tenue = false;
                    std::cout << i << " LIAISON ECHOUEE\n";
                } else {
                    casqueLie = true;
                }
            }
        }

        // Regle 7 : le niveau, toujours atteint.
        if (casqueLie) {
            std::cout << i << " NIVEAU 1 CASQUE\n";
        } else if (g == "OUI") {
            std::cout << i << " NIVEAU 2 SIMULATEUR CARTE\n";
        } else {
            std::cout << i << " NIVEAU 3 SIMULATEUR LOGICIEL\n";
        }
        std::cout << i << " CHARGEES " << chargees << " LIBEREES " << liberees << "\n";
    }
    return 0;
}
