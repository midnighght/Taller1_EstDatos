#pragma once
#include <string>
#include <vector>
#include "MaterialBibliografico.h"
#include "Libro.h"
#include "Revista.h"
#include "Usuario.h"
using namespace std;

class Sistema
{
private:
    MaterialBibliografico *materiales[100];
    int contadorMateriales = 0;
    vector<Usuario *> usuarios;     // Vector para almacenar usuarios
    const int MAX_MATERIALES = 100; // Máximo de materiales en la biblioteca
    const int MAX_USUARIOS = 50;    // Máximo de usuarios en la biblioteca

public:
    // Métodos para gestionar materiales
    bool agregarMaterial(MaterialBibliografico *material);
    void mostrarMateriales();
    MaterialBibliografico *buscarMaterial(string criterio);
    bool prestarMaterial(string isbn, Usuario *usuario);
    bool devolverMaterial(string isbn, Usuario *usuario);

    // Métodos para gestionar usuarios
    bool agregarUsuario(Usuario *usuario);
    Usuario *buscarUsuario(string criterio);
    void eliminarUsuario(string ID);

    // MEtodos para gestionar datos
    void guardarDatos(string filename);
    void cargarDatos(string filename);
    void eliminarDatos();

    // Interfaz de usuario
    void menu();

    // Destructor
    ~Sistema();
};