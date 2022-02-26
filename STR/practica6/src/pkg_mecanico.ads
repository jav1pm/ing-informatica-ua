--******************* PKG_mecanico.ADS **************************
-- Paquete que implementa el comportamiento de un mecanico
--*******************************************************************

with PKG_tipos; use PKG_tipos;

package PKG_mecanico is

   TASK TYPE T_Tarea_Mecanico (tipoAveria: T_Tipo_Averia) is

      entry mecanico_repara_averia (carril: T_Carril; tipoAveria: T_Tipo_Averia);

   END T_Tarea_Mecanico;

   M1 : T_Tarea_Mecanico(SIN_GASOLINA); -- mecanico repara averia sin gasolina
   M2 : T_Tarea_Mecanico(PINCHAZO); -- mecanico repara averia pinchazo


end PKG_mecanico;
