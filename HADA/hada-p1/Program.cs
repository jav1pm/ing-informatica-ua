using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hada_p1
{
    class Program
    {
        /// <summary>
        /// Main para ofrecer al usuario varias opciones de conversión.
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            String resp;

            do
            {
                Console.WriteLine("¿De que unidad partes, horas, minutos o segundos?");
                String unid = Console.ReadLine();

                if (unid == "horas")
                {
                    Console.WriteLine("¿Cantidad?");
                    double c3 = double.Parse(Console.ReadLine());
                    Console.WriteLine(HadaP1.Hours2Minutes(c3) + "min");
                }
                else if (unid == "segundos")
                {
                    Console.WriteLine("¿Cantidad?");
                    double c = double.Parse(Console.ReadLine());
                    Console.WriteLine(HadaP1.Seconds2Minutes(c) + "min");
                }
                else if (unid == "minutos")
                {
                    Console.WriteLine("¿Cantidad?");
                    double c2 = double.Parse(Console.ReadLine());
                    Console.WriteLine(HadaP1.Minutes2Seconds(c2) + "s");
                }
                else
                {
                    Console.WriteLine("Error, elige una de las tres unidades dadas");
                }
                Console.WriteLine("¿Quiere realizar más conversiones? (s/n)");
                resp = Console.ReadLine();

            } while (resp == "s");
        }
    }
}
