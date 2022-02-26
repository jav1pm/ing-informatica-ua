with PKG_graficos;
with PKG_debug;
with Ada.exceptions; use Ada.exceptions;
WITH Ada.Numerics.Discrete_Random;

package body PKG_cronometro_calendar is

   task body periodica_calendar is 
      periodo : constant Duration := 1.0;
      Inicio : Time;
      Siguiente : Time;
      
   begin
      Inicio := Clock;
      Siguiente := Clock + periodo;
      loop
         
         --action
         PKG_graficos.Actualiza_Cronometro((Clock - Inicio));
         delay until Siguiente;
         -- delay 1.0;
         Siguiente := Siguiente + periodo;
      end loop;
   
   exception
       when event: others =>
         PKG_debug.Escribir("ERROR en TASK CALENDAR: " & Exception_Name(Exception_Identity(event)));
   end periodica_calendar;
   
   

end PKG_cronometro_calendar;
