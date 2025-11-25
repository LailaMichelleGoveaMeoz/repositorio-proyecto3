#ifndef OPERACIONES_DOCTORES_HPP 
#define OPERACIONES_DOCTORES_HPP 
 
#include "doctor.hpp" 
#include "../persistencia/constantes.hpp" 
#include "../utilidades/validaciones.hpp" 
 
class OperacionesDoctores { 
public: 
   static bool agregarDoctor(Doctor& nuevoDoctor); 
 
   static Doctor buscarDoctorPorID(int id); 
   static int buscarIndiceDoctorPorID(int id); 
   static bool actualizarDoctor(Doctor& doctorModificado); 
   static bool eliminarDoctor(int id); 
   static void listarTodosDoctores(); 
   static int buscarDoctoresPorEspecialidad(const char* especialidad, Doctor 
resultados[], int maxResultados); 
   static int obtenerDoctoresDisponibles(Doctor resultados[], int maxResultados); 
   static int contarDoctoresActivos(); 
   static bool existeDoctor(int id); 
   static int obtenerTodosDoctores(Doctor resultados[], int maxResultados); 
   static int buscarDoctoresPorNombre(const char* nombre, Doctor resultados[], int 
maxResultados); 
   static void mostrarDoctoresArray(Doctor doctores[], int cantidad); 
}; 
 
#endif 
