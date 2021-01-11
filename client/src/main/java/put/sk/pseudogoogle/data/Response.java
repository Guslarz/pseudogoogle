package put.sk.pseudogoogle.data;

import java.util.ArrayList;
import java.util.Collection;

public class Response {

  public enum Type {
    OK,
    NOT_FOUND
  }

  private final Type type;
  private final Collection<String> urls;

  public Response(int type) {
    this.type = Type.values()[type];
    this.urls = new ArrayList<>();
  }

  public void addUrl(String url) {
    urls.add(url);
  }

  public Type getType() {
    return type;
  }

  public Collection<String> getUrls() {
    return urls;
  }
}
