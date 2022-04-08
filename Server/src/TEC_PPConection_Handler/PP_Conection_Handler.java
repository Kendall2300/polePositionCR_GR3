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
        InputStream input= null;
        BufferedReader brinp = null;
        PrintWriter output= null;
        String line;
        try{
            input = socketToHandle.getInputStream();
            brinp = new BufferedReader(new InputStreamReader(input));
            output = new PrintWriter(socketToHandle.getOutputStream());

            line = brinp.readLine();
            System.out.println(line);
            if ((line == null) || line.equalsIgnoreCase("QUIT")){
                socketToHandle.close();
            }else {
                System.out.println(line);
                output.println(line + "\n");
                output.flush();
            }
        }catch (Exception error){
            System.out.println(error);
            System.out.println("Error manejando al cliente: "+error);
            return;
        }
    }
}
//investigar sobre la sincronia y asincronia de datos porque si no espera a la terminacion
//de uno de los sistemas para darrespuesta.
