package put.sk.pseudogoogle.logic.communication;

import put.sk.pseudogoogle.data.Response;

import java.util.Collection;

public class Result {

  private String queryString;
  private Response response;

  public String getQueryString() {
    return queryString;
  }

  public Response getResponse() {
    return response;
  }

  public void setQueryString(String queryString) {
    this.queryString = queryString;
  }

  public void setResponse(Response response) {
    this.response = response;
  }
}
