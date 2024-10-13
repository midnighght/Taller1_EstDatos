#pragma once
#include "MaterialBibliografico.h"
using namespace std;

class Libro : public MaterialBibliografico
{
private:
    // Atributos de la clase
    string fechaPublicacion;
    string resumen;

public:
    // Constructor
    Libro(string nombre, string isbn, string autor, bool prestado, string fechaPublicacion, string resumen);

    void mostrarInformacion();

    // Getters
    string getFechaPublicacion();
    string getResumen();

    // Destructor
    ~Libro();
};
