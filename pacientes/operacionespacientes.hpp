#ifndef operaciones_pacientes_hpp 
#define OPERACIONES_PACIENTES_HPP 
 
#include "paciente.hpp" 
#include "../persistencia/constantes.hpp" 
#include "../utilidades/validaciones.hpp" 
 
class OperacionesPacientes { 
public: 
   static bool agregarPaciente(Paciente& nuevoPaciente); 
   static Paciente buscarPacientePorID(int id); 
   static Paciente buscarPacientePorCedula(const char* cedula); 
   static bool existePacienteConCedula(const char* cedula); 
   static int buscarIndiceDeID(int id); 
   static bool actualizarPaciente(Paciente& pacienteModificado); 
   static bool eliminarPaciente(int id); 
   static void listarTodosPacientes(); 
}; 
 
#endif 
