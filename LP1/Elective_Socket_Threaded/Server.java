import java.io.*;
import java.net.*;
import java.util.Scanner;

class Server {
    public static void main(String[] args) {
        ServerSocket server = null;

        try {

            server = new ServerSocket(8000);
            server.setReuseAddress(true);

            while (true) {

                Socket client = server.accept();

                System.out.println("New client connected"
                        + client.getInetAddress()
                                .getHostAddress());

                ClientHandler clientSock = new ClientHandler(client);

                new Thread(clientSock).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (server != null) {
                try {
                    server.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private static class ClientHandler implements Runnable {
        private final Socket clientSocket;
        String id;

        public ClientHandler(Socket socket) {
            this.clientSocket = socket;
            this.id = socket.getInetAddress()
                    .getHostAddress();
        }

        public void run() {
            PrintWriter out = null;
            BufferedReader in = null;
            try {

                out = new PrintWriter(
                        clientSocket.getOutputStream(), true);

                in = new BufferedReader(
                        new InputStreamReader(
                                clientSocket.getInputStream()));

                String line;
                while ((line = in.readLine()) != null) {

                    // System.out.printf(id + " : %s\n", line);
                    // String rep;
                    // Scanner sc = new Scanner(System.in);
                    // rep = sc.nextLine();
                    out.println(line);
                }
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    if (out != null) {
                        out.close();
                    }
                    if (in != null) {
                        in.close();
                        clientSocket.close();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
