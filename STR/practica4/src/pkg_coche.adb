--******************* PKG_coche.ADB **************************************
-- Paquete que implementa la generación de coches y su comportamiento
--***********************************************************************

with PKG_graficos;
with PKG_debug;
with Ada.exceptions; use Ada.exceptions;
WITH Ada.Numerics.Discrete_Random;
with PKG_Semaforo; use PKG_Semaforo;

package body PKG_coche is

   --*************************************************************************
   -- TAREA ENCARGADA DE LA GENERACIÓN DE COCHES PERIÓDICAMENTE EN EL CARRIL 1
   --*************************************************************************
   
   TASK BODY Tarea_GeneraCoches IS
      
      Tarea_coche : Ptr_Tarea_Coche;
      ptr_coche   : Ptr_T_RecordCoche;
      
      -- Creación de paquete para generar un color aleatorio
      PACKAGE Pkg_ColorCoche_Aleatorio
                is new Ada.Numerics.Discrete_Random(T_ColorCoche);
      Generador_ColorCoche: Pkg_ColorCoche_Aleatorio.Generator;
      colorCoche : T_ColorCoche;
      
      -- Creación de paquete para generar coches aleatoriamente
      Package Pkg_RetardoCoches_Aleatorios
                is new Ada.Numerics.Discrete_Random(T_RetardoCoches);
      Generador_Coches: Pkg_RetardoCoches_Aleatorios.Generator;
      retardoCoche : T_RetardoCoches;
      
      -- Creación de paquete para generar velocidades aleatorias iniciales de los coches
      Package Pkg_Velocidad_Aleatoria
                is new Ada.Numerics.Discrete_Random(T_RangoVelocidadAparicion);
      Generador_VelocidadApCoche: Pkg_Velocidad_Aleatoria.Generator;
      velocidadApCoche : T_RangoVelocidadAparicion;
      
      idCoche : T_IdCoche;
      idCarril : T_Carril;
      
      BEGIN
      PKG_debug.Escribir("======================INICIO TASK GeneraCoches");

      -- inicializar generadores de valores aleatorios
      Pkg_ColorCoche_Aleatorio.Reset(Generador_ColorCoche);
      Pkg_RetardoCoches_Aleatorios.Reset(Generador_Coches);
      Pkg_Velocidad_Aleatoria.Reset(Generador_VelocidadApCoche);

      idCoche := 1;
      
      LOOP

         ptr_coche := new T_RecordCoche;
         
         -- generar retardos aleatorios en la aparición de coches
         retardoCoche := Pkg_RetardoCoches_Aleatorios.Random(Generador_Coches);

         -- actualizar identificador del carril por el que circula
         idCarril := T_Carril(carril_param);
         PKG_graficos.Actualiza_Atributo(idCarril, ptr_coche.all);
            
         -- actualizar identificador del coche
         pkg_graficos.Actualiza_Atributo(idCoche, ptr_coche.all);
         idCoche := idCoche + 1;

         -- generar color aleatorio
         colorCoche := Pkg_ColorCoche_Aleatorio.Random(Generador_ColorCoche); 
         pkg_graficos.Actualiza_Atributo(colorCoche, ptr_coche.all);
            
         -- generar velocidades iniciales aleatorias de los coches
         velocidadApCoche := Pkg_Velocidad_Aleatoria.Random(Generador_VelocidadApCoche);
         PKG_graficos.Actualiza_Atributo(velocidadApCoche, ptr_coche.all);
           
         -- actualizar posición del coche
         pkg_graficos.Actualiza_Atributo(pkg_graficos.Pos_Inicio(ptr_coche.all), ptr_coche.all);
            
         -- Crear una tarea para el comportamiento del coche
         Tarea_coche := NEW T_Tarea_Coche(ptr_coche);
         
         DELAY(Standard.Duration(retardoCoche)); -- casting 

      END LOOP;

   exception
       when event: others =>
        PKG_debug.Escribir("ERROR en TASK GeneraCoches: " & Exception_Name(Exception_Identity(event)));
      
   END Tarea_GeneraCoches;
   
   
   --*************************************************************
   -- TIPO TAREA ENCARGADA DEL COMPORTAMIENTO DE UN COCHE
   --*************************************************************
   TASK BODY T_Tarea_Coche IS
      Coche  : T_RecordCoche;
   begin
      PKG_debug.Escribir("======================INICIO TASK Coche");

      -- Inicializar los datos del coche pasados como parámetros del tipo tarea
      Coche := ptr_coche.all;

      -- Visualizar el coche
      PKG_graficos.Aparece(Coche);

      -- el coche se mueve hasta llegar al final del carril
      WHILE NOT PKG_graficos.Pos_Final(Coche) LOOP
         
         IF PKG_graficos.Posicion_Stop_Semaforo(Coche) then
            IF PKG_Semaforo.OP_Semaforo.Semaforo_Rojo then
               PKG_graficos.Actualiza_Atributo(T_RangoVelocidad(0), Coche);
               PKG_graficos.Actualiza_Movimiento(Coche);
               OP_Semaforo.suspende_tarea;
               PKG_graficos.Actualiza_Atributo(T_RangoVelocidad(VELOCIDAD_COCHE), Coche);
            END IF;
         END IF;
         
         IF PKG_graficos.Coche_Parado(coche) then
            PKG_graficos.Actualiza_Movimiento(coche);
            OP_Semaforo.suspende_tarea;
            PKG_graficos.Actualiza_Atributo(T_RangoVelocidad(VELOCIDAD_COCHE), Coche);
         END if;
         
         PKG_graficos.Actualiza_Movimiento(Coche);

         delay(RETARDO_MOVIMIENTO);

      END LOOP;

      -- El coche deja de visualizarse
      PKG_graficos.Desaparece(Coche);

      PKG_debug.Escribir("======================FIN TASK Coche");

   exception
      when PKG_tipos.DETECTADA_COLISION_TREN => PKG_graficos.Desaparece(coche => Coche);
      when event: others =>
        PKG_debug.Escribir("ERROR en TASK Coche: " & Exception_Name(Exception_Identity(event)));

   end T_Tarea_Coche;
   

end PKG_coche;
