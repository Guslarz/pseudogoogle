package put.sk.pseudogoogle.components.frames;

import put.sk.pseudogoogle.data.Response;
import put.sk.pseudogoogle.error.ConnectionException;
import put.sk.pseudogoogle.logic.communication.Communicator;
import put.sk.pseudogoogle.logic.connection.Connector;

import javax.swing.*;
import java.awt.event.*;
import java.net.Socket;
import java.nio.charset.Charset;
import java.util.List;

public class CommunicationFrame extends JFrame {
  private final Connector connector;
  private final Communicator communicator;
  private final Runnable onResponseListener;
  private final Runnable onDisconnectListener;
  private JPanel contentPane;
  private JButton buttonSearch;
  private JButton buttonDisconnect;
  private JTextField textFieldWord;

  public CommunicationFrame(
      Connector connector,
      Communicator communicator,
      Runnable onResponseListener,
      Runnable onDisconnectListener) {
    this.connector = connector;
    this.communicator = communicator;
    this.onResponseListener = onResponseListener;
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

  @Override
  public void setVisible(boolean b) {
    textFieldWord.setText("");
    super.setVisible(b);
  }

  private void onSearch() {
    Socket socket = connector.getSocket();
    String word = textFieldWord.getText();
    buttonSearch.setEnabled(false);
    buttonDisconnect.setEnabled(false);
    SwingUtilities.invokeLater(
        () -> {
          try {
            communicator.sendWord(socket, word);
            communicator.receiveResponse(socket);
            onResponseListener.run();
          } catch (ConnectionException ex) {
            JOptionPane.showMessageDialog(
                null, "Disconnected.", "Connection error", JOptionPane.ERROR_MESSAGE);
            buttonDisconnect.doClick();
          } finally {
            buttonSearch.setEnabled(true);
            buttonDisconnect.setEnabled(true);
          }
        });
  }

  private void onDisconnect() {
    SwingUtilities.invokeLater(onDisconnectListener);
  }
}
