package table;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;
import java.sql.Statement;
import java.util.Scanner;
import com.mysql.cj.jdbc.exceptions.MysqlDataTruncation;

public class Course {

  private static final String DB_URL = "jdbc:mysql://localhost:3306/teaching_database?serverTimezone=GMT";
  private static final String USER = "root";
  private static final String PASS = "123456";
  
  public static void InsertTuple() {
    Connection conn = null;
    Statement stmt = null;
    @SuppressWarnings("resource")
    Scanner sc = new Scanner(System.in);
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      conn = DriverManager.getConnection(DB_URL,USER,PASS);
      stmt = conn.createStatement();
      
      System.out.print("course number: ");
      String cno = sc.nextLine();
      System.out.print("course name: ");
      String cname = sc.nextLine();
      System.out.print("prepera course number: ");
      String precno = sc.nextLine();
      System.out.print("course semester: ");
      String time = sc.nextLine();
      
      // �ù�ϵ���� precno���Կ���ȡ��ֵ
      if(cno.equals("")) {
        System.out.println("Insert Error: Course number can not be null!\n");
      } else if(cname.equals("")) {
        System.out.println("Insert Error: Course name can not be null!\n");
      } else if(time.equals("")) {
        System.out.println("Insert Error: Course time can not be null!\n");
      } else {
        stmt.executeLargeUpdate("insert into course "
                              + "values('" + cno + "', '" + cname +  "', '" + precno + "', '" + time + "');");
        
        System.out.println("����ɹ�!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      String str = e.getMessage();
      if(str.contains("Duplicate entry")) {
        System.out.println("Insert Error: Primary key 'course number' has existed in this table!\n");
      }
      if(str.contains("foreign key constraint")) {
        System.out.println("Insert Error: Foreign key 'prepare course number' don't exist in Course table!\n");
      }
    } catch (SQLException se) {
      se.printStackTrace();
    } catch (ClassNotFoundException e) {
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
  
  public static void DeleteTuple() {
    Connection conn = null;
    Statement stmt = null;
    @SuppressWarnings("resource")
    Scanner sc = new Scanner(System.in);
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      conn = DriverManager.getConnection(DB_URL,USER,PASS);
      stmt = conn.createStatement();
      
      System.out.print("course number: ");
      String cno = sc.nextLine();
      System.out.print("course time: ");
      String time = sc.nextLine();
      
      if(cno.equals("") || time.equals("")) {
        System.out.println("Delete Error: college number can not be null!\n");
      } else {
        stmt.executeLargeUpdate("delete from course "
                              + "where cno = '" + cno + "' and "
                              + "time = '" + time + "';");
        
        System.out.println("ɾ���ɹ�!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      System.out.println("Insert Error: the entered primary key has appeared in the foreign key of other tables.!\n");
    } catch (SQLException se) {
      se.printStackTrace();
    } catch (ClassNotFoundException e) {
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
