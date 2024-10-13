#pragma once
#include "MaterialBibliografico.h"
using namespace std;

class Revista : public MaterialBibliografico
{
private:
    // atributos de la clase
    string numeroEdicion;
    string mesPublicacion;

public:
    // constructor 
    Revista(string nombre, string isbn, string autor, bool prestado, string numeroEdicion, string mesPublicacion);

    void mostrarInformacion();

    // Getters
    string getNumeroEdicion();
    string getMesPublicacion();

    // Destructor
    ~Revista();
};