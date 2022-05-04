package main;
import java.awt.EventQueue;

import model.Aplicacion;

/**
 * @author Francisco Javier Perez Martinez 74384305M
 * @author Francisco Joaquin Murcia Gomez 48734281H
 */
public class main1 {

	/**
	 * The main method.
	 *
	 * @param args the arguments
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Aplicacion app = new Aplicacion();
					app.setVisible(true);//para ver la ventana
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
}
