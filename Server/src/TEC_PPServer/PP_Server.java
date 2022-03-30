package TEC_PPServer;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class PP_Server {

    public static void main(String[] args) {
        int puerto = 2300;
        try {
            ServerSocket serverSock = new ServerSocket(puerto);
            Socket sock = serverSock.accept();
        }catch (IOException e){
            System.out.println("Problemas en conectar con el cliente");
            e.printStackTrace();
        }

        System.out.println("cliente conectado");
    }
}
