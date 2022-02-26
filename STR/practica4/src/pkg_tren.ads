--******************* PKG_tren.ADS ************************************
-- Paquete que implementa la generación de trenes y su comportamiento
--***********************************************************************

with PKG_tipos; USE PKG_tipos;

package PKG_tren is

   -- tarea encargada de la generación de trenes
   TASK Tarea_GeneraTrenes;

   -- Tipo tarea encargada del comportamiento de un tren
   TASK TYPE T_Tarea_Tren(ptr_tren: Ptr_T_RecordTren);
   type Ptr_Tarea_Tren is access T_Tarea_Tren;

end PKG_tren;
