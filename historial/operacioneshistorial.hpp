#ifndef OPERACIONES_HISTORIAL_HPP 
#define OPERACIONES_HISTORIAL_HPP 
 
 
#include "historialmedico.hpp" 
#include "../persistencia/constantes.hpp" 
 
class OperacionesHistorial { 
public: 
   static bool agregarHistorial(HistorialMedico& nuevoHistorial); 
   static HistorialMedico buscarHistorialPorID(int id); 
}; 
 
#endif 
