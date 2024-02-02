# CY_Truck :

Ce script shell a été conçu pour effectuer des traitements spécifiques sur des fichiers CSV contenant des données sur les trajets effectués par des conducteurs.

## Utilisation :

### Prérequis :

Vous devez avoir environnement Bash disposant des outils nécessaires tels que `awk`, `gcc` pour compiler, `gnuplot` pour la génération des graphiques.

### Exécution du script :

Pour exécuter le script, ouvrez un terminal et assurez-vous que votre fichier à analyser est placé dans le dossier **`data`** situé dans le répertoire du code. Puis exécutez la commande suivante :

```bash
./projet.sh data.csv -h 
```

**Exemples:**
```bash
./projet.sh -h # Montre l'aide
./projet.sh data.csv -d1 # Execute les traitements d1
./projet.sh data.csv -d2 -l .. # Execute plusieur traitement en même temps
```

### Option du script :
  Le script Shell offre plusieurs options pour traiter et analyser les données d'un fichiers CSV de trajets de conducteurs. Voici un résumé des options disponibles :

#### TRAITEMENT [D1] : conducteurs avec le plus de trajets :
- Option : `-d1`

- Temps d'exécution  : Environ 8 secondes.

####  TRAITEMENT [D2] : conducteurs et la plus grande distance: 
- Option : `-d2`

- Temps d'exécution  : Environ 7 secondes.

#### TRAITEMENT [L] : les 10 trajets les plus longs : 
- Option : `-l`

- Temps d'exécution  : Environ 8 secondes.

#### TRAITEMENT [T] : les 10 villes les plus traversées :
- Option : `-t`
  
- Temps d'exécution : Environ 20 secondes.

#### Traitement [S] : statistiques sur les étapes : 
- Option : `-s`
