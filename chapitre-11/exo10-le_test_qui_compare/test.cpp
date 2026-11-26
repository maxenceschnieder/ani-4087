#include <iostream>

// Test deterministe : tete scriptee et horloge scriptee.
// Aucune lecture de l'heure : deux executions donnent la meme sortie.
int main() {
    long long hz = 0, ipd = 0, n = 0;
    long long x = 0, y = 0, z = 0, k0 = 0, dk = 0, vx = 0;
    std::cin >> hz >> ipd >> n;
    std::cin >> x >> y >> z >> k0 >> dk >> vx;

    if (hz <= 1) {
        hz = 72;
    }
    const long long periode = 1000000000LL / hz;
    const long long demi = ipd / 2;

    // Droite de la tete vue de dessus (x, z) pour les lacets 0, 1, 2, 3.
    const long long droiteX[4] = {1, 0, -1, 0};
    const long long droiteZ[4] = {0, -1, 0, 1};

    std::cout << "PERIODE " << periode << "\n";
    for (long long t = 1; t <= n; ++t) {
        long long lacet = (k0 + (t - 1) * dk) % 4;
        if (lacet < 0) {
            lacet += 4;
        }
        long long tx = x + (t - 1) * vx;
        long long rx = droiteX[lacet];
        long long rz = droiteZ[lacet];

        long long gx = tx - demi * rx;
        long long gz = z - demi * rz;
        long long dx = tx + demi * rx;
        long long dz = z + demi * rz;
        long long instant = t * periode;

        std::cout << t << " G " << gx << " " << y << " " << gz
                  << " D " << dx << " " << y << " " << dz
                  << " I " << instant << "\n";
    }
    return 0;
}
