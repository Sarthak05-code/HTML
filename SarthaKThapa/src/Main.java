import java.awt.Color;

import javax.swing.JFrame;
import javax.swing.JLabel;

public class Main  extends JFrame{
    Main(){
        JLabel label = new JLabel();
        label.setText("This is a start");
        this.setTitle("Library Management system");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(720, 680);
        this.setVisible(true);
        this.getContentPane().setBackground(new Color(123, 50 , 250));
        this.add(label);
    }

    public static void main(String[] args) {
        new Main();
    }
}
