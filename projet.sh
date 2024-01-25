#!/bin/bash

# Dossiers à vérifier
dossier_temp="temp"
dossier_images="images"

# Création des dossiers 'temp' et 'images' si nécessaire
[ -d "$dossier_temp" ] && rm -rf "$dossier_temp"/* || mkdir "$dossier_temp"
[ ! -d "$dossier_images" ] && mkdir "$dossier_images"

# Emplacements des exécutables C
executable_t="chemin/vers/executable_t"
executable_s="chemin/vers/executable_s"

# Gestion de l'option d'aide (-h)
for arg in "$@"; do
    if [ "$arg" = "-h" ]; then
        echo "Usage: $0 chemin_du_fichier_csv traitement1 [traitement2 ...]"
        echo "Options de traitement :"
        echo "- traitement1 : Description du traitement1"
        echo "- traitement2 : Description du traitement2"
        exit 0
    fi
done

# Vérification des arguments
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 chemin_du_fichier_csv traitement1 [traitement2 ...]"
    exit 1
fi
chemin_csv=$1

# Début de la mesure du temps
start_time=$(date +%s)

# Implémentation des traitements
case "$2" in
  -d1)
                                                                                 # Traitement D1 avec Shell
 cut -d ';' -f1,6 "$chemin_csv" | perl -ne 'print if  !$seen{$_}++' | awk -F ';' '{trajets[$2] +=1} END { for (driver in trajets) print  driver ";" trajets[driver] }' | sort -nt ';' -k2 | tail -10 > "$dossier_temp/resultat_d1.txt"
          
        
  tac "$dossier_temp/resultat_d1.txt"
    
        gnuplot  "graph.gp"
    ;;
    
  -d2)
                                                                                 # Traitement D2 avec Shell
  LC_NUMERIC=C awk -F ';' '{distance[$6] += $5} END { for (conducteurs in distance) printf "%s;%.6f\n", conducteurs,distance[conducteurs] }' "$chemin_csv" | sort -nt ';' -k2 | tail -10 > "$dossier_temp/resultat_d2.txt"
       
        tac "$dossier_temp/resultat_d2.txt" 
        
        gnuplot  "graph2.gp"
    ;;
    
  -l)
                                                                                # Traitement L avec Shell
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
;;
    
    
  -t)
    # Traitement T avec programme C
   cut -d ';' -f1,2,3,4  "$chemin_csv" > "result.csv"
#awk -F';' '!seen[$1 FS $2 FS $3 FS $4 ]++ && $2 == 1 { count[$3]++ } END { for (city in count) print count[city] "\t" city }' data.csv | sort -k1,1nr -k2,2 > resultat77.txt

 
    ;;
  -s)
    # Traitement S avec programme C
    "$executable_s" "$chemin_csv" "$dossier_temp/resultat_s.txt"

    gnuplot -e "
        set terminal png size 800,600;
        set output '$dossier_images/courbes_min_max_moyenne_s.png';
        set title 'Statistiques des étapes pour les trajets';
        set xlabel 'Identifiant du trajet';
        set ylabel 'Distance (km)';
        set key outside;
        set xtics rotate by -45;
        plot '$dossier_temp/resultat_s.txt' using 1:2 with linespoints title 'Min', \
             '' using 1:3 with linespoints title 'Max', \
             '' using 1:4 with linespoints title 'Moyenne';
    "
    ;;
esac

# Mesure et affichage du temps d'exécution
end_time=$(date +%s)
duree_traitement=$((end_time - start_time))
echo "Durée du traitement: $duree_traitement secondes"
