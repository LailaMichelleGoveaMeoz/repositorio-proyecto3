#include "validaciones.hpp" 
#include <cstring> 
 
bool Validaciones::validarFecha(const char* fecha) { 
   int año, mes, dia; 
   if(strlen(fecha) != 10) return false; 
   if(fecha[4] != '-' || fecha[7] != '-') return false; 
   
 
   for(int i = 0; i < 10; i++) { 
       if (i == 4 || i == 7) continue; 
       if (fecha[i] < '0' || fecha[i] > '9') return false; 
   } 
   
   año = (fecha[0]-'0')*1000 + (fecha[1]-'0')*100 + (fecha[2]-'0')*10 + 
(fecha[3]-'0'); 
   mes = (fecha[5]-'0')*10 + (fecha[6]-'0'); 
   dia = (fecha[8]-'0')*10 + (fecha[9]-'0'); 
   
   if (año < 1900 || año > 2100) return false; 
   if (mes < 1 || mes > 12) return false; 
   if (dia < 1 || dia > 31) return false; 
   
   if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { 
       if (dia > 30) return false; 
   } else if (mes == 2) { 
       bool esBisiesto = (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0); 
       if (esBisiesto) { 
           if (dia > 29) return false; 
       } else { 
           if (dia > 28) return false; 
       } 
   } 
   return true; 
} 
 
bool Validaciones::validarHora(const char* hora) { 
   if (strlen(hora) != 5) return false; 
   if (hora[2] != ':') return false; 
   
   for (int i = 0; i < 5; i++) { 
       if (i == 2) continue; 
       if (hora[i] < '0' || hora[i] > '9') return false; 
   } 
   
   int HH = (hora[0] - '0') * 10 + (hora[1] - '0'); 
   int MM = (hora[3] - '0') * 10 + (hora[4] - '0'); 
   
   return (HH >= 0 && HH <= 23) && (MM >= 0 && MM <= 59); 
} 
 
bool Validaciones::validarCedula(const char* cedula) { 
   if (!cedula || strlen(cedula) == 0 || strlen(cedula) > 20) return false; 
   return true; 
 
} 
 
bool Validaciones::validarEmail(const char* email) { 
   if(strlen(email) == 0) return false; 
   bool tienearroba = false; 
   bool tienepunto = false; 
   for(int i = 0; email[i] != '\0'; i++) { 
       if(email[i] == '@') tienearroba = true; 
       else if(email[i] == '.' && tienearroba) tienepunto = true; 
   } 
   return tienearroba && tienepunto; 
} 
 
bool Validaciones::validarEdad(int edad) { 
   return (edad >= 0 && edad <= 120); 
} 
 
bool Validaciones::validarSexo(char sexo) { 
   return (sexo == 'M' || sexo == 'F'); 
} 
 
int Validaciones::compararFechas(const char* fecha1, const char* fecha2) { 
   for (int i = 0; i < 10; i++) { 
       if (fecha1[i] < fecha2[i]) return -1; 
       if (fecha1[i] > fecha2[i]) return 1; 
   } 
   return 0; 
} 
 
int Validaciones::mi_strcasecmp(const char* s1, const char* s2) { 
   while(*s1 && *s2) { 
       char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1; 
       char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2; 
       if(c1 != c2) return c1 - c2; 
       s1++; 
       s2++; 
   } 
   return *s1 - *s2; 
}

