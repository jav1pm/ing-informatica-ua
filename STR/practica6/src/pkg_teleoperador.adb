with PKG_graficos;
with PKG_debug;
with Ada.exceptions; use Ada.exceptions;
WITH Ada.Numerics.Discrete_Random;
with PKG_Semaforo; use PKG_Semaforo;
with PKG_Averias; with PKG_mecanico;

package body PKG_Teleoperador is

   TASK BODY Tarea_Teleoperador IS
      
   BEGIN
      
      LOOP
         
         accept Mensaje_Averia (carril : in T_Carril; tipoAveria : in T_Tipo_Averia) do
            
            PKG_graficos.Actualiza_Tipo_Averia_Carril(carril, tipoAveria);
               
            if tipoAveria = PKG_tipos.SIN_GASOLINA then
               requeue PKG_mecanico.M1.mecanico_repara_averia;
            else
               requeue PKG_mecanico.M2.mecanico_repara_averia;
            end if;

         end Mensaje_Averia;
         
         
      END loop;
      
         
   END Tarea_Teleoperador;
   

end PKG_Teleoperador;
