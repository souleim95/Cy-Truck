#!/bin/bash

# Votre code ici

# Dossiers à vérifier
dossier_temp="temp"
dossier_images="images"
dossier_progc="progc"

cd "$dossier_progc"

# Compiler avec make
make -s

# Vérifier la présence de l'exécutable
executable="./exec"

if [ -x "$executable" ]; then
    echo "L'exécutable dans le dossier progc est présent."
else
    echo "Erreur : L'exécutable dans le dossier progc est introuvable."
    exit 1
fi

# Revenir au dossier parent de progc
cd ..

# Création des dossiers 'temp' et 'images' si nécessaire
[ -d "$dossier_temp" ] && rm -rf "$dossier_temp"/* || mkdir "$dossier_temp"
[ ! -d "$dossier_images" ] && mkdir "$dossier_images"

# Gestion de l'option d'aide (-h)
for arg in "$@"; do
    if [ "$arg" = "-h" ]; then
        echo "Veuillez taper dans le terminal la ligne suivante "./projet.sh data.csv" suivi d'une option"
        echo "Options de traitement :"
        echo "L'option "-d1" qui vous permet d'afficher la liste des 10 premiers conducteurs avec le plus grand nombre de trajets."
        echo "L'option "-d2" qui vous permet d'afficher la liste des 10 premiers conducteurs avec la plus grande distance parcourue."
        echo "L'option "-l" qui vous permet d'afficher les 10 trajets les plus longs."
        echo "L'option "-t" qui vous permet d'afficher les 10 villes les plus traversées."
        echo "L'option "-s" qui vous permet d'afficher les statistiques sur les étapes."
        exit 0
    fi
done

# Vérification des arguments
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 chemin_du_fichier_csv traitement1 [traitement2 ...]"
    exit 1
fi

chemin_csv="data/data.csv"

# Début de la mesure du temps


# Itération à partir du deuxième argument
for arg in "${@:2}"; do
    case "$arg" in
         -d1)
        start_time=$(date +%s)
        echo "TRAITEMENT D1 :"
           cut -d ';' -f1,6 "$chemin_csv" | perl -ne 'print if  !$seen{$_}++' | awk -F ';' '{trajets[$2] +=1} END { for (driver in trajets) print  driver ";" trajets[driver] }' | sort -nt ';' -k2 | tail -10 > "$dossier_temp/resultat_d1.txt"
          
        
  tac "$dossier_temp/resultat_d1.txt"
    
        gnuplot  "graph.gp"
        end_time=$(date +%s)
duree_traitement=$((end_time - start_time))
echo "Durée du traitement: $duree_traitement secondes"
            ;;
        -d2)
        start_time=$(date +%s)
        echo "TRAITEMENT D2:"
            LC_NUMERIC=C awk -F ';' '{distance[$6] += $5} END { for (conducteurs in distance) printf "%s;%.6f\n", conducteurs,distance[conducteurs] }' "$chemin_csv" | sort -nt ';' -k2 | tail -10 > "$dossier_temp/resultat_d2.txt"
       
        tac "$dossier_temp/resultat_d2.txt" 
        
        gnuplot  "graph2.gp"
         end_time=$(date +%s)
duree_traitement=$((end_time - start_time))
echo "Durée du traitement: $duree_traitement secondes"
            ;;
        -l)
         start_time=$(date +%s)
        echo "TRAITEMENT L:"
             LC_NUMERIC=C  awk -F ';' '{ distance[$1] += $5 } END { for (trajet in distance) printf "%s;%.6f\n", trajet, distance[trajet] }' "$chemin_csv" | sort -nrt ';' -k2 | head -10 | sort -nrt ';' -k1 > "$dossier_temp/resultat_l.txt"
                
        sort -nr "$dossier_temp/resultat_l.txt"  | cat
 gnuplot -e "
        set terminal png size 800,600;
        set output '$dossier_images/histogramme_vertical_l.png';
        set title 'Option -l : Distance = f(Route)';
        set xlabel 'ROUTE ID';
        set ylabel 'Distance (km)';
        set style data histograms;
        set style fill solid;
        set datafile separator ';';
        set xrange [-0.5:];
        set yrange [0:*];
        set boxwidth 2.0;
        plot '$dossier_temp/resultat_l.txt' using 2:xticlabels(1) notitle lc rgb 'skyblue';
    "
    end_time=$(date +%s)
duree_traitement=$((end_time - start_time))
echo "Durée du traitement: $duree_traitement secondes"
            ;;
        -t)
          start_time=$(date +%s)
           # Traitement T avec programme C
 echo "TRAITEMENT T:"
# Définir les chemins




# Créer le fichier result.csv dans le dossier progc
cut -d ';' -f1,2,3,4 "$chemin_csv" | tail -n+2 > "$dossier_progc/result.csv"

# Aller dans le dossier progc
cd "$dossier_progc"
# Compiler avec make


# Exécuter le script et rediriger la sortie vers le fichier dans le dossier temp
./exec > "../$dossier_temp/resultat_t.txt"
make -s clean
rm -r "result.csv"
# Revenir au dossier parent de progc si nécessaire
cd ..

# Afficher le contenu du fichier resultat_t.txt
cat "$dossier_temp/resultat_t.txt"


    gnuplot "graph3.gp"
    end_time=$(date +%s)
duree_traitement=$((end_time - start_time))
echo "Durée du traitement: $duree_traitement secondes"
            ;;
        -s)
            # Traitement S avec programme C
            # ... (votre code pour le traitement S)
            ;;
        *)
            # Code pour les arguments inconnus, si nécessaire
            echo "Argument inconnu : $arg"
            ;;
    esac
done


