#ifndef CITA_HPP 
#define CITA_HPP 
 
#include <cstring> 
#include <ctime> 
 
class Cita { 
private: 
   int id; 
   int PacienteID; 
   int DoctorID; 
   char fecha[11]; 
   char hora[6]; 
   char motivo[150]; 
   char estado[20]; 
   char observaciones[200]; 
   bool atendida; 
   int consultaID;     
   char diagnostico[100]; 
   char tratamiento[100]; 
   char medicamentos[100]; 
float costo; 
   bool eliminado; 
   time_t fechaCreacion; 
   time_t fechaModificacion; 
 
public: 
   Cita(); 
   
   // Getters 
   int getId() const; 
   int getPacienteID() const; 
   int getDoctorID() const; 
   const char* getFecha() const; 
   const char* getHora() const; 
   const char* getEstado() const; 
   bool getAtendida() const; 
   bool getEliminado() const; 
   const char* getDiagnostico() const; 
   const char* getTratamiento() const; 
   const char* getMedicamentos() const; 
   const char* getMotivo() const; 
   time_t getFechaCreacion() const;  
   float getCosto() const; 
   time_t getFechaModificacion() const; 
   
   // Setters 
   void setId(int id); 
   void setPacienteID(int id); 
   void setDoctorID(int id); 
   void setFecha(const char* fecha); 
   void setHora(const char* hora); 
   void setMotivo(const char* motivo); 
   void setEstado(const char* estado); 
   void setAtendida(bool atendida); 
   void setEliminado(bool elim); 
   void setFechaModificacion(time_t tiempo); 
   void setConsultaID(int id); 
   void setDiagnostico(const char* diagnostico); 
   void setTratamiento(const char* tratamiento); 
   void setMedicamentos(const char* medicamentos); 
   void setFechaCreacion(time_t tiempo); 
   void setCosto(float costo); 
 
   bool validarDatos() const; 
   static size_t obtenerTamano(); 
}; 
 
#endif 
