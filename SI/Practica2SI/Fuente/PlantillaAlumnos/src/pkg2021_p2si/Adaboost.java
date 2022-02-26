/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg2021_p2si;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.text.DecimalFormat;
import java.util.ArrayList;

/**
 *
 * @author fidel
 * @author-2 Francisco Javier Pérez Martínez
 */
public class Adaboost {
    
    // Nº de clasificadores débiles a usar.
    private static final int T = 100;
    // Nº de pruebas aleatorias.
    private static final int A = 85;
    // % para aplicar al conjunto de entrenamiento
    private static final double P = 0.80;
    // Indicar una clase
    private static int tipoImagen;
    
    public static int Byte2Unsigned(byte b) {
        return b & 0xFF;
    }
    
    /**
     * Función para rellenar el vector X(imagenes) y el vector Y(clase real) tanto para conjunto de entrenamiento como para de test.
     * @param X
     * @param Y
     * @param Xtest
     * @param Ytest
     * @param porcentaje 
     * @param total 
     * @param tipoImagen 
     * @param choose 
     */
    public static void fillXandY(ArrayList<Imagen> X, int[] Y, ArrayList<Imagen> Xtest, int[] Ytest, double porcentaje, int total, int tipoImagen, boolean choose)
    {
        CIFAR10Loader ml = new CIFAR10Loader();
        ml.loadDBFromPath("./cifar10_2000");
        if(choose){
            int indice = 0;
            for(int i=0;i<=9;i++){
                 ArrayList d1imgs = ml.getImageDatabaseForDigit(i);
                if(i==tipoImagen){ // accedemos a la clase indicada i
                    for(int j=0;j<(int) porcentaje;j++){   
                        Imagen img = (Imagen) d1imgs.get(j);
                        X.add(img);
                        Y[indice] = 1;
                        indice++;
                    }
                } else {
                    // Resto de imagenes.
                    for(int j=0;j<(int) porcentaje/9;j++){
                        Imagen img = (Imagen) d1imgs.get(j);
                        X.add(img);
                        Y[indice] = -1;
                        indice++;
                    }
                }
            }
        } else {
            int indice = 0;
            for(int i=0;i<=9;i++){
                 ArrayList d1imgs = ml.getImageDatabaseForDigit(i);
                if(i==tipoImagen){ // accedemos a la clase indicada i
                    for(int j=(int) porcentaje;j<total;j++){   
                        Imagen img = (Imagen) d1imgs.get(j);
                        Xtest.add(img);
                        Ytest[indice] = 1;
                        indice++;
                    }
                } else {
                    // Resto de imagenes.
                    for(int j=0;j<(total-porcentaje)/9;j++){
                        Imagen img = (Imagen) d1imgs.get(j);
                        Xtest.add(img);
                        Ytest[indice] = -1;
                        indice++;
                    }
                }
            }
        }
    }
    
    /**
     * Función auxiliar de entrenamiento de un clasificadorDebil
     * @param X
     * @param Y
     * @param D 
     * @return  
     */
    public static clasificadorDebil trainClasifDebil(ArrayList<Imagen> X, int[] Y, double[] D)
    {
        ArrayList<clasificadorDebil> clasDeb = new ArrayList<>();
        
        for(int i=1;i<=A;i++){
            clasificadorDebil cD = clasificadorDebil.generalClasifAzar(X.size());
            cD.aplicarClasifDebil(cD, X);
            cD.obtenerErrorClasif(cD, X, Y, D);
            clasDeb.add(cD);
        }
        clasificadorDebil mejor = null;
        mejor = clasDeb.get(0);
        for(int j=1;j<clasDeb.size();j++){
            if(mejor.getError() > clasDeb.get(j).getError()){
               mejor = clasDeb.get(j); //obtenemos el menor comprobando el que tenga menor tasa de error.
            }    
        }
        return mejor;
    }
    
