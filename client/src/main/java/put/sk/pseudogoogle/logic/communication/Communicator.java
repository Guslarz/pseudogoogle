package put.sk.pseudogoogle.logic.communication;

import put.sk.pseudogoogle.data.Response;
import put.sk.pseudogoogle.error.ConnectionException;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;

public class Communicator {
  public void sendWord(Socket socket, String word) throws ConnectionException {
    byte[] encodedWord = encodeWord(word);
    try {
      OutputStream out = socket.getOutputStream();
      out.write(encodedWord);
    } catch (IOException ex) {
      throw new ConnectionException();
    }
  }

  public Response receiveResponse(Socket socket) {
    try {
      InputStream in = socket.getInputStream();
      Response response = new Response();

      int wordsLength = readFixed32(in);
      for (int i = 0; i < wordsLength; ++i) {
        int wordLength = readFixed32(in);
        String word = readString(in, wordLength);
        response.addWord(word);
      }

      int urlsLength = readFixed32(in);
      for (int i = 0; i < urlsLength; ++i) {
        int urlLength = readFixed32(in);
        String url = readString(in, urlLength);
        response.addUrl(url);
      }

      return response;
    } catch (Exception ex) {
      throw new ConnectionException();
    }
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
