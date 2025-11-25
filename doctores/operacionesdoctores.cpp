#include "operacionesdoctores.hpp" 
#include "../persistencia/gestorarchivos.hpp" 
#include "../utilidades/validaciones.hpp" 
#include <iostream> 
#include <fstream> 
#include <iomanip> 
 
using namespace std; 
 
bool OperacionesDoctores::agregarDoctor(Doctor& nuevoDoctor) { 
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES); 
   nuevoDoctor.setId(header.siguienteId); 
   nuevoDoctor.setFechaCreacion(GestorArchivos::obtenerTimestamp()); 
   nuevoDoctor.setFechaModificacion(GestorArchivos::obtenerTimestamp()); 
   nuevoDoctor.setEliminado(false); 
   
   ofstream archivo(FILE_DOCTORES, ios::binary | ios::app); 
   if (!archivo.is_open()) return false; 
   
   archivo.write(reinterpret_cast<const char*>(&nuevoDoctor), sizeof(Doctor)); 
   if (archivo.fail()) { 
       archivo.close(); 
       return false; 
   } 
   
   header.cantidadRegistros++; 
 
   header.siguienteId++; 
   header.registrosActivos++; 
   bool exitoHeader = GestorArchivos::actualizarHeader(FILE_DOCTORES, header); 
   archivo.close(); 
   return exitoHeader; 
} 
 
Doctor OperacionesDoctores::buscarDoctorPorID(int id) { 
   Doctor doctor; 
   if (id < 1) return doctor; 
   
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES); 
   ifstream archivo(FILE_DOCTORES, ios::binary); 
   if (!archivo.is_open()) return doctor; 
   
   archivo.seekg(sizeof(ArchivoHeader), ios::beg); 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       Doctor doctorActual; 
       archivo.read(reinterpret_cast<char*>(&doctorActual), sizeof(Doctor)); 
       if (archivo.fail()) break; 
       
       if (doctorActual.getId() == id && !doctorActual.getEliminado()) { 
           doctor = doctorActual; 
           break; 
       } 
   } 
   archivo.close(); 
   return doctor; 
} 
 
int OperacionesDoctores::buscarIndiceDoctorPorID(int id) { 
   ifstream archivo(FILE_DOCTORES, ios::binary); 
   if (!archivo.is_open()) return -1; 
   
   ArchivoHeader header; 
   archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader)); 
   Doctor temp; 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       archivo.read(reinterpret_cast<char*>(&temp), sizeof(Doctor)); 
       if (temp.getId() == id && !temp.getEliminado()) { 
           archivo.close(); 
           return i; 
       } 
   } 
   archivo.close(); 
 
   return -1; 
} 
 
bool OperacionesDoctores::actualizarDoctor(Doctor& doctorModificado) { 
   int indice = buscarIndiceDoctorPorID(doctorModificado.getId()); 
   if (indice == -1) return false; 
   
   fstream archivo(FILE_DOCTORES, ios::binary | ios::in | ios::out); 
   if (!archivo.is_open()) return false; 
   
   long posicion = GestorArchivos::getPosicionDoctor(indice); 
   archivo.seekp(posicion); 
   doctorModificado.setFechaModificacion(GestorArchivos::obtenerTimestamp()); 
   archivo.write(reinterpret_cast<const char*>(&doctorModificado), sizeof(Doctor)); 
   bool exito = !archivo.fail(); 
   archivo.close(); 
   return exito; 
} 
 
bool OperacionesDoctores::eliminarDoctor(int id) { 
   int indice = buscarIndiceDoctorPorID(id); 
   if (indice == -1) return false; 
   
   fstream archivo(FILE_DOCTORES, ios::binary | ios::in | ios::out); 
   if (!archivo.is_open()) return false; 
   
   long posicion = GestorArchivos::getPosicionDoctor(indice); 
   archivo.seekg(posicion); 
   Doctor doctor; 
   archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor)); 
   if (archivo.fail()) { 
       archivo.close(); 
       return false; 
   } 
   
   if (doctor.getEliminado()) { 
       archivo.close(); 
       return false; 
   } 
   
   doctor.setEliminado(true); 
   doctor.setFechaModificacion(time(0)); 
   doctor.setDisponible(false); 
   
   archivo.seekp(posicion); 
 
   archivo.write(reinterpret_cast<const char*>(&doctor), sizeof(Doctor)); 
   
   if (archivo.fail()) { 
       archivo.close(); 
       return false; 
   } 
   
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES); 
   header.registrosActivos--; 
   if (!GestorArchivos::actualizarHeader(FILE_DOCTORES, header)) { 
       archivo.close(); 
       return false; 
   } 
   
   archivo.close(); 
   return true; 
} 
 
