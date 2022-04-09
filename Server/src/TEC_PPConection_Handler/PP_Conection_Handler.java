package TEC_PPConection_Handler;

import TEC_PP_Player.PP_Jugadores;
import TEC_PP_Player.PP_Player;
import java.io.*;
import java.net.*;

/**
 * @author kendall Martinez Carvajal kendallmc@estudiantec.cr
 */
public class PP_Conection_Handler implements Runnable {
    protected Socket socketToHandle;

    /**
     * Este metodo se encarga de recibir y establecer el socket que se desea manipular
     * @param aSocketToHandle un socket que se desea manipular
     */
    public PP_Conection_Handler(Socket aSocketToHandle){
        socketToHandle=aSocketToHandle;
    }
    public void run(){
        try {
            File archivo=new File("src/variables/out.txt");
            FileReader f_reader=new FileReader(archivo);
            BufferedReader buf_reader=new BufferedReader(f_reader);
            String linea=buf_reader.readLine();
            buf_reader.close();
            if(linea==null){
                FileWriter fichero=new FileWriter("src/variables/out.txt");
                PrintWriter p_write=new PrintWriter(fichero);
                PP_Jugadores jugador=new PP_Player();
                p_write.println(jugador.inicio=0);
                p_write.println(jugador.vidas=3);
                p_write.println(jugador.score=0);
                p_write.println(jugador.x_pos=179);
                p_write.println(jugador.y_pos=640);
                p_write.println(jugador.diferencia_y=0);
                p_write.close();

            }else{
                FileWriter fichero=new FileWriter("src/variables/out.txt");
                FileWriter fichero2=new FileWriter("src/variables/out2.txt");
                PrintWriter p_write=new PrintWriter(fichero);
                PrintWriter p2_write=new PrintWriter(fichero2);
                PP_Jugadores jugador1=new PP_Player(); jugador1.inicio=1;
                p_write.println(jugador1.inicio); p_write.println(jugador1.vidas=3);
                p_write.println(jugador1.score=0); p_write.println(jugador1.x_pos=179);
                p_write.println(jugador1.y_pos=640); p_write.println(jugador1.diferencia_y=0);
                p_write.close();

                PP_Jugadores jugador2=new PP_Player();
                p2_write.println(jugador2.inicio=1); p2_write.println(jugador2.vidas=3);
                p2_write.println(jugador2.score=0); p2_write.println(jugador2.x_pos=279);
                p2_write.println(jugador2.y_pos=640); p2_write.println(jugador2.diferencia_y=0);
                p2_write.close();
            }
        }catch (FileNotFoundException error){
            System.out.println("Ocurrio un problema, al manejar el txt: "+error);
        } catch (IOException e) {
            System.out.println("Problema con identificador: "+e);
        }
    }
}
