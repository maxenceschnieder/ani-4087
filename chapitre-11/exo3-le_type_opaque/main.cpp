#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

static bool finitPar(const std::string& s, const std::string& suffixe) {
    return s.size() >= suffixe.size() &&
           s.compare(s.size() - suffixe.size(), suffixe.size(), suffixe) == 0;
}

int main() {
    long long e = 0;
    std::cin >> e;
    std::set<std::string> externes;
    for (long long i = 0; i < e; ++i) {
        std::string nom;
        std::cin >> nom;
        externes.insert(nom);
    }

    long long f = 0;
    std::cin >> f;
    std::vector<std::string> ordre;
    std::map<std::string, std::vector<std::string>> inclusions;
    for (long long i = 0; i < f; ++i) {
        std::string nom;
        long long k = 0;
        std::cin >> nom >> k;
        std::vector<std::string> liste;
        for (long long j = 0; j < k; ++j) {
            std::string inc;
            std::cin >> inc;
            liste.push_back(inc);
        }
        if (!inclusions.count(nom)) {
            ordre.push_back(nom);
        }
        inclusions[nom] = liste;
    }

    long long touchees = 0;
    long long unites = 0;
    for (const std::string& unite : ordre) {
        if (!finitPar(unite, ".cpp") || externes.count(unite)) {
            continue;
        }
        ++unites;

        // Parcours par niveaux, chaque nom n'est repris qu'une fois.
        std::map<std::string, std::string> parent;
        std::set<std::string> vus;
        std::queue<std::string> file;
        vus.insert(unite);
        file.push(unite);
        std::string trouve;

        while (!file.empty() && trouve.empty()) {
            std::string courant = file.front();
            file.pop();
            auto it = inclusions.find(courant);
            if (it == inclusions.end()) {
                continue;
            }
            for (const std::string& inc : it->second) {
                if (vus.count(inc)) {
                    continue;
                }
                vus.insert(inc);
                parent[inc] = courant;
                if (externes.count(inc)) {
                    trouve = inc;
                    break;
                }
                if (inclusions.count(inc)) {
                    file.push(inc);
                }
                // Sinon : en-tete du systeme, il n'inclut rien.
            }
        }

        if (trouve.empty()) {
            std::cout << unite << " NON\n";
        } else {
            ++touchees;
            std::vector<std::string> chemin;
            std::string pas = trouve;
            chemin.push_back(pas);
            while (pas != unite) {
                pas = parent[pas];
                chemin.push_back(pas);
            }
            std::reverse(chemin.begin(), chemin.end());
            std::cout << unite << " OUI ";
            for (std::size_t i = 0; i < chemin.size(); ++i) {
                if (i > 0) {
                    std::cout << ">";
                }
                std::cout << chemin[i];
            }
            std::cout << "\n";
        }
    }

    std::cout << "TOUCHEES " << touchees << " SUR " << unites << "\n";
    return 0;
}
