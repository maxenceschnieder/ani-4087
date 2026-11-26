#include <iostream>
#include <string>
#include <vector>

int main() {
    long long hz = 0;
    std::cin >> hz;
    if (hz <= 1) {
        hz = 72;
    }
    const long long periode = 1000000000LL / hz;

    std::string mot;
    std::cin >> mot;
    long long pose[5] = {0, 0, 0, 1700, 0};
    if (mot == "FIXE") {
        for (long long& p : pose) {
            std::cin >> p;
        }
    }

    long long t = 0;
    std::cin >> t;
    if (t < 0) {
        t = 0;
    }
    std::vector<long long> a(static_cast<std::size_t>(t));
    std::vector<long long> b(static_cast<std::size_t>(t));
    for (long long& v : a) {
        std::cin >> v;
    }
    for (long long& v : b) {
        std::cin >> v;
    }

    std::cout << "PERIODE " << periode << "\n";
    std::cout << "POSE " << pose[0] << " " << pose[1] << " " << pose[2] << " "
              << pose[3] << " " << pose[4] << "\n";

    long long premierBrut = 0;
    long long premierRelatif = 0;
    for (long long i = 0; i < t; ++i) {
        std::size_t k = static_cast<std::size_t>(i);
        long long preditA = a[k] + periode;
        long long preditB = b[k] + periode;
        long long brut = preditB - preditA;
        long long relatif = (preditB - (b[0] + periode)) - (preditA - (a[0] + periode));
        long long scripte = (i + 1) * periode;
        std::cout << (i + 1) << " BRUT " << brut << " RELATIF " << relatif
                  << " SCRIPTE " << scripte << "\n";
        if (brut != 0 && premierBrut == 0) {
            premierBrut = i + 1;
        }
        if (relatif != 0 && premierRelatif == 0) {
            premierRelatif = i + 1;
        }
    }

    if (premierBrut == 0) {
        std::cout << "BRUT IDENTIQUE\n";
    } else {
        std::cout << "BRUT DIFFERENT " << premierBrut << "\n";
    }
    if (premierRelatif == 0) {
        std::cout << "RELATIF IDENTIQUE\n";
    } else {
        std::cout << "RELATIF DIFFERENT " << premierRelatif << "\n";
    }
    return 0;
}
