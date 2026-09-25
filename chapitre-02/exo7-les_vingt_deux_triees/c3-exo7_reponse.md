## Les dépendances de la démonstration du moteur

### 1. Dépendances dont le nom suffit à deviner le rôle

- **NKPlatform** : gestion des différentes plateformes.
- **NKMemory** : gestion de la mémoire.
- **NKContainers** : structures de données et conteneurs.
- **NKMath** : fonctions et structures mathématiques.
- **NKThreading** : gestion des threads.
- **NKLogger** : gestion des journaux et messages de débogage.
- **NKTime** : gestion du temps.
- **NKEvent** : gestion des événements.
- **NKWindow** : gestion des fenêtres.
- **NKImage** : gestion des images.
- **NKPhysics** : gestion de la physique.
- **NKCollision** : gestion des collisions.
- **NKRenderer** : rendu graphique.
- **NKCore** : fonctionnalités fondamentales du moteur.
- **NKVFX** : pour gérer les effets visuels du moteur.


### 2. Dépendances dont on peut avoir une idée sans certitude

- **NKStream** : semble fournir des fonctionnalités de lecture et d'écriture de flux de données.
- **NKFileSystem** : semble fournir une abstraction pour accéder au système de fichiers.
- **NKReflection** : semble permettre d'obtenir des informations sur les types et les objets du moteur.
- **NKMedia** : semble être lié à la gestion des contenus multimédias.
- **NKRHI** : semble être une abstraction permettant au moteur de communiquer avec les API graphiques.
- **NKAnima** : semble être le système consacré aux animations.
- **NKSL** : semble être lié à la gestion des shaders ou à un langage de shading.



### 3. Dépendances dont le rôle n'est pas évident avec le nom seul



- **NKGlad** : fournit le chargement des fonctions OpenGL nécessaires au moteur pour accéder aux fonctionnalités graphiques de l'API.

- **NKSerialization** : permet de transformer les données et objets du moteur en une représentation sérialisée et de les reconstruire à partir de celle-ci.

