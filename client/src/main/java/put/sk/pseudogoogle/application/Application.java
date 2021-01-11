package put.sk.pseudogoogle.application;

import put.sk.pseudogoogle.components.frames.CommunicationFrame;
import put.sk.pseudogoogle.components.frames.ConnectionFrame;
import put.sk.pseudogoogle.components.frames.ResponseFrame;
import put.sk.pseudogoogle.logic.communication.Communicator;
import put.sk.pseudogoogle.logic.connection.Connector;

import javax.swing.*;

public class Application {
  private final Connector connector;
  private final Communicator communicator;
  private final ConnectionFrame connectionFrame;
  private final CommunicationFrame communicationFrame;
  private final ResponseFrame responseFrame;

  Application() {
    this.connector = new Connector();
    this.communicator = new Communicator();
    this.connectionFrame =
        new ConnectionFrame(connector, this::connectedCallback, this::closeApplication);
    this.communicationFrame =
        new CommunicationFrame(
            connector, communicator, this::responseCallback, this::disconnectedCallback);
    this.responseFrame = new ResponseFrame(communicator, this::responseFrameCancelCallback);
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
    communicationFrame.dispose();
    responseFrame.dispose();
  }

  private void responseCallback() {
    connector.disconnect();
    communicationFrame.setVisible(false);
    responseFrame.setVisible(true);
  }

  private void disconnectedCallback() {
    connector.disconnect();
    communicationFrame.setVisible(false);
    connectionFrame.setVisible(true);
  }

  private void responseFrameCancelCallback() {
    responseFrame.setVisible(false);
    if (connector.reconnect()) {
      communicationFrame.setVisible(true);
    } else {
      connectionFrame.setVisible(true);
    }
  }
}
