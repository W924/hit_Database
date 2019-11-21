package lab2;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;


public class test {

  private static final String DB_URL =
      "jdbc:mysql://localhost:3306/teaching_database?serverTimezone=GMT";

  private static final String USER = "root";
  private static final String PASS = "123456";

  public static void main(String[] args) {
    Connection conn = null;
    Statement stmt = null;
    try {
      
      Class.forName("com.mysql.cj.jdbc.Driver");
      conn = DriverManager.getConnection(DB_URL,USER,PASS);
      stmt = conn.createStatement();
      
      String encoding = "utf8";
      File file = new File("E:\\course\\database\\lab3\\data\\ss.txt");
      if (file.isFile() && file.exists()) {
        InputStreamReader read = new InputStreamReader(
            new FileInputStream(file), encoding);
        BufferedReader bufferedReader = new BufferedReader(read);
        String lineTxt = null;
        while ((lineTxt = bufferedReader.readLine()) != null) {
          String[] words = lineTxt.split("\t");
          String s1 = words[0];
          String s2 = words[1];
          String s3 = words[2];
          stmt.executeLargeUpdate("insert into ss "
                                + "values('" + s1 + "', '" + s2 + "', '" + s3 +  "');");             
        }
        read.close();
        stmt.close();
        conn.close();

      }
    } catch (SQLException se) {
      se.printStackTrace();
    } catch (Exception e) {
      e.printStackTrace();
    } finally {
      try {
        if (stmt != null)
          stmt.close();
      } catch (SQLException se2) {
      }
      try {
        if (conn != null)
          conn.close();
      } catch (SQLException se) {
        se.printStackTrace();
      }
    }
  }
}
