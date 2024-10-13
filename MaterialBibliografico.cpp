#include <iostream>
#include "MaterialBibliografico.h"

//constructor 
MaterialBibliografico::MaterialBibliografico(string nombre, string isbn, string autor, bool prestado)
{
    this->nombre = nombre;
    this->isbn = isbn;
    this->autor = autor;
    this->prestado = prestado;
}

void MaterialBibliografico::mostrarInformacion()
// Muestra en pantalla los datos del material bibliografico solicitado
{
    cout << "Nombre: " << nombre << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Autor: " << autor << endl;
    if (!prestado) // Muestra si el material está prestado o no
    {
        cout << "Prestado: NO" << endl;
    } 
    else
    {
        cout << "Prestado: SI" << endl;
    }
}

//Getters
string MaterialBibliografico::getNombre()
{
    return nombre;
}

string MaterialBibliografico::getIsbn()
{
    return isbn;
}

string MaterialBibliografico::getAutor()
{
    return autor;
}

bool MaterialBibliografico::isPrestado()
{
    return prestado;
}

Usuario *MaterialBibliografico::getUsuario()
{
    return usuario;
}

// Setters
void MaterialBibliografico::setNombre(string nombre)
{
    this->nombre = nombre;
}

void MaterialBibliografico::setIsbn(string isbn)
{
    this->isbn = isbn;
}

void MaterialBibliografico::setAutor(string autor)
{
    this->autor = autor;
}

void MaterialBibliografico::setPrestado(bool prestado)
{
    this->prestado = prestado;
}

void MaterialBibliografico::setUsuario(Usuario *usuario)
{
    this->usuario = usuario;
}

//destructor
MaterialBibliografico::~MaterialBibliografico()
{

}
