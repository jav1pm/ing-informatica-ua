with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Float_Text_IO;
with pkg_ejercicio2c;

procedure ejercicio3 is
   diaS : pkg_ejercicio2c.TdiasSemana;
   pos : Natural;
   valor : pkg_ejercicio2c.TdiasSemana;
begin
   Put("Numero de alumnos:");
   Ada.Integer_Text_IO.Put(pkg_ejercicio2c.numAlumnos, 2);
   Put(" Nota media:");
   Ada.Float_Text_IO.Put(pkg_ejercicio2c.getNotaMedia, 2, 1, 0);

   New_Line;
   for dia in pkg_ejercicio2c.TdiasSemana loop
      pkg_ejercicio2c.pkg_TdiasSemana.Put(dia);
      New_Line;
   end loop;

   Put(Item => "Introduce un dia cualquiera: ");
   pkg_ejercicio2c.pkg_TdiasSemana.Get(Item => diaS);

   pos := pkg_ejercicio2c.TdiasSemana'Pos(diaS);
   valor := pkg_ejercicio2c.TdiasSemana'Val(pos);

   Put("Has seleccionado el dia ");
   pkg_ejercicio2c.pkg_TdiasSemana.Put(Item => valor);

end ejercicio3;

-- Cuestiones

-- 3.d) Para acceder a la variable privada he creado una funcion getter.
-- 4.c) si se introduce un valor que no pertenece al enumerado se produciria una excepcion.
