package put.sk.pseudogoogle.components.frames;

import put.sk.pseudogoogle.error.ConnectionException;
import put.sk.pseudogoogle.error.InvalidAddressException;
import put.sk.pseudogoogle.error.InvalidPortException;
import put.sk.pseudogoogle.logic.connection.Connector;

import javax.swing.*;
import java.awt.event.*;

public class ConnectionFrame extends JFrame {
  private final Connector connector;
  private final Runnable onConnectListener;
  private final Runnable onCancelListener;
  private JPanel contentPane;
  private JButton buttonConnect;
  private JTextField textFieldAddress;
  private JTextField textFieldPort;

  public ConnectionFrame(
      Connector connector, Runnable onConnectListener, Runnable onCancelListener) {
    this.connector = connector;
    this.onConnectListener = onConnectListener;
    this.onCancelListener = onCancelListener;

    setContentPane(contentPane);
    getRootPane().setDefaultButton(buttonConnect);
    setResizable(false);
    pack();
    setLocationRelativeTo(null);

    buttonConnect.addActionListener(e -> onConnect());

    setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    addWindowListener(
        new WindowAdapter() {
          public void windowClosing(WindowEvent e) {
            onCancel();
          }
        });

    contentPane.registerKeyboardAction(
        e -> onCancel(),
        KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0),
        JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);
  }

  private void onConnect() {
    buttonConnect.setEnabled(false);
    String address = textFieldAddress.getText();
    String port = textFieldPort.getText();
    SwingUtilities.invokeLater(
        () -> {
          try {
            connector.connect(address, port);
            onConnectListener.run();
          } catch (InvalidAddressException ex) {
            showError("Could not resolve specified address.");
          } catch (InvalidPortException ex) {
            showError("Port is not a number.");
          } catch (ConnectionException ex) {
            showError("Couldn't connect.");
          } finally {
            buttonConnect.setEnabled(true);
          }
        });
  }

  private void onCancel() {
    SwingUtilities.invokeLater(onCancelListener);
  }

  private void showError(String message) {
    JOptionPane.showMessageDialog(null, message, "Connection error", JOptionPane.ERROR_MESSAGE);
  }
}
