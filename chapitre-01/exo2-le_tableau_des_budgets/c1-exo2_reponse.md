
| Étape | Ordre de grandeur (ms) | Valeur mesurée typique (ms) | Source |
|---|---|---|---|
| Les capteurs mesurent le mouvement | 1 à 2 | Capteur souris : < 1 ms ; IMU VR : 0,2 – 1,0 ms | https://sensconverter.app/input-lag-guide/ |
| Le système transmet la mesure | 1 à 3 | Polling USB 1000 Hz : ~0,5 ms ; transport middleware : 1 – 2 ms | https://sensconverter.app/input-lag-guide/ |
| Votre application décide et dessine | 5 à 11 | Moteur : 1 – 15 ms ; CPU + GPU XR : 2 – 8 ms ; VR 90–120 Hz : 1 – 6 ms | https://beefed.ai/en/ultra-low-latency-xr-rendering |
| Le compositeur assemble | 1 à 2 | Compositor navigateur : 2 – 8 ms ; VR (compositor + scanout) : 0,5 – 1,5 ms ; SteamVR mesuré : ~3,1 ms | https://arwd.ca/latency-budgeting-how-to-allocate-frame-time-for-smooth-vr/ |
| L’écran affiche la ligne | 2 à 5 | Display scan‑out + réponse : 1 – 6 ms ; 240 Hz : 2 – 4,2 ms ; panneaux très rapides : ~2 ms | https://sensconverter.app/input-lag-guide/ |
