#pragma once
#include <string>
#include "MaterialBibliografico.h"
using namespace std;
class MaterialBibliografico;

class Usuario
{
private:
//atributos de la clase
    string nombre;
    string ID;
    MaterialBibliografico *materialesPrestados[5]; // Array de punteros a MaterialBibliografico
    int contadorPrestados = 0;                         // Contador de materiales prestados

public:

    Usuario(string nombre, string ID); // Constructor

    bool prestarMaterial(MaterialBibliografico *material); //Añade un nuevo material al usuario

    bool devolverMaterial(string isbn); // Para eliminar un material de los que posee el usuario

    void mostrarMaterialesPrestados(); // Muestra en pantalla los materiales que le han sido prestados

    // Getters
    string getNombre();
    string getID();
    int getContadorPrestados();
    string getISBNs();

    // Setters
    void setNombre(string nombre);
    void setID(string ID);

    // Destructor
    ~Usuario();
};