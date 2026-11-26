#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Reglage {
    bool lit = false;
    bool ecrit = false;
    bool env = false;
    bool getenv = false;
};

int main() {
    long long r = 0;
    std::cin >> r;

    std::vector<std::string> ordre;
    std::map<std::string, Reglage> reglages;
    for (long long i = 0; i < r; ++i) {
        std::string nom, action;
        if (!(std::cin >> nom >> action)) {
            break;
        }
        if (!reglages.count(nom)) {
            ordre.push_back(nom);
            reglages[nom] = Reglage();
        }
        Reglage& reg = reglages[nom];
        if (action == "LIT") {
            reg.lit = true;
        } else if (action == "ECRIT") {
            reg.ecrit = true;
        } else if (action == "ENV") {
            reg.env = true;
        } else if (action == "GETENV") {
            reg.getenv = true;
        }
        // DECLARE : le champ existe, ce n'est pas une ecriture.
    }

    long long menus = 0;
    for (const std::string& nom : ordre) {
        const Reglage& reg = reglages[nom];
        std::string classe;
        if (reg.getenv) {
            classe = "CACHE";
        } else if (!reg.lit) {
            classe = "FANTOME";
        } else if (!reg.ecrit && !reg.env) {
            classe = "CONSTANTE";
        } else {
            classe = "MENU";
            ++menus;
        }
        std::cout << nom << " " << classe << "\n";
    }
    std::cout << "MENU " << menus << " SUR " << ordre.size() << "\n";
    return 0;
}
