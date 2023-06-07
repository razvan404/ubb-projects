package utils;

import java.io.*;
import java.util.Base64;

public class BlobSerializer {
    public static String toString(Serializable obj) {
        try {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(baos);
            oos.writeObject(obj);
            oos.close();
            return Base64.getEncoder().encodeToString(baos.toByteArray());
        } catch (IOException ex) {
            System.err.println(ex.getMessage());
        }
        return null;
    }

    public static Object fromString(String str) {
        try {
            byte[] data = Base64.getDecoder().decode(str);
            ObjectInputStream ois = new ObjectInputStream(new ByteArrayInputStream(data));
            Object o = ois.readObject();
            ois.close();
            return o;
        } catch (IOException | ClassNotFoundException ex) {
            System.err.println(ex.getMessage());
        }
        return null;
    }
}
