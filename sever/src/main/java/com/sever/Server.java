package com.sever;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {
    public static void main(String[] args) throws IOException {
        try(ServerSocket serverSocket = new ServerSocket(5000)){
            while (true) {
                Socket sever = serverSocket.accept();
                InputStream inputStream = sever.getInputStream();
                Scanner scanner = new Scanner(inputStream);
                String response = scanner.nextLine();
                System.out.println(response);

                OutputStream outputStream = sever.getOutputStream();
                PrintWriter printWriter = new PrintWriter(outputStream, true);
                printWriter.println("Response received");
            }
        }

        

    }
}
