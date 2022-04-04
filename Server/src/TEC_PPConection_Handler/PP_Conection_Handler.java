package TEC_PPConection_Handler;

import java.io.*;
import java.net.*;


public class PP_Conection_Handler implements Runnable {
    protected Socket socketToHandle;
    public PP_Conection_Handler(Socket aSocketToHandle){
        socketToHandle=aSocketToHandle;
    }
    public void run(){
        InputStream input= null;
        BufferedReader brinp = null;
        DataOutputStream output= null;
        try{
            input = socketToHandle.getInputStream();
            brinp = new BufferedReader(new InputStreamReader(input));
            output = new DataOutputStream(socketToHandle.getOutputStream());
            /*
            PrintWriter streamWriter = new PrintWriter(socketToHandle.getOutputStream());
            BufferedReader streamReader = new BufferedReader((new InputStreamReader(socketToHandle.getInputStream())));

            String fileToRead = streamReader.readLine();
            BufferedReader fileReader = new BufferedReader(new FileReader("src/Variables/"+fileToRead+".txt"));

            String line = null;
            while ((line = fileReader.readLine()) != null){
                streamWriter.println(line);
                System.out.println(line);
            }

            fileReader.close();
            streamWriter.close();
            streamReader.close();*/
        }catch (Exception error){
            System.out.println("Error manejando al cliente: "+error);
            return;
        }
        String line;
        while (true){
            try{
                line = brinp.readLine();
                if ((line == null) && line.equalsIgnoreCase("QUIT")){
                        socketToHandle.close();
                    }else {
                    output.writeBytes(line + "\n\r");
                    output.flush();
                }
            }catch (IOException e){
                e.printStackTrace();
                return;
            }
        }
    }
}
