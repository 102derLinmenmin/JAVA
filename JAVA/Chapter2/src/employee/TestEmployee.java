package employee;
public class TestEmployee {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Employee employeea = new Employee("xx", "2016-09-01", "a", 1000);
		Employee employeeb = new Employee("yy", "2017-09-01", "b", 2000);
		Employee employeec = new Employee("zz", "2018-09-01", "c", 3000);
		
		Employee a[] = { employeea,employeeb,employeec};
		System.out.println("���֣�"+a[0].getName()+"���ţ�"+a[0].getDepartment()+"��ְʱ�䣺"+a[0].getTime()+"���ʣ�"+a[0].getSalary());
		System.out.println("���֣�"+a[1].getName()+"���ţ�"+a[1].getDepartment()+"��ְʱ�䣺"+a[1].getTime()+"���ʣ�"+a[1].getSalary());
		System.out.println("���֣�"+a[2].getName()+"���ţ�"+a[2].getDepartment()+"��ְʱ�䣺"+a[2].getTime()+"���ʣ�"+a[2].getSalary());
		a[0].setDepartment("a");
		a[1].setSalary(2000);
		a[2].setTime("2018-09-01");
		System.out.println("���֣�"+a[0].getName()+"���ţ�"+a[0].getDepartment()+"��ְʱ�䣺"+a[0].getTime()+"���ʣ�"+a[0].getSalary());
		System.out.println("���֣�"+a[1].getName()+"���ţ�"+a[1].getDepartment()+"��ְʱ�䣺"+a[1].getTime()+"���ʣ�"+a[1].getSalary());
		System.out.println("���֣�"+a[2].getName()+"���ţ�"+a[2].getDepartment()+"��ְʱ�䣺"+a[2].getTime()+"���ʣ�"+a[2].getSalary());
	}

}
