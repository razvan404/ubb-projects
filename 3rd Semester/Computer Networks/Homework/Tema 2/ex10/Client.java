import java.net.*;
import java.io.*;

public class Client {
    public static void main(String[] args) throws Exception {
        if (args.length != 2) {
            System.err.println("Invalid syntax!");
            System.err.println(" Usage: java Client IP_ADDR PORT");
            return;
        }
        Socket c = new Socket(args[0], Integer.parseInt(args[1]));
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String s1, s2;
        System.out.print("First string: ");
        s1 = reader.readLine();
        System.out.print("Second string: ");
        s2 = reader.readLine();
        
        DataInputStream socketIn = new DataInputStream(c.getInputStream());
        DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());
        
        socketOut.writeShort(s1.length());
        socketOut.writeBytes(s1);
        socketOut.writeByte(0);
        socketOut.writeShort(s2.length());
        socketOut.writeBytes(s2);
        socketOut.writeByte(0);

        byte cMaxByte = socketIn.readByte();
        char cMax = (char)(cMaxByte & 0xFF);
        int frec = socketIn.readUnsignedShort();
        
        if (cMax == 0) {
            System.out.println("There are no characters in corresponding positions");
        }
        else {
            System.out.println("The character '" + cMax + "' appears in both the string in corresponding positions " + frec + " times");
        }

        reader.close();
        c.close();
    }
}
