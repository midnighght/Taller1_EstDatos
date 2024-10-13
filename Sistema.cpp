#include <iostream>
#include <fstream>
#include <sstream>
#include "Sistema.h"

// Metodos para gestionar materiales
bool Sistema::agregarMaterial(MaterialBibliografico *material)
{
    if (contadorMateriales < MAX_MATERIALES) // Verificar que no se exceda el max de materiales
    {
        materiales[contadorMateriales] = material; // Agregar el material al final del array
        contadorMateriales++;                      // Actualizar contador de materiales
        cout << "Material agregado con exito." << endl;
        return true;
    }
    else
    {
        cout << "Error: Se alcanzo el limite maximo de materiales." << endl;
        return false;
    }
}

void Sistema::mostrarMateriales()
{
    for (int i = 0; i < contadorMateriales; i++) // Recorrer el array de materiales
    {
        if (materiales[i] != nullptr)
        {
            cout << "\n";
            materiales[i]->mostrarInformacion(); // Mostrar la informacion de cada material
        }
    }
}

MaterialBibliografico *Sistema::buscarMaterial(string criterio)
{
    for (MaterialBibliografico *material : materiales) // Recorrer el array de materiales
    {
        if (material->getNombre() == criterio || material->getAutor() == criterio) // Verificar si el ISBN o el nombre concuerdan
        {
            return material; // Retornar el material
        }
    }
    return nullptr;
}

bool Sistema::prestarMaterial(string isbn, Usuario *usuario)
{
    MaterialBibliografico *material = buscarMaterial(isbn); // Buscar el material por su ISBN

    if (material == nullptr) // Verificar si el material fue encontrado
    {
        cout << "Material no encontrado." << endl;
        return false;
    }

    if (material->isPrestado()) // Verificar si el material ya fue prestado
    {
        cout << "El material ya esta prestado." << endl;
        return false;
    }
    else
    {
        return usuario->prestarMaterial(material); // Intentar prestar el material desde el usuario
    }
}

bool Sistema::devolverMaterial(string isbn, Usuario *usuario)
{
    MaterialBibliografico *material = buscarMaterial(isbn); // Buscar el material por su ISBN

    if (material == nullptr) // Verificar si el material fue encontrado
    {
        cout << "Material no encontrado." << endl;
        return false;
    }

    if (!material->isPrestado()) // Verificar si el material ya fue prestado
    {
        cout << "El material no esta prestado." << endl;
        return false;
    }

    if (usuario->devolverMaterial(isbn)) // Intentar devolver el material desde el usuario
    {
        material->setPrestado(false);  // Marcar el material como no prestado
        material->setUsuario(nullptr); // Eliminar el usuario asignado al material
        return true;
    }
    else
    {
        cout << "El usuario no tiene este material prestado." << endl;
        return false;
    }
}

// Metodos para gestionar usuarios
bool Sistema::agregarUsuario(Usuario *usuario)
{
    if (usuarios.size() < MAX_USUARIOS) // Verificar que no se exceda el max de usuarios
    {
        this->usuarios.push_back(usuario); // Añadir el puntero al vector
        return true;                       //
    }
    else
    {
        cout << "Error: Se alcanzo el limite maximo de usuarios." << endl;
        return false; //
    }
}

Usuario *Sistema::buscarUsuario(string criterio)
{
    for (Usuario *usuario : usuarios) // Recorrer el vector de punteros
    {
        if (usuario->getID() == criterio || usuario->getNombre() == criterio) // Verificar si la ID o el nombre concuerdan
        {
            return usuario; // Retornar el puntero
        }
    }
    return nullptr;
}

