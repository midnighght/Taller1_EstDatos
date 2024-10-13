#include <iostream>
#include "Revista.h"
// constructor
Revista::Revista(string nombre, string isbn, string autor, bool prestado, string numeroEdicion, string mesPublicacion)
    : MaterialBibliografico(nombre, isbn, autor, prestado), numeroEdicion(numeroEdicion), mesPublicacion(mesPublicacion) {};

void Revista::mostrarInformacion()
{
    // Muestra los datos del material
    cout << "Nombre: " << nombre << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Autor: " << autor << endl;
    cout << "Numero de Edicion: " << numeroEdicion << endl;
    cout << "Mes de Publicacion: " << mesPublicacion << endl;

    if (!prestado) // Muestra si el material ha sido o no prestado
    {
        cout << "Prestado: NO" << endl;
    }
    else
    {
        cout << "Prestado: SI" << endl;
    }
}

// Getters
string Revista::getNumeroEdicion()
{
    return numeroEdicion;
}
string Revista::getMesPublicacion()
{
    return mesPublicacion;
}

// destructor
Revista::~Revista()
{
}