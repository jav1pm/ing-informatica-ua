using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.Common;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.Configuration;
using System.Collections;

namespace library
{
    public class CADUsuario
    {
        private string constring;
        private ArrayList listar = new ArrayList();

        public CADUsuario()
        {
            constring = ConfigurationManager.ConnectionStrings["miconexion"].ToString();
        }

        /// <summary>
        /// Función auxiliar en la que guardo en una lista los nifs de los usuarios.
        /// </summary>
        /// <returns></returns>
        private ArrayList ListarUsuarios()
        {
            SqlConnection c = new SqlConnection(constring);

            try
            {
                c.Open();
                string usuarios = "Select * from Usuarios";
                SqlCommand com = new SqlCommand(usuarios, c);
                SqlDataReader dr = com.ExecuteReader();

                while(dr.Read())
                {
                    listar.Add(dr["nif"].ToString());
                }
                dr.Close();
            }
            catch(SqlException ex)
            {
                Console.WriteLine("User operation has failed. Error: {0}", ex.Message);
            }
            finally { c.Close(); }
            return listar;
        }

        /// <summary>
        /// Función auxiliar para buscar si existe el nif pasado por parámetro en nuestra lista.
        /// </summary>
        /// <param name="nif"></param>
        /// <returns></returns>
        private bool BuscarUsuarios(string nif)
        {
            for(int i = 0; i < listar.Count; i++)
            {
                if(listar[i].ToString().Equals(nif))
                {
                    return true;
                }
            }
            return false;
        }

        public bool createUsuario(ENUsuario en)
        {
            ListarUsuarios();

            if (!BuscarUsuarios(en.nifUsuario))
            {
                SqlConnection c = new SqlConnection(constring);

                try
                {
                    string create = "INSERT INTO Usuarios (nif, nombre, edad) VALUES ('" + en.nifUsuario + "','" + en.nombreUsuario + "','" + en.edadUsuario + "')";

                    c.Open();
                    SqlCommand com = new SqlCommand(create, c);
                    com.ExecuteNonQuery();
                }
                catch (SqlException ex)
                {
                    Console.WriteLine("User operation has failed. Error: {0}", ex.Message);
                    return false;
                }
                finally { c.Close(); }
            }
            else return false;
            return true;
        }

        public bool readUsuario(ENUsuario en)
        {
            string nif = en.nifUsuario;
            string nombre = "";
            int edad = 0;

            ListarUsuarios();

            if (!BuscarUsuarios(nif)) return false;

            SqlConnection c = new SqlConnection(constring);

            try
            {
                string read = "SELECT nif, nombre, edad FROM Usuarios WHERE nif = '" + en.nifUsuario + "'";

                c.Open();
                SqlCommand com = new SqlCommand(read, c);

                SqlDataReader dr = com.ExecuteReader();

                while(dr.Read())
                {
                    nif = Convert.ToString(dr[0]);
                    nombre = Convert.ToString(dr[1]);
                    edad = Convert.ToInt32(dr[2]);
                }
                dr.Close();

                en.nifUsuario = nif;
                en.nombreUsuario = nombre;
                en.edadUsuario = edad;
            }
            catch(SqlException ex)
            {
                Console.WriteLine("User operation has failed. Error: {0}", ex.Message);
                return false;
            }
            finally { c.Close(); }
            return true;
        }

        public bool readFirstUsuario(ENUsuario en)
        {
            ListarUsuarios();

            if (listar.Count == 0)
            {
                Console.WriteLine("Error: no hay usuarios todavía en la BD.");
                return false;
            }

            SqlConnection c = new SqlConnection(constring);

            try
            {
                string read = "SELECT nif, nombre, edad FROM Usuarios WHERE nif = '" + listar[0].ToString() + "'";

                c.Open();
                SqlCommand com = new SqlCommand(read, c);

                SqlDataReader dr = com.ExecuteReader();

                while (dr.Read())
                {
                    en.nifUsuario = dr["nif"].ToString();
                    en.nombreUsuario = dr["nombre"].ToString();
                    en.edadUsuario = Convert.ToInt32(dr["edad"].ToString());
                }
                dr.Close();
            }
            catch (SqlException ex)
            {
                Console.WriteLine("User operation has failed. Error: {0}", ex.Message);
                return false;
            }
            finally { c.Close(); }
            return true;
        }

