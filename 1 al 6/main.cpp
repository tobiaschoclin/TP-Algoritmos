#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;


struct Usuario
{
int UsuarioID;
char FechaCreacion[50];
bool Activo;
float TotalImporteCompras;
char eMail[50];
bool borrado = false;
};

struct Compra
{
int CompraID;
char FechaHora[50];
float Monto;
int UsuarioID;
int NroArticulo;
bool borrado = false;
};

struct Nodo
{
    Usuario info;
    Compra info2;
    Nodo *sgte;
};

void cargarUsuario(Usuario &u)
{
    cout << "ID: ";
    cin >> u.UsuarioID;
    fflush(stdin);
    cout << "Fecha: ";
    fgets(u.FechaCreacion, 50, stdin);
    fflush(stdin);
    cout << "Activo (1-si / 2-no): ";
    int act;
    cin >> act;
    if(act == 1)
        u.Activo = true;
    else
        u.Activo = false;
    cout << "Total compras: ";
    cin >> u.TotalImporteCompras;
    fflush(stdin);
    cout << "Correo: ";
    fgets(u.eMail, 50, stdin);
    fflush(stdin);
}

void mostrarUsuario(Usuario u)
{
    cout << "==========================" << endl;
    cout << "ID: " << u.UsuarioID << endl;
    cout << "Fecha creacion: " << u.FechaCreacion;
    cout << "Activo: ";
    if(u.Activo == true)
        cout << "Si" << endl;
    else
        cout << "No" << endl;
    cout << "Total compras: " << u.TotalImporteCompras << endl;
    cout << "Correo: " << u.eMail << endl;
    cout << "==========================" << endl;
}

void buscar_ID(int id)
{
    FILE *f;
    int encontrado = 0;
    Usuario u;
    if(f = fopen("clientes.bin", "rb"))
    {
        while(fread(&u, sizeof(Usuario), 1, f) && !encontrado)
        {
            if(u.UsuarioID == id)
            {
                encontrado = 1;
                cout << "==========================" << endl;
                cout << "ID: " << u.UsuarioID << endl;
                cout << "Fecha creacion: " << u.FechaCreacion;
                cout << "Activo: ";
                if(u.Activo == true)
                    cout << "Si" << endl;
                else
                    cout << "No" << endl;
                cout << "Total compras: " << u.TotalImporteCompras << endl;
                cout << "Correo: " << u.eMail << endl;
                cout << "==========================" << endl;

            }
        }
        fclose(f);
//        return 1;
    }
    return;
}

Usuario buscar_ID1(int id) // Devuelve el cliente
{
    FILE *f;
    int encontrado = 0;
    Usuario u;
    Usuario k;
    if(f = fopen("clientes.bin", "rb"))
    {
        while(fread(&u, sizeof(Usuario), 1, f) && !encontrado)
        {
            if(u.UsuarioID == id)
            {
                return u;
            }
        }
        fclose(f);
        }
    return k;
}


int buscar_Mail(char mail[])
{
    FILE *f;
    int encontrado =0;
    Usuario u;
    if (f=fopen("clientes.bin","rb"))
    {
        while(fread(&u,sizeof(Usuario),1,f) && !encontrado)
        {
            if (strcmp(mail, u.eMail)==0)
            {
                encontrado = 1;
                cout << "==========================" << endl;
                cout << "ID: " << u.UsuarioID << endl;
                cout << "Fecha creacion: " << u.FechaCreacion;
                cout << "Activo: ";
                if(u.Activo == true)
                    cout << "Si" << endl;
                else
                    cout << "No" << endl;
                cout << "Total compras: " << u.TotalImporteCompras << endl;
                cout << "Correo: " << u.eMail << endl;
                cout << "==========================" << endl;
            }
        }
        if (!encontrado)
            cout << "No se encontro la persona buscada" << endl;
        fclose(f);
        return 1;
    }
    return 0;
}

int borrarConID (int id)
{
    FILE *f;
    int encontrado =0;
    Usuario u;
    if (f=fopen("clientes.bin","rb+"))
    {
        while(!encontrado && fread(&u,sizeof(Usuario),1,f))
        {
            if (u.UsuarioID == id)
            {
                encontrado = 1;
                u.borrado = 1;
                fseek(f,(-1)*sizeof(Usuario), SEEK_CUR);
                fwrite(&u,sizeof(Usuario),1,f);
            }
        }
        if (!encontrado)
            cout << "No se encontro la persona a borrar." << endl;
        fclose(f);
        return 1;
    }
    return 0;
}

