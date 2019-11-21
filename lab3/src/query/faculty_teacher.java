package query;

import java.sql.Connection;
import java.sql.Driver;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;
import java.util.Scanner;

public class faculty_teacher {

  private static final String DB_URL = "jdbc:mysql://localhost:3306/teaching_database?serverTimezone=GMT";
  private static final String USER = "root";
  private static final String PASS = "123456";
  
  public static void query() {
    Connection conn = null;
    Statement stmt = null;
    @SuppressWarnings("resource")
    Scanner sc = new Scanner(System.in);
    try{
      
      Driver driver = new com.mysql.cj.jdbc.Driver();
      Properties props = new Properties();
      props.setProperty("user", USER);
      props.setProperty("password", PASS);
      conn = driver.connect(DB_URL, props);
      stmt = conn.createStatement();
      ResultSet rs = null;
      
      System.out.println("faculty name: ");
      String fname = sc.nextLine();
      
      String sql1 = "select tname, tsex "
                  + "from teacher, faculty "
                  + "where faculty.fname = '" + fname + "' and "
                  + "faculty.fno = teacher.fno";
      rs = stmt.executeQuery(sql1);
      System.out.println("所属系名称为" + fname + "的教室姓名和性别");
      System.out.println("------------------------------------------");
      System.out.println("tname   tsex");
      while(rs.next()){
        String tname = rs.getString("tname");
        String tsex = rs.getString("tsex");
        System.out.println(tname + "\t" + tsex);
      }
      System.out.println("------------------------------------------\n"); 

      rs.close();
      stmt.close();
      conn.close();
  }catch(SQLException se){
      se.printStackTrace();
  }catch(Exception e){
      e.printStackTrace();
  }finally{
      try{
          if(stmt!=null) stmt.close();
      }catch(SQLException se2){
      }
      try{
          if(conn!=null) conn.close();
      }catch(SQLException se){
          se.printStackTrace();
      }
    }
  }
}
