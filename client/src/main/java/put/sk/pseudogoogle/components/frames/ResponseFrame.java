package put.sk.pseudogoogle.components.frames;

import put.sk.pseudogoogle.data.Response;
import put.sk.pseudogoogle.logic.communication.Communicator;

import javax.swing.*;
import java.awt.event.*;

public class ResponseFrame extends JFrame {
  private final Communicator communicator;
  private final Runnable onCancelListener;
  private JPanel contentPane;
  private JList<String> urlList;

  public ResponseFrame(Communicator communicator, Runnable onCancelListener) {
    this.communicator = communicator;
    this.onCancelListener = onCancelListener;

    setContentPane(contentPane);
    setResizable(false);

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

  @Override
  public void setVisible(boolean b) {
    if (b) {
      setupUrlList();
    }
    super.setVisible(b);
  }

  private void setupUrlList() {
    DefaultListModel<String> listModel = new DefaultListModel<>();
    Response response = communicator.getResponse();

    if (response.getType() == Response.Type.NOT_FOUND) {
      listModel.addElement("No urls found");
    } else {
      for (String url : response.getUrls()) {
        listModel.addElement(url);
      }
    }
    urlList.setModel(listModel);
    urlList.revalidate();
    urlList.repaint();
    pack();
    setLocationRelativeTo(null);
  }

  private void onCancel() {
    SwingUtilities.invokeLater(onCancelListener);
  }
}
