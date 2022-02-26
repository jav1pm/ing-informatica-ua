using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using library;

namespace usuWeb
{
    public partial class Default : System.Web.UI.Page
    {
        private string mensajeError = "";
        private string mensajeOK = "";

        protected void Page_Load(object sender, EventArgs e)
        {
            LError.Visible = false;
            LOk.Visible = false;
        }

        private void resetCampos()
        {
            TNif.Text = "";
            TNombre.Text = "";
            TEdad.Text = "";
        }

        private void rellenarUsuarios(ENUsuario en)
        {
            TNif.Text = en.nifUsuario;
            TNombre.Text = en.nombreUsuario;
            TEdad.Text = en.edadUsuario.ToString();
        }

        private void setMensajeError(string mensaje)
        {
            LError.Text = mensajeError;
            LError.Visible = true;
        }

        protected void BLeer_Click(object sender, EventArgs e)
        {
            ENUsuario en = new ENUsuario(TNif.Text, "", 0);

            if(en.readUsuario())
            {
                LError.Visible = false;
                rellenarUsuarios(en);
                mensajeOK = "Usuario leído correctamente.";
                LOk.Text = mensajeOK;
                LOk.Visible = true;
            }
            else
            {
                mensajeError = "Se produjo un error al intentar leer usuarios en la BD";
                setMensajeError(mensajeError);
            }
        }

        protected void BLeerP_Click(object sender, EventArgs e)
        {
            ENUsuario en = new ENUsuario();

            if(en.readFirstUsuario())
            {
                LError.Visible = false;
                rellenarUsuarios(en);
                mensajeOK = "Primer usuario leído correctamente.";
                LOk.Text = mensajeOK;
                LOk.Visible = true;
            }
            else
            {
                mensajeError = "Se produjo un error al intentar leer el primer usuario en la BD";
                setMensajeError(mensajeError);
            }
        }

        protected void BLeerA_Click(object sender, EventArgs e)
        {
            ENUsuario en = new ENUsuario();
            en.nifUsuario = TNif.Text;

            if (en.readPrevUsuario())
            {
                LError.Visible = false;
                rellenarUsuarios(en);
                mensajeOK = "Usuario anterior leído correctamente.";
                LOk.Text = mensajeOK;
                LOk.Visible = true;
            }
            else
            {
                mensajeError = "Se produjo un error al intentar leer el anterior usuario en la BD";
                setMensajeError(mensajeError);
            }
        }

        protected void BLeerS_Click(object sender, EventArgs e)
        {
            ENUsuario en = new ENUsuario();
            en.nifUsuario = TNif.Text;

            if(en.readNextUsuario())
            {
                LError.Visible = false;
                rellenarUsuarios(en);
                mensajeOK = "Siguiente usuario leído correctamente.";
                LOk.Text = mensajeOK;
                LOk.Visible = true;
            }
            else
            {
                mensajeError = "Se produjo un error al intentar leer el siguiente usuario en la BD";
                setMensajeError(mensajeError);
            }
        }

        protected void BCrear_Click(object sender, EventArgs e)
        {
            if (TNif.Text.Equals("") || TNombre.Text.Equals("") || TEdad.Text.Equals(""))
            {
                mensajeError = "Por favor, rellene los campos vacíos.";
                setMensajeError(mensajeError);
            }
            else
            {
                ENUsuario en = new ENUsuario(TNif.Text, TNombre.Text, Convert.ToInt32(TEdad.Text));

                if (en.createUsuario())
                {
                    LError.Visible = false;
                    mensajeOK = "Usuario creado correctamente.";
                    LOk.Text = mensajeOK;
                    LOk.Visible = true;
                    resetCampos();
                }
                else
                {
                    mensajeError = "Se produjo un error al intentar crear un usuario en la BD";
                    setMensajeError(mensajeError);
                }
            }
        }

        protected void BActu_Click(object sender, EventArgs e)
        {
            if (TNif.Text.Equals("") || TNombre.Text.Equals("") || TEdad.Text.Equals(""))
            {
                mensajeError = "Por favor, rellene los campos vacíos.";
                setMensajeError(mensajeError);
            }
            else
            {
                ENUsuario en = new ENUsuario(TNif.Text, TNombre.Text, Convert.ToInt32(TEdad.Text));

                if (en.updateUsuario())
                {
                    LError.Visible = false;
                    mensajeOK = "Usuario actualizado correctamente.";
                    LOk.Text = mensajeOK;
                    LOk.Visible = true;
                    resetCampos();
                }
                else
                {
                    mensajeError = "Se produjo un error al intentar actualizar un usuario en la BD";
                    setMensajeError(mensajeError);
                }
            }
        }

        protected void BBorrar_Click(object sender, EventArgs e)
        {
            ENUsuario en = new ENUsuario(TNif.Text, "", 0);

            if(en.deleteUsuario())
            {
                LError.Visible = false;
                resetCampos();
                mensajeOK = "Usuario borrado correctamente.";
                LOk.Text = mensajeOK;
                LOk.Visible = true;
            }
            else
            {
                mensajeError = "Se produjo un error al intentar borrar un usuario";
                setMensajeError(mensajeError);
            }
        }
    }
}