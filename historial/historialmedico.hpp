#ifndef HISTORIAL_MEDICO_HPP 
#define HISTORIAL_MEDICO_HPP 
 
#include <cstring> 
#include <ctime> 
 
class HistorialMedico { 
private: 
   int id; 
   int PacienteID; 
   char fecha[11]; 
   char hora[6]; 
   char diagnostico[200]; 
   char tratamiento[200]; 
 
   char medicamentos[150]; 
   int DoctorID; 
   float costo; 
   int siguienteConsultaId; 
   bool eliminado; 
   time_t fecharegistro; 
 
public: 
   HistorialMedico(); 
   
   // Getters 
   int getId() const; 
   int getPacienteID() const; 
   const char* getFecha() const; 
   const char* getHora() const; 
   const char* getDiagnostico() const; 
   const char* getTratamiento() const; 
   int getDoctorID() const; 
   float getCosto() const; 
   int getSiguienteConsultaId() const; 
   bool getEliminado() const; 
   
   // Setters 
   void setId(int id); 
   void setPacienteID(int id); 
   void setFecha(const char* fecha); 
   void setHora(const char* hora); 
   void setDiagnostico(const char* diagnostico); 
   void setTratamiento(const char* tratamiento); 
   void setMedicamentos(const char* medicamentos); 
   void setDoctorID(int id); 
   void setCosto(float costo); 
   void setSiguienteConsultaId(int id); 
   void setEliminado(bool elim); 
   void setFecharegistro(time_t tiempo); 
   
   bool validarDatos() const; 
   static size_t obtenerTamano(); 
}; 
 
#endif 
