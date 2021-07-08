import java.awt.*;
import java.awt.event.*;
import javax.swing.*;




public class Hex extends JPanel{
	private int size;
	private boolean choice;
	private boolean turn;
	private Cell[][] hexCells;
	private final String EMPTY = ".";
	private final String PLAYER1 = "X";
	private final String PLAYER2 = "O";
	private JButton[] cells;
	private JFrame frame;

	private class Cell {
		private int coor_y;
		private int coor_x;
		private String state;

		public Cell() {
			coor_y = 0;
			coor_x = 0;
			state = EMPTY;
		}

		public void set_coordinates(int pos_y, int pos_x, String form) {
			if (pos_y > 0 && pos_y <= size && pos_x > 0 && pos_x <= size) {
				coor_y = pos_y;
				coor_x = pos_x;
				state = form;
			}
		}
	}

	public void init_board() {
		int i, j;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				Cell cell = new Cell();
				cell.set_coordinates(i, j, EMPTY);
				hexCells[i][j] = cell;
			}
		}
	}


	public Hex() {
		size = 6;
		choice = false;
		turn = false;
		
		hexCells = new Cell[size][size];
		init_board();
	}

	public Hex(int board_size, boolean user_choice) {
		size = board_size;
		choice = user_choice;
		turn = false;

		hexCells = new Cell[size][size];
		init_board();
		cells = new JButton[size*size];

		frame = new JFrame();
		frame.setSize(800, 800);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new GridLayout(size, size));
		frame.setResizable(false);
		frame.setTitle("Hex Game");
		frame.setVisible(true);

		Dimension button_size = new Dimension(50,50);
		JPanel j_board = new JPanel();
		j_board.setLayout(new GridLayout(size, size));
		int i;
		for (i = 0; i < size*size; i++) {
			cells[i] = new JButton(" ");
			cells[i].setPreferredSize(button_size);
			j_board.add(cells[i]);
			frame.getContentPane().add(cells[i]);
			MoveListener moveListener = new MoveListener();
			cells[i].addActionListener(moveListener);
		}
		

	}

	public void make_move(JButton b) {
		if (turn == false) {
			b.setText(PLAYER1);
			b.setEnabled(false);
		}
		else {
			b.setText(PLAYER2);
			b.setEnabled(false);
		}
	}

	public int convert_to_cell_id(int pos_y, int pos_x) {
		return pos_y*size + pos_x;
	}

	public int get_size() {
		return size;
	}

	public boolean get_choice() {
		return choice;
	}

	public class MoveListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			make_move((JButton)e.getSource());
			if (turn == true) {
				if (win_check_p1(false, 0, 0)) {
					JOptionPane.showMessageDialog(null, "Player1 Won");
					System.exit(0);
				}

				turn = false;
			}
			else {
				if (win_check_p2(false, 0, 0)) {
					JOptionPane.showMessageDialog(null, "Player2 Won");
					System.exit(0);
				}
				turn = true;
			}

		}
	}
	
	public boolean win_check_p1(boolean flag, int pos_y, int pos_x) {
		if (flag == false) { //Flag == 0 means it has to find a symbol at first row.
			int i;
			boolean test;
			for (i = 0; i < size; i++) { //At the beginning it looks for a user1symbol('X') in first row.
				if (cells[convert_to_cell_id(0, i)].getText() == PLAYER1) {
					test = win_check_p1(true, 0, i);
					if (test == true)
						return true;
				}
			}
		}
		else { //If it finds a user1_mark at first row, now it looks for southeast, south and southwest directions if the chain goes on.(recursively)
			boolean wtest = false;
			if (pos_y == size-1) 
				return true;
			if (pos_x > 0 && cells[convert_to_cell_id(pos_y+1, pos_x-1)].getText() == PLAYER1) {
				wtest = win_check_p1(true, pos_y+1, pos_x-1);
				if (wtest == true) 
					return true;
			}
			if (cells[convert_to_cell_id(pos_y+1, pos_x)].getText() == PLAYER1) {
				wtest = win_check_p1(true, pos_y+1, pos_x);
				if (wtest == true) 
					return true;
			}
			return false;
		}
		return false;
	}

	public boolean win_check_p2(boolean flag, int pos_y, int pos_x) {
		if (flag == false) {
			int i = 0;
			boolean test;
			for (i = 0; i < size; i++) {
				if (cells[convert_to_cell_id(i, 0)].getText() == PLAYER2) {
					test = win_check_p2(true, i, 0);
					if (test == true)
						return true;
				}
			}
		}
		else {
			boolean wtest = false;
			if (pos_x == size-1) 
				return true;
			if (pos_y > 0 && cells[convert_to_cell_id(pos_y-1, pos_x+1)].getText() == PLAYER2) {
				wtest = win_check_p2(true, pos_y-1, pos_x+1);
				if (wtest == true) 
					return true;
			}
			if (cells[convert_to_cell_id(pos_y, pos_x+1)].getText() == PLAYER2) {
				wtest = win_check_p2(true, pos_y, pos_x+1);
				if (wtest == true) 
					return true;
			}
			return false;
		}
		return false;
	}
	
	
}