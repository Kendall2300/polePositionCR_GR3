package TEC_PPServer;
import TEC_PPConection_Handler.PP_Conection_Handler;
import java.io.*;
import java.net.*;

/**
 * @author Kendall Martinez Carvajal kendallmc@estudiantec.cr
 */
public class PP_Server {
    protected int listenPort;

    /**
     * Este metodo se encarga de obtener el puerto al que se escuchara en el programa
     * @param aListenPort un integer que define el puerto a escuchar por el socket servidor
     */
    public PP_Server(int aListenPort){
        listenPort = aListenPort;
    }

    /**
     * Este metodo se encarga de aceptar las conexiones entrantes al servidor, tiene una capacidad
     * maxima de 4 usuarios a la vez
     */
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

    /**
     * Este metodo se encarga de iniciar los hilos para manejar las conexiones con el cliente
     * @param connectionToHandle este parametro corresponde al socket que se tiene que manipular
     */
    public void handleConnection(Socket connectionToHandle){
        new Thread(new PP_Conection_Handler(connectionToHandle)).start();
    }

    /**
     * El metodo principal que inicializa el programa completo
     * @param args
     */
    public static void main(String[] args){
        PP_Server server = new PP_Server(9300);
        server.acceptConections();
    }
}