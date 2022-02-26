with PKG_graficos;
with PKG_debug;
with Ada.exceptions; use Ada.exceptions;
WITH Ada.Numerics.Discrete_Random;
with PKG_Semaforo; use PKG_Semaforo;
with PKG_Averias;

package body PKG_mecanico is

   TASK BODY T_Tarea_Mecanico is
      
      contador : Integer := 0;
      
   begin
      LOOP
         select
            
            accept mecanico_repara_averia (carril : in T_Carril; tipoAveria : in T_Tipo_Averia) do
               PKG_graficos.Actualiza_Tipo_Averia_Carril(Carril => carril, Tipo_Averia => tipoAveria);
               PKG_Averias.OP_Indicador_Averia(carril).Actualiza_Indicador(PKG_tipos.REPARANDO_AVERIA);
               
               if PKG_Averias.Duracion_Tipo_Averia(tipo_averia => tipoAveria) = 10.0 then
                  contador := 10;
               else
                  contador := 15;
               end if;
               
               while contador > 0 loop
                  PKG_graficos.Actualiza_Reloj_Averia(carril => carril, Valor_Reloj => contador);
                  delay 1.0;
                  contador := contador - 1;
               end loop;
               PKG_graficos.Actualiza_Reloj_Averia(carril => carril, Valor_Reloj => contador);
               PKG_Averias.OP_Indicador_Averia(carril).Actualiza_Indicador(estado => PKG_tipos.T_Estado_Averia(NO_AVERIA));
            end mecanico_repara_averia; 
         end select;
      end loop;
   end T_Tarea_Mecanico;
end PKG_mecanico;