void borrador()
{
    FILE *faux;
    FILE *f;
    Usuario u;
    faux = fopen("auxiliar","wb");
    if (f=fopen("clientes.bin","rb+"))
    {
        while(fread(&u,sizeof(Usuario),1,f))
        {
            if (!u.borrado)
            {
                fwrite(&u, sizeof(Usuario),1,faux);
            }
        }
        fclose(f);
    }
    fclose(faux);
    if (!remove("clientes.bin"))
    {
        if(!rename("auxiliar","clientes.bin"))
            cout << "Archivo renombrado exitosamente" << endl;
        else
            cout << "No se pudo renombrar el archivo" << endl;
    }
    else
        cout << "No se pudo borrar el viejo archivo" << endl;
    return;
}

void InsertarSiguiente(Nodo *&n, Usuario x)
{
    Nodo *nuevo = new Nodo();
    nuevo -> info = x;
    if(n)
    {
        nuevo -> sgte = n -> sgte;
        n -> sgte = nuevo;
    }
    else
    {
        nuevo -> sgte = n;
        n = nuevo;
    }
    return;
}

Nodo *BuscarNodoAnterior(Nodo *inicial, Nodo *anterior_a)
{
    Nodo *p = NULL;
    if(inicial != anterior_a)
    {
        p = inicial;
        while(p && (p -> sgte != anterior_a))
        {
            p = p -> sgte;
        }
        return p;
    }
    else
        return NULL;
}

Nodo *ObtenerUltimo(Nodo *p)
{
    if(p)
    {
        while(p -> sgte)
        {
            p = p -> sgte;
        }
    }
    return p;
}

void InsertarAlFinal(Nodo *&inicial, Usuario x)
{
    Nodo *aux;
    aux = ObtenerUltimo(inicial);
    if(aux)
        InsertarSiguiente(aux, x);
    else
        InsertarSiguiente(inicial, x);
    return;
}

void InsertarPrimero(Nodo *&inicial, Usuario x)
{
    Nodo *nuevo = new Nodo();
    Nodo *aux = inicial;
    nuevo->info = x;
    inicial = nuevo;
    nuevo->sgte = aux;
    return;
}

void InsertarOrdenado(Nodo *&inicial, Usuario x)
{
    Nodo *anterior = NULL;
    Nodo *aux = inicial;
    while(aux && aux->info.TotalImporteCompras < x.TotalImporteCompras)
    {
        aux = aux->sgte;
    }
    if(aux && aux!=inicial)
    {
        anterior = BuscarNodoAnterior(inicial, aux);
        InsertarSiguiente(anterior, x);
    }
    else
    {
        if(aux == NULL)
            InsertarAlFinal(inicial, x);
        else if(aux == inicial)
            InsertarPrimero(inicial, x);
    }
    return;
}

Nodo *ObtenerSiguiente(Nodo *n)
{
    if(n)
        return n -> sgte;
    else
        return NULL;
}

void MostrarLista(Nodo *lista)
{
    while(lista)
    {
        mostrarUsuario(lista->info);
        lista = ObtenerSiguiente(lista);
    }
}

void OrdenarCompras(Usuario u)
{
    FILE *f = NULL;
    Nodo *lista = NULL;
    if(f = fopen("clientes.bin", "r"))
    {
        fread(&u, sizeof(Usuario), 1, f);
        while(!feof(f))
        {
            InsertarOrdenado(lista, u);
            fread(&u, sizeof(Usuario), 1, f);
        }
    fclose(f);
    }

    MostrarLista(lista);
    return;
}

void CargarCompra(Compra &c)
{
    cout << "ID compra: ";
    cin >> c.CompraID;
    fflush(stdin);
    cout << "Fecha: ";
    fgets(c.FechaHora, 50, stdin);
    fflush(stdin);
    cout << "Monto: ";
    cin >> c.Monto;
    fflush(stdin);
    cout << "ID usuario: ";
    cin >> c.UsuarioID;
    fflush(stdin);
    cout << "Numero de articulo: ";
    cin >> c.NroArticulo;
    fflush(stdin);
    return;
}

void MostrarCompra(Nodo *lista)
{
    while(lista)
    {
        cout << "ID Compra: " <<lista->info2.CompraID<< endl;
        cout << "Fecha y Hora: " << lista->info2.FechaHora << endl;
        cout << "Monto: " << lista->info2.Monto << endl;
        cout << "ID Usuario: " << lista->info2.UsuarioID << endl << endl;
        cout << "Nro. Articulo: " << lista->info2.NroArticulo << endl;
        lista = lista->sgte;
    }
}

void InsertarCompraEnLista (Nodo *&n, Compra x)
{
    Nodo *nuevo= new Nodo();
    nuevo->info2=x;
    if (n!=NULL)
    {
        nuevo->sgte= n->sgte;
        n->sgte = nuevo;
    }
    else
    {
        nuevo->sgte= n;
        n= nuevo;
    }

    return;
}

void InsertarUsuarioEnLista (Nodo *&n, Usuario x)
{
    Nodo *nuevo= new Nodo();
    nuevo->info=x;
    if (n!=NULL)
    {
        nuevo->sgte= n->sgte;
        n->sgte = nuevo;
    }
    else
    {
        nuevo->sgte= n;
        n= nuevo;
    }

    return;
}

