package employee;
public class TestEmployee {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Employee employeea = new Employee("xx", "2016-09-01", "a", 1000);
		Employee employeeb = new Employee("yy", "2017-09-01", "b", 2000);
		Employee employeec = new Employee("zz", "2018-09-01", "c", 3000);
		
		Employee a[] = { employeea,employeeb,employeec};
		System.out.println("名字："+a[0].getName()+"部门："+a[0].getDepartment()+"入职时间："+a[0].getTime()+"工资："+a[0].getSalary());
		System.out.println("名字："+a[1].getName()+"部门："+a[1].getDepartment()+"入职时间："+a[1].getTime()+"工资："+a[1].getSalary());
		System.out.println("名字："+a[2].getName()+"部门："+a[2].getDepartment()+"入职时间："+a[2].getTime()+"工资："+a[2].getSalary());
		a[0].setDepartment("a");
		a[1].setSalary(2000);
		a[2].setTime("2018-09-01");
		System.out.println("名字："+a[0].getName()+"部门："+a[0].getDepartment()+"入职时间："+a[0].getTime()+"工资："+a[0].getSalary());
		System.out.println("名字："+a[1].getName()+"部门："+a[1].getDepartment()+"入职时间："+a[1].getTime()+"工资："+a[1].getSalary());
		System.out.println("名字："+a[2].getName()+"部门："+a[2].getDepartment()+"入职时间："+a[2].getTime()+"工资："+a[2].getSalary());
	}

}
