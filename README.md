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
```

### Option du script :
  Le script Shell offre plusieurs options pour traiter et analyser les données d'un fichiers CSV de trajets de conducteurs. Voici un résumé des options disponibles :

#### [D1] : Conducteurs avec le Plus de Trajets
- Option : `-d1`

- Temps d'exécution ciblé : Environ 8 secondes.

#### [D2] : Conducteurs et la Plus Grande Distance
- Option : `-d2`

- Temps d'exécution ciblé : Environ 7 secondes.

#### [L] : Les 10 Trajets les Plus Longs
- Option : `-l`

- Temps d'exécution ciblé : Environ 8 secondes.

#### [T] : Les 10 Villes les Plus Traversées
- Option : `-t`
  
- Temps d'exécution ciblé : Environ 20 secondes.

#### [S] : Statistiques sur les Étapes
- Option : `-s`
