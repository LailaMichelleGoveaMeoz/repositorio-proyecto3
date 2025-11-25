#include "operacioneshistorial.hpp" 
#include "../persistencia/gestorarchivos.hpp" 
#include <iostream> 
#include <fstream> 
 
using namespace std; 
 
bool OperacionesHistorial::agregarHistorial(HistorialMedico& nuevoHistorial) { 
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_HISTORIALES); 
   nuevoHistorial.setId(header.siguienteId); 
   nuevoHistorial.setFecharegistro(GestorArchivos::obtenerTimestamp()); 
   nuevoHistorial.setEliminado(false); 
   
   ofstream archivo(FILE_HISTORIALES, ios::binary | ios::app); 
   if (!archivo.is_open()) return false; 
   
   archivo.write(reinterpret_cast<const char*>(&nuevoHistorial), 
sizeof(HistorialMedico)); 
   if (archivo.fail()) { 
       archivo.close(); 
       return false; 
   } 
   
   header.cantidadRegistros++; 
   header.siguienteId++; 
   header.registrosActivos++; 
   bool exitoHeader = GestorArchivos::actualizarHeader(FILE_HISTORIALES, header); 
   archivo.close(); 
   return exitoHeader; 
} 
 
HistorialMedico OperacionesHistorial::buscarHistorialPorID(int id) { 
 
   HistorialMedico historial; 
   if (id < 1) return historial; 
   
   ArchivoHeader header = GestorArchivos::leerHeader(FILE_HISTORIALES); 
   ifstream archivo(FILE_HISTORIALES, ios::binary); 
   if (!archivo.is_open()) return historial; 
   
   archivo.seekg(sizeof(ArchivoHeader), ios::beg); 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       HistorialMedico historialActual; 
       archivo.read(reinterpret_cast<char*>(&historialActual), 
sizeof(HistorialMedico)); 
       if (archivo.fail()) break; 
       
       if (historialActual.getId() == id && !historialActual.getEliminado()) { 
           historial = historialActual; 
           break; 
       } 
   } 
   archivo.close(); 
   return historial; 
} 
