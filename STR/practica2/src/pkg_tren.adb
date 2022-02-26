--******************* PKG_tren.ADB **************************************
-- Paquete que implementa la generación de trenes y su comportamiento
--***********************************************************************

with PKG_graficos;
with PKG_debug;
with Ada.exceptions; use Ada.exceptions;
WITH Ada.Numerics.Discrete_Random;


package body PKG_tren is

   --*************************************************************
   -- TAREA ENCARGADA DE LA GENERACIÓN DE TRENES PERIÓDICAMENTE
   --*************************************************************
   TASK BODY Tarea_GeneraTrenes IS
      Tarea_tren : Ptr_Tarea_Tren;
      ptr_tren   : Ptr_T_RecordTren;

      -- Creación de paquete para generar un color aleatorio
      PACKAGE Pkg_ColorTren_Aleatorio
                is new Ada.Numerics.Discrete_Random(T_ColorTren);
      Generador_ColorTren: Pkg_ColorTren_Aleatorio.Generator;
      numVagones : T_NumVagones;
      
      -- Creación de paquete para generar un numero de vagones aleatorio
      PACKAGE Pkg_NumVagones_Aleatorio
                is new Ada.Numerics.Discrete_Random(T_NumVagones);
      Generador_NumVagones: Pkg_NumVagones_Aleatorio.Generator;
      colorTren : T_ColorTren;
      

   BEGIN
      PKG_debug.Escribir("======================INICIO TASK GeneraTrenes");

      -- inicializar generador de valores aleatorio
      Pkg_ColorTren_Aleatorio.Reset(Generador_ColorTren);
      Pkg_NumVagones_Aleatorio.Reset(Generador_NumVagones);
      
      LOOP
         -- Crear un nuevo tren solo si no hay ninguno presente
         IF NOT PKG_graficos.Hay_Tren THEN
            
            ptr_tren := NEW T_RecordTren;
            
            -- generar color aleatorio
            colorTren := Pkg_ColorTren_Aleatorio.Random(Generador_ColorTren);
            pkg_graficos.Actualiza_Atributo(colorTren, ptr_tren.all);

            -- generar vagones aleatorios
            numVagones := Pkg_NumVagones_Aleatorio.Random(Generador_NumVagones);
            pkg_graficos.Actualiza_Atributo(numVagones, ptr_tren.all);

            -- Crear una tarea para el comportamiento del tren
            Tarea_Tren := NEW T_Tarea_Tren(ptr_tren);
            
         END IF;

         DELAY(PERIODO_TREN);

      END LOOP;

      exception
       when event: others =>
        PKG_debug.Escribir("ERROR en TASK GeneraTrenes: " & Exception_Name(Exception_Identity(event)));
   END Tarea_GeneraTrenes;
   
   
   --*************************************************************
   -- TIPO TAREA ENCARGADA DEL COMPORTAMIENTO DE UN TREN
   --*************************************************************
   TASK BODY T_Tarea_Tren IS
      Tren  : T_RecordTren;
   begin
      PKG_debug.Escribir("======================INICIO TASK Tren");

      -- Inicializar los datos del tren pasados como parámetros del tipo tarea
      Tren := ptr_tren.all;

      -- Visualizar el tren
      PKG_graficos.Aparece(Tren);

      -- el tren se mueve hasta llegar al final de la vía
      WHILE NOT PKG_graficos.Pos_Final(Tren) LOOP
         
         PKG_graficos.Actualiza_Movimiento(Tren);

         delay(RETARDO_MOVIMIENTO);

      END LOOP;

      -- El tren deja de visualizarse
      PKG_graficos.Desaparece(Tren);

      PKG_debug.Escribir("======================FIN TASK Tren");

      exception
       when event: others =>
        PKG_debug.Escribir("ERROR en TASK Tren: " & Exception_Name(Exception_Identity(event)));

   end T_Tarea_Tren;

end PKG_tren;
