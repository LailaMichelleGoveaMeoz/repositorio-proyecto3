#ifndef VALIDACIONES_HPP 
#define VALIDACIONES_HPP 
 
class Validaciones { 
 
public: 
   static bool validarFecha(const char* fecha); 
   static bool validarHora(const char* hora); 
   static bool validarCedula(const char* cedula); 
   static bool validarEmail(const char* email); 
   static bool validarEdad(int edad); 
   static bool validarSexo(char sexo); 
   static int compararFechas(const char* fecha1, const char* fecha2); 
   static int mi_strcasecmp(const char* s1, const char* s2); 
}; 
 
#endif 
