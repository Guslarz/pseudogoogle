package put.sk.pseudogoogle.application;

import put.sk.pseudogoogle.components.frames.CommunicationFrame;
import put.sk.pseudogoogle.components.frames.ConnectionFrame;
import put.sk.pseudogoogle.logic.connection.Connector;

import javax.swing.*;

public class Application {
  private final Connector connector;
  private final ConnectionFrame connectionFrame;
  private final CommunicationFrame communicationFrame;

  Application() {
    this.connector = new Connector();
    this.connectionFrame =
        new ConnectionFrame(connector, this::connectedCallback, this::closeApplication);
    this.communicationFrame = new CommunicationFrame(connector, this::disconnectedCallback);
  }

  public void run() {
    this.connectionFrame.setVisible(true);
  }

  public static void main(String[] args) {
    SwingUtilities.invokeLater(
        () -> {
          Application application = new Application();
          application.run();
        });
  }

  private void connectedCallback() {
    connectionFrame.setVisible(false);
    communicationFrame.setVisible(true);
  }

  private void closeApplication() {
    connector.disconnect();
    connectionFrame.dispose();
  }

  private void disconnectedCallback() {
    connector.disconnect();
    communicationFrame.setVisible(false);
    connectionFrame.setVisible(true);
  }
}
