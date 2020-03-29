#!/bin/bash

# Put here the program (maybe with path)
GETF0="bin/get_pitch"

rm "iteracions.txt"

#function ejecutar {
    for fwav in pitch_db/train/*.wav; do
        ff0=${fwav/.wav/.f0}
        # echo "$GETF0 $fwav $ff0 ----"
        $GETF0 $fwav $ff0 $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14} ${15} ${16} ${17} > /dev/null || (echo "Error in $GETF0 $fwav $ff0"; exit 1)
    done
    #echo -n "Run:probpoth_=$a  probpotl_=$b  probzeros_=$c  probr1normh_=$d  probr1norml_=$e  probrmaxnormh_=$f  probrmaxnorml_=$g  probmin_=$i  "
    #echo -n "Run:probpoth_=$a  probpotl_=$b  probzeros_=$c  probr1normh_=$d  probr1norml_=$e  probrmaxnormh_=$f  probrmaxnorml_=$g  probmin_=$i  " >> iteracions.txt
    resultat=$((bin/PSO_pitch_evaluate pitch_db/train/*f0ref) 2>&1)
    echo -n "$resultat"
#}


# Versio probabilitats

#for a in 83.5; do #probpoth_
#    for b in 2.9; do #probpotl_
#        for c in 0.73; do #probzeros_
#            for d in 1.00; do #probr1normh_
#                for e in 0.21; do #probr1norml_
#                    for f in 2.19; do #probrmaxnormh_
#                        for g in 0.35; do #probrmaxnorml_
#                            for i in 58.75; do #probmin_
#                                ejecutar
#                            done
#                        done
#                    done
#                done
#            done
#        done
#    done
#done





exit 0

# Versio parametres

#        $GETF0 $fwav $ff0 $a $b $c $d $e $f $g $j> /dev/null || (echo "Error in $GETF0 $fwav $ff0"; exit 1)
#    done
#    echo -n "Run:pot=$a  r1=$b  rmax=$c  zeros=$d  thcc1=$e  thcc2=$f  minf0=$g  maxf0=$j  "
#    echo -n "Run:pot=$a  r1=$b  rmax=$c  zeros=$d  thcc1=$e  thcc2=$f  minf0=$g  maxf0=$j  " >> iteracions.txt
#    bin/pitch_evaluate pitch_db/train/*f0ref

#
#for ((a = 66; a <= 66; a += 2)); do #potencia es fa negatiu
#    for ((b = 66; b <= 66; b += 2)); do #r1norm entre 100
#        for ((c = 30; c <= 30; c += 1)); do #rmaxnorm
#            for ((d = 2040; d <= 2040; d += 10)); do #zeros
#                for ((e = 98; e <= 98; e += 1)); do #thcc1 es fa /100
#                    for((f = 10; f <= 10; f += 2)); do #thcc2 es fa /100
#                        for ((g = 60; g <= 60; g += 10)); do #minf0
#                            for ((j = 405; j <= 405; j += 10)); do #maxf0
#                                ejecutar
#                            done
#                        done
#                    done
#                done
#            done
#        done
#    done
#done