package put.sk.pseudogoogle.logic.communication;

import put.sk.pseudogoogle.data.Response;
import put.sk.pseudogoogle.error.ConnectionException;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;

public class Communicator {
  private Response response;

  public void sendWord(Socket socket, String word) throws ConnectionException {
    byte[] encodedWord = encodeWord(word);
    try {
      OutputStream out = socket.getOutputStream();
      out.write(encodedWord);
    } catch (IOException ex) {
      throw new ConnectionException();
    }
  }

  public void receiveResponse(Socket socket) {
    response = null;
    try {
      InputStream in = socket.getInputStream();

      int type = in.read();
      Response response = new Response(type);
      if (response.getType() == Response.Type.NOT_FOUND) {
        this.response = response;
        return;
      }

      int length = readFixed32(in);

      for (int i = 0; i < length; ++i) {
        int urlLength = readFixed32(in);
        String url = readString(in, urlLength);
        response.addUrl(url);
      }
      this.response = response;
    } catch (IOException ex) {
      throw new ConnectionException();
    }
  }

  public Response getResponse() {
    return response;
  }

  private byte[] encodeWord(String word) {
    ByteBuffer buffer = ByteBuffer.allocate(4 + word.length());
    buffer.putInt(word.length());
    buffer.put(word.getBytes());
    return buffer.array();
  }

  private int readFixed32(InputStream in) throws IOException {
    byte[] buffer = new byte[4];
    int count = 0;
    while (count != 4) {
      count += in.read(buffer, count, 4 - count);
    }
    ByteBuffer byteBuffer = ByteBuffer.allocate(4);
    byteBuffer.put(buffer);
    return byteBuffer.getInt(0);
  }

  private String readString(InputStream in, int length) throws IOException {
    byte[] buffer = new byte[length];
    int count = 0;
    while (count != length) {
      count += in.read(buffer, count, length - count);
    }
    return new String(buffer);
  }
}
