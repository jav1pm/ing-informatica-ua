package model;

import java.awt.Color;
import java.awt.Font;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.EmptyBorder;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFileChooser;

import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.awt.event.ActionEvent;

/**
 * Clase Aplicacion: Esta clase administra la parte visual del programa, 
 * tanto la impresión por consola como la ventana del pack gráfico de java.
 *
 * @author Francisco Javier Perez Martinez 74384305M
 * @author Francisco Joaquin Murcia Gomez 48734281H
 */

public class Aplicacion extends JFrame {
	
	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = 1L;

	/**  Panel del gestor. */
	private JPanel PanelGestor;
	
	/** Algoritmo de PeorHueco. */
	public static final int PeorHueco = 1;
	
	/** Algoritmo de MejorHueco. */
	public static final int MejorHueco = 2;
	
	/** Algoritmo elegido en el menu. */
	public static int option;
	
	/** Procesos extraídos del fichero de lectura. No tienen por qué estar en memoria. */
	public static ArrayList<Proceso> procesos = new ArrayList<Proceso>(); 
	
	/** memoria. */
	public static Memoria memoria = new Memoria();
	
	/** nombre fichero salida/entrada. */
	public static String nombreFicheroEntrada;
	
	/**
	 * Inicializo el Frame.
	 */
	public Aplicacion() {
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
				| UnsupportedLookAndFeelException e2) {
			System.err.println("Error al establecer el tema");
		}
		
		setTitle("Gestor de memoria");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(200, 200, 480, 950);
		PanelGestor = new JPanel();
		PanelGestor.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(PanelGestor);
		PanelGestor.setLayout(null);
		BotonesVentana();
	}
		
	/**
	 * Escogemos fichero entrada y devolvemos la ruta de este.
	 *
	 * @return the string
	 */
	private String ArchivoEntrada() {
		String s;
		JFileChooser ch = new JFileChooser(System.getProperty("user.dir"));
		if(ch.showOpenDialog(PanelGestor) == JFileChooser.APPROVE_OPTION) { File f = ch.getSelectedFile(); s = f.getAbsolutePath(); }
		else s = "";
		return s;
	}
	
	/**
	 * Leemos el fichero de entrada y añadimos el proceso leido al fichero.
	 *
	 * @param nombre the nombre
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	private void LeerFichero(String nombre) throws IOException {
		try(BufferedReader br = new BufferedReader(new FileReader(nombre))) {
			for(String linea; (linea = br.readLine()) != null && linea.equals("")==false; ) {
				procesos.add(new Proceso(linea));
			}
		}
	}
		
	/**
	 * Pintamos de distinto color los rectángulos, es decir, los procesos que esten ocupando un bloque de memoria.
	 *
	 * @param hueco the hueco
	 * @param rect the rect
	 */
	private void pintar(int hueco, String rect) {
		Color colors[] = {
				Color.gray, Color.green, Color.orange, Color.magenta, Color.cyan, Color.blue,
				Color.yellow, Color.red, Color.white, Color.pink };
		JLabel fila = new JLabel(String.valueOf(hueco));
		fila.setOpaque(true);
		fila.setBounds(12, 120+40*hueco, 20, 15);
		PanelGestor.add(fila);
		for(int i = 0; i < 20; i++) {
			JLabel jlb = new JLabel();
			jlb.setOpaque(true);
			jlb.setBounds(35+20*i, 120+40*hueco, 15, 15);
			jlb.setBorder(BorderFactory.createLineBorder(Color.black,1));
			jlb.setBackground(colors[Character.getNumericValue(rect.charAt(i))%10]);
			PanelGestor.add(jlb);
		}
	}
	
	/**
	 * Recorro todos los procesos leídos y les voy asignando un hueco en función del algoritmo elegido.
	 *
	 * @param algoritmo the algoritmo
	 * @throws FileNotFoundException the file not found exception
	 * @throws UnsupportedEncodingException the unsupported encoding exception
	 */
	private void exportar(int algoritmo) throws FileNotFoundException, UnsupportedEncodingException {
		boolean insercion = false;
		PrintWriter ficheroSalida = new PrintWriter("particiones.txt", "UTF-8");//creamos fichero salida
		PanelGestor.removeAll(); // Si un algoritmo se ejecuta de nuevo, borramos todo lo anterior.
		BotonesVentana();
		
		for(int momento = 1; procesos.isEmpty()==false || memoria.vacio()==false; momento++) {
			for(int i = 0; i < procesos.size(); i++) {
				if(procesos.get(i).getLlegada() <= momento) {
					if(algoritmo == PeorHueco) insercion = memoria.peorHueco(procesos.get(i));
					if(algoritmo == MejorHueco) insercion = memoria.mejorHueco(procesos.get(i));	
					if(insercion) procesos.remove(i--); //reajustamos la posicion del vector	
				}
			}
			//dibujamos
			pintar(momento, memoria.toMap()); 
			PanelGestor.repaint();
			//imprimimos en pantalla y en el fichero
			ficheroSalida.println(momento + ": " + memoria.toString()); 
			System.out.println(momento + ": " + memoria.toString());
			memoria.decrementar(); //decrementamos el tiempo de vida
		}	
		ficheroSalida.close();
	}
		
	/**
	 * Inicializamos los botones de la ventana principal.
	 */
	private void BotonesVentana() {
		//mejor hueco
		JButton btnMejorHueco = new JButton("MEJOR HUECO");
		btnMejorHueco.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					LeerFichero(nombreFicheroEntrada);
					exportar(MejorHueco);
				} catch (IOException e1) {
					JOptionPane.showMessageDialog(PanelGestor, "Error, introduce un fichero de entrada",
							"Error en", JOptionPane.ERROR_MESSAGE);
					procesos.clear(); //Borramos si ha leído.
				}
			}
		});
		btnMejorHueco.setBounds(240, 80, 210, 60);
		btnMejorHueco.setFont(new Font("calibri", Font.BOLD, 18));
		PanelGestor.add(btnMejorHueco);
		
		//peor hueco
		JButton btnpeorHueco = new JButton("PEOR HUECO");
		btnpeorHueco.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					LeerFichero(nombreFicheroEntrada);
					exportar(PeorHueco);
				} catch (Exception e1) {
					JOptionPane.showMessageDialog(PanelGestor, "Error, introduce un fichero de entrada",
							"Error en", JOptionPane.ERROR_MESSAGE);
					procesos.clear(); //Borramos si se ha leído.
				}
			}
		});
		btnpeorHueco.setBounds(10, 80, 210, 60);
		btnpeorHueco.setFont(new Font("calibri", Font.BOLD, 18));
		PanelGestor.add(btnpeorHueco);
		
		// entrada
		JButton inButt = new JButton("ENTRADA");
		inButt.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(!(nombreFicheroEntrada = ArchivoEntrada()).equals(""))
					System.out.println("Entrada: " + nombreFicheroEntrada);
				else System.err.println("No se ha especificado ningún fichero");
			}
		});
		inButt.setBounds(10, 30, 440, 40);
		inButt.setFont(new Font("calibri", Font.BOLD, 14));
		PanelGestor.add(inButt);
	}
}

