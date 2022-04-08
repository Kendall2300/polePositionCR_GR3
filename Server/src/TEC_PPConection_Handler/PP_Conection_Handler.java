package TEC_PPConection_Handler;

import java.io.*;
import java.net.*;

/**
 *
 */
public class PP_Conection_Handler implements Runnable {
    protected Socket socketToHandle;
    public PP_Conection_Handler(Socket aSocketToHandle){
        socketToHandle=aSocketToHandle;
    }
    public void run(){
        try {
            File archivo=new File("..\\src\\variables\\out.txt");
            FileReader f_reader=new FileReader(archivo);
            BufferedReader buf_reader=new BufferedReader(f_reader);
            FileWriter fichero=new FileWriter("..\\src\\variables\\out.txt");
            PrintWriter p_write=new PrintWriter(fichero);
            String linea=buf_reader.readLine();
            while(linea!=null){
                System.out.println(linea);
                /*if (line==escriba aqui lo que ocupa dependiendo de lo escrito por el cliente){

                    escriba aqui la logica, el
                    tuto: http://chuwiki.chuidiang.org/index.php?title=Lectura_y_Escritura_de_Ficheros_en_Java

                }*/
            }

        }catch (FileNotFoundException error){
            System.out.println("Ocurrio un problema, identificador: "+error);
        } catch (IOException e) {
            System.out.println("Problema con identificador: "+e);
        }
    }
}
