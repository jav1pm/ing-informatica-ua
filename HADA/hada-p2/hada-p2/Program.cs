using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hada
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Main");
            Vehiculo.maxTemperatura = 95;
            Vehiculo.maxVelocidad = 120;
            Vehiculo.minCombustible = 1;
            Vehiculo.rand = new Random();

            if (VehiculoOk())
            {
                Autovia a = new Autovia(4);
                Console.WriteLine(a);
                if (a.moverCoches())
                {
                    a.moverCochesEnBucle();
                }
                List<Vehiculo> vehiculosExcedenLimiteVelocidad = new List<Vehiculo>();
                vehiculosExcedenLimiteVelocidad = a.getCochesExcedenLimiteVelocidad();
                List<Vehiculo> vehiculosExcedenLimiteTemperatura = new List<Vehiculo>();
                vehiculosExcedenLimiteTemperatura = a.getCochesExcedenLimiteTemperatura();
                List<Vehiculo> vehiculosExcedenMinimoCombustible = new List<Vehiculo>();
                vehiculosExcedenMinimoCombustible = a.getCochesExcedenMinimoCombustible();

                Console.WriteLine(a);
            }

        }

        public static bool VehiculoOk()
        {
            string nombre = "vehiculo";
            int velocidad = 30;
            int temperatura = 40;
            int combustible = 50;

            Vehiculo v = new Vehiculo(nombre, velocidad, temperatura, combustible);

            nombre = v.nombre;
            v.incVelocidad();
            v.incTemperatura();
            v.decCombustible();
            v.mover();
            Console.WriteLine(v);

            VelocidadMaximaExcedidaArgs vmax = new VelocidadMaximaExcedidaArgs(velocidad);
            velocidad = vmax.velocidad;
            TemperaturaMaximaExcedidaArgs tmax = new TemperaturaMaximaExcedidaArgs(temperatura);
            temperatura = tmax.temperatura;
            CombustibleMinimoExcedidoArgs cmin = new CombustibleMinimoExcedidoArgs(combustible);
            combustible = cmin.combustible;


            return v.todoOk();
        }
    }
}