void OperacionesDoctores::listarTodosDoctores() { 
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES); 
   ifstream archivo(FILE_DOCTORES, ios::binary); 
   if (!archivo.is_open()) { 
       cout << "Error: No se pudo abrir archivo de doctores" << endl; 
       return; 
   } 
   
   archivo.seekg(sizeof(ArchivoHeader)); 
   int doctoresActivos = 0; 
   Doctor doctor; 
   
   cout << 
"\n+--------------------------------------------------------------------------+" << 
endl; 
   cout << "� ID  � NOMBRE COMPLETO       � ESPECIALIDAD   � A�OS EXP.    � COSTO      �" << endl; 
   cout << 
"�-----+-----------------------+----------------+--------------+------------�" << 
endl; 
 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor)); 
       if (archivo.fail()) break; 
       
       if (!doctor.getEliminado()) { 
           doctoresActivos++; 
 
           
           char nombreCompleto[100]; 
           snprintf(nombreCompleto, sizeof(nombreCompleto), "%s %s", 
                    doctor.getNombre(), doctor.getApellido()); 
           
           if (strlen(nombreCompleto) > 21) { 
               nombreCompleto[18] = '.'; 
               nombreCompleto[19] = '.'; 
               nombreCompleto[20] = '.'; 
               nombreCompleto[21] = '\0'; 
           } 
 
           cout << "� " << setw(3) << left << doctor.getId() << " "; 
           cout << "� " << setw(21) << left << nombreCompleto << " "; 
           cout << "� " << setw(14) << left << doctor.getEspecialidad() << " "; 
           cout << "� " << setw(12) << left << doctor.getAniosExperiencia() << " "; 
           cout << "� $" << setw(8) << left << fixed << setprecision(2) << 
doctor.getCostoConsulta() << "�" << endl; 
       } 
   } 
 
   if (doctoresActivos == 0) { 
       cout << "�                     NO HAY DOCTORES REGISTRADOS                      �" << endl; 
   } 
 
   cout << 
"+--------------------------------------------------------------------------+" << 
endl; 
   cout << "Total de doctores activos: " << doctoresActivos << endl; 
   archivo.close(); 
} 
 
int OperacionesDoctores::buscarDoctoresPorEspecialidad(const char* especialidad, 
Doctor resultados[], int maxResultados) { 
   int encontrados = 0; 
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES); 
   ifstream archivo(FILE_DOCTORES, ios::binary); 
   
   if (!archivo.is_open()) return 0; 
   
   archivo.seekg(sizeof(ArchivoHeader)); 
   Doctor doctor; 
   
 
   for (int i = 0; i < header.cantidadRegistros && encontrados < maxResultados; 
i++) { 
       archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor)); 
       if (archivo.fail()) break; 
       
       if (!doctor.getEliminado() && strcmp(doctor.getEspecialidad(), especialidad) 
== 0) { 
           resultados[encontrados] = doctor; 
           encontrados++; 
       } 
   } 
   
   archivo.close(); 
   return encontrados; 
} 
 
int OperacionesDoctores::obtenerDoctoresDisponibles(Doctor resultados[], int 
maxResultados) { 
   int encontrados = 0; 
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES); 
   ifstream archivo(FILE_DOCTORES, ios::binary); 
   
   if (!archivo.is_open()) return 0; 
   
   archivo.seekg(sizeof(ArchivoHeader)); 
   Doctor doctor; 
   
   for (int i = 0; i < header.cantidadRegistros && encontrados < maxResultados; 
i++) { 
       archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor)); 
       if (archivo.fail()) break; 
       
       if (!doctor.getEliminado() && doctor.getDisponible()) { 
           resultados[encontrados] = doctor; 
           encontrados++; 
       } 
   } 
   
   archivo.close(); 
   return encontrados; 
} 
 
