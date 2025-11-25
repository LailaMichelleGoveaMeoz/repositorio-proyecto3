#include "operacionespacientes.hpp" 
#include "../persistencia/gestorarchivos.hpp" 
 
#include "../utilidades/validaciones.hpp" 
#include <iostream> 
#include <fstream> 
#include <iomanip> 
 
using namespace std; 
 
bool OperacionesPacientes::agregarPaciente(Paciente& nuevoPaciente) { 
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES); 
   nuevoPaciente.setId(header.siguienteId); 
   nuevoPaciente.setFechaCreacion(GestorArchivos::obtenerTimestamp()); 
   nuevoPaciente.setFechaModificacion(GestorArchivos::obtenerTimestamp()); 
   nuevoPaciente.setEliminado(false); 
   
   ofstream archivo(FILE_PACIENTES, ios::binary | ios::app); 
   if (!archivo.is_open()) return false; 
   
   archivo.write(reinterpret_cast<const char*>(&nuevoPaciente), sizeof(Paciente)); 
   if (archivo.fail()) { 
       archivo.close(); 
       return false; 
   } 
   
   header.cantidadRegistros++; 
   header.siguienteId++; 
   header.registrosActivos++; 
   bool exitoHeader = GestorArchivos::actualizarHeader(FILE_PACIENTES, header); 
   archivo.close(); 
   return exitoHeader; 
} 
 
Paciente OperacionesPacientes::buscarPacientePorID(int id) { 
   Paciente paciente; 
   if (id < 1) return paciente; 
   
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES); 
   ifstream archivo(FILE_PACIENTES, ios::binary); 
   if (!archivo.is_open()) return paciente; 
   
   archivo.seekg(sizeof(ArchivoHeader), ios::beg); 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       Paciente pacienteActual; 
       archivo.read(reinterpret_cast<char*>(&pacienteActual), sizeof(Paciente)); 
       if (archivo.fail()) break; 
       
 
       if (pacienteActual.getId() == id && !pacienteActual.getEliminado()) { 
           paciente = pacienteActual; 
           break; 
       } 
   } 
   archivo.close(); 
   return paciente; 
} 
 
Paciente OperacionesPacientes::buscarPacientePorCedula(const char* cedula) { 
   Paciente paciente; 
   if (strlen(cedula) == 0) return paciente; 
   
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES); 
   ifstream archivo(FILE_PACIENTES, ios::binary); 
   if (!archivo.is_open()) return paciente; 
   
   archivo.seekg(sizeof(ArchivoHeader), ios::beg); 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       Paciente pacienteActual; 
       archivo.read(reinterpret_cast<char*>(&pacienteActual), sizeof(Paciente)); 
       if (archivo.fail()) break; 
       
       if (Validaciones::mi_strcasecmp(pacienteActual.getCedula(), cedula) == 0 && 
!pacienteActual.getEliminado()) { 
           paciente = pacienteActual; 
           break; 
       } 
   } 
   archivo.close(); 
   return paciente; 
} 
 
bool OperacionesPacientes::existePacienteConCedula(const char* cedula) { 
   Paciente p = buscarPacientePorCedula(cedula); 
   return p.getId() != 0; 
} 
 
int OperacionesPacientes::buscarIndiceDeID(int id) { 
   ifstream archivo(FILE_PACIENTES, ios::binary); 
   if (!archivo.is_open()) return -1; 
   
   ArchivoHeader header; 
   archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader)); 
   Paciente temp; 
 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       archivo.read(reinterpret_cast<char*>(&temp), sizeof(Paciente)); 
       if (temp.getId() == id && !temp.getEliminado()) { 
           archivo.close(); 
           return i; 
       } 
   } 
   archivo.close(); 
   return -1; 
} 
 
bool OperacionesPacientes::actualizarPaciente(Paciente& pacienteModificado) { 
   int indice = buscarIndiceDeID(pacienteModificado.getId()); 
   if (indice == -1) return false; 
   
   fstream archivo(FILE_PACIENTES, ios::binary | ios::in | ios::out); 
   if (!archivo.is_open()) return false; 
   
   long posicion = GestorArchivos::getPosicionPaciente(indice); 
   archivo.seekp(posicion); 
   pacienteModificado.setFechaModificacion(GestorArchivos::obtenerTimestamp()); 
   archivo.write(reinterpret_cast<const char*>(&pacienteModificado), 
sizeof(Paciente)); 
   archivo.close(); 
   return true; 
} 
 
