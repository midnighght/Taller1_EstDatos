#include <iostream>
#include "Libro.h"
using namespace std;

// Constructor
Libro::Libro(string nombre, string isbn, string autor, bool prestado, string fechaPublicacion, string resumen)
    : MaterialBibliografico(nombre, isbn, autor, prestado), fechaPublicacion(fechaPublicacion), resumen(resumen) {};

void Libro::mostrarInformacion()
{
    // Muestra los datos del material
    cout << "Titulo: " << nombre << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Autor: " << autor << endl;
    cout << "Fecha de Publicacion: " << fechaPublicacion << endl;
    cout << "Resumen: " << resumen << endl;

    if (!prestado) // Indica si el material ha sido o no prestado
    {
        cout << "Prestado: NO" << endl;
    }
    else
    {
        cout << "Prestado: SI" << endl;
    }
}

// Getters
string Libro::getFechaPublicacion()
{
    return fechaPublicacion;
}
string Libro::getResumen()
{
    return resumen;
}

// Destructor
Libro::~Libro()
{
}
