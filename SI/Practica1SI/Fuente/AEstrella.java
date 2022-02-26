/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package AEstrella;

import static java.lang.Math.abs;
import static java.lang.Math.pow;
import static java.lang.Math.sqrt;
import java.util.ArrayList;


/**
 * Francisco Javier Perez Martinez
 * @author mirse
 */
public class AEstrella {
 
    //Mundo sobre el que se debe calcular A*
    Mundo mundo;
    
    //Camino
    public char camino[][];
    
    //Casillas expandidas
    int camino_expandido[][];
    
    //Número de nodos expandidos
    int expandidos;
    
    //Coste del camino
    float coste_total;
    
    public AEstrella(){
        expandidos = 0;
        mundo = new Mundo();
    }
    
    public AEstrella(Mundo m){
        //Copia el mundo que le llega por parámetro
        mundo = new Mundo(m);
        camino = new char[m.tamanyo_y][m.tamanyo_x];
        camino_expandido = new int[m.tamanyo_y][m.tamanyo_x];
        expandidos = 0;
        
        //Inicializa las variables camino y camino_expandidos donde el A* debe incluir el resultado
            for(int i=0;i<m.tamanyo_x;i++)
                for(int j=0;j<m.tamanyo_y;j++){
                    camino[j][i] = '.';
                    camino_expandido[j][i] = -1;
                }
    }
    
    private int Manhattan(Coordenada c1, Coordenada c2){
        
        return abs(c2.getX() - c1.getX()) + abs(c2.getY() - c1.getY());
    }
    
    private int Euclidea(Coordenada c1, Coordenada c2) {
        return (int) sqrt(pow((c1.getX() - c2.getY()), 2) + pow((c1.getY() - c2.getX()), 2));
    }
    
    /**
     * M�todo para convertir de coordenadas axiales a coordenadas c�bicas.
     * @param c
     * @return 
     */
    private Cube conversion(Coordenada c){
        int x = c.getX() - (c.getY() + (c.getY()&1)) / 2;
        int z = c.getY();
        int y = -x-z;
        return new Cube(x,y,z);
    } 
    
    private int Cubicas(Coordenada c1, Coordenada c2){
        Cube cubo = new Cube();
        return cubo.distanciaMapasHex(conversion(c1), conversion(c2));
    }
    
    /**
     * M�todo auxiliar para generar los hijos
     * @param n
     * @return 
     */
    private ArrayList<Estado> Adyacentes(Estado n){
         
        ArrayList<Estado> listaAdyacentes = new ArrayList<>();
        int comp = n.getC().getY() %2 != 0 ? 1:-1; //1 caso impar, -1 caso par.
        
        for(int i=-1;i<=1;i++){ // filas
            for(int j=-1;j<=1;j++){ // columnas
                if(i!=0 || j!=0){
                    if( i==0 || j != comp){
                        Coordenada adyC = new Coordenada(n.getC().getX()+j, n.getC().getY()+i);
                        Estado ady = new Estado(adyC, null);
                        
//                        *************** Heur�sticas ***************

//                        ady.setH(Manhattan(adyC, mundo.getDragon()));
//                          ady.setH(Euclidea(adyC, mundo.getDragon()));
                        ady.setH(Cubicas(adyC, mundo.getDragon()));
                        char celda = mundo.getCelda(ady.getC().getX(), ady.getC().getY());
                        if(celda != 'p' && celda != 'b') {
                            switch(celda){
                                case('c'):
                                    ady.setG(1);
                                    break;
                                case('h'):
                                    ady.setG(2);
                                    break;
                                case('a'):
                                    ady.setG(3);
                                    break;
                                case('d'):
                                    ady.setG(1);
                                    break;
                                default:
                                    break;
                            }
                            listaAdyacentes.add(ady);
                        }
                    }
                }
            }
        }
        return listaAdyacentes;
    }
    
