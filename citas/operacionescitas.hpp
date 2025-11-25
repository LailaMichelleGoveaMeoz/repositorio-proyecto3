#ifndef OPERACIONES_CITAS_HPP 
#define OPERACIONES_CITAS_HPP 
 
#include "citas.hpp" 
#include "../persistencia/constantes.hpp" 
#include "../utilidades/validaciones.hpp" 
class OperacionesCitas { 
public: 
   static bool agregarCita(Cita& nuevaCita); 
   static Cita buscarCitaPorID(int id); 
   static int buscarIndiceCitaPorID(int id); 
   static bool actualizarCita(Cita& citaModificada); 
   static bool eliminarCita(int id); 
   static bool cancelarCita(int idCita); 
   static bool atenderCita(int idCita, const char* diagnostico, const char* 
tratamiento, 
   const char* medicamentos, float costo); 
   static void listarCitasPendientes();                      
private: 
   static void mostrarError(const char* mensaje); 
   static void mostrarExito(const char* mensaje); 
}; 
 
#endif
