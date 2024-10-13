#include <iostream>
#include "Usuario.h"
using namespace std;

// Constructor
Usuario::Usuario(string nombre, string ID)
{
    this->nombre = nombre;
    this->ID = ID;
}

bool Usuario::prestarMaterial(MaterialBibliografico *material)
{
    cout <<1;
    // Verificar si el usuario ya tiene 5 materiales prestados
    if (contadorPrestados >= 5)
    {
        cout << "El usuario ha alcanzado el limite de materiales prestados." << endl;
        return false;
    }
    cout <<2;

    // Verificar si el material ya esta prestado
    if (material->isPrestado())
    {
        cout << "El material ya esta prestado." << endl;
        return false;
    }
    cout <<3;
    // Prestar el material
    materialesPrestados[contadorPrestados] = material; // Agregar el material al array
    material->setPrestado(true);
    material->setUsuario(this);                       // Marcar el material como prestado
    contadorPrestados++;                               // Incrementar el contador de materiales prestados
    cout << "Material con ISBN: " << material->getIsbn() << " prestado con exito." << endl;
    return true;
}

bool Usuario::devolverMaterial(string isbn) // Elimina un puntero de material que posee el usuario 
{
    for (int i = 0; i < contadorPrestados; ++i) // Recorre el array de punteros de materiales prestados
    {
        if (materialesPrestados[i] != nullptr && materialesPrestados[i]->getIsbn() == isbn)
        {
            // Marcar el material como devuelto
            materialesPrestados[i]->setPrestado(false);
            cout << "Material con ISBN: " << isbn << " devuelto con exito." << endl;

            // Remover el material del array desplazando el resto de los elementos
            for (int j = i; j < contadorPrestados - 1; ++j)
            {
                materialesPrestados[j] = materialesPrestados[j + 1];
            }
            materialesPrestados[contadorPrestados - 1] = nullptr; // Limpiar el ultimo elemento
            contadorPrestados--;                                  // Decrementar el contador de materiales prestados
            return true;
        }
    }

    // Si el material no fue encontrado
    cout << "Material con ISBN " << isbn << " no encontrado entre los materiales prestados." << endl;
    return false;
}

void Usuario::mostrarMaterialesPrestados() //Muestra el material que posee el usuario en pantalla
{
    if (contadorPrestados == 0) //Muestra en pantalla si el usuario no posee ningún material
    {
        cout << "No hay materiales prestados." << endl;
        return;
    }

    cout << "Materiales prestados a " << nombre << " (ID: " << ID << "):" << endl;
    for (int i = 0; i < contadorPrestados; ++i) // Cuenta la cantidad de materiales prestados
    {
        if (materialesPrestados[i] != nullptr)
        {
            materialesPrestados[i]->mostrarInformacion(); // Muestra informacion sobre los materiales que han sido prestados al usuario
        }
    }
}

// Getters
string Usuario::getNombre()
{
    return nombre;
}

string Usuario::getID()
{
    return ID;
}

int Usuario::getContadorPrestados()
{
    return contadorPrestados;
}

string Usuario::getISBNs() {
    string ISBNs = materialesPrestados[0]->getIsbn();
    for (int i = 1; i < contadorPrestados; i++)
        {
            ISBNs += "\n" + materialesPrestados[i]->getIsbn();
        }
    return ISBNs;
}

// Setters
void Usuario::setNombre(string nombre)
{
    this->nombre = nombre;
}

void Usuario::setID(string ID)
{
    this->ID = ID;
}

//Destructor
Usuario::~Usuario()
{
}