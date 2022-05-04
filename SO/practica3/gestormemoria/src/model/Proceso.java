package model;

/**
 * Clase Proceso: traduce la informacion del fichero a objetos "procesos".
 *
 * @author Francisco Javier Perez Martinez 74384305M
 * @author Francisco Joaquin Murcia Gomez 48734281H
 */
public class Proceso {
	
	/** Nombre del proceso. */
	private String name;
	
	/** Instante de llegada. */
	private int llegada;
	
	/** Tamaño que ocupa en memoria el proceso. */
	private int size;
	
	/** Instantes que dura en su ejecución. */
	private int duracion;
	
	/** Direccion de memoria incial. */
	private int d_inicio;	
	
	
	/**
	 * Dividimos el string en funcion de sus espacios y asignamos los campos al proceso.
	 *
	 * @param linea the linea
	 */
	public Proceso(String linea) {
		
		String[] cadena = linea.split(" "); // Separamos por espacios lo leído en cada línea.
		this.name = cadena[0];
		this.llegada = Integer.parseInt(cadena[1]);
		this.size = Integer.parseInt(cadena[2]);
		this.duracion = Integer.parseInt(cadena[3]);
		setInicio(0); // aun no conocemos la direccion de comienzo en la memoria
	}
	/**
	 * Aqui creamos el ultimo hueco de la memoria.
	 */
	public Proceso() {
		this.llegada = 0;
		this.duracion = 0;
		this.d_inicio = 0;
		this.size = Memoria.MAXMEMORIA;
	}
	
	/**
	 * Gets the name.
	 *
	 * @return the name
	 */
	public String getName() { 
		return name;
	}
	
	/**
	 * Gets the llegada.
	 *
	 * @return the llegada
	 */
	public int getLlegada() { 
		return llegada; 
	}
	
	/**
	 * Gets the size.
	 *
	 * @return the size
	 */
	public int getSize() { 
		return size;
	}
	
	/**
	 * Gets the duracion.
	 *
	 * @return the duracion
	 */
	public int getDuracion() { 
		return duracion; 
	}
	
	/**
	 * Gets the start.
	 *
	 * @return the start
	 */
	public int getStart() { 
		return d_inicio; 
	}
	
	/**
	 * Sets the name.
	 *
	 * @param nombre the new name
	 */
	public void setName(String nombre) { 
		this.name = nombre; 
	}
	
	/**
	 * Sets the llegada.
	 *
	 * @param arrival the new llegada
	 */
	public void setLlegada(int arrival) { 
		this.llegada = arrival; 
	}
	
	/**
	 * Sets the size.
	 *
	 * @param size the new size
	 */
	public void setSize(int size) { 
		this.size = size; 
	}
	
	/**
	 * Sets the duracion.
	 *
	 * @param tiempo the new duracion
	 */
	public void setDuracion(int tiempo) { 
		this.duracion = tiempo;
	}
	
	/**
	 * Sets the inicio.
	 *
	 * @param inicio the new inicio
	 */
	public void setInicio(int inicio) { 
		this.d_inicio = inicio; 
	}
	/**
	 * Por cada instante que pase, debemos disminuir la duracion del proceso hasta que termine.
	 */
	public void disminuir() { 
		if(duracion > 0) {
			duracion--;
		}
	}

	/**
	 * To string.
	 *
	 * @return the string
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder("[" + d_inicio);
		
		if(duracion > 0) { // Si tiene duracion es un proceso
			sb.append(" " + name + " ");
		}
		else { // Cuando no tiene duracion es porque es un hueco
			sb.append(" HUECO ");
		}
		sb.append(size + "]");
		return sb.toString();
	}
	
	
}
