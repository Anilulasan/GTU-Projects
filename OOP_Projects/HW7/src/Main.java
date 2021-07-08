import java.awt.event.*;
import javax.swing.*;
import java.awt.*;

public class Main extends JPanel{
	private JFrame frame;
	private Hex game;
	public Main() {
		setup();
	}

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Main gui = new Main();
					gui.frame.setVisible(true);
				}
				catch(Exception ex) {
					ex.printStackTrace();
				}
			}
			
			
		});
		
	}

	public void setup() {
		frame = new JFrame();
		frame.setSize(500, 220);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		frame.setResizable(false);
		frame.setTitle("MENU");


		JLabel lb = new JLabel();
		lb.setBounds(5,5,100,20);
		lb.setText("Board Size: ");
		
		frame.getContentPane().add(lb);

		JTextField text = new JTextField();
		text.setBounds(100,5,50,20);
		text.setEditable(true);
		frame.getContentPane().add(text);

		JLabel lb2 = new JLabel();
		lb2.setBounds(5,55,100,20);
		lb2.setText("Game Choice: ");
		frame.getContentPane().add(lb2);

		JCheckBox box1 = new JCheckBox("User vs Computer");
		box1.setBounds(105, 55, 160, 20);
		frame.getContentPane().add(box1);

		JCheckBox box2 = new JCheckBox("User vs User");
		box2.setBounds(265, 55, 130, 20);
		frame.getContentPane().add(box2);

		JButton save = new JButton("SAVE");
		frame.getContentPane().add(save);
		save.setBounds(320,100, 60, 30);
		JButton load = new JButton("LOAD");
		frame.getContentPane().add(load);
		load.setBounds(320,130, 60, 30);
		JButton reset = new JButton("RESET");
		frame.getContentPane().add(reset);
		reset.setBounds(320,160, 80, 30);
		


		JButton enter = new JButton("Enter");
		enter.setBounds(200,130, 80, 50);
		frame.getContentPane().add(enter);
		enter.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				try {
					int size;
					boolean choice = false;
					size = Integer.parseInt(text.getText());
					if (box1.isSelected()==true)
						choice = false;;
					if (box2.isSelected() == true)
						choice = true;

					if (size < 6 || size > 29)
						throw new NumberFormatException();
					else {
						game = new Hex(size, choice);
						
					}
				}
				catch(NumberFormatException ex) {
					String error = ex.getMessage();
					JOptionPane.showMessageDialog(null, "Invalid size. Size must be between 6-30");
				}
			}
		});
	}
	


}