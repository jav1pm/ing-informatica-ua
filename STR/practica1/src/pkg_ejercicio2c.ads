with Ada.Text_IO; use Ada.Text_IO;
with Ada.Float_Text_IO;

-- Ejercicio 2

package pkg_ejercicio2c is 
   procedure OtroProcedimiento;
   
   type TdiasSemana is (Lunes, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo);
   numAlumnos : Integer := 7;
   package pkg_TdiasSemana is new Ada.Text_IO.Enumeration_IO(Enum => TdiasSemana);
   
   function getNotaMedia return Float;
private
   notaMedia : Float := 3.19;

end pkg_ejercicio2c;
