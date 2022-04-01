package TEC_PPConection_Handler;

import java.io.*;
import java.net.*;


public class PP_Conection_Handler implements Runnable {
    protected Socket socketToHandle;
    public PP_Conection_Handler(Socket aSocketToHandle){
        socketToHandle=aSocketToHandle;
    }
    public void run(){
        try{
            PrintWriter streamWriter = new PrintWriter(socketToHandle.getOutputStream());
            BufferedReader streamReader = new BufferedReader((new InputStreamReader(socketToHandle.getInputStream())));

            String fileToRead = streamReader.readLine();
            BufferedReader fileReader = new BufferedReader(new FileReader(fileToRead));

            String line = null;
            while ((line = fileReader.readLine()) != null){
                streamWriter.println(line);
            }

            fileReader.close();
            streamWriter.close();
            streamReader.close();
        }catch (Exception error){
            System.out.println("Error manejando al cliente: "+error);
        }
    }
}