    /**
     * Función adaboost que devuelve un clasificador fuerte
     * @param X
     * @param Y
     * @return 
     */
    public static clasificadorFuerte Adaboost(ArrayList<Imagen> X, int[] Y, ArrayList<Imagen> Xtest, int[] Ytest)
    {
        double[] D = new double[X.size()];
        ArrayList<clasificadorDebil> H = new ArrayList<>();
//        clasificadorFuerte cF = null;
//        clasificadorFuerte cFtrain = null;
        
        for(int i=0;i<X.size();i++){
            D[i] = 1.0/(double) X.size(); // Indicamos como de dificil es de clasificar cada punto.
        }
        for(int t=1;t<=T;t++){
            // función que calcula y aplica clasificadores débiles
            // devolviendo el clasificador debil que mejor clasfica
            clasificadorDebil mejor = trainClasifDebil(X, Y, D);

            double confianza = 0.5 * Math.log((1.0-mejor.getError())/mejor.getError()) / Math.log(2);
            mejor.setConfianza(confianza);

            double Z = 0.0;
            double[] numD = new double [X.size()];
            //Actualizar pesos
            for(int i=0;i<X.size();i++){ //numerador
                double outClasif = -mejor.getConfianza() * Y[i] * mejor.getPertenece()[i];
                numD[i] = D[i] * Math.pow(Math.E, outClasif);
                Z += numD[i];// suma de todos los numeradores
            }     
            for(int j=0;j<X.size();j++){
                D[j] = numD[j]/Z;
            }
            H.add(mejor);
            
//            cF = new clasificadorFuerte(H, Xtest.size());
//            cFtrain = new clasificadorFuerte(H, X.size());
//            cFtrain.aplicarClasificadorFuerte(X);
//            cF.aplicarClasificadorFuerte(Xtest);
//            int aciertosTest = Xtest.size() - cF.obtenerErrorClasif(Xtest, Ytest);         
//            double percentTest = (aciertosTest/(double) Xtest.size()) * 100;
//            int aciertos = X.size() - cFtrain.obtenerErrorClasif(X, Y);         
//            double percent = (aciertos/(double) X.size()) * 100;
//            DecimalFormat dfTest = new DecimalFormat("#.00");
//            System.out.println(dfTest.format(percent) + "\t" + dfTest.format(percentTest));
              
//            int aciertos = mejor.getAciertos();
//            DecimalFormat df = new DecimalFormat("#.00");
//            double percent = (aciertos/(double) X.size()) * 100;
//            System.out.println(df.format(percent));
        }
        return new clasificadorFuerte(H, X.size());
    }
    
    /**
     * Función que devuelve el nº de imágenes de un directorio
     * @param directorio
     * @return 
     */
    public static int totalArchivos(File directorio) {
        
        int total = 0;
        String[] arrArchivos = directorio.list();
        total += arrArchivos.length;
        File tmpFile;
        
        for(int i=0; i<arrArchivos.length; ++i){
            tmpFile = new File(directorio.getPath() + "/" +arrArchivos[i]);
            if(tmpFile.isDirectory()){
              total += totalArchivos(tmpFile);
            }
        }
        return total;
    }
    
    /**
     * Función para almacenar los clasificadores fuertes obtenidos.
     * @param cFuertes 
     */
    public static void almacenarClasificadoresFuertes(ArrayList<clasificadorFuerte> cFuertes){
        
        PrintWriter fichero = null;
        String file = "fichero_clasificadores_fuertes.txt";
        
        try {
            fichero = new PrintWriter(new OutputStreamWriter(new FileOutputStream(new File(file)), StandardCharsets.UTF_8));
            PrintWriter pw = new PrintWriter(fichero);
            
            String out = "";
            for(int i=0;i<cFuertes.size();i++){
                out += cFuertes.get(i).toString();
                pw.println(out);
                out = "";
            }
        } catch (Exception e){
            e.printStackTrace();
        }  finally {
           try {
            if (null != fichero)
               fichero.close();
            } catch (Exception e2) {
               e2.printStackTrace();
            }
        }
    }
    
