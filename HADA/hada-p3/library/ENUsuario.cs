using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace library
{
    public class ENUsuario
    {
        private string nif;
        private string nombre;
        private int edad;

        public string nifUsuario
        {
            get { return nif; }
            set { nif = value; }
        }

        public string nombreUsuario
        {
            get { return nombre; }
            set { nombre = value; }
        }

        public int edadUsuario
        {
            get { return edad; }
            set { edad = value; }
        }

        public ENUsuario()
        {
            nif = "";
            nombre = "";
            edad = 0;
        }

        public ENUsuario(string nif, string nombre, int edad)
        {
            this.nif = nif;
            this.nombre = nombre;
            this.edad = edad;
        }

        public bool createUsuario()
        {
            CADUsuario u = new CADUsuario();
            return u.createUsuario(this);
        }

        public bool readUsuario()
        {
            CADUsuario u = new CADUsuario();
            return u.readUsuario(this);
        }

        public bool readFirstUsuario()
        {
            CADUsuario u = new CADUsuario();
            return u.readFirstUsuario(this);
        }

        public bool readNextUsuario()
        {
            CADUsuario u = new CADUsuario();
            return u.readNextUsuario(this);
        }

        public bool readPrevUsuario()
        {
            CADUsuario u = new CADUsuario();
            return u.readPrevUsuario(this);
        }

        public bool updateUsuario()
        {
            CADUsuario u = new CADUsuario();
            return u.updateUsuario(this);
        }

        public bool deleteUsuario()
        {
            CADUsuario u = new CADUsuario();
            return u.deleteUsuario(this);
        }
    }
}