int OperacionesDoctores::contarDoctoresActivos() { 
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES); 
   return header.registrosActivos; 
 
} 
 
bool OperacionesDoctores::existeDoctor(int id) { 
   return buscarIndiceDoctorPorID(id) != -1; 
} 
 
int OperacionesDoctores::obtenerTodosDoctores(Doctor resultados[], int 
maxResultados) { 
   int total = 0; 
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES); 
   ifstream archivo(FILE_DOCTORES, ios::binary); 
   
   if (!archivo.is_open()) return 0; 
   
   archivo.seekg(sizeof(ArchivoHeader)); 
   Doctor doctor; 
   
   for (int i = 0; i < header.cantidadRegistros && total < maxResultados; i++) { 
       archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor)); 
       if (archivo.fail()) break; 
       resultados[total] = doctor; 
       total++; 
   } 
   
   archivo.close(); 
   return total; 
} 
 
int OperacionesDoctores::buscarDoctoresPorNombre(const char* nombre, Doctor 
resultados[], int maxResultados) { 
   int encontrados = 0; 
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES); 
   ifstream archivo(FILE_DOCTORES, ios::binary); 
   
   if (!archivo.is_open()) return 0; 
   
   archivo.seekg(sizeof(ArchivoHeader)); 
   Doctor doctor; 
   
   for (int i = 0; i < header.cantidadRegistros && encontrados < maxResultados; 
i++) { 
       archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor)); 
       if (archivo.fail()) break; 
       
       if (!doctor.getEliminado()) { 
 
           char nombreDoctor[50]; 
           strcpy(nombreDoctor, doctor.getNombre()); 
           for (int j = 0; nombreDoctor[j]; j++) { 
               nombreDoctor[j] = tolower(nombreDoctor[j]); 
           } 
           
           char nombreBuscado[50]; 
           strcpy(nombreBuscado, nombre); 
           for (int j = 0; nombreBuscado[j]; j++) { 
               nombreBuscado[j] = tolower(nombreBuscado[j]); 
           } 
           
           if (strstr(nombreDoctor, nombreBuscado) != NULL) { 
               resultados[encontrados] = doctor; 
               encontrados++; 
           } 
       } 
   } 
   
   archivo.close(); 
   return encontrados; 
} 
 
void OperacionesDoctores::mostrarDoctoresArray(Doctor doctores[], int cantidad) { 
   if (cantidad == 0) { 
       cout << "No se encontraron doctores." << endl; 
       return; 
   } 
   
   cout << 
"\n+--------------------------------------------------------------------------+" << 
endl; 
   cout << "� ID  � NOMBRE COMPLETO       � ESPECIALIDAD   � A�OS EXP.    � COSTO      �" << endl; 
   cout << 
"�-----+-----------------------+----------------+--------------+------------�" << 
endl; 
 
   for (int i = 0; i < cantidad; i++) { 
       char nombreCompleto[100]; 
       snprintf(nombreCompleto, sizeof(nombreCompleto), "%s %s", 
                doctores[i].getNombre(), doctores[i].getApellido()); 
       
       if (strlen(nombreCompleto) > 21) { 
           nombreCompleto[18] = '.'; 
 
           nombreCompleto[19] = '.'; 
           nombreCompleto[20] = '.'; 
           nombreCompleto[21] = '\0'; 
       } 
 
       cout << "� " << setw(3) << left << doctores[i].getId() << " "; 
       cout << "� " << setw(21) << left << nombreCompleto << " "; 
       cout << "� " << setw(14) << left << doctores[i].getEspecialidad() << " "; 
       cout << "� " << setw(12) << left << doctores[i].getAniosExperiencia() << " "; 
       cout << "� $" << setw(8) << left << fixed << setprecision(2) << 
doctores[i].getCostoConsulta() << "�" << endl; 
   } 
   cout << 
"+--------------------------------------------------------------------------+" << 
endl; 
   cout << "Total encontrados: " << cantidad << endl; 
} 

