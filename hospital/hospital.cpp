#include "hospital.hpp" 
#include <iostream> 
#include <iomanip> 
 
using namespace std; 
 
Hospital::Hospital() { 
   strcpy(nombre, "Hospital General"); 
   strcpy(direccion, ""); 
   strcpy(telefono, ""); 
   siguienteIdPaciente = 1; 
   siguienteIdDoctor = 1; 
   siguienteIdCita = 1; 
   siguienteIdConsulta = 1; 
   totalPacientesRegistrados = 0; 
   totalDoctoresRegistrados = 0; 
   totalCitasAgendadas = 0; 
   totalConsultasRealizadas = 0; 
} 
Hospital::Hospital(const char* nombre, const char* direccion, const char* telefono) 
{ 
 
   strncpy(this->nombre, nombre, 99); 
   this->nombre[99] = '\0'; 
   strncpy(this->direccion, direccion, 149); 
   this->direccion[149] = '\0'; 
   strncpy(this->telefono, telefono, 14); 
   this->telefono[14] = '\0'; 
   siguienteIdPaciente = 1; 
   siguienteIdDoctor = 1; 
   siguienteIdCita = 1; 
   siguienteIdConsulta = 1; 
   totalPacientesRegistrados = 0; 
   totalDoctoresRegistrados = 0; 
   totalCitasAgendadas = 0; 
   totalConsultasRealizadas = 0; 
} 
// Getters 
const char* Hospital::getNombre() const { return nombre; } 
const char* Hospital::getDireccion() const { return direccion; } 
const char* Hospital::getTelefono() const { return telefono; } 
int Hospital::getSiguienteIdPaciente() const { return siguienteIdPaciente; } 
int Hospital::getSiguienteIdDoctor() const { return siguienteIdDoctor; } 
int Hospital::getSiguienteIdCita() const { return siguienteIdCita; } 
int Hospital::getSiguienteIdConsulta() const { return siguienteIdConsulta; } 
int Hospital::getTotalPacientesRegistrados() const { return 
totalPacientesRegistrados; } 
int Hospital::getTotalDoctoresRegistrados() const { return 
totalDoctoresRegistrados; } 
int Hospital::getTotalCitasAgendadas() const { return totalCitasAgendadas; } 
int Hospital::getTotalConsultasRealizadas() const { return 
totalConsultasRealizadas; } 
 
// Setters 
void Hospital::setNombre(const char* nombre) { 
   strncpy(this->nombre, nombre, 99); 
   this->nombre[99] = '\0'; 
} 
 
void Hospital::setDireccion(const char* direccion) { 
   strncpy(this->direccion, direccion, 149); 
   this->direccion[149] = '\0'; 
} 
 
void Hospital::setTelefono(const char* telefono) { 
   strncpy(this->telefono, telefono, 14); 
   this->telefono[14] = '\0'; 
 
} 
 
// Generadores de IDs 
int Hospital::generarIdPaciente() { return siguienteIdPaciente++; } 
int Hospital::generarIdDoctor() { return siguienteIdDoctor++; } 
int Hospital::generarIdCita() { return siguienteIdCita++; } 
int Hospital::generarIdConsulta() { return siguienteIdConsulta++; } 
 
// Incrementadores 
void Hospital::incrementarPacientesRegistrados() { totalPacientesRegistrados++; } 
void Hospital::incrementarDoctoresRegistrados() { totalDoctoresRegistrados++; } 
void Hospital::incrementarCitasAgendadas() { totalCitasAgendadas++; } 
void Hospital::incrementarConsultasRealizadas() { totalConsultasRealizadas++; } 
 
bool Hospital::validarDatos() const { 
   return strlen(nombre) > 0 && strlen(telefono) > 0; 
} 
 
void Hospital::mostrarInformacion() const { 
   cout << "\n=== INFORMACIÓN DEL HOSPITAL ===" << endl; 
   cout << "Nombre: " << nombre << endl; 
   cout << "Dirección: " << direccion << endl; 
   cout << "Teléfono: " << telefono << endl; 
} 
 
void Hospital::mostrarEstadisticas() const { 
   cout << "\n=== ESTADÍSTICAS DEL SISTEMA ===" << endl; 
   cout << "Pacientes registrados: " << totalPacientesRegistrados << endl; 
   cout << "Doctores registrados: " << totalDoctoresRegistrados << endl; 
   cout << "Citas agendadas: " << totalCitasAgendadas << endl; 
   cout << "Consultas realizadas: " << totalConsultasRealizadas << endl; 
} 
 
size_t Hospital::obtenerTamano() { return sizeof(Hospital); }
