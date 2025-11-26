#ifndef PACIENTE_HPP
#define PACIENTE_HPP 
 
#include <cstring> 
 
#include <ctime> 
 
class Paciente { 
private: 
   int id; 
   char nombre[50]; 
   char apellido[50]; 
   char cedula[20]; 
   int edad; 
   char sexo; 
   char tipoSangre[5]; 
   char telefono[15]; 
   char direccion[100]; 
   char email[50]; 
   char alergias[500]; 
   char observaciones[500]; 
   bool activo; 
   int cantidadConsultas; 
   int primerConsultaID; 
   int cantidadCitas; 
   int citasIDs[20]; 
   bool eliminado; 
   time_t fechaCreacion; 
   time_t fechaModificacion; 
 
public: 
   Paciente(); 
   
   // Getters 
   int getId() const; 
   const char* getNombre() const; 
   const char* getApellido() const; 
   const char* getCedula() const; 
   int getEdad() const; 
   char getSexo() const; 
   const char* getTelefono() const; 
   const char* getEmail() const; 
   bool getEliminado() const; 
   int getCantidadCitas() const; 
   int getCantidadConsultas() const; 
   int getPrimerConsultaID() const; 
   time_t getFechaModificacion() const; 
   
   // Setters 
   void setId(int id); 
 
   void setNombre(const char* nombre); 
   void setApellido(const char* apellido); 
   void setCedula(const char* cedula); 
   void setEdad(int edad); 
   void setSexo(char sexo); 
   void setTelefono(const char* telefono); 
   void setEmail(const char* email); 
   void setEliminado(bool eliminado); 
   void setFechaModificacion(time_t tiempo); 
   void setFechaCreacion(time_t tiempo); 
   void setCantidadConsultas(int cantidad); 
   void setPrimerConsultaID(int id); 
   
   bool agregarCitaID(int citaID); 
   bool validarDatos() const; 
   static size_t obtenerTamano(); 
}; 
 
#endif 

