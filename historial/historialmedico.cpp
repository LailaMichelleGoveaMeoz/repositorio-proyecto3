#include "historialmedico.hpp" 
#include <cstring> 
 
HistorialMedico::HistorialMedico() { 
   id = 0; 
   PacienteID = -1; 
   strcpy(fecha, ""); 
   strcpy(hora, ""); 
   strcpy(diagnostico, ""); 
   strcpy(tratamiento, ""); 
   strcpy(medicamentos, ""); 
   DoctorID = -1; 
   costo = 0; 
   siguienteConsultaId = -1; 
   eliminado = false; 
   fecharegistro = time(0); 
} 
 
// Getters 
int HistorialMedico::getId() const { return id; } 
int HistorialMedico::getPacienteID() const { return PacienteID; } 
const char* HistorialMedico::getFecha() const { return fecha; } 
const char* HistorialMedico::getHora() const { return hora; } 
const char* HistorialMedico::getDiagnostico() const { return diagnostico; } 
 
const char* HistorialMedico::getTratamiento() const { return tratamiento; } 
int HistorialMedico::getDoctorID() const { return DoctorID; } 
float HistorialMedico::getCosto() const { return costo; } 
int HistorialMedico::getSiguienteConsultaId() const { return siguienteConsultaId; } 
bool HistorialMedico::getEliminado() const { return eliminado; } 
 
// Setters 
void HistorialMedico::setId(int id) { this->id = id; } 
void HistorialMedico::setPacienteID(int id) { PacienteID = id; } 
void HistorialMedico::setFecha(const char* fecha) { strncpy(this->fecha, fecha, 
10); this->fecha[10] = '\0'; } 
void HistorialMedico::setHora(const char* hora) { strncpy(this->hora, hora, 5); 
this->hora[5] = '\0'; } 
void HistorialMedico::setDiagnostico(const char* diagnostico) { 
strncpy(this->diagnostico, diagnostico, 199); this->diagnostico[199] = '\0'; } 
void HistorialMedico::setTratamiento(const char* tratamiento) { 
strncpy(this->tratamiento, tratamiento, 199); this->tratamiento[199] = '\0'; } 
void HistorialMedico::setMedicamentos(const char* medicamentos) { 
strncpy(this->medicamentos, medicamentos, 149); this->medicamentos[149] = '\0'; } 
void HistorialMedico::setDoctorID(int id) { DoctorID = id; } 
void HistorialMedico::setCosto(float costo) { this->costo = costo; } 
void HistorialMedico::setSiguienteConsultaId(int id) { siguienteConsultaId = id; } 
void HistorialMedico::setEliminado(bool elim) { eliminado = elim; } 
void HistorialMedico::setFecharegistro(time_t tiempo) { fecharegistro = tiempo; } 
 
bool HistorialMedico::validarDatos() const { 
   return PacienteID > 0 && DoctorID > 0 && strlen(diagnostico) > 0 && costo >= 0; 
} 
 
size_t HistorialMedico::obtenerTamano() { return sizeof(HistorialMedico); }

