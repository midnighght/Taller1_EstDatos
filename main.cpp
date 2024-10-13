#include <iostream>
#include "Sistema.h"

int main()
{
    Sistema *sistema = new Sistema();

    sistema->cargarDatos("AutoSave.txt");
    sistema->menu();

    return 0;
}