    //Calcula el A*
    public int CalcularAEstrella(){

        boolean encontrado = false;
        int result = -1;
        
        //AQU�? ES DONDE SE DEBE IMPLEMENTAR A*
        
        //Nodos que vamos seleccionando para expandir, es decir, para que estos generen hijos.
        ArrayList<Estado> listaInterior = new ArrayList<>();
        //Inicio, almacenar nodos que son adyacentes y aptos para ser evaluados.
        ArrayList<Estado> listaFrontera = new ArrayList<>();
        
        //Guardamos las coordeandas del drag�n y el caballero(inicial).
        Coordenada dragon = mundo.getDragon();
        Coordenada caballero = mundo.getCaballero();
        
        listaFrontera.add(new Estado(caballero,null));
        
        while(!listaFrontera.isEmpty() && !encontrado){
            if(caballero.getY() == dragon.getY() && caballero.getX() == dragon.getX()){
                return result;
            }
            
            //Estado inicial, posicion 0 de la lista, es decir, la del caballero.
            Estado n = listaFrontera.get(0);
            
            //Buscar nodo con menor funci�n de coste.
            for(Estado menor : listaFrontera){
                if(menor.getF() < n.getF()){
                    n = menor;
                }
                else if(menor.getF() == n.getF()){
                    if(menor.getG() < n.getG()){
                        n = menor;
                    }
                }
            }
            
            //aumentando caminos expandidos
            camino_expandido[n.getC().getY()][n.getC().getX()] = expandidos;
            expandidos++;
            
            //Si el dragon ha sido encontrado.
            if(n.getC().getY() == dragon.getY() && n.getC().getX() == dragon.getX()) {
                encontrado = true;
                coste_total = n.getG();
                result = (int) coste_total;
                
                while(n != null){
                    camino[n.getC().getY()][n.getC().getX()] = 'X'; //Dibujar camino
                    n = n.getPadre();
                }
            }
            //Si el dragon no ha sido encontrado.
            else {
//                for(int i = 0; i<listaFrontera.size();i++){
//                    System.out.println("ListaFrontera: " + listaFrontera.get(i).getC());
//                }
                listaFrontera.remove(n);
                listaInterior.add(n);
//                
//                for(int i = 0; i<listaFrontera.size();i++){
//                    System.out.println("ListaFrontera Despues: " + listaFrontera.get(i).getC());
//                }
//                
//                for(int i = 0; i<listaInterior.size();i++){
//                    System.out.println("ListaInterior: " + listaInterior.get(i).getC());
//                }
//                System.out.println('\n');
                
                ArrayList<Estado> ady = Adyacentes(n);
//                System.out.println("G: " + n.getG() + " -- H: " + n.getH() + " -- F: " + n.getF() + " " + n.getC() + '\n');
                
                for(Estado hijo : ady){
                    boolean findI = false;
                    
                    //para cada hijo m de n que no est� en lista interior
                    for(int i=0;i<listaInterior.size();i++){
                        if(hijo.getC().getX() == listaInterior.get(i).getC().getX() && hijo.getC().getY() == listaInterior.get(i).getC().getY()){
                            findI = true;
                        }
                    }               
                    if(!findI){
                        int G = hijo.getG() + n.getG();
                        int newH = hijo.getH();
                        boolean findF = false;
                        
                        //Comprobar si el hijo est� en listaFrontera
                        for(int j=0;j<listaFrontera.size() && !findF;j++){
                            if(hijo.getC().getX() == listaFrontera.get(j).getC().getX() && hijo.getC().getY() == listaFrontera.get(j).getC().getY()){
                                findF = true;
                            }
                        }  
                        // Si no se encuentra, creamos el hijo y a�adimos a listaFrontera.
                        if(!findF){
                            hijo.setG(G);
                            hijo.setH(newH);
                            hijo.setPadre(n);
                            listaFrontera.add(hijo);
                        }
                        //si el hijo se encuentra...
                        else {
                            // Si g del hijo menor que el que se encuentra en listaFrontera (mirar el mejor)
                            if(G < hijo.getG()){
                                hijo.setG(G);
                                hijo.setH(newH);
                                hijo.setPadre(n);
                                listaFrontera.remove(hijo); //Elimino el hijo de listaFrontera.
                                listaFrontera.add(hijo); //A�ado el hijo evaluado.
                            }
                        }
                    }
                }
            }
        }

        //Si ha encontrado la solución, es decir, el camino, muestra las matrices camino y camino_expandidos y el número de nodos expandidos
        if(encontrado){
            //Mostrar las soluciones
            System.out.println("Camino");
            mostrarCamino();

            System.out.println("Camino explorado");
            mostrarCaminoExpandido();
            
            System.out.println("Nodos expandidos: "+expandidos);
        }

        return result;
    }

    //Muestra la matriz que contendrá el camino después de calcular A*
    public void mostrarCamino(){
        for (int i=0; i<mundo.tamanyo_y; i++){
            if(i%2==0)
                System.out.print(" ");
            for(int j=0;j<mundo.tamanyo_x; j++){
                System.out.print(camino[i][j]+" ");
            }
            System.out.println();   
        }
    }
    
    //Muestra la matriz que contendrá el orden de los nodos expandidos después de calcular A*
    public void mostrarCaminoExpandido(){
        for (int i=0; i<mundo.tamanyo_y; i++){
            if(i%2==0)
                    System.out.print(" ");
            for(int j=0;j<mundo.tamanyo_x; j++){
                if(camino_expandido[i][j]>-1 && camino_expandido[i][j]<10)
                    System.out.print(" ");
                System.out.print(camino_expandido[i][j]+" ");
            }
            System.out.println();   
        }
    }
    
    public void reiniciarAEstrella(Mundo m){
        //Copia el mundo que le llega por parámetro
        mundo = new Mundo(m);
        camino = new char[m.tamanyo_y][m.tamanyo_x];
        camino_expandido = new int[m.tamanyo_y][m.tamanyo_x];
        expandidos = 0;
        
        //Inicializa las variables camino y camino_expandidos donde el A* debe incluir el resultado
            for(int i=0;i<m.tamanyo_x;i++)
                for(int j=0;j<m.tamanyo_y;j++){
                    camino[j][i] = '.';
                    camino_expandido[j][i] = -1;
                }
    }
    
    public float getCosteTotal(){
        return coste_total;
    }
}


