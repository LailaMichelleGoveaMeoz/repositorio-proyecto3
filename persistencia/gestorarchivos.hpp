#ifndef GESTOR_ARCHIVOS_HPP 
#define GESTOR_ARCHIVOS_HPP 
 
#include "../hospital/hospital.hpp" 
#include "constantes.hpp" 
#include "../pacientes/paciente.hpp" 
#include "../doctores/doctor.hpp" 
#include "../citas/citas.hpp" 
#include "../historial/historialmedico.hpp" 
#include <ctime> 
#include <iostream> 
#include <fstream> 
 
class GestorArchivos { 
public: 
   static time_t obtenerTimestamp(); 
   static void mostrarError(const char* mensaje); 
   static void mostrarExito(const char* mensaje); 
   static void pausar(); 
   static void limpiarBuffer(); 

   static bool inicializarHeader(const char* nombreArchivo); 
   static ArchivoHeader leerHeader(const char* nombreArchivo); 
   static bool actualizarHeader(const char* nombreArchivo, ArchivoHeader header);

   static bool verificarArchivo(const char* nombreArchivo); 
   static bool inicializarArchivo(const char* nombreArchivo); 
   static bool verificarIntegridadArchivos(); 

   static long getPosicionPaciente(int indice); 
   static long getPosicionDoctor(int indice); 
   static long getPosicionCita(int indice); 
   static long getPosicionHistorial(int indice); 

   static bool compactarArchivoPacientes(); 
   static bool compactarArchivoDoctores(); 
   static bool compactarArchivoCitas(); 
   static bool compactarArchivoHistoriales(); 

   static void hacerRespaldo(); 
   static void restaurarRespaldo(); 
   
   static void mostrarEstadisticas(); 
   static bool verificarIntegridadReferencial(); 
   static bool repararIntegridadReferencial(); 
   
   // M�todos para operaciones espec�ficas 
   static bool guardarHospital(const Hospital& hospital); 
   static bool cargarHospital( Hospital& hospital); 
   
private: 
   static bool compactarArchivo(const char* nombreArchivo, size_t tamanoRegistro, 
bool (*actualizarReferencias)(int[])); 
   static bool actualizarReferenciasPacientes(int mapaIDs[]); 
   static bool actualizarReferenciasEnDoctores(int mapaIDs[]); 
   static bool actualizarReferenciasEnCitas(int mapaIDs[]); 
   static bool actualizarReferenciasEnHistoriales(int mapaIDs[]); 
   static bool actualizarReferenciasDoctores(int mapaIDs[]); 
   static bool actualizarReferenciasDoctoresEnCitas(int mapaIDs[]); 
   static bool actualizarReferenciasDoctoresEnHistoriales(int mapaIDs[]); 
}; 
 
#endif
