package put.sk.pseudogoogle.logic.connection;

import put.sk.pseudogoogle.error.ConnectionException;
import put.sk.pseudogoogle.error.InvalidAddressException;
import put.sk.pseudogoogle.error.InvalidPortException;

import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class Connector {
  private Socket socket = null;
  private InetAddress lastAddress = null;
  private Integer lastPort = null;

  public void connect(String address, String port)
      throws InvalidAddressException, InvalidPortException, ConnectionException {
    lastAddress = null;
    lastPort = null;
    disconnect();
    InetAddress inetAddress = parseInetAddress(address);
    int portNumber = parsePortNumber(port);
    try {
      socket = new Socket(inetAddress, portNumber);
      lastAddress = inetAddress;
      lastPort = portNumber;
      socket.setSoTimeout(1000);
    } catch (Exception ex) {
      throw new ConnectionException();
    }
  }

  public void disconnect() {
    if (socket != null) {
      try {
        socket.close();
      } catch (IOException exception) {
        throw new ConnectionException();
      }
      socket = null;
    }
  }

  public boolean reconnect() {
    if (lastAddress == null || lastPort == null) {
      return false;
    }

    try {
      if (socket != null) {
        socket.close();
      }
      socket = new Socket(lastAddress, lastPort);
      return true;
    } catch (Exception ex) {
      return false;
    }
  }

  public Socket getSocket() {
    return socket;
  }

  private InetAddress parseInetAddress(String address) throws InvalidAddressException {
    try {
      return InetAddress.getAllByName(address)[0];
    } catch (UnknownHostException ex) {
      throw new InvalidAddressException();
    }
  }

  private int parsePortNumber(String port) throws InvalidPortException {
    try {
      return Integer.parseInt(port);
    } catch (NumberFormatException ex) {
      throw new InvalidPortException();
    }
  }
}
