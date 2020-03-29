 
---------------------------------------------------------------------
Evaluación de la Detección de Pitch (F0)

Antonio Bonafonte
UPC, Barcelona
2016
---------------------------------------------------------------------


Con objeto de evaluar el algoritmos de detección de pitch, se proporciona
una base de datos etiquetada y un programa para calcular métricas de error.

-------------------------
1. Base de datos.
-------------------------

La base de datos que se utilizará es:
Fundamental Frequency Determination Algorithm (FDA) Evaluation Database.

Centre for Speech Technology Research
University of Edinburgh
80 South Bridge
Edinburgh EH1 1HN
U.K.

Se ha obtenido de
http://www.cstr.ed.ac.uk/research/projects/fda/fda_eval.tar.gz 

Puede consultar la original para tener más información sobre la base de datos
y datos adicionales (glotografo, programas, etc.)


La base de datos original incluye ficheros de audio (20k, 16bits) 
y unos ficheros con el contorno de f0 obtenido a partir de un segundo
fichero que recoge la salida de un laringografo. Este aparato 
mide la impedancia entre los sensores que se conectan a ambos lados de la 
"nuez", con lo que el contorno obtenido puede utilizarse como referencia.

Hemos realizado un cambio de formato, de forma que los ficheros de audio sean 
.wav, y los contornos de f0 de referencia (.f0ref) estén interpolados 
cada 15 milisegundos.


-------------------------
2. Detección de Pitch
-------------------------

Para cada fichero .wav, su programa debe calcular un fichero con extensión 
.f0, con una línea por tramo de 15 milisegundos, indicando la frecuencia
fundamental en Hz. En caso que el tramo sea sordo, debe escribir el valor '0'.
(Esto es lo que en principio realiza el programa proporcionado get_pitch)

Para ejecutar su programa en todos los ficheros .wav de la base de datos 
puede utilizar un script en bash. Por ejemplo, edite y adapte el script 
run_getpitch.sh


-------------------------
3. Evaluación
-------------------------

Una vez dispone de los ficheros con el pitch detectado, (extensión .f0),
que deben estar en el mismo directorio que los ficheros de referencia,
.f0ref, puede utilizar el programa pitch_evaluate para evaluarlo, 
pasando los ficheros .f0ref que desee considerar.

Por ejemplo,
pitch_evaluate pitch_db/rl*.f0ref  (MALE Voice)
pitch_evaluate pitch_db/sb*.f0ref  (FEMALE Voice)
pitch_evaluate pitch_db/*.f0ref    (BOTH MALE & FEMALE)

Este programa calcula para cada fichero:

* Voiced frames -> unvoiced: (1 - recall voiced)
  Número de tramos sordos que han sido clasificados, erróneamente, como sonoras.

* Unvoiced frames -> voiced: (1 - recall unvoiced)
  Número de tramos sonoros que han sido clasificados, erróneamente, como sordos.

* Gross voiced errors:
  De los tramos sonoros, detectados como sonoros, 
  cuántos errores son mayores al 20%	

* MSE of fine errors:	
  De los tramos sonoros, detectados como sonoros, y con un error menos del 20%,
  el promedio de ese error.
  (En el resumen, el promedio es respecto número de ficheros)


