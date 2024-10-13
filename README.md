# Taller 1 Estructura de Datos
Integrantes: 
* Maximo Sarno Jiménez  21853202-0  maximo.sarno@alumnos.ucn.cl  C1
* Itzel Acuña Machuca   27067365-1  itzel.acuna@alumnos.ucn.cl   C1

## Resumen

Este programa es un sistema que permite gestionar los materiales, usuarios y prestamos de una biblioteca. Los materiales pueden ser de tipo Libro o Revista.

## Funciones

* Agregar materiales (libros y revistas) al sistema
* Buscar material por título o autor
* Prestar y devolver materiales a usuarios
* Gestionar usuarios (agregar, eliminar y buscar por nombre o ID)
* Listar materiales con su información

## Cómo ejecutar

1. Compilar el programa ```g++ -o main .\MaterialBibliografico.cpp .\Libro.cpp .\Revista.cpp .\Usuario.cpp .\Sistema.cpp .\main.cpp```
2. Ejecutar `main.exe`


### Notas
Al ejecutar el programa se crea un objeto de Sistema y luego se cargan los datos "AutoSave.txt"

Al cerrar el programa los datos se guardarán en este mismo save, pero tambien se pueden guardar y cargar manualmente en "ManualSave.txt"

## Estructura de save files
`MATERIALES\n`
`tipo;nombre;ISBN;autor;estadoPrestamo;parametro1;parametro2\n`
`...\n`
`USUARIOS\n`
`Nombre;ID;contadorPrestados\n`
`ISBN (si hay prestados)\n`
`...`
 