package put.sk.pseudogoogle.components.frames;

import put.sk.pseudogoogle.logic.connection.Connector;

import javax.swing.*;
import java.awt.event.*;

public class CommunicationFrame extends JFrame {
  private final Connector connector;
  private final Runnable onDisconnectListener;
  private JPanel contentPane;
  private JButton buttonSearch;
  private JButton buttonDisconnect;
  private JTextField textFieldWord;

  public CommunicationFrame(Connector connector, Runnable onDisconnectListener) {
    this.connector = connector;
    this.onDisconnectListener = onDisconnectListener;

    setContentPane(contentPane);
    getRootPane().setDefaultButton(buttonSearch);
    setResizable(false);
    pack();
    setLocationRelativeTo(null);

    buttonSearch.addActionListener(e -> onSearch());

    buttonDisconnect.addActionListener(e -> onDisconnect());

    setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    addWindowListener(
        new WindowAdapter() {
          public void windowClosing(WindowEvent e) {
            onDisconnect();
          }
        });

    contentPane.registerKeyboardAction(
        e -> onDisconnect(),
        KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0),
        JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);
  }

  private void onSearch() {
    String word = textFieldWord.getText();
    buttonSearch.setEnabled(false);
    buttonDisconnect.setEnabled(false);
    SwingUtilities.invokeLater(() -> {});
  }

  private void onDisconnect() {
    SwingUtilities.invokeLater(onDisconnectListener);
  }
}
