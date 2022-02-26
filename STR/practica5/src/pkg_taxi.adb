--******************* PKG_TAXI.ADB **************************************
-- Paquete que implementa la generación de taxis y su comportamiento
--***********************************************************************

with PKG_graficos;
with PKG_debug;
with Ada.exceptions; use Ada.exceptions;
with Ada.Calendar; use Ada.Calendar;
with PKG_Semaforo; use PKG_Semaforo;
with Ada.Integer_Text_IO, Ada.Text_IO;


PACKAGE BODY PKG_Taxi IS

   PROTECTED body OP_Recogida is

      PROCEDURE Cambiar_Estado_Taxi(estado: IN Boolean) is
      begin

         indicador := estado;

      END Cambiar_Estado_Taxi;

      FUNCTION Color_Indicador_Taxi RETURN Boolean is

         begin
         RETURN indicador = true;

      END Color_Indicador_Taxi;

      PROCEDURE Subir_Peaton is

      begin

         -- Si el taxi esta libre
         if (indicador = true) then
               num_pasajeros := num_pasajeros + 1;
            if (num_pasajeros = PKG_tipos.CAPACIDAD_TAXI) then
               Cambiar_Estado_Taxi(estado => false);
            end if;
         end if;

      END Subir_Peaton;

      PROCEDURE Resetear_Pasajeros is
      begin
         num_pasajeros := 0;
      END Resetear_Pasajeros;


      ENTRY TaxiOcupado WHEN indicador = false is
      begin
         null;
      END TaxiOcupado;

      ENTRY Recogida_Peaton WHEN indicador = true is
      begin
         Subir_Peaton;
      END Recogida_Peaton;

   END OP_Recogida;



   --*************************************************************
   -- TAREA ENCARGADA DE LA GENERACIÓN DE TAXIS PERIÓDICAMENTE
   --*************************************************************
   TASK BODY Tarea_GeneraTaxis IS
      Tarea_taxi : Ptr_Tarea_Taxi;
      ptr_taxi   : Ptr_T_RecordTaxi;

      Siguiente : Time;

   BEGIN

      Siguiente := Clock + PERIODO_TAXI;
      PKG_debug.Escribir("======================INICIO TASK GeneraTaxis");

      LOOP
         -- Crear un nuevo taxi solo si no hay ninguno presente
         IF NOT PKG_graficos.Hay_Taxi THEN

            Ptr_Taxi := NEW T_RecordTaxi;

            -- Crear una tarea para el comportamiento del taxi
            Tarea_Taxi := NEW T_Tarea_Taxi(ptr_taxi);
         END IF;

         DELAY UNTIL Siguiente;
         Siguiente := Siguiente + PERIODO_TAXI;

      END LOOP;

      exception
       when event: others =>
        PKG_debug.Escribir("ERROR en TASK GeneraTaxis: " & Exception_Name(Exception_Identity(event)));

   END Tarea_GeneraTaxis;

   --*************************************************************
   -- TIPO TAREA ENCARGADA DEL COMPORTAMIENTO DE UN TAXI
   --*************************************************************

   TASK BODY T_Tarea_Taxi IS
      Taxi  : T_RecordTaxi;
   begin
      PKG_debug.Escribir("======================INICIO TASK Taxi");

      -- Inicializar los datos del taxi pasados como parámetros del tipo tarea
      taxi:= ptr_taxi.all;

      -- Visualizar el taxi
      PKG_graficos.Aparece(Taxi);

      -- el taxi se mueve hasta llegar al final de la carretera
      WHILE NOT PKG_graficos.Pos_Final(Taxi) LOOP

         IF pkg_graficos.Pos_Parada_Taxi(taxi) THEN
            -- Detener el taxi en la parada un tiempo fijo
            pkg_graficos.Actualiza_Atributo(T_RangoVelocidad(0), taxi);
            delay(TIEMPO_PARADA_OBLIGATORIA);

            OP_Recogida.Cambiar_Estado_Taxi(estado => true);
            PKG_graficos.Actualiza_Indicador_Taxi(true, Taxi);

            -- El taxi sube peatones

            SELECT
               OP_Recogida.TaxiOcupado;
            OR
               DELAY TIEMPO_RECOGIDA_PASAJEROS;

            END SELECT;

            OP_Recogida.Cambiar_Estado_Taxi(estado => false);
            PKG_graficos.Actualiza_Indicador_Taxi(false, Taxi);

            -- reanudar la marcha
            pkg_graficos.Actualiza_Atributo(T_RangoVelocidad(VELOCIDAD_TAXI), taxi);
         END IF;

         -- Control del taxi regulado por el semáforo
         IF PKG_graficos.Posicion_Stop_Semaforo(taxi) then
            IF PKG_Semaforo.OP_Semaforo.Semaforo_Rojo then
               PKG_graficos.Actualiza_Atributo(T_RangoVelocidad(0), taxi);
               OP_Semaforo.suspende_tarea; -- entry
               PKG_graficos.Actualiza_Atributo(T_RangoVelocidad(VELOCIDAD_TAXI), taxi);
            END IF;
         END IF;


         -- actualiza la posicion del taxi
         PKG_graficos.Actualiza_Movimiento(taxi);

         delay(RETARDO_MOVIMIENTO);

      END LOOP;

      PKG_Taxi.OP_Recogida.Resetear_Pasajeros;
      -- El taxi deja de visualizarse
      PKG_graficos.Desaparece(taxi);

      PKG_debug.Escribir("======================FIN TASK Taxi");

   exception
      when PKG_tipos.DETECTADA_COLISION_TREN => PKG_graficos.Desaparece(taxi => Taxi);
      when event: others =>
        PKG_debug.Escribir("ERROR en TASK Taxi: " & Exception_Name(Exception_Identity(event)));

   end T_Tarea_Taxi;


END PKG_taxi;
