package TEC_PPConection_Handler;

import java.io.IOException;

public class PP_Input_Handler {
    public int c;
    public String d;
    public void readData(java.io.DataInputStream input) throws IOException {
        c=input.readInt() -1;

        byte [] aux=null;
        aux=new byte[c];

        input.read(aux,0,1);
    }
    public void writeData(java.io.DataOutputStream out) throws IOException{
        out.writeInt(c+1);
        out.writeBytes(d);
        out.writeByte('\0');
    }
}