void Sistema::eliminarUsuario(string ID)
{
    Usuario *usuario = buscarUsuario(ID);
    if (usuario != nullptr)
    {
        // Si se encontró el usuario, buscarlo en el vector y eliminarlo
        for (auto it = usuarios.begin(); it != usuarios.end(); ++it)
        {
            if (*it == usuario)
            {
                delete *it;         // Eliminar el objeto Usuario de memoria
                usuarios.erase(it); // Eliminar el puntero del vector
                cout << "Usuario ID: " << ID << " eliminado." << endl;
                return;
            }
        }
    }
    else
    {
        cout << "Usuario con ID o nombre " << ID << " no encontrado." << endl;
    }
}

// Metodos para gestionar datos
string getMaterialType(MaterialBibliografico *material) // Identifica y devuelve el tipo de material
{
    if (dynamic_cast<Libro *>(material))
    {
        return "Libro";
    }
    else if (dynamic_cast<Revista *>(material))
    {
        return "Revista";
    }
}

void Sistema::guardarDatos(string filename)
{
    ofstream file(filename);

    // Guardar materiales
    file << "MATERIALES" << endl;

    for (int i = 0; i < contadorMateriales; i++) // Recorrer el array de materiales
    {
        MaterialBibliografico *material = materiales[i];
        if (getMaterialType(material) == "Libro")
        {
            file << "Libro;" << material->getNombre() << ";" << material->getIsbn() << ";"
                 << material->getAutor() << ";" << material->isPrestado() << ";"
                 << dynamic_cast<Libro *>(material)->getFechaPublicacion() << ";"
                 << dynamic_cast<Libro *>(material)->getResumen() << endl;
        }
        else
        {
            file << "Revista;" << material->getNombre() << ";" << material->getIsbn() << ";"
                 << material->getAutor() << ";" << material->isPrestado() << ";"
                 << dynamic_cast<Revista *>(material)->getNumeroEdicion() << ";"
                 << dynamic_cast<Revista *>(material)->getMesPublicacion() << endl;
        }
    }

    // Guardar usuarios
    file << "USUARIOS" << endl;
    for (Usuario *usuario : usuarios)
    {
        file << usuario->getNombre() << ";" << usuario->getID() << ";" << usuario->getContadorPrestados() << endl;
        if (usuario->getContadorPrestados() != 0)
        {
            file << usuario->getISBNs() << endl;
        }
    }
    file.close();
}

void Sistema::cargarDatos(string filename)
{
    string line;
    ifstream file(filename);
    // int nLine = 1; // Contador de linea

    getline(file, line); // Ignorar linea MATERIALES

    while (getline(file, line))
    {
        if (line != "USUARIOS")
        {
            stringstream info(line);
            string tipoMaterial, nombre, isbn, autor, prestadoStr;
            bool prestado;

            getline(info, tipoMaterial, ';');
            getline(info, nombre, ';');
            getline(info, isbn, ';');
            getline(info, autor, ';');
            getline(info, prestadoStr, ';');

            if (tipoMaterial == "Libro")
            {
                string fechaPublicacion, resumen;
                getline(info, fechaPublicacion, ';');
                getline(info, resumen, ';');

                MaterialBibliografico *libro = new Libro(nombre, isbn, autor, false, fechaPublicacion, resumen);
                this->agregarMaterial(libro);
            }
            else if (tipoMaterial == "Revista")
            {
                string numeroEdicion, mesPublicacion;
                getline(info, numeroEdicion, ';');
                getline(info, mesPublicacion, ';');

                MaterialBibliografico *revista = new Revista(nombre, isbn, autor, false, numeroEdicion, mesPublicacion);
                this->agregarMaterial(revista);
            }
        }
        else
        {
            break;
        }
    }

    while (getline(file, line))
    {
        // Leer los datos
        stringstream info(line);
        string nombre, id, contadorPrestadosStr;
        int contadorPrestados;

        getline(info, nombre, ';');
        getline(info, id, ';');
        getline(info, contadorPrestadosStr, ';');
        contadorPrestados = stoi(contadorPrestadosStr);

        // Crear y agregar el usuario
        Usuario *usuario = new Usuario(nombre, id);
        this->agregarUsuario(usuario);

        // Prestar cada material con su isbn
        if (contadorPrestados > 0)
        {
            string isbn;
            for (int i = 0; i < contadorPrestados; i++)
            {
                getline(file, isbn);
                this->prestarMaterial(isbn, usuario);
            }
        }
    
    }

    cout << "Datos cargados exitosamente" << endl;

    file.close();
}

