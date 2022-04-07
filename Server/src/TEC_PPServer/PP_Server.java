package TEC_PPServer;

import TEC_PPConection_Handler.PP_Conection_Handler;

import java.io.*;
import java.net.*;


public class PP_Server {
    protected int listenPort;

    public PP_Server(int aListenPort){
        listenPort = aListenPort;
    }

    public void acceptConections(){
        try{
            InetAddress addr = InetAddress.getByName("127.0.0.1");
            ServerSocket server = new ServerSocket(listenPort,4,addr);
            Socket incomingConnection = null;
            while(true){
                incomingConnection = server.accept();
                handleConnection(incomingConnection);
            }
        }catch (BindException error){
            System.out.println("Incapaz de hacer enlazar con el pruerto: "+listenPort);
        }catch (IOException error2){
            System.out.println("Incapaz de instanciar el Socket Servidor en el puerto: "+listenPort);
        }
    }
    public void handleConnection(Socket connectionToHandle){
        new Thread(new PP_Conection_Handler(connectionToHandle)).start();
    }
    public static void main(String[] args){
        PP_Server server = new PP_Server(9300);
        server.acceptConections();
    }
}