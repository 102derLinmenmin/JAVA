package book;

public class TestBook{
	public static void main(String[] args){
		
		Book b1 = new Book();
		b1.setBook("��ҹ��", "��Ұ����", 150);
		b1.printBook();
		
		Book b2 = new Book("��ͽ��ͯ�� ","xx",160);
		b2.printBook();
	}
}

 class Book {
	
	String name;
	String author;
	int sale;
	
	Book(){
	}
	
	Book(String name, String author, int sale){
		this.name = name;
		this.author = author;
		this.sale = sale;
	}
	void setBook(String name, String author, int sale){
		this.name = name;
		this.author = author;
		this.sale = sale;
	}
	void printBook(){
		System.out.println("����:"+name+" "+"����:"+author+ " "+"��������"+sale);
	}
	

}
