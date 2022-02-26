using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hada
{
    class Autovia
    {
        List<Vehiculo> vehiculosAutovia { get; set; }
        List<Vehiculo> vehiculosExcedeVelocidad { get; set; }
        List<Vehiculo> vehiculosExcedeTemperatura { get; set; }
        List<Vehiculo> vehiculosExcedeCombustible { get; set; }

        public Autovia(int nc)
        {
            vehiculosAutovia = new List<Vehiculo>();
            vehiculosExcedeVelocidad = new List<Vehiculo>();
            vehiculosExcedeTemperatura = new List<Vehiculo>();
            vehiculosExcedeCombustible = new List<Vehiculo>();

            for (int i = 0; i < nc; i++)
            {
                string nombre = "Coche_" + i;
                Vehiculo v = new Vehiculo(nombre, 50, 50, 50);
                v.velocidadMaximaExcedida += cuandoVelocidadMaximaExcedida;
                v.temperaturaMaximaExcedida += cuandoTemperaturaMaximaExcedida;
                v.combustibleMinimoExcedido += cuandoCombustibleMinimoExcedido;
                vehiculosAutovia.Add(v);
            }
        }

        public bool moverCoches()
        {
            bool move = false;

            for (int i = 0; i < vehiculosAutovia.Count(); i++)
            {
                if(vehiculosAutovia[i].todoOk())
                {
                    vehiculosAutovia[i].mover();
                    move = true;
                }
            }
            return move;
        }

        public void moverCochesEnBucle()
        {
            while (moverCoches());
        }

        public List<Vehiculo> getCochesExcedenLimiteVelocidad()
        {
            return vehiculosExcedeVelocidad;
        }

        public List<Vehiculo> getCochesExcedenLimiteTemperatura()
        {
            return vehiculosExcedeTemperatura;
        }

        public List<Vehiculo> getCochesExcedenMinimoCombustible()
        {
            return vehiculosExcedeCombustible;
        }

        public override string ToString()
        {
            string os;

            os = "[AUTOVÍA] " + "Exceso velocidad: " + getCochesExcedenLimiteVelocidad().Count() + 
                "; Exceso temperatura: " + getCochesExcedenLimiteTemperatura().Count() + 
                "; Défecit combustible: " + getCochesExcedenMinimoCombustible().Count() + "\n";

            foreach (Vehiculo v in vehiculosAutovia) { os += v.ToString(); }
            return os;
        }

        private void cuandoVelocidadMaximaExcedida(Object sender, VelocidadMaximaExcedidaArgs args)
        {
            Vehiculo v = (Hada.Vehiculo) sender;
            Console.WriteLine("¡¡Velocidad máxima excedida!!");
            Console.WriteLine("Vehículo: " + v.nombre);
            Console.WriteLine("Velocidad: " + args.velocidad + " km/h\n");

            if(vehiculosExcedeVelocidad.Contains(v) == false) { vehiculosExcedeVelocidad.Add(v); }
        }

        private void cuandoTemperaturaMaximaExcedida(Object sender, TemperaturaMaximaExcedidaArgs args)
        {
            Vehiculo v = (Hada.Vehiculo) sender;
            Console.WriteLine("¡¡Temperatura máxima excedida!!");
            Console.WriteLine("Vehículo: " + v.nombre);
            Console.WriteLine("Temperatura: " + args.temperatura + " ºC\n");
            vehiculosExcedeTemperatura.Add(v);
        }

        private void cuandoCombustibleMinimoExcedido(Object sender, CombustibleMinimoExcedidoArgs args)
        {
            Vehiculo v = (Hada.Vehiculo) sender;
            Console.WriteLine("¡¡Combustible mínimo excedida!!");
            Console.WriteLine("Vehículo: " + v.nombre);
            Console.WriteLine("Combustible: " + args.combustible + " %\n");
            vehiculosExcedeCombustible.Add(v);
        }
    }
}