        public bool readNextUsuario(ENUsuario en)
        {
            ListarUsuarios();

            string nif = en.nifUsuario;
            int posNif = 0;
            bool find = false;

            if(listar.Count == 0)
            {
                Console.WriteLine("User operation has failed. Error: {0}");
                return false;           
            }

            // Buscamos el siguiente nif en nuestra lista de usuarios.
            for(int i = 0; i < listar.Count; i++)
            {
                if(listar[i].ToString().Equals(nif))
                {
                    find = true;
                    posNif = i;
                }
            }
            if(!find || listar.Count <= posNif + 1)
            {
                Console.WriteLine("User operation has failed. Error: {0}");
                return false;
            }

            string nombre = "";
            int edad = 0;

            SqlConnection c = new SqlConnection(constring);

            try
            {
                string read = "SELECT nif, nombre, edad FROM Usuarios WHERE nif = '" + listar[posNif+1].ToString() + "'";

                c.Open();
                SqlCommand com = new SqlCommand(read, c);

                SqlDataReader dr = com.ExecuteReader();

                while (dr.Read())
                {
                    nif = Convert.ToString(dr[0]);
                    nombre = Convert.ToString(dr[1]);
                    edad = Convert.ToInt32(dr[2]);
                }
                dr.Close();

                en.nifUsuario = nif;
                en.nombreUsuario = nombre;
                en.edadUsuario = edad;
            }
            catch (SqlException ex)
            {
                Console.WriteLine("User operation has failed. Error: {0}", ex.Message);
                return false;
            }
            finally { c.Close(); }
            return true;
        }

        public bool readPrevUsuario(ENUsuario en)
        {
            ListarUsuarios();

            string nif = en.nifUsuario;
            int posNif = 0;
            bool find = false;

            // Buscamos el siguiente nif en nuestra lista de usuarios.
            for (int i = 0; i < listar.Count; i++)
            {
                if (listar[i].ToString().Equals(nif))
                {
                    find = true;
                    if (i - 1 >= 0)
                    {
                        posNif = i;
                        nif = listar[i - 1].ToString();
                    }
                }
            }

            if(!find) return false; // Si el nif que le pasamos no existe, return false.
            if (posNif == 0) return false;

            string nombre = "";
            int edad = 0;

            SqlConnection c = new SqlConnection(constring);

            try
            {
                string read = "SELECT nif, nombre, edad FROM Usuarios WHERE nif = '" + nif + "'";

                c.Open();
                SqlCommand com = new SqlCommand(read, c);

                SqlDataReader dr = com.ExecuteReader();

                while (dr.Read())
                {
                    nif = Convert.ToString(dr[0]);
                    nombre = Convert.ToString(dr[1]);
                    edad = Convert.ToInt32(dr[2]);
                }
                dr.Close();

                en.nifUsuario = nif;
                en.nombreUsuario = nombre;
                en.edadUsuario = edad;
            }
            catch (SqlException ex)
            {
                Console.WriteLine("User operation has failed. Error: {0}", ex.Message);
                return false;
            }
            finally { c.Close(); }
            return true;
        }

        public bool updateUsuario(ENUsuario en)
        {
            ListarUsuarios();

            if (BuscarUsuarios(en.nifUsuario))
            {
                SqlConnection c = new SqlConnection(constring);

                try
                {
                    string create = "UPDATE Usuarios SET nif = '" + en.nifUsuario + "', nombre = '" + en.nombreUsuario + "', edad = '" + en.edadUsuario + "' WHERE nif = '" + en.nifUsuario + "'";

                    c.Open();
                    SqlCommand com = new SqlCommand(create, c);
                    com.ExecuteNonQuery();
                }
                catch (SqlException ex)
                {
                    Console.WriteLine("User operation has failed. Error: {0}", ex.Message);
                    return false;
                }
                finally { c.Close(); }
            }
            else return false;
            return true;
        }

        public bool deleteUsuario(ENUsuario en)
        {
            ListarUsuarios();

            if (!BuscarUsuarios(en.nifUsuario)) return false;

            SqlConnection c = new SqlConnection(constring);

            try
            {
                string create = "DELETE FROM Usuarios WHERE nif = '" + en.nifUsuario + "'";

                c.Open();
                SqlCommand com = new SqlCommand(create, c);
                com.ExecuteNonQuery();
            }
            catch (SqlException ex)
            {
                Console.WriteLine("User operation has failed. Error: {0}", ex.Message);
                return false;
            }
            finally { c.Close(); }
            return true;
        }
    }
}
