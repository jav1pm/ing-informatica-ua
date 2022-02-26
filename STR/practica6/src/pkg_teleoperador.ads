--******************* PKG_Teleoperador.ADS **************************
-- Paquete que implementa el comportamiento de un teleoperador
--*******************************************************************

with PKG_tipos; USE PKG_tipos;

package PKG_Teleoperador is

   -- Tarea encargada de recibir mensajes de coches averiados
   
   TASK Tarea_Teleoperador is 
      ENTRY Mensaje_Averia(carril : T_Carril; tipoAveria : T_Tipo_Averia);
      
   END Tarea_Teleoperador;
   

end PKG_Teleoperador;
