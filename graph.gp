

set terminal pngcairo size 800,600   # Specify the terminal type and size
set output 'images/horizontal_d1.png' # Specify the output file name
set title 'Option -d1 : Nb routes = f(Driver)'
set xlabel 'NB ROUTES'
set ylabel 'DRIVERS NAMES';
set yrange [0:*]      # start at zero, find max from the data
set style fill solid   # solid color boxes
unset key             # turn off all titles
set datafile separator ';'
myBoxWidth = 0.8
set offsets 0,0,0.7-myBoxWidth/2.,0.7
plot 'temp/resultat_d1.txt' using (0.5*$2):0:(0.5*$2):(myBoxWidth/2.):(3):ytic(1) with boxxy lc var 
### end of script
set output  # Reset output to default (to avoid accidentally overwriting subsequent plots)

