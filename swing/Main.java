import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;

import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JToolBar;

/**
 * The main class that interacts with the server and manages the graphical user
 * interface: establishing a connection with the server, requestoring a request,
 * displaying the server's response, closing the connection, and adding text
 * lines to the screen.
 */
public class Main extends JFrame {

    private static final long serialVersionUID = 1L;
    static final String host = "localhost";
    static final int port = 3331;
    private BufferedReader input;
    private BufferedWriter output;
    private static Boolean status = false;
    private String str;
    private JMenu jMenu;
    private JPanel panel;
    private JToolBar jToolBar;
    private JMenuBar jMenuBar;
    private JTextArea jTextArea;
    private JTextField jTextField;
    private JScrollPane scrollPane;
    private JButton button1, button2, button3, button4;
    private JMenuItem jMenuItem1, jMenuItem2, jMenuItem3, jMenuItem4, jMenuItem5;

    public static void main(String[] argv) {

        try {
            new Main();
        } catch (IOException e) {

            e.printStackTrace();
            System.err.println("Client: Couldn't connect to " + host + ":" + port);
            System.exit(1);
        }

    }

    /**
     * This Class Create Our Remote Control Graphical Interfcae
     * 
     * @throws UnknownHostException
     * @throws IOException
     */

    public Main() throws UnknownHostException, IOException {
        ImageIcon jMenuResizedImage = new ImageIcon(
                new ImageIcon("./assets/more.png").getImage().getScaledInstance(20, 20, 1));
        ImageIcon connectImage = new ImageIcon(
                new ImageIcon("./assets/connect.png").getImage().getScaledInstance(20, 20, 1));
        ImageIcon closeImage = new ImageIcon(
                new ImageIcon("./assets/close.png").getImage().getScaledInstance(20, 20, 1));
        ImageIcon clearImage = new ImageIcon(
                new ImageIcon("./assets/clear.png").getImage().getScaledInstance(20, 20, 1));
        ImageIcon helpImage = new ImageIcon(new ImageIcon("./assets/help.png").getImage().getScaledInstance(20, 20, 1));

        panel = new JPanel();
        jTextArea = new JTextArea(30, 60);
        jTextArea.setText("Press Help Button !\n");
        scrollPane = new JScrollPane(jTextArea);

        add(panel, BorderLayout.SOUTH);
        add(scrollPane, BorderLayout.CENTER);

        jMenuBar = new JMenuBar();
        jMenu = new JMenu("");
        jToolBar = new JToolBar();
        jTextField = new JTextField(10);
        jTextField.setText("Media name Or Command ...");

        jMenuBar.add(jTextField);
        jMenuBar.add(jToolBar, BorderLayout.NORTH);
        jToolBar.setRollover(true);
        jToolBar.add(new MenuElement("List"));
        jToolBar.add(new MenuElement("Show"));
        jToolBar.add(new MenuElement("Play"));

        jMenuItem1 = new JMenuItem("Add Photo");
        jMenuItem2 = new JMenuItem("Add Video");
        jMenuItem3 = new JMenuItem("Add Film");
        jMenuItem4 = new JMenuItem("Add Group");
        jMenuItem5 = new JMenuItem("Add To Group");

        jMenu.setIcon(jMenuResizedImage);
        jMenu.add(jMenuItem1);
        jMenu.add(jMenuItem2);
        jMenu.add(jMenuItem3);
        jMenu.add(jMenuItem4);
        jMenu.add(jMenuItem5);

        jMenuItem1.setAction(new MenuElement("Add Photo"));
        jMenuItem2.setAction(new MenuElement("Add Video"));
        jMenuItem3.setAction(new MenuElement("Add Film"));
        jMenuItem4.setAction(new MenuElement("Add Group"));
        jMenuItem5.setAction(new MenuElement("Add To Group"));

        setJMenuBar(jMenuBar);
        jMenuBar.add(jMenu);

        button1 = new JButton("Connect");
        button1.setIcon(connectImage);
        button2 = new JButton("Help");
        button2.setIcon(helpImage);
        button3 = new JButton("Clear");
        button3.setIcon(clearImage);
        button4 = new JButton("Close");
        button4.setIcon(closeImage);

        panel.add(button1);
        panel.add(button2);
        panel.add(button3);
        panel.add(button4);

        button1.addActionListener(new Connect(this));
        button2.addActionListener(new Helper());
        button3.addActionListener(new Cleaner());
        button4.addActionListener(new CloseRemote());

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        pack();

        setVisible(true);

    }

