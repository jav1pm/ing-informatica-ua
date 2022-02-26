with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with pkg_ejercicio2c;

procedure ejercicio1 is
   s : String := "Comenzamos las prácticas de STR";
   numero : Natural := 0;
begin
   Put("Hola Mundo!!!");
   Put_Line(s);
   pkg_ejercicio2c.OtroProcedimiento;

   -- Ejercicio 3
   begin
      Put("Introduce un numero:");
      Ada.Integer_Text_IO.Get(numero);

      case numero is
      when 12 | 1 | 2 => Put_Line("Invierno");
      when 3 | 4 | 5 => Put_Line("Primavera");
      when 6 | 7 | 8 => Put_Line("Verano");
      when 9 | 10 | 11 => Put_Line("Otoño");
      when others => Put_Line("Mes incorrecto");
      end case;

   -- Ejercicio 5

   exception
      when Constraint_Error => Put_Line("El numero de mes debe ser > 0");
   end;
   Put_Line("FIN DEL PROGRAMA");


end ejercicio1;

--- Apartado 1.d)

-- Una ventaja al usar la cláusula *use* es que nos ahorramos escribir todo el tiempo el nombre del paquete.
-- Un incoveniente sería que cuando tengamos demasiados paquetes nos será mas dificil conocer a que paquete pertenece.


-- Ejercicio 2

--  procedure OtroProcedimiento is
--  begin
--     Put_Line("Soy OtroProcedimiento");
--  end OtroProcedimiento;

-- 2.b)
-- En un fichero solo puedo haber una unidad de compilación a no ser que esten anidados, en este caso estan separados y es por esto que no compila.

