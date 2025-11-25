#include "citas.hpp" 
#include <cstring> 
 
Cita::Cita() { 
   id = 0; 
   PacienteID = -1; 
   DoctorID = -1; 
   strcpy(fecha, ""); 
   strcpy(hora, ""); 
   strcpy(motivo, ""); 
   strcpy(estado, "Agendada"); 
   strcpy(observaciones, ""); 
   atendida = false; 
   consultaID = -1; 
   eliminado = false; 
   fechaCreacion = time(0); 
   fechaModificacion = time(0); 
} 
 
// Getters 
int Cita::getId() const { return id; } 
int Cita::getPacienteID() const { return PacienteID; } 
int Cita::getDoctorID() const { return DoctorID; } 
const char* Cita::getFecha() const { return fecha; } 
const char* Cita::getHora() const { return hora; } 
const char* Cita::getEstado() const { return estado; } 
bool Cita::getAtendida() const { return atendida; } 
bool Cita::getEliminado() const { return eliminado; } 
const char* Cita::getDiagnostico() const { return diagnostico; } 
const char* Cita::getTratamiento() const { return tratamiento; } 
const char* Cita::getMedicamentos() const { return medicamentos; } 
const char* Cita::getMotivo() const { return motivo; } 
time_t Cita::getFechaCreacion() const { return fechaCreacion; } 
float Cita::getCosto() const { return costo; } 
time_t Cita::getFechaModificacion() const { return fechaModificacion; } 
 
// Setters 
void Cita::setId(int id) { this->id = id; } 
void Cita::setPacienteID(int id) { PacienteID = id; } 
void Cita::setDoctorID(int id) { DoctorID = id; } 
void Cita::setFecha(const char* fecha) { strncpy(this->fecha, fecha, 10); 
this->fecha[10] = '\0'; } 
void Cita::setHora(const char* hora) { strncpy(this->hora, hora, 5); this->hora[5] 
= '\0'; } 
void Cita::setMotivo(const char* motivo) { strncpy(this->motivo, motivo, 149); 
this->motivo[149] = '\0'; } 
void Cita::setEstado(const char* estado) { strncpy(this->estado, estado, 19); 
this->estado[19] = '\0'; } 
void Cita::setAtendida(bool atendida) { this->atendida = atendida; } 
void Cita::setEliminado(bool elim) { eliminado = elim; } 
void Cita::setFechaModificacion(time_t tiempo) { fechaModificacion = tiempo; } 
void Cita::setConsultaID(int id) { consultaID = id; } 
void Cita::setDiagnostico(const char* diagnostico) { strncpy(this->diagnostico, 
diagnostico, 99); this->diagnostico[99] = '\0'; } 
void Cita::setTratamiento(const char* tratamiento) { strncpy(this->tratamiento, 
tratamiento, 99); this->tratamiento[99] = '\0'; } 
void Cita::setMedicamentos(const char* medicamentos) { strncpy(this->medicamentos, 
medicamentos, 99); this->medicamentos[99] = '\0'; } 
void Cita::setFechaCreacion(time_t tiempo) { fechaCreacion = tiempo; } 
void Cita::setCosto(float costo) { this->costo = costo; } 
 
bool Cita::validarDatos() const { 
   return PacienteID > 0 && DoctorID > 0 && strlen(fecha) > 0 && strlen(hora) > 0; 
} 
 
size_t Cita::obtenerTamano() { return sizeof(Cita); } 
