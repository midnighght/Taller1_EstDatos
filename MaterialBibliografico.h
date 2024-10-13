#pragma once
#include <string>
#include "Usuario.h"
using namespace std;
class Usuario;

class MaterialBibliografico
{
    // Atributos de la clase
protected:
    string nombre;
    string isbn;
    string autor;
    bool prestado;
    Usuario *usuario;

    // Constructor
    MaterialBibliografico(string nombre, string isbn, string autor, bool prestado);

public:
    virtual void mostrarInformacion();

    // Getters
    string getNombre();
    string getIsbn();
    string getAutor();
    bool isPrestado();
    Usuario *getUsuario();

    // Setters
    void setNombre(string nombre);
    void setIsbn(string isbn);
    void setAutor(string autor);
    void setPrestado(bool prestado);
    void setUsuario(Usuario *usuario);

    // Destructor
    virtual ~MaterialBibliografico();
};