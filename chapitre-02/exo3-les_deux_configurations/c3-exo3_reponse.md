## debug

``` jenga build --config Debug```

 Time: 1.00s
 taille: 138 Ko

( j'ai fais un ``` jenga clean``` avant chaque commande pour m'assurer que jenga n'a pas gardé les elements en cache pour limiter le temps d'execution d'une ou l'autre commande.)

## release

 ``` jenga build --config Release ```

 Time: 1.17s 
 taille: 138 Ko

## comparaison 

 ```
 on constate que les deux exécutable ont la même taille mais que le temps d'execution en debug est plus court que le temps d'execution en release. la simplicité du programme utilisé pour le test ne permet pas d'avoir une veritable comparaison.

 ```