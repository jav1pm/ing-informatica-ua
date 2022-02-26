--******************* PKG_TAXI.ADS *************************************
-- Paquete que implementa la generación de taxis y su comportamiento
--***********************************************************************

WITH PKG_tipos; USE PKG_tipos;

PACKAGE PKG_Taxi IS

   -- tarea encargada de la generación de taxis
   task Tarea_GeneraTaxis;

   -- Tipo tarea encargada del comportamiento de un taxi
   TASK TYPE T_Tarea_Taxi(ptr_taxi : Ptr_T_RecordTaxi);
   type Ptr_Tarea_Taxi is access T_Tarea_Taxi;

   PROTECTED OP_Recogida IS

      PROCEDURE Cambiar_Estado_Taxi(estado: IN Boolean);

      FUNCTION Color_Indicador_Taxi RETURN Boolean;

      PROCEDURE Subir_Peaton;

      PROCEDURE Resetear_Pasajeros;

      ENTRY TaxiOcupado;
      ENTRY Recogida_Peaton;


   PRIVATE

      indicador : Boolean := false;
      num_pasajeros : Integer := 0;

   END OP_Recogida;

end PKG_taxi;

