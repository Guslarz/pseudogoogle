package put.sk.pseudogoogle.data;

import java.util.ArrayList;
import java.util.Collection;

public class Response {

  private final Collection<String> words;
  private final Collection<String> urls;

  public Response() {
    this.words = new ArrayList<>();
    this.urls = new ArrayList<>();
  }

  public void addWord(String word) {
    words.add(word);
  }

  public void addUrl(String url) {
    urls.add(url);
  }

  public Collection<String> getWords() {
    return words;
  }

  public Collection<String> getUrls() {
    return urls;
  }
}
