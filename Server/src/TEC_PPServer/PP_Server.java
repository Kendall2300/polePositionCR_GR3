package TEC_PPServer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class PP_Server {

    public static void main(String[] args) throws IOException {
        int puerto = 9300;
        boolean run = true;
        while (run) {
            try {
                ServerSocket server = new ServerSocket(puerto);
                Socket cliente = server.accept();
                System.out.println("Cliente conectado en puerto: "+puerto);
                BufferedReader entrada = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
                PrintWriter salida = new PrintWriter(cliente.getOutputStream(),true);
                String datos_recibidos = entrada.readLine();
                System.out.println("Se recibio: "+datos_recibidos);
            } catch (IOException e) {
                System.out.println("Problemas en conectar con el cliente");
                e.printStackTrace();
            }
        }
    }
}