void ProcesarLoteDeCompras(Usuario u, Nodo *&lotedecompras)
{
    FILE *f = NULL;
    Nodo *lista = NULL;
    // PASO 1: Leo los usuarios de clientes.bin y los meto en la lista (probado, anda bien)
    if(f = fopen("clientes.bin", "r"))
    {
        fread(&u, sizeof(Usuario), 1, f);
        while(!feof(f))
        {
            InsertarUsuarioEnLista(lista, u);
            fread(&u, sizeof(Usuario), 1, f);
        }
        fclose(f);
    }
    /* PASO 2: Voy leyendo del lote de compras. Si coincide con el ID de algun usuario de la lista actualizo sus
    gastos */
    Nodo *aux = lista;
    Nodo *auxlote = lotedecompras;
    while(auxlote)
    {
        while(aux)
        {
            if(auxlote->info2.UsuarioID == aux->info.UsuarioID)
                {
                    aux->info.TotalImporteCompras+=auxlote->info2.Monto;
                }
            aux = aux->sgte;
        }
            while(aux != lista)
        {
            aux = BuscarNodoAnterior(lista, aux);
        }
        auxlote = auxlote->sgte;
    }
    while(aux != lista)
    {
        aux = BuscarNodoAnterior(lista, aux);
    }
    MostrarLista(aux); // La lista aux tiene lo mismo que clientes.bin, pero con los montos actualizados seg�n este lote de compras

    /*PASO 3: Reescribo clientes.bin con los montos actualizados (usando la lista aux)*/

    /*PASO 4: Subo el lote de compras a procesados.bin*/
    return;
}

int main()
{
    FILE *clientes = NULL;
    FILE *comp = NULL;
    Nodo *compras = NULL;
    Usuario u;
    Compra c;
    int pos = 0;
    int tam = 0;
    int idbusq, menubusq, idborrar;
    char mailbusq[50];
    int opcion;
    do
    {
        cout << "Elija una opcion" << endl;
        cout << "1 - Mostrar los clientes del archivo Clientes.bin." << endl;
        cout << "2 - Cargar un nuevo cliente." << endl;
        cout << "3 - Desactivar un usuario existente" << endl;
        cout << "4 - Buscar un cliente por ID o por mail."<< endl;
        cout << "5 - Listar todos los clientes activos ordenados por total del importe." <<endl;
        cout << "6 - Procesar un lote de compras." <<endl;
        cout << "7 - Mostrar por pantalla todas las compras realizadas de un cliente dado (desde el archivo procesados.bin)." <<endl;
        cout << "8 - Mostrar todas las compras realizadas entre dos fechas en un reporte escrito en formato html. Tambi�n mostrar el total de las compras " <<endl;
        cout << "9 - Mostrar el mismo reporte que el punto 8 en formato CSV " <<endl;
        cout << "10 - Finalizar jornada." <<endl;
        cout << "11 - Cargar datos en Clientes.bin." <<endl;
        cout << "12 - Cargar lote de compras" << endl;
        cout << "13 - Mostrar lote de compras" << endl;

        cout << "esc - Salir" << endl;
        cin >> opcion;
        switch(opcion)
        {
            case 1:
                clientes = fopen("clientes.bin", "rb");
                if(clientes != NULL)
                {
                    while(fread(&u, sizeof(Usuario), 1, clientes))
                    {
                        mostrarUsuario(u);
                    }
                    fclose(clientes);
                }

            break;

            case 2:
                clientes = fopen("clientes.bin", "ab");
                if(clientes != NULL)
                {
                    cargarUsuario(u);
                    fwrite(&u, sizeof(Usuario), 1, clientes);
                    fclose(clientes);
                }

                break;
            case 3:
                    cout << "ID del usuario a borrar: ";
                    cin >> idborrar;
                    borrarConID(idborrar);
                    borrador();
                break;
            case 4:
                    cout << "1- Buscar por ID" << endl;
                    cout << "2- Buscar por mail" << endl;
                    cin >> menubusq;
                    if(menubusq == 1)
                    {
                        cout << "ID buscado: ";
                        cin >> idbusq;
                        buscar_ID(idbusq);
                    }
                    if(menubusq == 2)
                    {
                        cout << "Mail buscado: ";
                        fflush(stdin);
                        fgets(mailbusq, 50, stdin);
                        buscar_Mail(mailbusq);
                    }
                break;

             case 5:
                    OrdenarCompras(u);
                break;

              case 6:
                    ProcesarLoteDeCompras(u, compras);
                break;

                case 7:

                break;

               case 8:

                break;

                 case 9:

                break;

                 case 10:

                break;
                 case 12:
                    CargarCompra(c);
                    InsertarCompraEnLista(compras, c);
                break;

                 case 13:
                    MostrarCompra(compras);
                break;
        }


    }while (opcion!= 27);
    getch();
    return 0;
}