    /**
     * Función para leer los clasificadores fuertes almacenados en un fichero
     * @return 
     */
    public static ArrayList<clasificadorFuerte> leerFichero(){
       
        ArrayList<clasificadorFuerte> cFuertes = new ArrayList<>();
        
        String nombreFichero = "fichero_clasificadores_fuertes.txt";
        //Declarar una variable BufferedReader
        BufferedReader br = null;
        try {
            String texto = "";
           //Crear un objeto BufferedReader al que se le pasa 
           //   un objeto FileReader con el nombre del fichero
           br = new BufferedReader(new FileReader(nombreFichero));
           //Leer la primera línea, guardando en un String
           //Repetir mientras no se llegue al final del fichero
           while( (texto = br.readLine()) != null)
           {
               clasificadorFuerte cF = null;
               String cadena[] = texto.split("\\/");
               ArrayList<clasificadorDebil> cFuerte = new ArrayList<>();
               for(int i=0;i<cadena.length;i++){
                   clasificadorDebil cD = new clasificadorDebil();
//                   System.out.println(cadena[i]);
                   String cadenaDebil[] = cadena[i].split("\\,");
                   cD.setPixel(Integer.parseInt(cadenaDebil[0]));
                   cD.setUmbral(Integer.parseInt(cadenaDebil[1]));
                   cD.setDireccion(Integer.parseInt(cadenaDebil[2]));
                   cD.setConfianza(Double.parseDouble(cadenaDebil[3]));
                   
                   cFuerte.add(cD);
               }
               cF = new clasificadorFuerte(cFuerte);
               cFuertes.add(cF);
           }
        }
        catch (FileNotFoundException e) {
            System.out.println("Error: Fichero no encontrado");
            System.out.println(e.getMessage());
        }
        catch(Exception e) {
            System.out.println("Error de lectura del fichero");
            System.out.println(e.getMessage());
        }
        finally {
            try {
                if(br != null)
                    br.close();
            }
            catch (Exception e) {
                System.out.println("Error al cerrar el fichero");
                System.out.println(e.getMessage());
            }
        }
        return cFuertes;
    }
    
    /**
     * Función que muestra por pantalla el % de acierto de cada clasificador fuerte tanto de entrenamiento como test.
     * @param i
     * @param tam
     * @param aciertos
     * @param tamTest
     * @param aciertosTest 
     */
    public static void mostrarAciertosDeCadaClase(int i, int tam, int aciertos, int tamTest, int aciertosTest) {
        
        DecimalFormat df = new DecimalFormat("#.00");
        double percent = (aciertos/(double) tam) * 100;
        double percentTest = (aciertosTest/(double) tamTest) * 100;
        
        System.out.println("----------------------------------------" + "\t\t" + "----------------------------------------");
        System.out.println("Clase: " + i + "\t\t\t\t\t\t" + "Clase: " + i);
        System.out.println("El numero de aciertos sobre " + tam + " imágenes es: " + aciertos + "\t" + "El numero de aciertos sobre " + tamTest + " imágenes es: " + aciertosTest);
        System.out.println("% De acierto del clasificador fuerte: " + df.format(percent) + '%' + "\t\t" + "% De acierto del clasificador fuerte: " + df.format(percentTest) + '%' + "\n");
//        System.out.println(df.format(percent));
    }
    
    /**
     * Función que muestra por pantalla el % medio de acierto de cada clasificador fuerte tanto de entrenamiento como test.
     * @param totalImagenes
     * @param aciertosTotales
     * @param totalImagenesTest
     * @param aciertosTotalesTest 
     */
    public static void mostrarMediaAciertos(int totalImagenes, int aciertosTotales, int totalImagenesTest, int aciertosTotalesTest) {
        
        double pMedio = (aciertosTotales/ (double) totalImagenes) * 100;
        double pMedioTest = (aciertosTotalesTest/ (double) totalImagenesTest) * 100;
        DecimalFormat df = new DecimalFormat("#.00");
        System.out.println("########################################################################################################");
        System.out.println("\n" + "Estadísticas Media - Conjunto de Entrenamiento" + "\t\t" + "Estadísticas Media - Conjunto de Test" + "\n");
        System.out.println("----------------------------------------" + "\t\t" + "----------------------------------------");
        System.out.println("El numero de aciertos sobre " + totalImagenes + " imágenes es: " + aciertosTotales + "\t" + "El numero de aciertos sobre " + totalImagenesTest + " imágenes es: " + aciertosTotalesTest);
        System.out.println("% De acierto del clasificador fuerte: " + df.format(pMedio) + '%' + "\t\t" + "% De acierto del clasificador fuerte: " + df.format(pMedioTest) + '%' + "\n");
    }
    
