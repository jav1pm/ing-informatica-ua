with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Float_Random;
with Ada.Float_Text_IO;

procedure numerosAleatorios is
   subtype T_Float is Float range 0.0..1.0;
   generador_float : Ada.Numerics.Float_Random.Generator; -- declarar generador de valores de tipo Float
   digito :  T_Float;
begin
   Ada.Numerics.Float_Random.Reset(generador_float); -- Inicializar generador de nº aleatorios
   for i in 0..5 loop
      digito := Ada.Numerics.Float_Random.Random(generador_float); -- generar nº aleatorio
      Ada.Float_Text_IO.Put(digito, Aft => 4, Exp => 0);
      Ada.Text_IO.Skip_Line;
   end loop;       
end numerosAleatorios;