    /**
     * This Class Create a Menu Element
     * associated with Action Listener
     * 
     * @param texte use for Element Name and Request Verb
     */

    class MenuElement extends AbstractAction {

        private static final long serialVersionUID = 1L;
        String req;

        MenuElement(String texte) {
            super(texte);
            this.req = texte.replaceAll("\\s", "").toUpperCase();
        }

        @Override
        public void actionPerformed(ActionEvent e) {

            str = jTextField.getText();
            if ((!str.isEmpty() && !str.equals("Media name Or Command ...") || req.contains("LIST"))) {
                try {
                    jTextArea.append(requestor(req + " " + str) + "\n");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            } else {
                jTextArea.append("Please enter Your media name\n");
            }
        }

    }

    /**
     * This Class establish and verify connection to server
     * 
     * @param main
     */
    class Connect implements ActionListener {

        private final Main main;
        Socket sock;

        Connect(Main main) {
            this.main = main;
        }

        public void actionPerformed(ActionEvent e) {
            try {
                sock = new java.net.Socket(Main.host, Main.port);
                this.main.jTextArea.append("Successfully connected to " + Main.host + ":" + Main.port + "\n");
                status = true;
            } catch (java.net.UnknownHostException ex) {
                this.main.jTextArea.append("Client: Couldn't Find Host " + Main.host + ":" + Main.port + "\n");

            } catch (java.io.IOException ex) {
                this.main.jTextArea.append("Client: Couldn't Reach Host " + Main.host + ":" + Main.port + "\n");

            }

            try {
                this.main.input = new BufferedReader(new InputStreamReader(sock.getInputStream()));
                this.main.output = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
            } catch (java.io.IOException ex) {
                this.main.jTextArea.append("Client: Couldn't open input or output streams\n");
            }

        }

    }

    /**
     * This class Is used to send request to server throught socket connection
     * 
     * @param request contain request String
     * @return If Error return Null otherwise only make request to server
     * @throws java.io.IOException
     */
    public String requestor(String request) throws java.io.IOException {
        // Envoyer la requete au serveur
        try {
            request += "\n";
            if (status == false) {
                jTextArea.append("Please Connect To Server first\n");
            } else {
                output.write(request, 0, request.length());
                output.flush();

            }
        } catch (java.io.IOException e) {
            jTextArea.append("Client: Couldn't requestor message: " + e + "\n");
            return null;
        }

        // Get Results
        try {
            return input.readLine().replaceAll(";", "\n");
        } catch (java.io.IOException e) {
            jTextArea.append("Client: Couldn't receive message: " + e + "\n");
            return null;
        }
    }

    /**
     * This Class Print Help Text
     * Into interfcae
     */
    class Helper implements ActionListener {
        private static final String file = "./help.txt";

        @Override
        public void actionPerformed(ActionEvent e) {
            jTextArea.setText("");
            try (// Creating an object of BufferedReader class
                    BufferedReader br = new BufferedReader(new FileReader(file))) {
                String st;
                while ((st = br.readLine()) != null)
                    jTextArea.append(st + "\n");
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }

    }

    /**
     * This Class allow Cleaning text in
     * JtextArea
     */
    class Cleaner implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            jTextArea.setText("");
        }

    }

}

/**
 * This Class act as Action Listener
 * that Provoke the end of program
 */
class CloseRemote implements ActionListener {

    public void actionPerformed(ActionEvent e) {

        System.exit(0);
    }

}