bool OperacionesPacientes::eliminarPaciente(int id) { 
   int indice = buscarIndiceDeID(id); 
   if (indice == -1) { 
       GestorArchivos::mostrarError("Paciente no encontrado"); 
       return false; 
   } 
   
   fstream archivo(FILE_PACIENTES, ios::binary | ios::in | ios::out); 
   if (!archivo.is_open()) { 
       GestorArchivos::mostrarError("No se pudo abrir el archivo de pacientes"); 
       return false; 
   } 
   
   long posicion = GestorArchivos::getPosicionPaciente(indice); 
   archivo.seekg(posicion); 
   Paciente paciente; 
   archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente)); 
   if (archivo.fail()) { 
 
       archivo.close(); 
       GestorArchivos::mostrarError("Error al leer el registro del paciente"); 
       return false; 
   } 
   
   if (paciente.getEliminado()) { 
       archivo.close(); 
       GestorArchivos::mostrarError("El paciente ya est� eliminado"); 
       return false; 
   } 
   
   paciente.setEliminado(true); 
   paciente.setFechaModificacion(time(0)); 
   archivo.seekp(posicion); 
   archivo.write(reinterpret_cast<const char*>(&paciente), sizeof(Paciente)); 
   
   if (archivo.fail()) { 
       archivo.close(); 
       return false; 
   } 
   
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES); 
   header.registrosActivos--; 
   if (!GestorArchivos::actualizarHeader(FILE_PACIENTES, header)) { 
       archivo.close(); 
       return false; 
   } 
   
   archivo.close(); 
   return true; 
} 
 
void OperacionesPacientes::listarTodosPacientes() { 
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES); 
    ifstream archivo(FILE_PACIENTES, ios::binary); 
    if (!archivo.is_open()) { 
        GestorArchivos::mostrarError("No se pudo abrir archivo de pacientes"); 
        return; 
    } 
    
    archivo.seekg(sizeof(ArchivoHeader)); 
    int pacientesActivos = 0; 
    Paciente paciente; 
    
    cout << "\n+------------------------------------------------------------+" << endl; 
    cout << "�                    LISTA DE PACIENTES                      �" << endl; 
    cout << "�------------------------------------------------------------�" << endl; 
    cout << "� ID  � NOMBRE COMPLETO     � C�DULA       � EDAD � CONSULTAS�" << endl; 
    cout << "�-----+---------------------+--------------+------+----------�" << endl; 

    for (int i = 0; i < header.cantidadRegistros; i++) { 
        archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente)); 
        if (archivo.fail()) break; 
        
        if (!paciente.getEliminado()) { 
            pacientesActivos++; 

            // Construcción del nombre completo con char[]
            char nombreCompleto[50];  
            strcpy(nombreCompleto, paciente.getNombre());  
            strcat(nombreCompleto, " ");  
            strcat(nombreCompleto, paciente.getApellido());  

            // Truncar si es demasiado largo
            if (strlen(nombreCompleto) > 19) { 
                char temp[20]; 
                strncpy(temp, nombreCompleto, 16); 
                temp[16] = '\0'; 
                strcat(temp, "..."); 
                strcpy(nombreCompleto, temp); 
            } 
            
            cout << "� " << setw(3) << left << paciente.getId() << " "; 
            cout << "� " << setw(19) << left << nombreCompleto << " "; 
            cout << "� " << setw(12) << left << paciente.getCedula() << " "; 
            cout << "� " << setw(4) << left << paciente.getEdad() << " "; 
            cout << "� " << setw(8) << left << paciente.getCantidadConsultas() << "�" << endl; 
        } 
    } 

    if (pacientesActivos == 0) { 
        cout << "�              NO HAY PACIENTES REGISTRADOS               �" << endl; 
    } 

    cout << "+------------------------------------------------------------+" << endl; 
    cout << "Total de pacientes activos: " << pacientesActivos << endl; 
    archivo.close(); 
}