    /**
     * Función que devuelve una arraylist de todos los clasificadores fuertes generados.
     * @return 
     */
    public static ArrayList<clasificadorFuerte> AdaboostParaTodasLasClases() {
        
        int aciertosTotales = 0, aciertosTotalesTest = 0;
        int totalImagenes = 0, totalImagenesTest = 0;
        ArrayList<clasificadorFuerte> clasifFuertes = new ArrayList<>();
        
        System.out.println("\n" + "Estadísticas - Conjunto de Entrenamiento" + "\t\t" + "Estadísticas - Conjunto de Test" + "\n");
        for(int i=0;i<=9;i++){
            File directorio = new File("./cifar10_2000/" + i);
            int total = totalArchivos(directorio);
            
            ArrayList<Imagen> X = new ArrayList<>();
            ArrayList<Imagen> Xtest = new ArrayList<>();
                
            double porcentaje = total * P;
            int[] Y = new int[(int) porcentaje * 2]; // Le asigno un tamaño mayor ya que sino daba error de ArrayIndexOutOfBoundsException.
            int[] Ytest = new int[(int) porcentaje * 2];
            tipoImagen = i;
            fillXandY(X, Y, Xtest, Ytest, porcentaje, total, tipoImagen, true);
            fillXandY(X, Y, Xtest, Ytest, porcentaje, total, tipoImagen, false);
            clasificadorFuerte cF = Adaboost(X,Y,Xtest,Ytest);
            cF.aplicarClasificadorFuerte(X); // Aplicamos el clasificador fuerte para el conjunto de entrenamiento.
            
            int aciertos = X.size() - cF.obtenerErrorClasif(X, Y);         
            aciertosTotales += aciertos;
            totalImagenes += X.size();
            
            cF.aplicarClasificadorFuerte(Xtest); // Aplicamos el clasificador fuerte para el conjunto de test.
            int aciertosTest = Xtest.size() - cF.obtenerErrorClasif(Xtest, Ytest);         
            aciertosTotalesTest += aciertosTest;
            totalImagenesTest += Xtest.size();
            
            // Mostrar estadísticas
            mostrarAciertosDeCadaClase(i, X.size(), aciertos, Xtest.size(), aciertosTest);
            clasifFuertes.add(cF);
        }
        mostrarMediaAciertos(totalImagenes, aciertosTotales, totalImagenesTest, aciertosTotalesTest);
        return clasifFuertes;
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        //Son necesarios dos argumentos 
        if (args.length == 2) {
            
            //Se ejecuta la práctica como entrenamiento
            if (args[0].equals("-t")) {
                
                ArrayList<clasificadorFuerte> cFuertes = new ArrayList<>();
                
                cFuertes = AdaboostParaTodasLasClases();
                almacenarClasificadoresFuertes(cFuertes);
                
            } else {
                //Se ejecuta la práctica como test
                File ImageFile = new File("./" + args[1]); // le pasamos la imagen
                ArrayList<clasificadorFuerte> cFuertesFichero = new ArrayList<>();
                cFuertesFichero = leerFichero(); // leemos los 10 clasificadores fuertes
                Imagen image = new Imagen(ImageFile); // creamos la imagen con el archivo pasado
                ArrayList<Imagen> imagenes = new ArrayList<>();
                
                imagenes.add(image);
                
                int tipoClase = -1;
                double valor = 0.0;
                
                for(int i=0;i<cFuertesFichero.size();i++){
                    clasificadorFuerte cF = cFuertesFichero.get(i);
                    double auxH = cF.obtenerHipotesisFinal(imagenes); //obtenemos los valores de H 
//                    System.out.println("auxH = " + auxH);
                    
                     if(valor < auxH){ //comprobamos que H es la mayor
                        valor = auxH;
                        tipoClase = i;
                    } 
                }
                // Imprimimos la H mayor con su respectiva representación del objeto (imagen).
                System.out.println("\nClasificación de la imagen \n");
                System.out.println("--------------------------------------------");
                System.out.println("La imagen " + args[1] + " representa al objeto: " + tipoClase);
                
//                for(int i=0;i<cFuertesFichero.size();i++){
//                    System.out.println("<" + i + ">" + "\n" + cFuertesFichero.get(i).toString());
//                }
            }
        } else {
            System.out.println("El número de parámetros es incorrecto");
            System.out.println("Las posibilidades son:");
            System.out.println("Adaboost –t <fichero_almacenamiento_clasificador_fuerte>");
            System.out.println("Adaboost <fichero_origen_clasificador_fuerte> <imagen_prueba>");
        }
    }
}