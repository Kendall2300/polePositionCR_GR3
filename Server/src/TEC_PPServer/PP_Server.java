package TEC_PPServer;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class PP_Server {

    public static void main(String[] args) throws IOException{
        int puerto = 9300;
        try {
            ServerSocket server = new ServerSocket(puerto);
            Socket sock = server.accept();
            System.out.println("Cliente en puerto: "+puerto);
        }catch (IOException e){
            System.out.println("Problemas en conectar con el cliente");
            e.printStackTrace();
        }

        System.out.println("Cliente conectado");
    }
}
