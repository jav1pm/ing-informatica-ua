package model;
import java.util.ArrayList;

/**
 * Clase Memoria: en esta clase están implementados los algoritmos de mejor y peor hueco y
 * el array con los espacios de memoria.
 *
 * @author Francisco Javier Perez Martinez 74384305M
 * @author Francisco Joaquin Murcia Gomez 48734281H
 */
public class Memoria {
	
	/** MEMORIA MAXIMA = 2000. */
	public static final int MAXMEMORIA = 2000;
	
	/** ultimo asignado. */
	public static int ultimoAsignado = 0;
	
	/** procesos. */
	private ArrayList<Proceso> procesos = new ArrayList<Proceso>();
	
	/**
	 * Tratamos el hueco restante de toda la memoria como si fuera un proceso.
	 */
	public Memoria() {
		procesos.add(new Proceso());
	}

	/**
	 * Vacío si solo hay un proceso.
	 *
	 * @return true, if is empty
	 */
	public boolean vacio() { 
		return procesos.size() == 1; 
	}
	/**
	 * Agregar proceso, insertamos el proceso en memoria, ademas insertamos le inicio y el final.
	 *
	 * @param nuevo the nuevo
	 * @param pos the pos
	 */
	private void agregarProceso(Proceso nuevo, int pos) {
		
		nuevo.setInicio(procesos.get(pos).getStart());
		procesos.get(pos).setInicio(procesos.get(pos).getStart() + nuevo.getSize());
		procesos.get(pos).setSize(procesos.get(pos).getSize() - nuevo.getSize());
		if(procesos.get(pos).getSize() == 0) procesos.remove(pos);
		procesos.add(pos, nuevo);
	}
	
	/**
	* Le quitamos una unidad de tiempo a todos los procesos en memoria.
	*/
	public void decrementar(){
		for(Proceso p : procesos) 
			p.disminuir();
		//Compruebamos si se crean nuevos huecos, en ese caso los metemos
		for(int i = 0; i < procesos.size(); i++) {
			if(procesos.get(i).getDuracion() == 0) { //Solo hacemos el acople si el actual es un hueco
				int next = i + 1;
				while(next < procesos.size() && procesos.get(next).getDuracion() == 0) {
					
					procesos.get(i).setSize(procesos.get(i).getSize() + procesos.get(next).getSize());
					procesos.remove(next); 
				}
			}
		}
	}
	
	/**
	* Algoritmo de PeorHueco.
	*
	* @param nuevo the nuevo
	* @return true, if successful
	*/
	public boolean peorHueco(Proceso nuevo){
		int posPeor = -1;

		for(int i = 0; i < procesos.size(); i++) 
			if(procesos.get(i).getDuracion() == 0 && nuevo.getSize() <= procesos.get(i).getSize()) {//Busca el primer hueco que encuentre
				if(posPeor == -1) {
					posPeor = i; 
				}
				//Si es mayor que la que tengo, me la quedo
				else if((procesos.get(i).getSize() - nuevo.getSize()) > (procesos.get(posPeor).getSize() - nuevo.getSize())) {
					posPeor = i;
				}
			}
		if(posPeor != -1) agregarProceso(nuevo, posPeor);
		
		return posPeor != -1;
	}
	
	/**
	* Algoritmo de MejorHueco.
	*
	* @param nuevo the nuevo
	* @return true, if successful
	*/
	public boolean mejorHueco(Proceso nuevo){
		int posMejor = -1;
		
		for(int i = 0; i < procesos.size(); i++) 
			if(procesos.get(i).getDuracion() == 0 && nuevo.getSize() <= procesos.get(i).getSize()) {//Busca el primer hueco que encuentre
				if(posMejor == -1) {
					posMejor = i; 
				}
				//Si es menor que la que tengo, me la quedo
				else if(procesos.get(i).getSize() - nuevo.getSize() < procesos.get(posMejor).getSize() - nuevo.getSize()) {
					posMejor = i;
				}
			}
		if(posMejor != -1) agregarProceso(nuevo, posMejor);
		
		return posMejor != -1;
	}
	
	/**
	* Devolvemos un string de 20 caracteres que nos servirá de mapa para pintar cada bloque de memoria de un color en función del número que tenga
	* el proceso dentro del campo nombre. Si el nombre del proceso no lleva ningún número, se verá como si fuera hueco
	* @return the string
	*/
	public String toMap() {
		StringBuilder sb = new StringBuilder();
		for(Proceso p : procesos) {
			String str = p.getName();
			String id = "";
			if(str != null) id = str.replaceAll("[^0-9]", "");
			if(id.equals("") || p.getDuracion() == 0) id = "0";
			
			for(int i = 0; i < p.getSize() / 100; i++) {
				sb.append(id);
			}
		}
		return sb.toString();
	}
	
	/**
	* Concatenamos todos los procesos que tenga la memoria.
	*
	* @return the string
	*/
	public String toString() {
		StringBuilder sb = new StringBuilder();
		
		for(int i=0; i<procesos.size(); i++) {
			sb.append(procesos.get(i).toString() + " ");
		}
		return sb.toString();
	}
}
