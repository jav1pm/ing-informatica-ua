<%@ Page Title="" Language="C#" MasterPageFile="~/Site1.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="usuWeb.Default" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <h2> Página de usuarios </h2>
   
    NIF:&nbsp;
    <asp:TextBox ID="TNif" runat="server" Width="191px"></asp:TextBox>
    <br />
    <br />
    Nombre:&nbsp;
    <asp:TextBox ID="TNombre" runat="server"></asp:TextBox>
    <br />
    <br />
    Edad:&nbsp;
    <asp:TextBox ID="TEdad" type="number" runat="server" Width="184px"></asp:TextBox>
    <br />
    <br />
    <asp:Button ID="BLeer" runat="server" OnClick="BLeer_Click" Text="Leer"/>
    <asp:Button ID="BLeerP" runat="server" OnClick="BLeerP_Click" Text="Leer Primero" style="margin-left: 14px"/>
    <asp:Button ID="BLeerA" runat="server" OnClick="BLeerA_Click" Text="Leer Anterior" style="margin-left: 14px"/>
    <asp:Button ID="BLeerS" runat="server" OnClick="BLeerS_Click" Text="Leer Siguiente" style="margin-left: 14px"/>
    <asp:Button ID="BCrear" runat="server" OnClick="BCrear_Click" Text="Crear" style="margin-left: 14px"/>
    <asp:Button ID="BActu" runat="server" OnClick= "BActu_Click" Text="Actualizar" style="margin-left: 14px"/>
    <asp:Button ID="BBorrar" runat="server" OnClick="BBorrar_Click" Text="Borrar" style="margin-left: 14px"/>

    <asp:Label ID="LError" runat="server" Visible="false">Error</asp:Label>
    <asp:Label ID="LOk" runat="server" Visible ="false"></asp:Label>
</asp:Content>

