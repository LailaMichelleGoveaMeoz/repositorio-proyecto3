#ifndef HOSPITAL_HPP 
#define HOSPITAL_HPP 
 
#include <cstring> 
 
class Hospital { 
private: 
   char nombre[100]; 
   char direccion[150]; 
 
   char telefono[15]; 
   int siguienteIdPaciente; 
   int siguienteIdDoctor; 
   int siguienteIdCita; 
   int siguienteIdConsulta; 
   int totalPacientesRegistrados; 
   int totalDoctoresRegistrados; 
   int totalCitasAgendadas; 
   int totalConsultasRealizadas; 
 
public: 
   Hospital(); 
   Hospital(const char* nombre, const char* direccion, const char* telefono); 
   
   // Getters 
   const char* getNombre() const; 
   const char* getDireccion() const; 
   const char* getTelefono() const; 
   int getSiguienteIdPaciente() const; 
   int getSiguienteIdDoctor() const; 
   int getSiguienteIdCita() const; 
   int getSiguienteIdConsulta() const; 
   int getTotalPacientesRegistrados() const; 
   int getTotalDoctoresRegistrados() const; 
   int getTotalCitasAgendadas() const; 
   int getTotalConsultasRealizadas() const; 
   
   // Setters 
   void setNombre(const char* nombre); 
   void setDireccion(const char* direccion); 
   void setTelefono(const char* telefono); 
   
   // Generadores de IDs 
   int generarIdPaciente(); 
   int generarIdDoctor(); 
   int generarIdCita(); 
   int generarIdConsulta(); 
   
   // Incrementadores 
   void incrementarPacientesRegistrados(); 
   void incrementarDoctoresRegistrados(); 
   void incrementarCitasAgendadas(); 
   void incrementarConsultasRealizadas(); 
   
   bool validarDatos() const; 
 
   void mostrarInformacion() const; 
   void mostrarEstadisticas() const; 
   static size_t obtenerTamano(); 
}; 
 
#endif 

