#include <iostream>
#include <string>
#include <locale>

using namespace std;

// Definición de la clase SocioClub

class SocioClub
{
private:
    int NumeroSocio;
    string NombreSocio;
    string Domicilio;
    int AnoIngreso;

public:
    SocioClub() : NumeroSocio(0), NombreSocio(""), Domicilio(""), AnoIngreso(0) {}

    SocioClub(int numerosocio, const string &nombresocio, const string &domicilio, int anoingreso)
        : NumeroSocio(numerosocio), NombreSocio(nombresocio), Domicilio(domicilio), AnoIngreso(anoingreso) {}

    int getNumeroSocio() const
    {
        return NumeroSocio;
    }

    string getNombreSocio() const
    {
        return NombreSocio;
    }

    string getDomicilio() const
    {
        return Domicilio;
    }

    void imprimir() const
    {
        cout << "\tNúmero de socio: " << NumeroSocio << endl;
        cout << "\tNombre: " << NombreSocio << endl;
        cout << "\tDomicilio: " << Domicilio << endl;
        cout << "\tAño de ingreso: " << AnoIngreso << endl;
        cout << "\t-------------------------\n" << endl;
    }

    // Sobrecarga del operador <
    bool operator<(const SocioClub &socio) const
    {
        return NumeroSocio < socio.NumeroSocio;
    }

    // Sobrecarga del operador ==
    bool operator==(const SocioClub &socio) const
    {
        return NumeroSocio == socio.NumeroSocio;
    }
};

// Clase lista simplemente ligada (LSLSE) para manejar objetos de tipo SocioClub
template<class T>
class LSLSE
{
private:


public:
    LSLSE() : lista(nullptr) {}

    struct node
    {
        T data;
        node* sig;
    };
    node* lista;

    bool vacia() const
    {
        return lista == nullptr;
    }

    void insertar(T elem)
    {
        node* nuevo = new node;
        nuevo->data = elem;

        if (vacia() || elem < lista->data)
        {
            nuevo->sig = lista;
            lista = nuevo;
        }
        else
        {
            node* actual = lista;
            while (actual->sig != nullptr && !(elem < actual->sig->data))
            {
                actual = actual->sig;
            }
            nuevo->sig = actual->sig;
            actual->sig = nuevo;
        }
    }

    bool eliminar(int numerosocio)
    {
        if (vacia())
        {
            return false;
        }

        node* actual = lista;
        node* anterior = nullptr;

        while (actual != nullptr && actual->data.getNumeroSocio() != numerosocio)
        {
            anterior = actual;
            actual = actual->sig;
        }

        if (actual == nullptr)
        {
            return false;
        }

        if (anterior == nullptr)
        {
            lista = actual->sig;
        }
        else
        {
            anterior->sig = actual->sig;
        }

        delete actual;
        return true;
    }

    void imprimir() const
    {
        node* actual = lista;
        while (actual != nullptr)
        {
            actual->data.imprimir();
            actual = actual->sig;
        }
    }

    node* getLista() const
    {
        return lista;
    }
};

int main()
{
    LSLSE<SocioClub> listaSocios;
    int opc;

    do
    {
        setlocale(LC_ALL,"");
        cout << "\t------------MENÚ - LISTA DINÁMICA (SOCIO CLUB)------------\n" << endl;
        cout << "\t1. Registrar un nuevo socio." << endl;
        cout << "\t2. Dar de baja un socio del club." << endl;
        cout << "\t3. Generar un reporte con los datos de todos los socios." << endl;
        cout << "\t4. Buscar por nombre y domicilio a un socio del club." << endl;
        cout << "\t5. Calcular e imprimir el total de socios registrados." << endl;
        cout << "\t6. Salir\n" << endl;
        cout << "\tIngrese una opción: ";
        cin >> opc;

        switch (opc)
        {
        case 1:
        {
            int numerosocio, anoingreso;
            string nombresocio, domicilio;
            cout << "\n\tIngrese el número de socio: ";
            cin >> numerosocio;
            cout << "\tIngrese el nombre del socio: ";
            cin.ignore();
            getline(cin, nombresocio);
            cout << "\tIngrese el domicilio del socio: ";
            getline(cin, domicilio);
            cout << "\tIngrese el año de ingreso: ";
            cin >> anoingreso;

            SocioClub nuevoSocio(numerosocio, nombresocio, domicilio, anoingreso);
            listaSocios.insertar(nuevoSocio);
            cout << "\n\t¡Se agregó el socio con éxito!\n" << endl;
            break;
        }
        case 2:
        {
            int numerosocio;
            cout << "\n\tIngrese el número del socio a dar de baja: ";
            cin >> numerosocio;

            if (listaSocios.eliminar(numerosocio))
            {
                cout << "\n\t¡Se eliminó el socio con éxito!\n" << endl;
            }
            else
            {
                cout << "\n\tNo se pudo eliminar el socio.\n" << endl;
            }
            break;
        }
        case 3: //reporte
        {
            if (listaSocios.vacia())
            {
                cout << "\n\tNo hay socios en la lista, no se puede generar el reporte.\n" << endl;
            }
            else
            {
                cout << "\n\tGenerando reporte..." << endl;
                cout << "\n\t----------------DATOS DE TODOS LOS SOCIOS----------------\n" << endl;
                listaSocios.imprimir();
            }
            break;
        }

        case 4:
        {
            string nombreBuscado, domicilioBuscado;
            cout << "\n\tIngrese el nombre del socio a buscar: ";
            cin.ignore();
            getline(cin, nombreBuscado);
            cout << "\tIngrese el domicilio del socio a buscar: ";
            getline(cin, domicilioBuscado);

            bool encontrado = false;
            typename LSLSE<SocioClub>::node* actual = listaSocios.getLista();
            while (actual != nullptr)
            {
                if (actual->data.getNombreSocio() == nombreBuscado && actual->data.getDomicilio() == domicilioBuscado)
                {
                    actual->data.imprimir();
                    encontrado = true;
                }
                actual = actual->sig;
            }

            if (!encontrado)
            {
                cout << "\n\tNo se encontró ningún socio con ese nombre y domicilio.\n" << endl;
            }
            break;
        }
        case 5:
        {
            int totalSocios = 0;
            typename LSLSE<SocioClub>::node* actual = listaSocios.getLista();
            while (actual != nullptr)
            {
                totalSocios++;
                actual = actual->sig;
            }
            cout << "\n\tEl total de socios registrados es: " << totalSocios << endl << endl;
            break;
        }
        }
    }
    while (opc != 6);

    return 0;
}
