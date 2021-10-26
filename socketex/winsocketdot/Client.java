import java.net.*;
import java.io.*;
import java.util.*;
import java.util.concurrent.Semaphore;

public class Client{
	public static void main(String [] args){
		int port = Integer.parseInt(args[0]);
		BufferedReader input;
		PrintWriter output;
		Socket socket;
		Console console = System.console();
		try{
			socket = new Socket("127.0.0.1", port);
			String feedback;
			input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			output = new PrintWriter(socket.getOutputStream(), true);
            output.println("Hello, !");
			feedback = "A";

			while(true){
				int a = input.read();
				System.out.print((char)a);
			}
		}
		catch(IOException i){
			System.out.println(i);
		}
		
	}
}