with PKG_graficos;
with PKG_debug;
with Ada.exceptions; use Ada.exceptions;
WITH Ada.Numerics.Discrete_Random;
with PKG_Semaforo; use PKG_Semaforo;
with PKG_Averias;

package body PKG_Teleoperador is

   TASK BODY Tarea_Teleoperador IS
      
   BEGIN
      
      LOOP
         
         SELECT
            accept Mensaje_Averia (carril   : in T_Carril; tipoAveria : in T_Tipo_Averia) do
            
               PKG_graficos.Actualiza_Tipo_Averia_Carril(carril, tipoAveria);
               PKG_Averias.OP_Indicador_Averia(carril).Actualiza_Indicador(estado => PKG_tipos.T_Estado_Averia(REPARANDO_AVERIA));
            
            end Mensaje_Averia;
            
         OR
            accept Mensaje_Reparado (carril : in T_Carril) do
               PKG_Averias.OP_Indicador_Averia(carril).Actualiza_Indicador(estado => PKG_tipos.T_Estado_Averia(NO_AVERIA));
            end Mensaje_Reparado;
            
         END select;
         
         
      END loop;
      
         
   END Tarea_Teleoperador;
   

end PKG_Teleoperador;
