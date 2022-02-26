using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hada
{
    /// <summary>
    /// Clase que representa un Vehiculo y sus características: velocidad máxima permitida, temperatura máxima permitida y
    /// el umbral mínimo de combustible.
    /// </summary>
    class Vehiculo
    {
        public static int maxVelocidad;
        public static int maxTemperatura;
        public static int minCombustible;

        public static Random rand
        {
            private get;
            set;
        }

        public string nombre
        {
            get;
            private set;
        }

        private int _velocidad;
        private int velocidad
        {
            get { return _velocidad; }

            set
            {
                _velocidad = value;

                if (value < 0)
                {
                    _velocidad = 0;
                }
                else if (value > maxVelocidad)
                {
                    if (velocidadMaximaExcedida != null)
                    {
                        velocidadMaximaExcedida(this, new VelocidadMaximaExcedidaArgs(value));
                    }
                }
            }
        }

        private int _temperatura;
        private int temperatura
        {
            get { return _temperatura;  }

            set
            {
                _temperatura = value;

                if (value > maxTemperatura)
                {
                    if (temperaturaMaximaExcedida != null)
                    {
                        temperaturaMaximaExcedida(this, new TemperaturaMaximaExcedidaArgs(value));
                    }
                }
            }
        }

        private int _combustible;
        private int combustible
        {
            get { return _combustible; }

            set
            {
                _combustible = value;

                if (value < 0)
                {
                    _combustible = 0;
                }
                else if (value > 100)
                {
                    _combustible = 100;
                }

                if (value < minCombustible)
                {
                  if (combustibleMinimoExcedido != null)
                  {
                       combustibleMinimoExcedido(this, new CombustibleMinimoExcedidoArgs(_combustible));
                  }
                }
            }
        }

        public Vehiculo(string nombre, int velocidad, int temperatura, int combustible)
        {
            this.nombre = nombre;
            this.velocidad = velocidad;
            this.temperatura = temperatura;
            this.combustible = combustible;
        }

        public void incVelocidad()
        {
            velocidad += rand.Next(1, 7 + 1);
        }

        public void incTemperatura()
        {
            temperatura += rand.Next(1, 5 + 1);
        }

        public void decCombustible()
        {
            combustible -= rand.Next(1, 5 + 1);
        }

        public bool todoOk()
        {
            if (temperatura <= maxTemperatura && combustible >= minCombustible)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public void mover()
        {
            if (todoOk())
            {
                incVelocidad();
                incTemperatura();
                decCombustible();
            }
        }

        public override string ToString()
        {
            return "[" + nombre + "] " + "Velocidad: " + velocidad + " km/h; " + "Temperatura: " +
                temperatura + " ºC; " + "Combustible: " + combustible + " %; " + "Ok: " + todoOk() + "\n";
        }

        public event EventHandler<VelocidadMaximaExcedidaArgs> velocidadMaximaExcedida;
        public event EventHandler<TemperaturaMaximaExcedidaArgs> temperaturaMaximaExcedida;
        public event EventHandler<CombustibleMinimoExcedidoArgs> combustibleMinimoExcedido;
    }

    public class CombustibleMinimoExcedidoArgs : EventArgs
    {
        public int combustible { get; set; }

        public CombustibleMinimoExcedidoArgs(int combustible)
        {
            this.combustible = combustible;
        }
    }

    public class TemperaturaMaximaExcedidaArgs : EventArgs
    {
        public int temperatura { get; set; }

        public TemperaturaMaximaExcedidaArgs(int temperatura)
        {
            this.temperatura = temperatura;
        }
    }

    public class VelocidadMaximaExcedidaArgs : EventArgs
    {
        public int velocidad { get; set; }

        public VelocidadMaximaExcedidaArgs(int velocidad)
        {
            this.velocidad = velocidad;
        }
    }
}
