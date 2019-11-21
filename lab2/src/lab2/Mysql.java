package lab2;

import java.sql.*;
import java.util.Properties;

public class Mysql {
  
  private static final String DB_URL = "jdbc:mysql://localhost:3306/COMPANY?serverTimezone=GMT";

  private static final String USER = "root";
  private static final String PASS = "123456";
  
  public static void main(String[] args) {
    
    String PNO = args[0];
    String PNAME = args[1];
    String DNAME = args[2];
    String SALARY = args[3];
    String ENAME = args[4];
    String PNO1 = args[5];
    String PNO2 = args[6];
    String N = args[7];
    String HOURS = args[8];
    
    Connection conn = null;
    Statement stmt = null;
    try{
       
        Driver driver = new com.mysql.cj.jdbc.Driver();
        Properties props = new Properties();
        props.setProperty("user", USER);
        props.setProperty("password", PASS);
        conn = driver.connect(DB_URL, props);
        stmt = conn.createStatement();
        ResultSet rs = null;
        
        String sql1 = "select ESSN "
                    + "from WORKS_ON "
                    + "where PNO = '" + PNO + "'";
        rs = stmt.executeQuery(sql1);
        System.out.println("�μ�����Ŀ���Ϊ" + PNO + "����Ŀ��Ա����");
        System.out.println("------------------------------------------");
        System.out.println("ESSN");
        while(rs.next()){
          String tmp = rs.getString("ESSN");
          System.out.println(tmp);
        }
        System.out.println("------------------------------------------\n"); 
        
        String sql2 = "select ENAME "
                    + "from WORKS_ON, PROJECT, EMPLOYEE "
                    + "where WORKS_ON.PNO = PROJECT.PNO and "
                    + "WORKS_ON.ESSN = EMPLOYEE.ESSN and "
                    + "PROJECT.PNAME = '" + PNAME + "'";
        rs = stmt.executeQuery(sql2);
        System.out.println("�μ�����Ŀ��Ϊ" + PNAME + "��Ա������");
        System.out.println("------------------------------------------");
        System.out.println("ENAME");
        while(rs.next()){
          String tmp = rs.getString("ENAME");
          System.out.println(tmp);
        }
        System.out.println("------------------------------------------\n"); 
        
        String sql3 = "select ENAME, ADDRESS "
                    + "from EMPLOYEE, DEPARTMENT "
                    + "where DEPARTMENT.DNO = EMPLOYEE.DNO and "
                    + "DEPARTMENT.DNAME = '" + DNAME + "'";
        rs = stmt.executeQuery(sql3);
        System.out.println("��" + DNAME + "���������й�����Ա�����ֺ͵�ַ");
        System.out.println("------------------------------------------");
        System.out.println("ENAME" + "\t" + "ADDRESS");
        while(rs.next()){
          String ename = rs.getString("ENAME");
          String address = rs.getString("ADDRESS");
          System.out.println(ename + "\t" + address);
        }
        System.out.println("------------------------------------------\n"); 
        
        String sql4 = "select ENAME, ADDRESS "
                    + "from EMPLOYEE, DEPARTMENT "
                    + "where DEPARTMENT.DNO = EMPLOYEE.DNO and "
                    + "DEPARTMENT.DNAME = '" + DNAME + "' and "
                    + "EMPLOYEE.SALARY < '" + SALARY + "'";
        rs = stmt.executeQuery(sql4);
        System.out.println("��" + DNAME + "�����ҹ��ʵ���" + SALARY + "Ԫ��Ա�����ֺ͵�ַ");
        System.out.println("------------------------------------------");
        System.out.println("ENAME" + "\t" + "ADDRESS");
        while(rs.next()){
          String ename = rs.getString("ENAME");
          String address = rs.getString("ADDRESS");
          System.out.println(ename + "\t" + address);
        }
        System.out.println("------------------------------------------\n"); 
        
        String sql5 = "select ENAME "
                    + "from EMPLOYEE "
                    + "where ESSN not in( "
                    + "select ESSN "
                    + "from WORKS_ON "
                    + "where PNO = '" + PNO + "')";
        rs = stmt.executeQuery(sql5);
        System.out.println("û�вμ���Ŀ���Ϊ" + PNO + "����Ŀ��Ա������");
        System.out.println("------------------------------------------");
        System.out.println("ENAME");
        while(rs.next()){
          String ename = rs.getString("ENAME");
          System.out.println(ename);
        }
        System.out.println("------------------------------------------\n"); 
        
        String sql6 = "select ENAME, DNAME "
                    + "from EMPLOYEE, DEPARTMENT "
                    + "where EMPLOYEE.DNO = DEPARTMENT.DNO and "
                    + "EMPLOYEE.SUPERSSN = ("
                    + "select ESSN "
                    + "from EMPLOYEE "
                    + "where ENAME = '" + ENAME + "')";
        rs = stmt.executeQuery(sql6);
        System.out.println("��" + ENAME + "�쵼�Ĺ�����Ա�����������ڲ��ŵ�����");
        System.out.println("------------------------------------------");
        System.out.println("ENAME" + "\t" + "DNAME");
        while(rs.next()){
          String ename = rs.getString("ENAME");
          String dname = rs.getString("DNAME");
          System.out.println(ename + "\t" + dname);
        }
        System.out.println("------------------------------------------\n"); 
        
        String sql7 = "select ESSN "
                    + "from WORKS_ON "
                    + "where PNO = '" + PNO1 + "' and "
                    + "ESSN in( "
                    + "select ESSN "
                    + "from WORKS_ON "
                    + "where PNO = '" + PNO2 + "')";
        rs = stmt.executeQuery(sql7);
        System.out.println("���ٲμ�����Ŀ���Ϊ" + PNO1 + "��" + PNO2 + "����Ŀ��Ա����");
        System.out.println("------------------------------------------");
        System.out.println("ESSN");
        while(rs.next()){
          String essn = rs.getString("ESSN");
          System.out.println(essn);
        }
        System.out.println("------------------------------------------\n"); 
        
        String sql8 = "select DNAME "
                    + "from EMPLOYEE, DEPARTMENT "
                    + "where EMPLOYEE.DNO = DEPARTMENT.DNO "
                    + "group by DEPARTMENT.DNAME "
                    + "having avg(EMPLOYEE.SALARY) < " + SALARY;
        rs = stmt.executeQuery(sql8);
        System.out.println("Ա��ƽ�����ʵ���" + SALARY + "Ԫ�Ĳ�������");
        System.out.println("------------------------------------------");
        System.out.println("DNAME");
        while(rs.next()){
          String dname = rs.getString("DNAME");
          System.out.println(dname);
        }
        System.out.println("------------------------------------------\n"); 
        
        String sql9 = "select ENAME "
                    + "FROM EMPLOYEE "
                    + "where ESSN in( "
                    + "select ESSN "
                    + "from WORKS_ON "
                    + "group by ESSN "
                    + "having count(*) >= " + N + " and "
                    + "sum(HOURS) <= " + HOURS + ")";
        rs = stmt.executeQuery(sql9);
        System.out.println("���ٲ�����" + N + "����Ŀ�ҹ���ʱ�䲻����" + HOURS + "Сʱ��Ա������");
        System.out.println("------------------------------------------");
        System.out.println("ENAME");
        while(rs.next()){
          String ename = rs.getString("ENAME");
          System.out.println(ename);
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
