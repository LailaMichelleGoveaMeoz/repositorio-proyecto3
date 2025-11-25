#include "doctor.hpp" 
#include <cstring> 
 
Doctor::Doctor() { 
   id = 0; 
   strcpy(nombre, ""); 
   strcpy(apellido, ""); 
   strcpy(cedula, ""); 
   strcpy(especialidad, ""); 
   aniosExperiencia = 0; 
   costoConsulta = 0; 
   strcpy(horarioAtencion, ""); 
   strcpy(telefono, ""); 
   strcpy(email, ""); 
   disponible = true; 
   cantidadPacientes = 0; 
 
   cantidadCitas = 0; 
   for(int i = 0; i < 50; i++) pacientesIDs[i] = -1; 
   for(int i = 0; i < 30; i++) citasIDs[i] = -1; 
   eliminado = false; 
   fechaCreacion = time(0); 
   fechaModificacion = time(0); 
} 
 
// Getters 
int Doctor::getId() const { return id; } 
const char* Doctor::getNombre() const { return nombre; } 
const char* Doctor::getApellido() const { return apellido; } 
const char* Doctor::getEspecialidad() const { return especialidad; } 
float Doctor::getCostoConsulta() const { return costoConsulta; } 
bool Doctor::getDisponible() const { return disponible; } 
bool Doctor::getEliminado() const { return eliminado; } 
int Doctor::getCantidadPacientes() const { return cantidadPacientes; } 
int Doctor::getCantidadCitas() const { return cantidadCitas; } 
time_t Doctor::getFechaModificacion() const { return fechaModificacion; } 
int Doctor::getAniosExperiencia() const { return aniosExperiencia; } 
const char* Doctor::getTelefono() const { return telefono; } 
 
// Setters 
void Doctor::setId(int id) { this->id = id; } 
void Doctor::setNombre(const char* nombre) { strncpy(this->nombre, nombre, 49); 
this->nombre[49] = '\0'; } 
void Doctor::setApellido(const char* apellido) { strncpy(this->apellido, apellido, 
49); this->apellido[49] = '\0'; } 
void Doctor::setEspecialidad(const char* especialidad) { 
strncpy(this->especialidad, especialidad, 49); this->especialidad[49] = '\0'; } 
void Doctor::setCostoConsulta(float costo) { costoConsulta = costo; } 
void Doctor::setDisponible(bool disp) { disponible = disp; } 
void Doctor::setEliminado(bool elim) { eliminado = elim; } 
void Doctor::setFechaModificacion(time_t tiempo) { fechaModificacion = tiempo; } 
void Doctor::setFechaCreacion(time_t tiempo) { fechaCreacion = tiempo; } 
void Doctor::setAniosExperiencia(int anos) { aniosExperiencia = anos; } 
void Doctor::setTelefono(const char* telefono) { strncpy(this->telefono, telefono, 
14); this->telefono[14] = '\0'; } 
 
bool Doctor::agregarPacienteID(int pacienteID) { 
   if(cantidadPacientes < 50) { 
       pacientesIDs[cantidadPacientes] = pacienteID; 
       cantidadPacientes++; 
       return true; 
   } 
 
   return false; 
} 
 
bool Doctor::agregarCitaID(int citaID) { 
   if(cantidadCitas < 30) { 
       citasIDs[cantidadCitas] = citaID; 
       cantidadCitas++; 
       return true; 
   } 
   return false; 
} 
 
bool Doctor::actualizarPacientesIDs(int mapaIDs[]) { 
   bool modificado = false; 
   for (int i = 0; i < cantidadPacientes; i++) { 
       int idViejo = pacientesIDs[i]; 
       if (mapaIDs[idViejo] != 0) { 
           pacientesIDs[i] = mapaIDs[idViejo]; 
           modificado = true; 
       } 
   } 
   return modificado; 
} 
 
bool Doctor::validarDatos() const { 
   return strlen(nombre) > 0 && strlen(apellido) > 0 && strlen(especialidad) > 0 && 
costoConsulta >= 0; 
} 
 
size_t Doctor::obtenerTamano() { return sizeof(Doctor); }
