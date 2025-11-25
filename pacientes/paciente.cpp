#include "paciente.hpp" 
#include <cstring> 
 
Paciente::Paciente() { 
   id = 0; 
   strcpy(nombre, ""); 
   strcpy(apellido, ""); 
   strcpy(cedula, ""); 
   edad = 0; 
   sexo = ' '; 
   strcpy(tipoSangre, ""); 
   strcpy(telefono, ""); 
   strcpy(direccion, ""); 
   strcpy(email, ""); 
   strcpy(alergias, ""); 
   strcpy(observaciones, ""); 
   activo = true; 
   cantidadConsultas = 0; 
   primerConsultaID = -1; 
   cantidadCitas = 0; 
   for(int i = 0; i < 20; i++) citasIDs[i] = -1; 
   eliminado = false; 
   fechaCreacion = time(0); 
   fechaModificacion = time(0); 
} 
 
// Getters 
int Paciente::getId() const { return id; } 
const char* Paciente::getNombre() const { return nombre; } 
const char* Paciente::getApellido() const { return apellido; } 
const char* Paciente::getCedula() const { return cedula; } 
int Paciente::getEdad() const { return edad; } 
char Paciente::getSexo() const { return sexo; } 
const char* Paciente::getTelefono() const { return telefono; } 
const char* Paciente::getEmail() const { return email; } 
bool Paciente::getEliminado() const { return eliminado; } 
int Paciente::getCantidadCitas() const { return cantidadCitas; } 
int Paciente::getCantidadConsultas() const { return cantidadConsultas; } 
 
int Paciente::getPrimerConsultaID() const { return primerConsultaID; } 
time_t Paciente::getFechaModificacion() const { return fechaModificacion; } 
 
// Setters 
void Paciente::setId(int id) { this->id = id; } 
void Paciente::setNombre(const char* nombre) { strncpy(this->nombre, nombre, 49); 
this->nombre[49] = '\0'; } 
void Paciente::setApellido(const char* apellido) { strncpy(this->apellido, 
apellido, 49); this->apellido[49] = '\0'; } 
void Paciente::setCedula(const char* cedula) { strncpy(this->cedula, cedula, 19); 
this->cedula[19] = '\0'; } 
void Paciente::setEdad(int edad) { this->edad = edad; } 
void Paciente::setSexo(char sexo) { this->sexo = sexo; } 
void Paciente::setTelefono(const char* telefono) { strncpy(this->telefono, 
telefono, 14); this->telefono[14] = '\0'; } 
void Paciente::setEmail(const char* email) { strncpy(this->email, email, 49); 
this->email[49] = '\0'; } 
void Paciente::setEliminado(bool eliminado) { this->eliminado = eliminado; } 
void Paciente::setFechaModificacion(time_t tiempo) { fechaModificacion = tiempo; } 
void Paciente::setFechaCreacion(time_t tiempo) { fechaCreacion = tiempo; } 
void Paciente::setCantidadConsultas(int cantidad) { cantidadConsultas = cantidad; } 
void Paciente::setPrimerConsultaID(int id) { primerConsultaID = id; } 
 
bool Paciente::agregarCitaID(int citaID) { 
   if(cantidadCitas < 20) { 
       citasIDs[cantidadCitas] = citaID; 
       cantidadCitas++; 
       return true; 
   } 
   return false; 
} 
 
bool Paciente::validarDatos() const { 
   return strlen(nombre) > 0 && strlen(apellido) > 0 && strlen(cedula) > 0 && edad 
>= 0; 
} 
 
size_t Paciente::obtenerTamano() { return sizeof(Paciente); } 

