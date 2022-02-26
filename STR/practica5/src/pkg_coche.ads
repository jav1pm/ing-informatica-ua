--******************* PKG_coche.ADS ************************************
-- Paquete que implementa la generación de coches y su comportamiento
--***********************************************************************

with PKG_tipos; USE PKG_tipos;

package PKG_coche is
   
   -- tarea encargada de la generación de coches
   TASK TYPE Tarea_GeneraCoches(carril_param: T_Carril);
   
   -- declaraciones a Tarea_GeneraCoches / cada carril es una tarea / su cuerpo es el mismo.
   C1 : Tarea_GeneraCoches(1);
   C2 : Tarea_GeneraCoches(2);

   -- Tipo tarea encargada del comportamiento de un coche
   TASK TYPE T_Tarea_Coche(ptr_coche: Ptr_T_RecordCoche);
   type Ptr_Tarea_Coche is access T_Tarea_Coche;

end PKG_coche;