void Sistema::eliminarDatos()
{
    // Eliminar todos los materiales
    for (int i = 0; i < contadorMateriales; i++)
    {
        delete materiales[i]; // Elimina de la memoria cada material
        materiales[i] = nullptr; // Establecer el puntero a nullptr
    }
    contadorMateriales = 0; // Reiniciar el contador de materiales

    // Eliminar todos los usuarios
    for (Usuario *usuario : usuarios)
    {
        delete usuario; // Elimina de la memoria cada usuario
    }
    usuarios.clear(); // Vacia el vector de usuarios
}

void Sistema::menu()
{
    string opcion = "";
    while (opcion != "0")
    {
        cout << "\nMenu:\n";
        cout << "1. Agregar Material\n";
        cout << "2. Listar Materiales\n";

        cout << "3. Buscar Material\n";
        cout << "4. Prestar Material\n";
        cout << "5. Devolver Material\n";

        cout << "6. Gestionar Usuarios\n";
        cout << "7. Gestionar Datos\n";

        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        getline(cin, opcion);

        if (opcion == "1")
        {
            opcion = "";
            while (opcion != "1" && opcion != "2")
            {
                cout << "\n1. Agregar Libro\n";
                cout << "2. Agregar Revista\n";
                cout << "Seleccione una opcion: ";
                getline(cin, opcion);

                if (opcion == "1")
                {
                    // Agregar Libro
                    string nombre, isbn, autor, fechaPublicacion, resumen;
                    cout << "Nombre: ";
                    getline(cin, nombre);
                    cout << "ISBN: ";
                    getline(cin, isbn);
                    cout << "Autor: ";
                    getline(cin, autor);
                    cout << "Fecha de Publicacion: ";
                    getline(cin, fechaPublicacion);
                    cout << "Resumen: ";
                    getline(cin, resumen);
                    this->agregarMaterial(new Libro(nombre, isbn, autor, false, fechaPublicacion, resumen));
                }
                else if (opcion == "2")
                {
                    // Agregar Revista
                    string nombre, isbn, autor, mesPublicacion;
                    string numeroEdicion;
                    cout << "Nombre: ";
                    getline(cin, nombre);
                    cout << "ISBN: ";
                    getline(cin, isbn);
                    cout << "Autor: ";
                    getline(cin, autor);
                    cout << "Numero de Edicion: ";
                    getline(cin, numeroEdicion);
                    cout << "Mes de Publicacion: ";
                    getline(cin, mesPublicacion);
                    this->agregarMaterial(new Revista(nombre, isbn, autor, false, numeroEdicion, mesPublicacion));
                }
                else
                {
                    cout << "Opcion no valida. Intente de nuevo." << endl;
                }
            }
        }
        else if (opcion == "2")
        {
            this->mostrarMateriales();
        }
        else if (opcion == "3")
        {
            // Buscar Material
            string criterio;
            cout << "Ingrese titulo o autor: ";
            getline(cin, criterio);

            MaterialBibliografico *material = this->buscarMaterial(criterio);
            if (material)
            {
                material->mostrarInformacion();
            }
            else
            {
                cout << "Material no encontrado." << endl;
            }
        }
        else if (opcion == "4")
        {
            // Prestar Material
            string userID, isbn;
            cout << "Ingrese el ID del usuario: ";
            getline(cin, userID);
            cout << "Ingrese el ISBN del material: ";
            getline(cin, isbn);
            Usuario *usuario = this->buscarUsuario(userID);
            if (usuario != nullptr)
            {
                this->prestarMaterial(isbn, usuario);
            }
            else
            {
                cout << "Usuario no encontrado." << endl;
            }
        }
        else if (opcion == "5")
        {
            // Devolver Material
            string userID, isbn;
            cout << "Ingrese el ID del usuario: ";
            getline(cin, userID);
            cout << "Ingrese el ISBN del material: ";
            getline(cin, isbn);
            Usuario *usuario = this->buscarUsuario(userID);
            if (usuario != nullptr)
            {
                this->devolverMaterial(isbn, usuario);
            }
            else
            {
                cout << "Usuario no encontrado." << endl;
            }
        }

        else if (opcion == "6")
        {
            opcion = "";
            while (opcion != "1" && opcion != "2" && opcion != "3")
            {
                cout << "\n1. Agregar Usuario\n";
                cout << "2. Buscar Usuario\n";
                cout << "3. Eliminar Usuario\n";
                cout << "Seleccione una opcion: ";
                getline(cin, opcion);

                if (opcion == "1")
                {
                    // Agregar Usuario
                    string nombre, ID;
                    cout << "Nombre: ";
                    getline(cin, nombre);
                    cout << "ID: ";
                    getline(cin, ID);
                    this->agregarUsuario(new Usuario(nombre, ID));
                }
                else if (opcion == "2")
                {
                    // Buscar Usuario
                    string criterio;
                    cout << "Ingrese el ID o nombre del usuario: ";
                    getline(cin, criterio);
                    Usuario *usuario = this->buscarUsuario(criterio);
                    if (usuario)
                    {
                        cout << "Usuario encontrado.\n";
                        cout << "Nombre: " << usuario->getNombre() << endl;
                        cout << "ID: " << usuario->getID() << endl;
                    }
                    else
                    {
                        cout << "Usuario no encontrado." << endl;
                    }
                }
                else if (opcion == "3")
                {
                    // Eliminar Usuario
                    string userID;
                    cout << "Ingrese el ID del usuario a eliminar: ";
                    getline(cin, userID);
                    this->eliminarUsuario(userID);
                }
                else
                {
                    cout << "Opcion no valida. Intente de nuevo." << endl;
                }
            }
        }

        else if (opcion == "7")
        {
            opcion = "";
            while (opcion != "1" && opcion != "2" && opcion != "3")
            {
                cout << "\n1. Guardar Estado\n";
                cout << "2. Cargar Estado\n";
                cout << "3. Eliminar Datos\n";
                cout << "Seleccione una opcion: ";
                getline(cin, opcion);

                if (opcion == "1")
                {
                    // Guardar Estado
                    string filename = "ManualSave.txt";
                    this->guardarDatos(filename);
                    cout << "Estado guardado en " << filename << endl;
                }
                else if (opcion == "2")
                {
                    // Cargar Estado
                    opcion = "";
                    while (opcion != "1" && opcion != "2")
                    {
                        cout << "\n1. Cargar guardado manual\n";
                        cout << "2. Cargar guardado automatico\n";
                        cout << "Seleccione una opcion: ";
                        getline(cin, opcion);

                        if (opcion == "1")
                        {
                            this->eliminarDatos();
                            this->cargarDatos("ManualSave.txt");
                        }
                        else if (opcion == "2")
                        {
                            this->eliminarDatos();
                            this->cargarDatos("AutoSave.txt");
                        }
                        else
                        {
                            cout << "Opcion no valida. Intente de nuevo." << endl;
                        }
                    }
                }
                else if (opcion == "3")
                {
                    this->eliminarDatos();
                    cout << "Los datos han sido eliminados." << endl;
                }
                else
                {
                    cout << "Opcion no valida. Intente de nuevo." << endl;
                }
            }
        }
        else if (opcion == "0")
        {
            this->guardarDatos("AutoSave.txt");
            cout << "Saliendo del sistema." << endl;
        }
        else
        {
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }
}

Sistema::~Sistema() // Destructor
{
}