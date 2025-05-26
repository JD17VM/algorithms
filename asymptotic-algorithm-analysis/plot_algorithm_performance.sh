#!/bin/bash

DATA_FILE1="$1"
ALG_NAME1="$2"
DATA_FILE2="$3"
ALG_NAME2="$4"

COMPARISON_MODE="false"
if [ -n "$DATA_FILE2" ] && [ -n "$ALG_NAME2" ]; then
    COMPARISON_MODE="true"
fi

PLOT_OUTPUT_FILENAME=""
if [ "$COMPARISON_MODE" == "true" ]; then
    PLOT_OUTPUT_FILENAME="comparison_${ALG_NAME1}_vs_${ALG_NAME2}_plot.png"
else
    PLOT_OUTPUT_FILENAME="${ALG_NAME1}_performance_plot.png"
fi

GNUPLOT_SCRIPT_FILE="temp_plot_commands.gp"

cat << EOF > "$GNUPLOT_SCRIPT_FILE"
set terminal pngcairo size 1024,768 enhanced font 'Verdana,10'
set output '${PLOT_OUTPUT_FILENAME}'
set xlabel 'Input Size (N)'
set ylabel 'Average Time (seconds)'
set grid
set key top left
set logscale y
EOF

if [ "$COMPARISON_MODE" == "true" ]; then
    LEGEND_ALG2_NAME="$ALG_NAME2"
    ALG1_LOWER=$(echo "$ALG_NAME1" | tr '[:upper:]' '[:lower:]')
    ALG2_LOWER=$(echo "$ALG_NAME2" | tr '[:upper:]' '[:lower:]')

    if [ "$ALG1_LOWER" == "$ALG2_LOWER" ]; then
        LEGEND_ALG2_NAME="${ALG_NAME2} (2)"
    fi

    cat << EOF >> "$GNUPLOT_SCRIPT_FILE"
set title '${ALG_NAME1} vs ${ALG_NAME2} comparation (Worst-Case)'
plot '${DATA_FILE1}' using 1:2 with linespoints title '${ALG_NAME1}' lc rgb 'blue' pt 7 ps 1, \
     '${DATA_FILE2}' using 1:2 with linespoints title '${LEGEND_ALG2_NAME}' lc rgb 'red' pt 5 ps 1
EOF
else
    cat << EOF >> "$GNUPLOT_SCRIPT_FILE"
set title '${ALG_NAME1} Performance (Worst-Case)'
plot '${DATA_FILE1}' using 1:2 with linespoints title '${ALG_NAME1}' lc rgb 'blue' pt 7 ps 1
EOF
fi

gnuplot "$GNUPLOT_SCRIPT_FILE"
rm "$GNUPLOT_SCRIPT_FILE"

exit 0